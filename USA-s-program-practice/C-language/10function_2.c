#include <stdio.h>

/* 

ŠÖ”F•¡”‚Ìˆ—

•Ô‚è’l‚ÌŒ^ ŠÖ”–¼(ˆø”, ...) {
    ˆ—;
    return •Ô‚è’l;
}

*/

float getMax(float a, float b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int main(void) {

    float result;
    result = getMax(2.3, 5.2);
    printf("%f\n", result);
    
    return 0;
}