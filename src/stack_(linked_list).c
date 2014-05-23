#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _STACK {
	int value;
	struct _STACK * next;
} STACK;

STACK * stack_push(STACK * stack, int value) {
	STACK * p = (STACK *)malloc(sizeof(STACK));
	p->value = value;
	p->next = stack;
	return p;
}

STACK * stack_pop(STACK * stack) {
	STACK * p = stack->next;
	free(stack);
	return p;
}

int stack_top(STACK * stack) {
	return stack->value;
}

int main () {
	STACK * stack = NULL;
	char cmd[256];

	printf("push [number] -- Push a number onto stack\n"
		   "pop           -- Pop a number from stack\n"
		   "peek          -- Peek the number from stack top\n"
		   "exit          -- Exit this program\n");

	while(1) {
		// "%255s" limits max string length to 255 bytes
		// it prevents buffer overflow
		// but it may modify 256 bytes of memory (with '\0' terminated)
		scanf("%255s", cmd);
		if (strcmp(cmd, "push") == 0) {
			// push
			int k;
			scanf("%d", &k);
			stack = stack_push(stack, k);
		} else if (strcmp(cmd, "pop") == 0) {
			// pop
			if (stack != NULL) {
				stack = stack_pop(stack);
			} else {
				puts("error: stack is empty");
			}
		} else if (strcmp(cmd, "peek") == 0) {
			// peek
			if (stack != NULL) {
				printf("top = %d\n", stack_top(stack));
			} else {
				puts("error: stack is empty");
			}
		} else if (strcmp(cmd, "exit") == 0) {
			// output stack
			puts("exit");
			while (stack) {
				printf("top = %d\n", stack_top(stack));
				stack = stack_pop(stack);
			}
			break;
		}
	}
	return 0;
}
