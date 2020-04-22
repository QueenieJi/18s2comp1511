#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int range[3] = {0};	
	int assignment = 1;

	printf("first\n");
	while (assignment < argc) {
		range[assignment] = atoi(argv[assignment]);
		assignment ++;
	}

    FILE *outputStream;
    outputStream = fopen(argv[3], "w");
    if (outputStream == NULL) {
        fprintf(stderr, "%s: open of '%s' failed\n", argv[0]);
        return 1;
    }
	fprintf(stdout,"hi\n");
	int i;
	i = range[1];
	while (i <= range[2]) {
		fprintf(outputStream,"%d",i);
		i++;
	}
	
    return 0;
}
