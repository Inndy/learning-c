#include <stdio.h>
#include <stdlib.h>

typedef struct _INT_LINK {
	int value;
	struct _INT_LINK * next;
} INT_LINK;

int main () {
	int i, k;
	INT_LINK * list = NULL, * p = NULL;
	puts("Input 5 Integers:");
	for (i = 0; i < 5; i++) {
		scanf("%d", &k);
		p = (INT_LINK *) malloc(sizeof(INT_LINK));
		p->next = list;
		list = p;
		list->value = k;
	}

	i = 1;
	while (list) {
		printf("Node #%d = %d\n", i++, list->value);
		p = list->next;
		free(list);
		list = p;
	}

	return 0;
}
