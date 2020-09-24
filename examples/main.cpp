#include "Foo_parser.hpp"
#include <iostream>

int main(int argc, const char *argv[]){
	Foo::FooParser parser("parse_file.foo");
	parser.foo_parse();

	std::unordered_map<std::string, std::vector<Foo::Pair>> parsed_result = parser.get_result(); // File is parsed

	// Printing out stuff
	for(const std::string& identifier : parser.get_identifier()){ // getting all the IDENTIFIERs
		std::cout << "Identifier: " << identifier << "\n";
		for(const Foo::Pair& pair : parsed_result[identifier]){
			std::cout << "Key: " << pair.key << "\n" << "Value: " << pair.value << "\n";
		}
		std::cout << "\n\n";
	}
	return 0;
}
