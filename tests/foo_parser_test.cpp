// Foo-Parser: primitive structure parser written in C++
// Copyright © 2020 Harsath
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "./test_helper.hpp"
#include "Foo_parser.hpp"
#include <unordered_map>

class FooParser_test{
	private:
		Foo::FooParser test_parser{"./parse_file.foo"};
	public:
		void parser_codeblock_test(){
			test_parser.foo_parse();
			std::unordered_map<std::string, std::vector<Foo::Pair>> map_results = test_parser.get_result();
			ASSERT_EQ(test_parser._identifier.at(0), "identifier_one", "parser: _identifier parsing check");
			ASSERT_EQ(test_parser._identifier.at(1), "identifier_two", "_identifier initilization check");

			ASSERT_EQ(map_results["identifier_one"].at(0).key, "key_one", "unordered_map 1st Foo structure's 1st key");
			ASSERT_EQ(map_results["identifier_one"].at(0).value, "value_one", "unordered_map 1st Foo structure's 1nd key");

			ASSERT_EQ(map_results[test_parser._identifier.at(0)].at(1).key, "key_two", "unordered_map 1st Foo structure's 2st key");
			ASSERT_EQ(map_results[test_parser._identifier.at(0)].at(1).value, "value_two", "unordered_map 1st Foo structure's 2nd key");

			ASSERT_EQ(map_results[test_parser._identifier.at(1)].at(0).key, "sec_key_one", "unordered_map 2st Foo structure's 1st key");
			ASSERT_EQ(map_results[test_parser._identifier.at(1)].at(0).value, "sec_value_one", "unordered_map 2st Foo structure's 1nd key");

			ASSERT_EQ(map_results[test_parser._identifier.at(1)].at(1).key, "sec_key_two", "unordered_map 2st Foo structure's 2st key");
			ASSERT_EQ(map_results[test_parser._identifier.at(1)].at(1).value, "sec_value_two", "unordered_map 2st Foo structure's 2nd key");

			std::vector<std::string> identifier = test_parser.get_identifier();
			ASSERT_EQ(identifier.at(0), "identifier_one", "get_identifier() check 1");
			ASSERT_EQ(identifier.at(1), "identifier_two", "get_identifier() check 2");

			std::vector<Foo::Pair> identifier_pair = test_parser.get_key_value_pair_from_identifier(identifier.at(0));
			ASSERT_EQ(identifier_pair.at(0).key, "key_one", "parser.get_key_value_pair_from_identifier() index 0 first Foo::Pair key check");
			ASSERT_EQ(identifier_pair.at(0).value, "value_one", "parser.get_key_value_pair_from_identifier() index 0 first Foo::Pair value check");
			ASSERT_EQ(identifier_pair.at(1).key, "key_two", "parser.get_key_value_pair_from_identifier() index 0 2nd Foo::Pair key check");
			ASSERT_EQ(identifier_pair.at(1).value, "value_two", "parser.get_key_value_pair_from_identifier() index 0 2nd Foo::Pair value check");

			std::vector<Foo::Pair> identifier_pair_two = test_parser.get_key_value_pair_from_identifier(identifier.at(1));
			ASSERT_EQ(identifier_pair_two.at(0).key, "sec_key_one", "parser.get_key_value_pair_from_identifier() index 1 first Foo::Pair key check");
			ASSERT_EQ(identifier_pair_two.at(0).value, "sec_value_one", "parser.get_key_value_pair_from_identifier() index 1 first Foo::Pair value check");

			std::vector<Foo::Pair> key_value_pair_index = test_parser.get_key_value_pair_from_index(0);
			ASSERT_EQ(identifier_pair.at(0).key, "key_one", "parser.get_key_value_pair_from_index() index 0 first Foo::Pair key check");
			ASSERT_EQ(identifier_pair.at(0).value, "value_one", "parser.get_key_value_pair_from_index() index 0 first Foo::Pair value check");

			std::vector<Foo::Pair> key_value_pair_index_two = test_parser.get_key_value_pair_from_index(1);
			ASSERT_EQ(identifier_pair.at(1).key, "key_two", "parser.get_key_value_pair_from_index() index 1 2nd Foo::Pair key check");
			ASSERT_EQ(identifier_pair.at(1).value, "value_two", "parser.get_key_value_pair_from_index() index 1 2nd Foo::Pair value check");
			

		}
};

int main(int argc, const char *argv[]){
	FooParser_test test;
	test.parser_codeblock_test();

	print_final_stat();
	return 0;
}
