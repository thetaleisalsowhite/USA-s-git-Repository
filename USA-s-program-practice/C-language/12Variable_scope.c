#include <stdio.h>

/* 

変数の有効範囲

*/

int a = 0; /* グローバル変数 */

void f(void) {
    a++;
    printf("a:%d\n", a);
}

int main(void) {

    f();
    printf("[main] a:%d\n", a);

    return 0;
}