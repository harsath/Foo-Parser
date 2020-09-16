#include "./test_helper.cpp"
#include "../Foo_parser.cpp"

class FooParser_test{
	private:
		Foo::FooParser test_parser{"./parse_file.foo"};
	public:
		void parser_codeblock_test(){
			test_parser.foo_parse();
			ASSERT_EQ(test_parser._identifier, "identifier_one", "parser: _identifier parsing check");
			const char* test_line = "	key_one -> value_one";
			std::vector<std::string> tokenized_pair = helper_key_value_split(test_line);
			ASSERT_EQ(tokenized_pair[0], "key_one", "helper_key_value_split: key parsed in vector check");
			ASSERT_EQ(tokenized_pair[1], "value_one", "helper_key_value_split: value parsed in vector check");
			ASSERT_EQ(tokenized_pair.size(), (unsigned) 2, "helper_key_value_split: vector size() check");

			const char* test_line_2 = "}";
			std::vector<std::string> tokenized_pair_2 = helper_key_value_split(test_line_2);
			ASSERT_EQ(tokenized_pair_2.size(), (unsigned) 1, "helper_key_value_split: parser check for } EOL");
			
			std::unordered_map<std::string, std::vector<Foo::Pair>> parsed_result = test_parser.get_result();
			ASSERT_EQ(parsed_result[test_parser.get_identifier()].at(0).key, "key_one", "Parser hashmap fillin check");
			ASSERT_EQ(parsed_result[test_parser.get_identifier()].at(0).value, "value_one", "Parser hashmap fillin check");
		}
};

int main(int argc, const char *argv[]){
	FooParser_test test;
	test.parser_codeblock_test();

	print_final_stat();
	return 0;
}
