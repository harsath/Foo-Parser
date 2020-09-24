cmake_minimum_required(VERSION 3.10)

project(Foo_Parser
	VERSION "0.1.0"
	DESCRIPTION "Primitive parser for Foo structures"
	LANGUAGES CXX)

# Sticking to modern C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# compiler_commands json file for LSP plugin
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# adding examples, test and lib dirs
add_subdirectory(./foo_parser)
add_subdirectory(./examples)
add_subdirectory(./tests)
