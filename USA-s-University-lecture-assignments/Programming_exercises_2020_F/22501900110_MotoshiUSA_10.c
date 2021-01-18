#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
float f_xy(float x,float y){
  float f_xy=sin(x)+cos(y);
  return  f_xy;
}

int main(void) {

int i=0,nnokosuu,j=0;
float x=0,y=0,a=0,b=0,h=0;
float k_1=0,k_2=0,k_3=0,k_4=0;
FILE *fp;
 if((fp=fopen("22501900110_MotoshiUSA_10.txt","w"))==NULL){
 printf("Cannot open the file\n");
 exit(1);
 }

printf("積分区間は０～π/2です。\n");
fprintf(fp,"積分区間は０～π/2です。\n");
a=0;
b=M_PI/2;
printf("分割数nの個数は15です。\n");
fprintf(fp,"分割数nの個数は15です。\n");
nnokosuu=15;

h=b/nnokosuu;

printf("入力された値は以下の通りです。\n積分区間は[%d,π/2]\n",a);
printf("h=%f\nn=%d\nx_0=%f\ny_0=%f\n",h,nnokosuu,x,y);
fprintf(fp,"入力された値は以下の通りです。\n積分区間は[%d,π/2]\n",a);
fprintf(fp,"h=%f\nn=%d\nx_0=%f\ny_0=%f\n",h,nnokosuu,x,y);


for(j=0;j<nnokosuu;j++){

    k_1=h*f_xy(x,y);
    k_2=h*f_xy(x+h/2,y+k_1/2);
    k_3=h*f_xy(x+h/2,y+k_2/2);
    k_4=h*f_xy(x+h,y+k_3);
    y  =y+(k_1+2*k_2+2*k_3+k_4)/6;
    x  =x+h;
    printf("n=%d  x=%f  y=%f\n",j+1,x,y);
    fprintf(fp,"n=%d  x=%f  y=%f\n",j+1,x,y);

}
    fclose(fp);
    return 0;
}