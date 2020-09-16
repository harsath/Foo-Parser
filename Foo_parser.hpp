#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <vector>

class FooParser_test;
namespace Foo{
	struct Pair{ std::string key, value; };
	bool is_failed = false;
	class FooParser{
		private:
			friend class ::FooParser_test;
			std::unordered_map<std::string, std::vector<Foo::Pair>> _fillin_datastructure; // Final return DS after parsed
			// tmp value holders used by parser
			std::string _identifier;
			std::vector<Foo::Pair> _key_value_map;
			std::string _file_name;
		public:
			FooParser(const std::string& file_name) noexcept : _file_name(file_name) {}
			FooParser& operator=(const FooParser&)=delete;
			FooParser()=delete;
			void foo_parse() noexcept;
			void file_exists() const noexcept;
			std::vector<Foo::Pair> get_key_value_pair() const noexcept;
			std::string get_identifier() const noexcept;
			std::unordered_map<std::string, std::vector<Foo::Pair>> get_result() noexcept; 
	};
}
