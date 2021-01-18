#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
float f_xy(float x,float y){
  float f_xy=-x*y;
  return  f_xy;
}

int main(void) {

int i=0,j=0,nnokosuu_int,a_int,b_int;
float x=0,y=0,f_b=0,a=0,b=0,h=0,nnokosuu,true;
float k_1=0,k_2=0,k_3=0,k_4=0;
FILE *fp;
 if((fp=fopen("22501900110_MotoshiUSA_12'.txt","w"))==NULL){
 printf("Cannot open the file\n");
 exit(1);
 }

printf("積分区間は０～15です。\n");
fprintf(fp,"積分区間は０～15です。\n");
a=0;
b=15;
a_int=a;
b_int=b;
printf("刻み幅hの値を入力してください\n");
fprintf(fp,"刻み幅hの値を入力してください\n");
scanf("%f",&h);
nnokosuu=15/h;
nnokosuu_int=nnokosuu;

y=15;

printf("入力された値は以下の通りです。\n積分区間は[%d,%d]\n",a_int,b_int);
printf("h=%f\nn=%d\nx_0=%f\ny_0=%f\n",h,nnokosuu_int,x,y);
fprintf(fp,"入力された値は以下の通りです。\n積分区間は[%d,%d]\n",a_int,b_int);
fprintf(fp,"h=%f\nn=%d\nx_0=%f\ny_0=%f\n",h,nnokosuu_int,x,y);


for(j=0;j<nnokosuu;j++){

    k_1=h*f_xy(x,y);
    k_2=h*f_xy(x+h/2,y+k_1/2);
    k_3=h*f_xy(x+h/2,y+k_2/2);
    k_4=h*f_xy(x+h,y+k_3);
    y  =y+(k_1+2*k_2+2*k_3+k_4)/6;
    true=15*exp(-0.5*pow(x,2));
    x  =x+h;
    printf("n=%d \t x=%f \t y=%f \t 真の値は%fです\n",j+1,x,y,true);
    fprintf(fp,"n=%d \t x=%f \t y=%f \t 真の値は%fです\n",j+1,x,y,true);

}
    fclose(fp);
    return 0;
}