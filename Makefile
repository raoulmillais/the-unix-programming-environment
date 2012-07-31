SHELL = bash

vis: ./src/vis.c
	cc -o ./bin/vis ./src/vis.c

args: ./src/args.c
	cc -o ./bin/args ./src/args.c

all: vis args

test: vis
	./test/test-vis.sh

.PHONY: test
