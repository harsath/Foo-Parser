include_directories(../include)
add_library(foo_parser STATIC ./Foo_parser.cpp)
target_compile_options(foo_parser PRIVATE -g)
