#include "generator.h"

int main(int argc, char **argv)
{
	int length;
	int capitals;
	int digits;
	/*
	 * checks number and validity of arguments
	 */
	if (argc != 4) {
		puts("please give length, number of capitals, and number of digits in that order");
		return 0;
	}
	length = atoi(argv[1]);
	capitals = atoi(argv[2]);
	digits = atoi(argv[3]);
	if (length < 1 || capitals < 0 || digits < 0) {
		puts("length should be positive");
		puts("numbers of capitals and digits should be positive");
		return 0;
	}
	if (length < capitals + digits) {
		puts("length should be at least the sum of the number of the capitals and the number of digits");
		return 0;
	}
	char *string = random_sequence(length, capitals, digits);
	printf("%s\n", string);
	free(string);
	return 0;
}

char *random_sequence(int length, int capitals, int digits)
{
	int i;
	enum char_type *types;
	char *string;
	/*
	 * produces a string of length n
	 * with the specified number of capitals and digits
	 * all other characters are lowercase letters
	 */
	types = permute_char_types(length, capitals, digits);
	string = malloc(sizeof(char) * (length + 1));
	for (i = 0; i < length; i++) {
		string[i] = random_char(types[i]);
	}
	string[length] = 0;
	free(types);
	return string;
}

enum char_type *permute_char_types(int length, int capitals, int digits)
{
	int i;
	int size;
	int *indices;
	enum char_type *array;
	/*
	 * produces an array
	 * with the specified number of entries
	 * equal to CAPITAL and DIGIT
	 * all other entries are equal to LOWERCASE
	 */
	indices = malloc(sizeof(int) * length);
	for (i = 0; i < length; i++) {
		indices[i] = i;
	}
	array = calloc(sizeof(enum char_type), length);
	size = length;
	for (i = 0; i < capitals; i++) {
		array[random_element(indices, size--)] = CAPITAL;
	}
	for (i = 0; i < digits; i++) {
		array[random_element(indices, size--)] = DIGIT;
	}
	free(indices);
	return array;
}

char random_char(enum char_type type)
{
	/*
	 * returns a random character of the specified type
	 */
	switch (type) {
	case LOWERCASE:
		return random_int(26) + 97;
	case CAPITAL:
		return random_int(26) + 65;
	case DIGIT:
		return random_int(10) + 48;
	default:
		printf("type %d is not defined\n", type);
		return '?';
	}
}

int random_element(int *array, int size) {
	int random_index;
	int random_element;
	/*
	 * returns a random element of the array
	 * the element is removed from the array
	 * the caller function is responsible for
	 * decrementing the size of the array
	 */
	random_index = random_int(size);
	random_element = array[random_index];
	array[random_index] = array[size - 1];
	return random_element;
}

int random_int(int range)
{
	unsigned long buffer;
	/*
	 * produces a random integer x such that
	 * 0 <= x < range
	 */
	if (getrandom(&buffer, sizeof(unsigned long), 0) !=
			sizeof(unsigned long)) {
		puts("failed to retrieve random bytes");
		return 0;
	}
	return buffer % range;
}
