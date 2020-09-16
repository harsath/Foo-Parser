#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include "./Foo_parser.hpp"

std::vector<std::string> helper_key_value_split(const char*);

std::vector<Foo::Pair> Foo::FooParser::get_key_value_pair() const noexcept {
	return _key_value_map;
}

std::string Foo::FooParser::get_identifier() const noexcept {
	return _identifier;
}

std::unordered_map<std::string, std::vector<Foo::Pair>> Foo::FooParser::get_result() noexcept {
	_fillin_datastructure[_identifier] = _key_value_map;
	return _fillin_datastructure;
}

void Foo::FooParser::foo_parse() noexcept {
	std::ifstream file_handler(_file_name);
	if(file_handler.is_open()){
		std::string line;
		bool first_line = true;
		while(std::getline(file_handler, line)){
			char* original_line = strdup(line.c_str());
			char* token; char* state;
			if(first_line){
				first_line = false;
				token = strtok_r(original_line, " ", &state);
				if(std::string(token) == "Foo"){
					char* tmp_identifier = strtok_r(NULL, " ", &state);
					_identifier = tmp_identifier;

					char* curly;
					if(!((curly = strtok_r(NULL, " ", &state)) && std::string(curly) == "{")){
						is_failed = true;		
					}
				}
			}else{
				// Tokenizing the key -> value pair
				std::vector<std::string> tokeize_line = helper_key_value_split(line.c_str());
				if(tokeize_line.size() == (unsigned) 2){ // tokenized pair
					struct Foo::Pair tmp_pair = {tokeize_line[0], tokeize_line[1]};
					_key_value_map.push_back(tmp_pair);	
				}else if(tokeize_line.size() == (unsigned) 1){ // EOL, "}"
					break;
				}else{
					is_failed = true;
				}
			}
			
		}
	}else{
		std::cout << "Cannot open the file" << std::endl;
		exit(EXIT_FAILURE);
	}
}


std::vector<std::string> helper_key_value_split(const char* line_original){
	auto trimmed_line_fn = [](const char* line) -> std::string {
				std::string original{line};
				original.erase(std::remove_if(std::begin(original), std::end(original), isspace), std::end(original));
				return original;
			    };
	std::string trimmed_line = trimmed_line_fn(line_original);

	char* line = strdup(trimmed_line.c_str());
	char* token;
	char* state;
	std::vector<std::string> returner;
	for(token = strtok_r(line, "->", &state); token != NULL; token = strtok_r(NULL, "->", &state)){
		returner.push_back(token);	
	}
	return returner;
}
