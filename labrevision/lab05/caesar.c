#include <stdio.h>
#include <stdlib.h>

int encrypt(int character,int shift);
int main (int argc, char *argv[]) {
	int shift = atoi(argv[1]);
	if (shift < 0) {
		shift = 26 + (shift % 26);
	}
	int ch = getchar();
	while (ch != EOF) {
		int new_ch  = encrypt(ch,shift);
		putchar(new_ch);
		ch = getchar();
	}
	return 0;
}
int encrypt(int character,int shift) {
	if (character >= 'a' && character <= 'z') {
		character = 'a' + (character -'a' + shift % 26) % 26;
	} else if (character >= 'A' && character <= 'Z') {
		character = 'A' + (character - 'A' + shift % 26) % 26;
	}
	return character;
}
