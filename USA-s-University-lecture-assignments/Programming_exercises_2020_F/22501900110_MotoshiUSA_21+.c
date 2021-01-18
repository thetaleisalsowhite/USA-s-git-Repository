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
        fx = 0;
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
        fy = -9.8;
    }
    return fy;
}
void rungekuttaX(float *tx, float *x, float dt)
{                                                   /*ルンゲクッタ法*/
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
}
void rungekuttaY(float *ty, float *y, float dt)
{                                                   /*ルンゲクッタ法*/
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
}

int main(void)
{
    float dt;
    int i = 0, n_int, initial_int, end_int; /*カウンタと表示の単純化*/
    float tx, ty, x[2], y[2], initial = 0, end = 0, n, v0 = 20;
    float txinstant[420], tyinstant[420];

    printf("積分区間は０～2.1です。\n");
    initial = 0;
    end = 2.1;
    initial_int = initial;
    end_int = end;
    printf("刻み幅dtは0.005です。\n");
    dt = 0.005;
    n = 2.1 / dt;
    n_int = n;
    float Xstorage[2][420], Ystorage[2][420];

    tx = 0;
    ty = 0;

    x[0] = 0;
    x[1] = v0 * cos((M_PI)/6);
    y[0] = 0;
    y[1] = v0 * sin((M_PI)/6);

    for (i = 0; i < n_int; i++)
    {
        Xstorage[0][i] = 0;
        Xstorage[1][i] = 0;
        Ystorage[0][i] = 0;
        Ystorage[1][i] = 0;
        txinstant[i] = 0;
        tyinstant[i] = 0;
    }

    printf("入力された値は以下の通りです。\n積分区間は[%d,%d]\n", initial_int, end_int); /*入力事項の確認*/
    printf("dt=%f\tn=%d\ttx_0=%f\tx[0]=%f\tx[1]=%f\tty_0=%f\ty[0]=%f\ty[1]=%f\n", dt, n_int, tx, x[0], x[1], ty, y[0], y[1]);
    for (i = 0; i < n; i++)
    {
        rungekuttaX(&tx, x, dt);
        Xstorage[0][i] = x[0];
        Xstorage[1][i] = x[1];
        txinstant[i] = tx;
    }
    for (i = 0; i < n; i++)
    {
        rungekuttaY(&ty, y, dt);
        Ystorage[0][i] = y[0];
        Ystorage[1][i] = y[1];
        tyinstant[i] = ty;
    }
    for (i = 0; i < n; i++)
    {
        printf("n=%d\tt=%f\tx[0]=%f\tx[1]=%f\ty[0]=%f\ty[1]=%f\n", i + 1, txinstant[i], Xstorage[0][i], Xstorage[1][i], Ystorage[0][i], Ystorage[1][i]); /*結果の出力*/
    }
    return 0;
}