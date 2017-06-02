all: generator generator_debug

generator: generator.c generator.h
	clang -O2 generator.c -o generator

generator_debug: generator.c generator.h
	clang -g -Og -Wall -Werror -fsanitize=address generator.c -o generator_debug

clean:
	rm -f generator generator_debug
