#include <stdio.h>

/* 

O€‰‰Zq

if (ğŒ) {
    return A;
} else {
    return B;
}

•Ô‚è’l = (ğŒ) ? A : B;

*/

float getMax(float a, float b) {
/*
    if (a >= b) {
        return a;
    } else {
        return b;
    }
*/
    return (a >= b) ? a : b;
}

int main(void) {

    float result;
    result = getMax(2.3, 5.2);
    printf("%f\n", result);
            
    return 0;
}