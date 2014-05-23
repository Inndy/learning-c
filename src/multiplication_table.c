#include <stdio.h>

void normal_9x9() {
	int i, j;
	for (i = 1; i <= 9; i++) {
		for (j = 1; j <= 9; j++) {
			printf("%d*%d = %2d  ", j, i, i * j);
		}
		printf("\n");
	}
}

void recursion_9x9(int i, int j) {
	// to observe how does it go
	printf("recursion_9x9(%d, %d)\n", i, j);

	if (j <= 0) {
		recursion_9x9(i - 1, 9);
		printf("\n");
	} else if (i > 0) {
		recursion_9x9(i, j - 1);
	}
	if (i > 0 && j > 0) {
		printf("%d*%d = %2d  ", j, i, i * j);
	}
}

int main () {
	printf("This is normal_9x9():\n");
	normal_9x9();

	printf("This is recursion_9x9():\n");
	recursion_9x9(9, 9);
	return 0;
}
