#include <stdio.h>

/* 

���[�v (for)

continue; ���X�L�b�v
break; ���[�v�𔲂���

*/

int main(void) {

    int m;
    for (m = 0; m < 10; m++) {
        if (m == 3) {
            continue;
        }
        if (m == 8) {
            break;
        }
        printf("m: %d\n", m);
    }

    /*
    int m = 0;    
    while (m < 10) {
        printf("m: %d\n", m);
        m++;
    }
    */
        
    return 0;
}