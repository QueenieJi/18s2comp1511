#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	if (argc != 4) {
		printf("Error!");
	}
	FILE *outputStream;

	outputStream = fopen(argv[3],"w");
	int i = atoi(argv[1]);
	while ( i <= atoi(argv[2])) {
		fprintf(outputStream,"%d\n",i);
		i++;
	}
	fclose(outputStream);


	return 0;
}
