#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Usage: %s word symbol\n", argv[0]);
		exit(1);
	}
	int res = 0;
	int n = strlen(argv[1]);
	char symbol = argv[2][0];
	
	char *word = (char *) malloc((n + 1) * sizeof(char));
	word = memcpy(word, argv[1], n + 1);

	for (int i = 0; i < n; i++) {
		if (word[i] == symbol) {
			res++;
		}
	}

	printf("number of symbols %c in %s is %d\n", symbol, word, res);
	
	free(word);
	free(word);

}


