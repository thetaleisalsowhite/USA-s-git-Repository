#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
int main(void) {

int n=0;
float x=0,f=0,df=0,dx=0,eps=0;
FILE *fp;
 if((fp=fopen("22501900110_MotoshiUSA_5.txt","w"))==NULL){
 printf("Cannot open the file\n");
 exit(1);
 }
eps=pow(10,-5);

do{

f=pow(x,3)-7*pow(x,2)+16*(x)-10;
df=3*pow(x,2)-14*x+16;
dx=-f/df;

printf("n = %d: x = %f, f = %lf ",n,x,f);
printf("df = %f, dx = %f\n",df,dx);
fprintf(fp,"n = %d: x = %f, f = %lf ",n,x,f);
fprintf(fp,"df = %f, dx = %f\n",df,dx);

x=x-f/df;
n=n+1;

if(fabsf(dx/x)<=eps)break;

printf("%lf\n",fabsf(dx/x));
fprintf(fp,"%lf\n",fabsf(dx/x));

}while(1);

printf("Ans: x = %f, f(x) = %f",x,f);
fprintf(fp,"Ans: x = %f, f(x) = %f",x,f);
    
    fclose(fp);
    return 0;

}