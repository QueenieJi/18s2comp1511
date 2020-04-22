#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char *filename;
	int range;

	if (argc == 2) {
		range = 10;
		filename = argv[1];
	} else if (argc == 4) {
		range = atoi(argv[2]);
		filename = argv[3];
	} else {
		fprintf(stderr, "Invalid Arguments\n");
		return 1;
	}

    FILE *file;
    file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "%s: open of failed\n", argv[0]);
        return 1;
    }

	int i = 0;
	while (i < range) {
		char str[1025];
		// You can also use 'break' to exit the loop.
		if (fgets(str, 1025, file) == NULL) {
			i = range;
		} else {
			printf("%s", str);
			i++;
		}
	}
	
    return 0;
}
