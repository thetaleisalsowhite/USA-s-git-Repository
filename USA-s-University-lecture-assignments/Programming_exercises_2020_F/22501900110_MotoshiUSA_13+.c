#include <stdio.h>
#include <math.h>

float h;


float x,y[2],a=0,b=0,nnokosuu;

void rungekutta(float *x,float *y,float h);
float function(float x,float *y,int j);

float function(float x,float *y,int j){       /*右辺を求める関数*/
float f;                                       /*変数宣言*/
if(j==0){
    f=y[1];
  }else{
    f=y[1]*x+y[0];
  }
  return f;
} 

void rungekutta(float *x,float *y,float h){   /*ルンゲクッタ法*/
int j=0;

float ywork[2],k0[2],k1[2],k2[2],k3[2];/*ルンゲクッタ法で用いる変数*/
  for(j=0;j<2;j++){                           /*k1の計算とyの変化量の記憶*/
    k0[j]=h*function(*x,y,j);
  }
  for(j=0;j<2;j++){
    ywork[j]=y[j]+0.5*k0[j];
  }
  for(j=0;j<2;j++){                           /*k2の計算とyの変化量の記憶*/
    k1[j]=h*function(*x+0.5*h,ywork,j);        
  }
  for(j=0;j<2;j++){
    ywork[j]=y[j]+0.5*k1[j];
  }
  for(j=0;j<2;j++){                           /*k3の計算とyの変化量の記憶*/
    k2[j]=h*function(*x+0.5*h,ywork,j);
  }
  for(j=0;j<2;j++){
    ywork[j]=y[j]+k2[j];
  }
  for(j=0;j<2;j++){                           /*k4の計算とyの計算*/
    k3[j]=h*function(*x+h,ywork,j);
  }
  for(j=0;j<2;j++){
    y[j]=y[j]+( k0[j]+2*k1[j]+2*k2[j]+k3[j])/6;
  }
  *x=*x+h;
  printf("y1=%f y2=%f\n",y[0],y[1]);
}

int main(void) {
  
int i=0,nnokosuu_int,a_int,b_int; /*カウンタと表示の単純化*/

printf("積分区間は０～1です。\n");  /*積分範囲の確認*/
a=0;
b=1;
a_int=a;
b_int=b;
printf("刻み幅hは0.1です。\n");    /*刻み幅の確認*/
h=0.1;
nnokosuu=1/h;
nnokosuu_int=nnokosuu;

x=0;
y[0]=1;   /*初期値の設定*/
y[1]=1;

printf("入力された値は以下の通りです。\n積分区間は[%d,%d]\n",a_int,b_int);    /*入力事項の確認*/
printf("h=%f\nn=%d\nx_0=%f y[1]=%f y[2]=%f\n",h,nnokosuu_int,x,y[0],y[1]);


for(i=0;i<nnokosuu;i++){
  rungekutta(&x,y,h);
  printf("n=%d  x=%f  y[1]=%f y[2]=%f\n",i+1,x,y[0],y[1]);/*結果の出力*/
  }
    return 0;
}