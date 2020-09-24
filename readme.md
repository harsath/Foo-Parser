### Foo-Parser: primitive structure parser written in C++

Usage syntax:
```
Foo <space> IDENTIFIER <LINEBREAK>
{
	KEY <space> -> <space> VALUE <opspace>	
}
```

Example, FILE: parse_me.foo

```
Foo list_one 
{
	key_one -> value_one 
	key_two -> value_two 	
}
```

Parsed into a data structure:

```c++
Foo::Pair --> struct{std::string key, std::string value}
std::unordered_map<std::string, std::vector<Foo::Pair>>
		  IDENTIFIER,   vector<KEY, VALUE>
```

Sample usage is shown in `/examples/main.cpp` for a reference. Feel free to use for your own projects.

```c++
//		       KEY              VALUES
std::unordered_map<std::string, std::vector<Foo::Pair>> Foo::FooParser::get_result();

// Get std::vector<Foo::Pair> (key value pair) from a IDENTIFIER
std::vector<Foo::Pair> Foo::FooParser::get_key_value_pair_from_identifier(
						const std::string& IDENTIFIER);

// Get std::vector<Foo::Pair> (key value pair) form a Foo structure's Index
std::vector<Foo::Pair> Foo::FooParser::get_key_value_pair_from_index(std::size_t INDEX);

// Get std::vector<std::string> (List of IDENTIFIERs)
std::vector<std::string> get_identifier();
```

#### All Done!

- [x] Parse the Foo structure and add entried into the datastructure
- [x] Multiple Foo structure in single file support for the parser
- [x] Better robust and debug implementation
