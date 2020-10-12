CFLAGS = -Wall -fPIC

GENERATES = prog prog-a prog-so README
TEST_DIR = tmp_dir
TRASH = *.o *~ o.* *.a *.so $(TEST_DIR)
CC = cc

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

prog-so:	prog.o liboutput.so
	export LD_LIBRARY_PATH="$(LD_LIBRARY_PATH);`pwd`"
	$(CC) -L. $< -loutput -o $@

test:	prog prog-a prog-so
	export LD_LIBRARY_PATH="$(LD_LIBRARY_PATH);`pwd`"
	mkdir -p $(TEST_DIR)
	./run_test.sh $(TEST_DIR)
	cmp $(TEST_DIR)/prog.txt $(TEST_DIR)/prog-a.txt
	cmo $(TEST_DIR)/prog.txt $(TEST_DIR)/prog-so.txt
	cmp $(TEST_DIR)/prog-a.txt $(TEST_DIR)/prog-so.txt

	rm -rf $(TEST_DIR)

README:	prog
	./$< 2> $@

clean:
	rm -rf $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)