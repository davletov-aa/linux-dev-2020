#include <assert.h>
#include <stdint.h>
#include <sys/time.h>

#include "buf.h"

static void test_buffer_init()
{
	float *a = NULL;
    assert(buf_capacity(a) == 0);
	assert(buf_size(a) == 0);
}

static void test_buffer_push_and_free()
{
	float *a = NULL;
	buf_push(a, 1.3f);
	assert(buf_size(a) == 1);
	assert(a[0] == 1.3f);
	buf_free(a);
	assert(a == NULL);
}

static void test_buffer_push()
{
	const int test_size = 10000;
	int* a = NULL;
	for (int i = 0; i < test_size; ++i)
		   buf_push(a, i);
	assert(buf_size(a) == test_size);
	
	int match = 0;
	for (int i = 0; i < test_size; match += a[i] == i, ++i);
	assert(match == test_size);
	buf_free(a);
	assert(a == NULL);
}

static void test_buffer_grow_and_trunc()
{
	const int test_size = 1000;
	int* a = NULL;
	buf_grow(a, test_size);
	assert(buf_capacity(a) == test_size);
	assert(buf_size(a) == 0);
	buf_trunc(a, test_size / 10);
	assert(buf_capacity(a) == test_size / 10);
	buf_free(a);
	assert(a == NULL);
}

static void test_buffer_pop()
{
	float* a = NULL;
	buf_push(a, 1.1);
	buf_push(a, 1.2);
	buf_push(a, 1.3);
	buf_push(a, 1.4);
	assert(buf_size(a) == 4);
	assert(buf_pop(a) == 1.4f);
	buf_trunc(a, 3);
	assert(buf_size(a) == 3);
	assert(buf_pop(a) == 1.3f);
	assert(buf_pop(a) == 1.2f);
	assert(buf_pop(a) == 1.1f);
	assert(buf_size(a) == 0);
	buf_free(a);
	assert(a == NULL);
}

static void test_buffer_clear_empty()
{
	int* a = NULL;
	buf_clear(a);
	assert(a == NULL);
}

static void test_buffer_clear_not_empty()
{
	int* a = NULL;
	buf_push(a, 1);
	assert(a != NULL);
	buf_clear(a);
	assert(buf_size(a) == 0);
	assert(a != NULL);
}

int main(int argc, char** argv)
{
	typedef void (*test_type)(void);
	test_type tests[] = {
		test_buffer_init,
		test_buffer_push_and_free,
		test_buffer_push,
		test_buffer_clear_empty,
		test_buffer_clear_not_empty,
		test_buffer_pop,
		test_buffer_grow_and_trunc,
	};

	for (int i = 1; i < argc; ++i)
	{
		int test_num = atoi(argv[i]);
		assert(test_num < sizeof(tests) / sizeof(test_type));
		tests[test_num]();
	}
	return 0;
}