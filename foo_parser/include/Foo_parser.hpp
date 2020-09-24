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
