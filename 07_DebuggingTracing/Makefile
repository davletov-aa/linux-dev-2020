SHELL=/bin/bash

.PHONY: all wrapper.so test clean

all: wrapper.so test clean

wrapper.so:
	gcc -shared -fPIC wrapper.c -o wrapper.so -ldl

test:
	touch file FIXed_file
	-rm ./file
	-rm ./FIXed_file

	touch file FIXed_file
	-LD_PRELOAD=`pwd`/wrapper.so rm ./file
	-LD_PRELOAD=`pwd`/wrapper.so rm ./FIXed_file

clean:
	rm -f wrapper.so file FIXed_file
