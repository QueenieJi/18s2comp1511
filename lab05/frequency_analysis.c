#include <stdio.h>

int main () {
    int c = getchar();
    int cha_counts[26];
    int i = 0;
    
    while (i < 26) {
        cha_counts[i] = 0;
        i++;
    }
    
    double sum = 0;
    
    while (c != EOF) {
               
         if ( c >= 'a' && c <= 'z') {
             cha_counts[c -'a'] = cha_counts[c -'a'] + 1; 
			 sum++;
         }
         else if (c >= 'A' && c <= 'Z') {
             cha_counts[c - 'A'] = cha_counts[c - 'A'] + 1;
             sum++;
         } 
         c = getchar();
	}

    
    double frequency = 0;
    int j = 0;
	while (j < 26) {
                
        frequency = (cha_counts[j] / sum);     
    	printf("'%c' %.6lf %d \n",j+'a',frequency, cha_counts[j]);
        j++;
    }
    return 0;
}
