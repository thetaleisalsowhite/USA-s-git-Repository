#include <stdio.h>

/* 

•Ï”‚Ì—LŒøŠúŒÀ

*/


void f(void) {
    static int a = 0; /* Ã“I•Ï” */
    a++;
    printf("a:%d\n", a);
}

int main(void) {

    f();
    f();
    f();

    return 0;
}