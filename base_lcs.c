#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "common.h"

int lcs(char *str1, int n, char *str2, int m) {
	int prev, tmp;
	int mat[m+1];

	memset(mat, 0, sizeof(mat));
	for (int i = 0; i < n; i++) {
		prev = 0;
		for (int j = 1; j < m+1; j++) {
			tmp = mat[j];
			if (str1[i] == str2[j-1]) {
				mat[j] = prev + 1;
			} else {
				mat[j] = max(mat[j-1], tmp);
			}
			prev = tmp;
		}
	}
	return mat[m];
}

int main(int argc, char **argv) {
	char *str1, *str2;
	int n1, n2, out;
	clock_t t;
	double t_sec;

	if (argc != 3) {
		fprintf(stderr, "usage: %s <file-1> <file-2>\n", argv[0]);
		return 1;
	}

	// Read input string files
	str1 = malloc(1024);
	if (str1 == NULL) {
		print_err("failed to allocate memory");
		return 1;
	}
	str2 = malloc(1024);
	if (str2 == NULL) {
		print_err("failed to allocate memory");
		return 1;
	}
	read_file(argv[1], &str1);
	n1 = strlen(str1);
	read_file(argv[2], &str2);
	n2 = strlen(str2);

	t = clock();
	out = lcs(str1, n1, str2, n2);
	t = clock() - t;
	t_sec = (double) t / CLOCKS_PER_SEC;
	if (out < 0) {
		print_err("algorithm failed on input");
		return -1;
	}
	printf("Length of longest common subsequence: %d\n", out);
	printf("Time taken: %ld ticks (%f sec)\n", t, t_sec);

	free(str1);
	free(str2);
	return 0;
}
