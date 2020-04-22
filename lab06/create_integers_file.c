#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int range[3] = {0};	
	int assignment = 1;

	while (assignment < argc -1) {
		range[assignment] = atoi(argv[assignment]);
		assignment ++;
	}

    FILE *outputStream;

    outputStream = fopen(argv[3], "w");
    if (outputStream == NULL) {
        fprintf(stderr, "%s: open of failed\n", argv[0]);
        return 1;
    }
	
	int i;
	i = range[1];
	while (i <= range[2]) {
		fprintf(outputStream,"%d\n",i);
		i++;
	}
	
    return 0;
}
