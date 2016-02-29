CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2 FATAL_ERROR)

PROJECT(argparse-generic VERSION 0.0.1 LANGUAGES CXX)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -Wold-style-cast -Wuninitialized -Wunreachable-code -Wstrict-overflow=3 -D_FORTIFY_SOURCE=2 -ffunction-sections -fdata-sections")
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-O1 -Wl,--hash-style=gnu -Wl,--sort-common -Wl,--gc-sections")

  IF(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmax-errors=1")
    IF (${CMAKE_BUILD_TYPE} MATCHES "Debug")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -ggdb3 -fno-omit-frame-pointer")
    ENDIF()
  ELSEIF(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ferror-limit=1")
    IF (${CMAKE_BUILD_TYPE} MATCHES "Debug")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
    ENDIF()
  ENDIF()
ELSE()
  MESSAGE(FATAL_ERROR "Unsupported system. Feel free to add flags for your system to CMakeLists.txt")
ENDIF()

FIND_PACKAGE(Boost 1.59.0 REQUIRED program_options system)
ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK -DBOOST_SPIRIT_USE_PHOENIX_V3 -DBOOST_RESULT_OF_USE_DECLTYPE)


ADD_EXECUTABLE(example example.cc)
TARGET_LINK_LIBRARIES(example ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
TARGET_INCLUDE_DIRECTORIES(example SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
