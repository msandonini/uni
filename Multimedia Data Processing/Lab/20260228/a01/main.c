// -- Compilation flags --

#define _CRT_SECURE_NO_WARNINGS


// -- Includes --

#include <stdio.h>
#include <stdlib.h>


// -- Exit codes --


// -- Macros --


// -- Constants --

#define PREALLOC 10


// -- Data structures --


// -- Function prototypes --

int qsortCompare(const void* a, const void* b) {
	int val1 = *((const int*) a);
	int val2 = *((const int*) b);

	fprintf(stdout, "Comparing %d and %d.\n", val1, val2);

	if (val1 < val2) return -1;
	if (val1 > val2) return 1;
	return 0;
}


// -- Main --

int main(int argc, char* argv[]) {
	FILE *fileIn, *fileOut;
	int capacity, count, *arr;

	if (argc != 3) {
		fprintf(stderr, "Error: Invalid number of arguments.\n");
		fprintf(stderr, "Usage: sort_int <filein.txt> <fileout.txt>\n");
		return 1;
	}

	fileIn = fopen(argv[1], "r");

	if (!fileIn) {
		fprintf(stderr, "Error: The specified input file does not exist or is inaccessible.\n");
		return 1;
	}

	fileOut = fopen(argv[2], "r");
	if (fileOut) {
		fprintf(stderr, "Error: The specified output file already exists.\n");

		fclose(fileIn);
		fclose(fileOut);
		return 1;
	}

	capacity = PREALLOC;
	count = 0;
	arr = (int*) malloc(capacity * sizeof(int));

	if (!arr) {
		fprintf(stderr, "Error: Memory allocation failed.\n");

		fclose(fileIn);
		return 1;
	}

	int inval;
	while (fscanf(fileIn, "%d", &inval) == 1) {
		if (count >= capacity) {
			capacity += PREALLOC;
			int* newArr = (int*)realloc(arr, capacity * sizeof(int));

			if (!newArr) {
				fprintf(stderr, "Error: Memory reallocation failed.\n");

				free(arr);
				fclose(fileIn);
				return 1;
			}

			arr = newArr;
		}

		arr[count++] = inval;
	}
	fprintf(stdout, "Finished reading file.\n");

	fclose(fileIn);

	fileOut = fopen(argv[2], "w");

	if (!count) {
		free(arr);
		fclose(fileOut);
		return 0;
	}

	qsort(arr, count, sizeof(int), qsortCompare);

	fprintf(stdout, "Finished sorting values.\n");

	int i;
	for (i = 0; i < count; i++) {
		fprintf(fileOut, "%d\n", arr[i]);
	}

	free(arr);
	fclose(fileOut);
	return 0;
}


// -- Functions --
