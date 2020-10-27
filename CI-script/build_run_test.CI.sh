#!/bin/bash
set -e
set -u
FOO_CONF_FILE=$PWD/tests/parse_file.foo
TEST_BINARY_NAME="parser_test"
if [[ -f ${FOO_CONF_FILE} ]]; then
	mkdir build && cd build
	cmake .. && make
	DIRECTORY_BASE=$(basename $PWD)
	if [[ ${DIRECTORY_BASE} == "build" ]]; then
		cp ../tests/parse_file.foo ./tests && cd tests
		if [[ -f ${TEST_BINARY_NAME} ]]; then
			./$TEST_BINARY_NAME 
		else
			echo -e "[ERROR] No binary found to test\n"
			exit 1
		fi
	fi
else
	echo -e "[ERROR] There is no foo_parser.foo file\n"
	exit 1
fi
