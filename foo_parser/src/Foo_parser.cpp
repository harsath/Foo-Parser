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
// or the use or other dealings in the software.

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include "Foo_parser.hpp"

std::vector<Foo::Pair> Foo::FooParser::get_key_value_pair_from_index(std::size_t index) const noexcept {
	std::vector<Foo::Pair> returner;
	if(index < _index_key_value_pair.size()){
		returner = _index_key_value_pair.at(index);
	}else{
		std::cerr << "Invalid Index" << std::endl;
		exit(EXIT_FAILURE);
	}
	return returner;
}

std::vector<Foo::Pair> Foo::FooParser::get_key_value_pair_from_identifier(const std::string& identifier) const noexcept {
	std::vector<Foo::Pair> returner;
	if(_fillin_datastructure.count(identifier)){
		returner = _fillin_datastructure.at(identifier);
	}else{
		std::cerr << "Invalid Identifier" << std::endl;
		exit(EXIT_FAILURE);
	}
	return returner;
}

std::vector<std::string> Foo::FooParser::get_identifier() const noexcept {
	return _identifier;
}

std::unordered_map<std::string, std::vector<Foo::Pair>> Foo::FooParser::get_result() const noexcept {
	return _fillin_datastructure;
}

std::vector<std::string> Foo::helper_tokenize_line(std::string token_line){
	std::vector<std::string> tokenized_lines;
	std::istringstream input_ss(token_line);
	for(std::string s; input_ss >> s;){ tokenized_lines.emplace_back(std::move(s)); }
	return tokenized_lines;
}

void Foo::FooParser::foo_parse() noexcept {
	std::vector<std::string> lines;
	std::string tmp_line;
	std::ifstream foo_file(_file_name);
	// tokenizing the lines
	if(foo_file.is_open()){
		while(std::getline(foo_file, tmp_line)){
			lines.emplace_back(std::move(tmp_line));
		}
	}else{
		std::cerr << "Cannot open the file" << std::endl;
		exit(EXIT_FAILURE);
	}
	// parsing the Foo structure
	struct statement_state{ bool first_line = true; bool in_scope = false; std::size_t current_processing_line = 0; } line_state;
	std::string tmp_identifier;
	for(std::string& token_line : lines){
		line_state.current_processing_line++;
		if(line_state.first_line){
			line_state.first_line = false;
			std::vector<std::string> foo_line_token = helper_tokenize_line(std::move(token_line)); // { "Foo", "IDENTIFIER" }
			tmp_identifier = foo_line_token.at(1);
			_identifier.emplace_back(std::move(foo_line_token.at(1)));
		}else{
			if(token_line == "{"){
				line_state.in_scope = true;
			}else if(line_state.in_scope){
				std::vector<std::string> key_value_splitter = helper_tokenize_line(token_line);
				if(key_value_splitter.size() == 3){
					if(key_value_splitter.at(1) == "->"){
						Foo::Pair tmp_pair = { std::move(key_value_splitter.at(0)), std::move(key_value_splitter.at(2)) };
						_fillin_datastructure[tmp_identifier].push_back(tmp_pair); 
					}else{
						std::cerr << "Key value pair must be split by \"->\" notation" << std::endl; 
						exit(EXIT_FAILURE);
					}
				}else if(token_line == "}"){
					line_state.in_scope = false;
					line_state.first_line = true;
				}
				else{
					std::cerr << "Key -> Value split parsing error. Please check your input" << std::endl;
					exit(EXIT_FAILURE);
				}
				
			}
			
		}	
	}

	this->_populate_key_value_pair_map();
}

void Foo::FooParser::_populate_key_value_pair_map(void) noexcept {
	for(std::size_t index = 0; index < _fillin_datastructure.size(); index++){
		_index_key_value_pair.push_back( _fillin_datastructure.at(_identifier.at(index)) );
	}
}

// Its dead code, but other way to parse the -> token
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
