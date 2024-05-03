test: test.c my-assert.h
	clang test.c -o test

clean:
	rm -f test
