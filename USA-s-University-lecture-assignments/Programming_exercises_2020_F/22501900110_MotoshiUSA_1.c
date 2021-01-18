#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void)
{ 
    double x[21];
    double y[21];
    int i=0;
    FILE *fp;
        if((fp=fopen("22501900110_MotoshiUSA_1.txt","w"))==NULL){
            printf("Cannot open the file\n");
            fprintf(fp,"Cannot open the file\n");
            exit(1);
        }

    x[0]=0;
    y[i]=3*pow(x[i],5)-5*pow(x[i],4)+14*pow(x[i],2)-6*x[i]+50;
    printf("x[%d]=%f\ny[%d]=%f\n",i,x[i],i,y[i]);
    fprintf(fp,"x[%d]=%f\ny[%d]=%f\n",i,x[i],i,y[i]);
    for (i = 1; i < 21; i++)
    {
        x[i]=x[i-1]+0.1;
        y[i]=3*pow(x[i],5)-5*pow(x[i],4)+14*pow(x[i],2)-6*x[i]+50;
        printf("x[%d]=%f\ny[%d]=%f\n",i,x[i],i,y[i]);
        fprintf(fp,"x[%d]=%f\ny[%d]=%f\n",i,x[i],i,y[i]);
    }
    fclose(fp);
    return 0;
}