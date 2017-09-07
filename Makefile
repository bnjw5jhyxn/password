all: generator generator_debug

generator: generator.c
	clang -O2 -o generator generator.c

generator_debug: generator.c
	clang -g -Og -Wall -Werror -fsanitize=address -fsanitize=undefined -o generator_debug generator.c

clean:
	rm -f generator generator_debug
