#include "./Foo_parser.cpp"
#include "./Foo_parser.hpp"

int main(int argc, const char *argv[]){
	Foo::FooParser parser("./parse_file.foo");
	parser.foo_parse();
	std::unordered_map<std::string, std::vector<Foo::Pair>> parsed_result = parser.get_result();

	std::cout << "Identifier: " << parser.get_identifier() << "\n";
	for(const Foo::Pair& pair : parsed_result[parser.get_identifier()]){
		std::cout << "\t" << pair.key << " : " << pair.value << "\n";
	}
	return 0;
}
