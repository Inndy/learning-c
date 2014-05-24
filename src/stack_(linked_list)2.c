#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct STRUCT_STACK {
  int value;
  struct STRUCT_STACK* priv;
  struct STRUCT_STACK* next;
} STACK;



int stack_init(STACK** stack){
  if((*stack = (STACK *)malloc(sizeof(STACK))) == NULL){
    return -1;
  }
  memset(*stack, 0, sizeof(**stack));
  return 0;
}

int stack_push(STACK** stack, int value) {
  if(*stack != NULL){
    if(stack_init(&((*stack)->next)) != 0){
      return -1;
    }
    else{
      (*stack)->next->priv = *stack;
      *stack = (*stack)->next;
      (*stack)->value = value;
    }
  }
  else{
    if(stack_init(stack) != 0){
      return -1;
    }
    else{
      (*stack)->value = value;
    }
  }
  return 0;
}

int stack_pop(STACK** stack) {
  int value = (*stack)->value;
  if((*stack)->priv != NULL){
    *stack = (*stack)->priv;
    free((*stack)->next);
    (*stack)->next = NULL;
  }
  else{
    free(*stack);
    *stack = NULL;
  }
  return value;
}

int stack_top(STACK* stack) {
  return stack->value;
}

int main () {
  STACK* stack = NULL;
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
      if(stack_push(&stack, k) != 0){
	fprintf(stderr, "Failed to push %d to stack\n", k);
      }
    } 
    else if (strcmp(cmd, "pop") == 0) {
      // pop
      if (stack != NULL) {
	printf("pop: %d\n",stack_pop(&stack));
      } 
      else {
	fprintf(stderr, "Error: stack is empty\n");
      }
    }
    else if (strcmp(cmd, "peek") == 0) {
      // peek
      if (stack != NULL) {
	printf("top = %d\n", stack_top(stack));
      }
      else {
	fprintf(stderr, "Error: stack is empty\n");
      }
    } 
    else if (strcmp(cmd, "exit") == 0) {
      // output stack
      puts("exit");
      while (stack) {
	printf("top = %d\n", stack_top(stack));
	stack_pop(&stack);
      }
      break;
    }
    else{
      fprintf(stderr, "Command not found\n");
      continue;
    }
  }
  return 0;
}
