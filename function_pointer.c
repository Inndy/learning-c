#include <stdio.h>

int func_add(int a, int b) { return a + b; }
int func_sub(int a, int b) { return a - b; }
int func_mul(int a, int b) { return a * b; }
int func_div(int a, int b) { return a / b; }

int main () {
    int (* funcs [4])(int, int) = {
        func_add, func_sub, func_mul, func_div
    };

    int a = 567, b = 23;
    int i;
    for (i = 0; i < sizeof(funcs) / sizeof(* funcs); i++)
        printf("func[%d](%d, %d) = %d;\n", i, a, b, funcs[i](a, b));

    return 0;
}
