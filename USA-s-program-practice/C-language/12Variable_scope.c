#include <stdio.h>

/* 

�ϐ��̗L���͈�

*/

int a = 0; /* �O���[�o���ϐ� */

void f(void) {
    a++;
    printf("a:%d\n", a);
}

int main(void) {

    f();
    printf("[main] a:%d\n", a);

    return 0;
}