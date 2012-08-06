SHELL = bash

vis: ./src/vis.c
	$(CC) -g -o ./bin/vis ./src/vis.c

args: ./src/args.c
	$(CC) -g -o ./bin/args ./src/args.c

all: vis args

test: vis
	./test/test-vis.sh

.PHONY: test
