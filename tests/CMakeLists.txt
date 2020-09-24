include_directories(../foo_parser/include)
add_executable(parser_test foo_parser_test.cpp)
target_link_libraries(parser_test foo_parser)
