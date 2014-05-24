#include <stdlib.h>
#include <stdio.h>


long long int memo[512];
long long int fib(int);
int main(){

	int n;
	for (n = 1; n <= 90; n++){
		printf("result of fib %d is :%lld\n", n,fib(n));
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
