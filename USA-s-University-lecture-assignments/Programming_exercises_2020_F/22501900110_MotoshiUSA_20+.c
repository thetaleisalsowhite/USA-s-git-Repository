#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void rungekuttaX(float *tx, float *x, float dt);
float functionX(float tx, float *x, int j);
void rungekuttaY(float *ty, float *y, float dt);
float functionY(float ty, float *y, int j);

float functionX(float tx, float *x, int j)
{ /*右辺を求める関数*/

  float fx, fy; /*変数宣言*/
  if (j == 0)
  {
    fx = x[1];
  }
  else
  {
    fx = x[1] * tx + x[0];
  }
  return fx;
}
float functionY(float ty, float *y, int j)
{ /*右辺を求める関数*/

  float fx, fy; /*変数宣言*/
  if (j == 0)
  {
    fy = y[1];
  }
  else
  {
    fy = y[1] * ty + y[0];
  }
  return fy;
}
void rungekuttaX(float *tx, float *x, float dt)
{                                                 /*ルンゲクッタ法*/
  float xwork[2], k0x[2], k1x[2], k2x[2], k3x[2]; /*ルンゲクッタ法で用いる変数*/
  int j = 0;
  for (j = 0; j < 2; j++)
  { /*k1の計算とyの変化量の記憶*/
    k0x[j] = dt * functionX(*tx, x, j);
  }
  for (j = 0; j < 2; j++)
  {
    xwork[j] = x[j] + 0.5 * k0x[j];
  }
  for (j = 0; j < 2; j++)
  { /*k2の計算とyの変化量の記憶*/
    k1x[j] = dt * functionX(*tx + 0.5 * dt, xwork, j);
  }
  for (j = 0; j < 2; j++)
  {
    xwork[j] = x[j] + 0.5 * k1x[j];
  }
  for (j = 0; j < 2; j++)
  { /*k3の計算とyの変化量の記憶*/
    k2x[j] = dt * functionX(*tx + 0.5 * dt, xwork, j);
  }
  for (j = 0; j < 2; j++)
  {
    xwork[j] = x[j] + k2x[j];
  }
  for (j = 0; j < 2; j++)
  { /*k4の計算とyの計算*/
    k3x[j] = dt * functionX(*tx + dt, xwork, j);
  }
  for (j = 0; j < 2; j++)
  {
    x[j] = x[j] + (k0x[j] + 2 * k1x[j] + 2 * k2x[j] + k3x[j]) / 6;
  }
  *tx = *tx + dt;
  printf("x1=%f x2=%f\n", x[0], x[1]);
}
void rungekuttaY(float *ty, float *y, float dt)
{                                                 /*ルンゲクッタ法*/
  float ywork[2], k0y[2], k1y[2], k2y[2], k3y[2]; /*ルンゲクッタ法で用いる変数*/
  int j = 0;
  for (j = 0; j < 2; j++)
  { /*k1の計算とyの変化量の記憶*/
    k0y[j] = dt * functionY(*ty, y, j);
  }
  for (j = 0; j < 2; j++)
  {
    ywork[j] = y[j] + 0.5 * k0y[j];
  }
  for (j = 0; j < 2; j++)
  { /*k2の計算とyの変化量の記憶*/
    k1y[j] = dt * functionY(*ty + 0.5 * dt, ywork, j);
  }
  for (j = 0; j < 2; j++)
  {
    ywork[j] = y[j] + 0.5 * k1y[j];
  }
  for (j = 0; j < 2; j++)
  { /*k3の計算とyの変化量の記憶*/
    k2y[j] = dt * functionY(*ty + 0.5 * dt, ywork, j);
  }
  for (j = 0; j < 2; j++)
  {
    ywork[j] = y[j] + k2y[j];
  }
  for (j = 0; j < 2; j++)
  { /*k4の計算とyの計算*/
    k3y[j] = dt * functionY(*ty + dt, ywork, j);
  }
  for (j = 0; j < 2; j++)
  {
    y[j] = y[j] + (k0y[j] + 2 * k1y[j] + 2 * k2y[j] + k3y[j]) / 6;
  }
  *ty = *ty + dt;
  printf("y1=%f y2=%f\n", y[0], y[1]);
}

int main(void)
{
  float dt;
  int i = 0, n_int, initial_int, end_int; /*カウンタと表示の単純化*/
  float tx, ty, x[2], y[2], initial = 0, end = 0, n;

  printf("積分区間は０～1です。\n"); /*積分範囲の確認*/
  initial = 0;
  end = 1;
  initial_int = initial;
  end_int = end;
  printf("刻み幅dtは0.1です。\n"); /*刻み幅の確認*/
  dt = 0.1;
  n = 1 / dt;
  n_int = n;

  tx = 0;
  ty = 0;
  x[0] = 1; /*初期値の設定*/
  x[1] = 1;
  y[0] = 1; /*初期値の設定*/
  y[1] = 1;

  printf("入力された値は以下の通りです。\n積分区間は[%d,%d]\n", initial_int, end_int); /*入力事項の確認*/
  printf("dt=%f\nn=%d\ntx_0=%f x[1]=%f x[2]=%f\nty_0=%f y[1]=%f y[2]=%f\n", dt, n_int, tx, x[0], x[1], ty, y[0], y[1]);

  for (i = 0; i < n; i++)
  {
    rungekuttaX(&tx, x, dt);
    printf("n=%d  tx=%f  x[1]=%f x[2]=%f\n", i + 1, tx, x[0], x[1]); /*結果の出力*/
  }
  for (i = 0; i < n; i++)
  {
    rungekuttaY(&ty, y, dt);
    printf("n=%d  ty=%f  y[1]=%f y[2]=%f\n", i + 1, ty, y[0], y[1]); /*結果の出力*/
  }
  return 0;
}