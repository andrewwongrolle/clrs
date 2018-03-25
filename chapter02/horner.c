/* horner.c 
 * Implements Horner's rule for evaluating polynomials 
 * Usage: ./horner a0 a1 a2 ... x0
 * to compute the polynomial a0 + a1x + a2x^2 + ... at x = x0
 * */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int i, ai;
    int x0 = atoi(argv[argc - 1]);
    long y = 0;
    for (i = argc - 3;  i >= 0; i--) {
        ai = atoi(argv[i + 1]);
        if (i == argc - 3) 
            printf("Evaluating polynomial f(x) = %dx^%d + ", ai, i);
        else if (i == 1)
            printf("%d*x + ", ai);
        else if (i == 0)
            printf("%d at x = %d...\n", ai, x0);
        else
            printf("%d*x^%d + ", ai, i);
        y = ai + x0 * y;
    }
        printf("f(%d) = %ld\n", x0, y);
        return 0;
}
