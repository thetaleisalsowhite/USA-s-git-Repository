#include <stdio.h>

/* 

�ϐ��̗L������

*/


void f(void) {
    static int a = 0; /* �ÓI�ϐ� */
    a++;
    printf("a:%d\n", a);
}

int main(void) {

    f();
    f();
    f();

    return 0;
}