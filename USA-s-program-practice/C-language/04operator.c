#include <stdio.h>

/* 

���Z�q
+ - * / %(�]��) 

����𔺂����Z�q
x = x + 5; �� x += 5;

�P�����Z�q
++ --

*/

int main(void) {

    int x;
    
    x = 10 % 3; /* 1 */

    printf("%d\n", x);

    x += 3; /* 4 */
    
    printf("%d\n", x);

    x++; /* 5 */
    
    printf("%d\n", x);

    return 0;
}