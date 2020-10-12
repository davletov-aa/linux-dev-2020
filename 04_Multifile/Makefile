GENERATES = prog prog-a prog-so README
TEST_DIR = tmp_dir
TRASH = *.o *~ o.* *.a *.so $(TEST_DIR)
CC = cc
CURRENT_DIR = $(shell pwd)

all:	README prog prog-a prog-so

fun.o:  outlib.h

prog.o:  outlib.h

liboutput_static.a:	const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	$(CC) -shared $^ -o $@

prog:	const.o fun.o prog.o
prog-a: prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -o $@

prog-so:export LD_LIBRARY_PATH=$(CURRENT_DIR)
prog-so:	prog.o liboutput.so
	$(CC) -L. $< -loutput -o $@

test:export LD_LIBRARY_PATH=$(CURRENT_DIR)
test:	prog prog-a prog-so
	mkdir -p $(TEST_DIR)
	./run_test.sh $(TEST_DIR)
	cmp $(TEST_DIR)/prog.txt $(TEST_DIR)/prog-a.txt
	cmp $(TEST_DIR)/prog.txt $(TEST_DIR)/prog-so.txt
	cmp $(TEST_DIR)/prog-a.txt $(TEST_DIR)/prog-so.txt
	rm -rf $(TEST_DIR)

README:	prog
	./$< 2> $@

clean:
	rm -rf $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)