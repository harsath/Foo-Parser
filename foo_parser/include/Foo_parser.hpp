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

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unistd.h>
#include <vector>


class FooParser_test;
namespace Foo{
	#define print_macro(arg) std::cout << arg << std::endl; // debug purposes

	std::vector<std::string> helper_tokenize_line(std::string);
	struct Pair{
		std::string key, value; 
		Pair(std::string _key, std::string _value) : key(_key), value(_value){}
	};
	class FooParser{
		private:
			friend class ::FooParser_test;
			std::unordered_map<std::string, std::vector<Foo::Pair>> _fillin_datastructure; // Final return DS after parsed
			// tmp value holders used by parser
			std::vector<std::string> _identifier;
			std::vector<std::vector<Foo::Pair>> _index_key_value_pair;
			std::string _file_name;
		public:
			FooParser(const std::string& file_name) noexcept : _file_name(file_name) {}
			FooParser& operator=(const FooParser&)=delete;
			FooParser()=delete;
			void foo_parse() noexcept;
			void file_exists() const noexcept;
			std::vector<Foo::Pair> get_key_value_pair_from_index(std::size_t) const noexcept;
			std::vector<Foo::Pair> get_key_value_pair_from_identifier(const std::string&) const noexcept;
			std::vector<std::string> get_identifier() const noexcept;
			std::unordered_map<std::string, std::vector<Foo::Pair>> get_result() const noexcept; 
		private:
			void _populate_key_value_pair_map(void) noexcept;
	};
}
