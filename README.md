### argparse-generic

Auto-generate argument parsers from data types (struct or class).

Inspired by http://www.haskellforall.com/2016/02/auto-generate-command-line-interface.html

Warning: proof of concept; I do not recommend using it for anything serious.


## Building the Example

    make

or using Nix for dependencies

    nix-shell --run 'make'


## Using the Example

    $ ./build/Release/example
    Error: the option '--host' is required but missing
    
    $ ./build/Release/example --help
    Make Query:
      --help                Help on usage
      --host arg            host
      --port arg            port
    
    $ ./build/Release/example --host localhost --port 5000
    (localhost 5000)


## In Your Code

Provide a model for the Fusion Sequence concept. The easiest way is to adapt your type.

References:
- http://www.boost.org/doc/libs/master/libs/fusion/doc/html/fusion/sequence.html
- http://www.boost.org/doc/libs/master/libs/fusion/doc/html/fusion/adapted.html

Note: Fusion lets you automatically pull in `deriving Show, Eq, Hashable` equivalents. See the example for Show.


## License

Copyright © 2016 Daniel J. Hofmann

Distributed under the MIT License (MIT).
