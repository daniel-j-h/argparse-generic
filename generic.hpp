#ifndef POG_GENERIC_HPP
#define POG_GENERIC_HPP

#include <cstddef>

#include <iostream>
#include <type_traits>

#include <boost/mpl/range_c.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/optional/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/program_options.hpp>


namespace Generic {
  namespace Meta = boost::mpl;
  namespace Fusion = boost::fusion;
  namespace Options = boost::program_options;
  template <typename T>
  using Optional = boost::optional<T>;


  // Implementation detail: recursively walk member attributes and register with Options.
  namespace Detail {

    template <typename Description, typename Record>
    struct AddAttributes final {

      template <typename Index>
      void operator()(Index index) const {
        const auto attrName = Fusion::extension::struct_member_name<Record, index>::call();
        using AttrType = typename Fusion::result_of::value_at<Record, Index>::type;
        auto& attr = Fusion::at_c<index>(record);

        description.add_options()(attrName, Options::value<AttrType>(&attr)->required(), attrName);
      }

      Description& description;
      Record& record;
    };

    template <typename Description, typename Record>
    void addAttributes(Description& description, Record& record) {
      using Indices = Meta::range_c<std::size_t, 0, Fusion::result_of::size<Record>::value>;
      Fusion::for_each(Indices{}, AddAttributes<Description, Record>{description, record});
    }
  }


  // Provides simple argument parsers for all types Record, for which member attributes are required.
  // Precondition: Record is a type that Fusion can handle, or is at least Fusion-adapted.
  // Postcondition: empty Optional when help was requested, valid Optional<Record> otherwise.
  // Throws: Options::error (derived from std::logic_error) when error populating Record is encountered.
  template <typename Record>
  Optional<Record> get(int argc, char** argv, const char* heading) {
    using Description = Options::options_description;

    Description description{heading};
    description.add_options()("help", "Help on usage");

    Record record;

    Detail::addAttributes(description, record);

    Options::variables_map map;
    Options::store(Options::command_line_parser{argc, argv}.options(description).run(), map);

    if (map.count("help")) {
      std::cerr << description << std::endl;
      return {};
    }

    Options::notify(map);

    return record;
  }
}

#endif
