#include <stdio.h>

/* 

ループ (for)

continue; 一回スキップ
break; ループを抜ける

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