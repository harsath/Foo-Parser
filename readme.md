### Foo-Parser: primitive structure parser written in C++

Usage syntax:
```
Foo <space> IDENTIFIER {
	KEY <space> -> <space> VALUE <opspace>	
}
```

Example, FILE: parse_me.foo

```
Foo list_one {
	key_one -> value_one 
	key_two -> value_two 	
}
```

Parsed into a data structure:

```
Foo::Pair --> struct{std::string key, std::string value}
std::unordered_map<std::string, std::vector<Foo::Pair>>
		  IDENTIFIER,   vector<KEY, VALUE>
```

Sample usage is shown in main.cpp for a reference. Feel free to use for your projects, This project is under dev and I'm in the process of completing the todo list

#### TODO

- [x] Parse the Foo structure and add entried into the datastructure
- [ ] Multiple Foo structure support for the parser
- [ ] Line break and semicolon syntax support
