#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>

enum char_type {
	LOWERCASE = 0,
	CAPITAL,
	DIGIT
};

char *random_sequence(int length, int capitals, int digits);
enum char_type *permute_char_types(int length, int capitals, int digits);
char random_char(enum char_type type);
int random_element(int *array, int size);
int random_int(int range);
