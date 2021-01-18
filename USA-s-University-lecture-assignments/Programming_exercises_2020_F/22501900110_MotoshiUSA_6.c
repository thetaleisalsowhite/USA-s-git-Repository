#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
float f_x(float x){
  float f_x=1/x;
  return  f_x;
}

int main(void) {

int i=0,nnokosuu,j=0;
float x=0,f_a=0,f_b=0,a=0,b=0,h=0,s=0;
FILE *fp;
 if((fp=fopen("22501900110_MotoshiUSA_6.txt","w"))==NULL){
 printf("Cannot open the file\n");
 exit(1);
 }

printf("積分区間aを入力してください。\n");
fprintf(fp,"積分区間aを入力してください。\n");
scanf("%f",&a);
printf("積分区間bを入力してください。\n");
fprintf(fp,"積分区間bを入力してください。\n");
scanf("%f",&b);
printf("分割数nの個数を入力してください。\n");
fprintf(fp,"分割数nの個数を入力してください。\n");
scanf("%d",&nnokosuu);
float n[nnokosuu];
for(j=1;j<nnokosuu+1;j++){
    printf("%d個めnの値を入力してください。\n",j);
    fprintf(fp,"%d個めnの値を入力してください。\n",j);
    scanf("%f",&n[j-1]);
}
printf("入力された値は以下の通りです。\na=%lf\nb=%lf\n",a,b);
for(j=1;j<nnokosuu+1;j++){
    printf("%d個目のn=%f\n",j,n[j-1]);
    fprintf(fp,"%d個目のn=%f\n",j,n[j-1]);
}


for(j=0;j<nnokosuu;j++){

    h=(b-a)/n[j];
    s=f_x(a)+f_x(b);
    x=a;
    i=1;
    do{

        x=x+h;
        if (i%2 == 0)
        {
            s=s+2*(f_x(x));
        }
        if (i%2 == 1)
        {
            s=s+4*(f_x(x));
        }

        i++;


        if(i>=n[j])break;

    }while(1);

    s=h/3*s;
    printf("n = %f: s = %f\n",n[j],s);
    fprintf(fp,"n = %f: s = %f\n",n[j],s);
}
    fclose(fp);
    return 0;
}