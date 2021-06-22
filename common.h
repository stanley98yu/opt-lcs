void print_err(char *msg) {
	fprintf(stderr, "%s\n", msg);
}

void print_arr(int *arr, int n1) {
    for (int i = 0; i < n1; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void read_file(char *fn, char **out) {
	FILE *fp;
	char c;
	int i = 0;
	int buf_size = 1024;

	fp = fopen(fn, "r");
	while ((c = getc(fp)) != EOF) {
    	if (i == buf_size-1) {
    	    buf_size *= 2;
    	    (*out) = realloc(*out, sizeof(char) * buf_size);
    	    if (out == NULL) {
    	        fprintf(stderr, "out of memory\n");
    	        exit(1);
    	    }
    	}
		if (c != '\n') {
    		(*out)[i++] = c;
		}
    }
	(*out)[i] = '\0';
	fclose(fp);
}

int max(int a, int b) {
    return a > b ? a : b;
}
