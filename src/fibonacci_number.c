#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long int ullint;

long long int memo[512];
long long int fib(int);
ullint fib_r(int n, ullint a, ullint b);

int main() {

	int n;
	for (n = 1; n <= 90; n++) {
		printf("result of fib %d is :%lld\n", n,fib(n));
	}
	
	
	printf("\nfib_r now!\n\n");
	for (n = 1; n <= 90; n++) {
		printf("result of fib_r(%d) is %lld\n", n, fib_r(n, 1, 1));
	}

	
	return 0;
}

long long int fib(int n){	 
	if (memo[n] != 0){
		return memo[n];
	}
	long long int temp_result = 0;
	if (n <= 2){
		temp_result = 1;
	}
	else{
		temp_result = fib(n-1) + fib(n-2);
	}
	memo[n] = temp_result;
	return temp_result;
}

ullint fib_r(int n, ullint a, ullint b) {
	if (n > 1)
		return fib_r(n - 1, a + b, a);
	else
		return b;
}
