#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>

const int BASE = 10;

enum char_type {
	LOWERCASE = 0,
	CAPITAL,
	DIGIT
};

char *random_sequence(unsigned int length, unsigned int capitals, unsigned int digits);
enum char_type *permute_char_types(unsigned int length, unsigned int capitals, unsigned int digits);
char random_char(enum char_type type);
int random_element(int *array, int size);
unsigned char random_int(unsigned char range);
void initialize_rng();
void set_intopt(char *str, unsigned int *ptr);
void set_fopt(char *str, FILE **ptr);

int main(int argc, char **argv)
{
	unsigned int number;
	unsigned int length;
	unsigned int capitals;
	unsigned int digits;
	char *string;
	int i;
	int c;
	bool help;
	extern char *optarg;
	FILE *outfile;
	/*
	 * reads command line arguments
	 */
	number = 1u;
	length = 16u;
	capitals = 1u;
	digits = 1u;
	outfile = stdout;
	help = false;
	while ((c = getopt(argc, argv, "n:l:c:d:o:h")) != -1) {
		switch (c) {
		case 'n':
			set_intopt(optarg, &number);
			break;
		case 'l':
			set_intopt(optarg, &length);
			break;
		case 'c':
			set_intopt(optarg, &capitals);
			break;
		case 'd':
			set_intopt(optarg, &digits);
			break;
		case 'o':
			set_fopt(optarg, &outfile);
			break;
		case 'h':
			help = true;
		/* we will let getopt() deal with error cases */
		}
	}
	if (help) {
		fprintf(stderr, "see readme for details\n");
	} else {
		if (capitals + digits > length) {
			length = capitals + digits;
		}
		for (i = 0; i < number; i++) {
			string = random_sequence(length, capitals, digits);
			fprintf(outfile, "%s\n", string);
			free(string);
		}
	}
	if (outfile != stdout) {
		fclose(outfile);
	}
	return 0;
}

char *random_sequence(unsigned int length, unsigned int capitals, unsigned int digits)
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

enum char_type *permute_char_types(unsigned int length, unsigned int capitals, unsigned int digits)
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
		return random_int(26) + 'a';
	case CAPITAL:
		return random_int(26) + 'A';
	case DIGIT:
		return random_int(10) + '0';
	default:
		fprintf(stderr, "fatal error: type %d is not defined\n", type);
		exit(EXIT_FAILURE);
	}
}

int random_element(int *array, int size) {
	int random_index;
	int random_element;
	/*
	 * returns a random element of the array, which is removed from the array
	 * the caller function is responsible for decrementing the size of the array
	 */
	random_index = random_int(size);
	random_element = array[random_index];
	array[random_index] = array[size - 1];
	return random_element;
}

unsigned char random_int(unsigned char range)
{
	/*
	 * produces a random integer x such that
	 * 0 <= x < range
	 */
	unsigned short buffer;
	if (getrandom(&buffer, sizeof(buffer), 0u) != sizeof(buffer)) {
		fprintf(stderr, "fatal error: unable to retrieve random bytes\n");
		exit(EXIT_FAILURE);
	}
	return (buffer % range);
}

void set_intopt(char *str, unsigned int *ptr) {
	int optval;
	optval = strtoul(str, (char **) NULL, BASE);
	if (optval) {
		*ptr = optval;
	} else {
		fprintf(stderr, "error: unable to read positive unsigned int \"%s\"\n", str);
	}
}

void set_fopt(char *str, FILE **ptr) {
	FILE *optval;
	if (access(str, F_OK) == 0) {
		fprintf(stderr, "error: file \"%s\" already exists\n", str);
	} else if ((optval = fopen(str, "w"))) {
		*ptr = optval;
	} else {
		fprintf(stderr, "error: unable to open file \"%s\"\n", str);
	}
}
