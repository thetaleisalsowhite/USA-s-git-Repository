#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float f; /*変数宣言*/
float h;
int j = 0;

float ywork[2], k0[2], k1[2], k2[2], k3[2]; /*ルンゲクッタ法で用いる変数*/

int i = 0, nnokosuu_int; /*カウンタと表示の単純化*/
float x, y[2], initial = 0, end = 0, nnokosuu;

void rungekutta(float *x, float *y, float h); /*関数の宣言*/
float function(float x, float *y, int j);

float function(float x, float *y, int j) /*二階微分*/
{
  double I; //変数宣言
  double ddt;
  double E = 206 * pow(10, 9);
  double W = 30;
  double b = 0.1;
  double H = 0.005;
  double l = 0.5;

  I = b * pow(H, 3) / 12;
  ddt = W / E / I;
  if (j == 0)
  {
    f = y[1];
  }
  else
  {
    f = ddt * (l - x);
  }
  return f;
}
void rungekutta(float *x, float *y, float h) /*ルンゲクッタ法*/
{

  for (j = 0; j < 2; j++)
  { /*k1の計算とyの変化量の記憶*/
    k0[j] = h * function(*x, y, j);
  }
  for (j = 0; j < 2; j++)
  {
    ywork[j] = y[j] + 0.5 * k0[j];
  }
  for (j = 0; j < 2; j++)
  { /*k2の計算とyの変化量の記憶*/
    k1[j] = h * function(*x + 0.5 * h, ywork, j);
  }
  for (j = 0; j < 2; j++)
  {
    ywork[j] = y[j] + 0.5 * k1[j];
  }
  for (j = 0; j < 2; j++)
  { /*k3の計算とyの変化量の記憶*/
    k2[j] = h * function(*x + 0.5 * h, ywork, j);
  }
  for (j = 0; j < 2; j++)
  {
    ywork[j] = y[j] + k2[j];
  }
  for (j = 0; j < 2; j++)
  { /*k4の計算とyの計算*/
    k3[j] = h * function(*x + h, ywork, j);
  }
  for (j = 0; j < 2; j++)
  {
    y[j] = y[j] + (k0[j] + 2 * k1[j] + 2 * k2[j] + k3[j]) / 6;
  }
  *x = *x + h;
  printf("y1=%f y2=%f\n", y[0], y[1]);
}

int main(void)
{
  /*ファイル定義*/
  FILE *fp;
  if ((fp = fopen("22501900110_MotoshiUSA_20.txt", "w")) == NULL)
  {
    printf("Cannot open the file\n");
    exit(1);
  }
  FILE *fp_csv;
  if ((fp_csv = fopen("22501900110_MotoshiUSA_20.csv", "w")) == NULL)
  {
    printf("Cannot open the file\n");
    exit(1);
  }
  /*積分範囲の確認*/
  printf("積分区間は０～0.5です。\n");
  fprintf(fp, "積分区間は０～0.5です。\n");
  initial = 0;
  end = 0.5;
  /*刻み幅の確認*/
  printf("刻み幅hは0.1です。\n");
  fprintf(fp, "刻み幅hは0.1です。\n");
  h = 0.001;
  nnokosuu = (end - initial) / h;
  nnokosuu_int = nnokosuu;

  /*初期値の設定*/
  x = 0;
  y[0] = 0;
  y[1] = 0;

  /*入力事項の確認*/
  printf("入力された値は以下の通りです。\n積分区間は[%lf,%lf]\n", initial, end);
  printf("h=%lf\nn=%ld\nx_0=%lf y[1]=%lf y[2]=%lf\n", h, nnokosuu_int, x, y[0], y[1]);
  fprintf(fp, "入力された値は以下の通りです。\n積分区間は[%lf,%lf]\n", initial, end);
  fprintf(fp, "h=%lf\nn=%ld\nx_0=%lf y[1]=%lf y[2]=%lf\n", h, nnokosuu_int, x, y[0], y[1]);
  fprintf(fp_csv, "y1=%lf y2=%lf\n", y[0], y[1]);

  /*計算と結果の出力*/
  for (i = 0; i < nnokosuu; i++)
  {
    rungekutta(&x, y, h);
    fprintf(fp, "y1=%lf y2=%lf\n", y[0], y[1]);
    printf("n=%d  x=%lf  y[1]=%lf y[2]=%lf\n", i + 1, x, y[0], y[1]);
    fprintf(fp, "n=%d  x=%lf  y[1]=%lf y[2]=%lf\n", i + 1, x, y[0], y[1]);
    fprintf(fp_csv, "%lf,%lf,%lf\n", x, y[0], y[1]);
  }
  fclose(fp);
  fclose(fp_csv);
  return 0;
}