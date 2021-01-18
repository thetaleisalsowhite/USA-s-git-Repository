#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float f; /*変数宣言*/
float h;
int j = 0;

float ywork[2], k0[2], k1[2], k2[2], k3[2]; /*ルンゲクッタ法で用いる変数*/

int i = 0, n_int, a_int, b_int; /*カウンタと表示の単純化*/
float t, y[2],Ystorage[2][10], a = 0, b = 0, n;

void rungekutta(float *t, float *y, float h);
float function(float t, float *y, int j);

float function(float t, float *y, int j)
{ /*右辺を求める関数*/
  if (j == 0)
  {
    f = y[1];
  }
  else
  {
    f = y[1] * t + y[0];
  }
  return f;
}

void rungekutta(float *t, float *y, float h)
{ /*ルンゲクッタ法*/

  for (j = 0; j < 2; j++)
  { /*k1の計算とyの変化量の記憶*/
    k0[j] = h * function(*t, y, j);
  }
  for (j = 0; j < 2; j++)
  {
    ywork[j] = y[j] + 0.5 * k0[j];
  }
  for (j = 0; j < 2; j++)
  { /*k2の計算とyの変化量の記憶*/
    k1[j] = h * function(*t + 0.5 * h, ywork, j);
  }
  for (j = 0; j < 2; j++)
  {
    ywork[j] = y[j] + 0.5 * k1[j];
  }
  for (j = 0; j < 2; j++)
  { /*k3の計算とyの変化量の記憶*/
    k2[j] = h * function(*t + 0.5 * h, ywork, j);
  }
  for (j = 0; j < 2; j++)
  {
    ywork[j] = y[j] + k2[j];
  }
  for (j = 0; j < 2; j++)
  { /*k4の計算とyの計算*/
    k3[j] = h * function(*t + h, ywork, j);
  }
  for (j = 0; j < 2; j++)
  {
    y[j] = y[j] + (k0[j] + 2 * k1[j] + 2 * k2[j] + k3[j]) / 6;
  }
  *t = *t + h;
}

int main(void)
{
  FILE *fp;
  if ((fp = fopen("22501900110_MotoshiUSA_13+.txt", "w")) == NULL)
  {
    printf("Cannot open the file\n");
    exit(1);
  }

  printf("積分区間は０～1です。\n"); /*積分範囲の確認*/
  fprintf(fp, "積分区間は０～1です。\n");
  a = 0;
  b = 1;
  a_int = a;
  b_int = b;
  printf("刻み幅hは0.1です。\n"); /*刻み幅の確認*/
  fprintf(fp, "刻み幅hは0.1です。\n");
  h = 0.1;
  n = 1 / h;
  n_int = n;

  t = 0;
  y[0] = 1; /*初期値の設定*/
  y[1] = 1;

  printf("入力された値は以下の通りです。\n積分区間は[%d,%d]\n", a_int, b_int); /*入力事項の確認*/
  printf("h=%f\nn=%d\nx_0=%f y[1]=%f y[2]=%f\n", h, n_int, t, y[0], y[1]);
  fprintf(fp, "入力された値は以下の通りです。\n積分区間は[%d,%d]\n", a_int, b_int);
  fprintf(fp, "h=%f\nn=%d\nx_0=%f y[1]=%f y[2]=%f\n", h, n_int, t, y[0], y[1]);

  for (i = 0; i < n; i++)
  {
    rungekutta(&t, y, h);
    Ystorage[2][i]=y[i];
  }
    for (i = 0; i < n; i++)
  {
    printf("n=%d\tt=%lf\ty[1][%d]=%lf\ty[2][%d]=%lf\n", i + 1, t,i, y[0],i, y[1]); /*結果の出力*/
  }
  fclose(fp);
  return 0;
}