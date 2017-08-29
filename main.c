/*
 * hexx - hexwiever
 *
 * Erik Liodden
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUF_SIZE 16

int main(int argc, char *argv[])
{
	int i, n;
	char buf[BUF_SIZE];
	FILE *fp;
	long count = 0;

	if (argc < 2) {
		fprintf(stderr, "usage: ./hexx <file>\n");
		exit(1);
	}

	/* open file to be printed */
	if ((fp = fopen(argv[1], "rb")) == NULL)
		perror(argv[1]);

	/* read file and print the output */
	while ((n = fread(buf, 1, BUF_SIZE, fp)) > 0) {
		printf("%08lx: ", count);
		for (i = 0; i < n; i++) {
			if (i % 2 == 0)
				printf(" ");
			printf("%02hhx", buf[i]);
		}
		printf("\n");
		count += n;
	}
	
	return 0;
}

