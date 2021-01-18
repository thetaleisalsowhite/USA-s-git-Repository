#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double sin(double x);
double cos(double x);
double tan(double x);



    float fx, fy; /*変数宣言*/
    float dt;

    float xwork[2], k0x[2], k1x[2], k2x[2], k3x[2]; /*ルンゲクッタ法で用いる変数*/
    float ywork[2], k0y[2], k1y[2], k2y[2], k3y[2]; /*ルンゲクッタ法で用いる変数*/

    int i, j, n_int; /*カウンタと表示の単純化*/
    float ty,tx, a, b, x[2], y[2], Xstorage[2][200], Ystorage[2][200], v0 = 20, T0 = 0, T = 2, n, g = -9.8;

    void rungekuttaX(float *tx, float *x, float dt);
    void rungekuttaY(float *ty, float *y, float dt);
    float functionX(float *x, int j);
    float functionY(float *y, int j);

    float functionX(float *x, int j)
    { /*右辺を求める関数*/
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
    float functionY(float *y, int j)
    { /*右辺を求める関数*/
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
    { /*ルンゲクッタ法*/

        for (j = 0; j < 2; j++)
        { /*k1の計算とxの変化量の記憶*/
            k0x[j] = dt * functionX(x, j);
        }
        for (j = 0; j < 2; j++)
        {
            xwork[j] = x[j] + 0.5 * k0x[j];
        }
        for (j = 0; j < 2; j++)
        { /*k2の計算とxの変化量の記憶*/
            k1x[j] = dt * functionX(xwork, j);
        }
        for (j = 0; j < 2; j++)
        {
            xwork[j] = x[j] + 0.5 * k1x[j];
        }
        for (j = 0; j < 2; j++)
        { /*k3の計算とxの変化量の記憶*/
            k2x[j] = dt * functionX(xwork, j);
        }
        for (j = 0; j < 2; j++)
        {
            xwork[j] = x[j] + k2x[j];
        }
        for (j = 0; j < 2; j++)
        { /*k4の計算とxの計算*/
            k3x[j] = dt * functionX(xwork, j);
        }
        for (j = 0; j < 2; j++)
        {
            x[j] = x[j] + (k0x[j] + 2 * k1x[j] + 2 * k2x[j] + k3x[j]) / 6;
        }
        *tx = *tx + dt;
    }

    void rungekuttaY(float *ty, float *y, float dt)
    { /*ルンゲクッタ法*/

        for (j = 0; j < 2; j++)
        { /*k1の計算とyの変化量の記憶*/
            k0y[j] = dt * functionY(y, j);
        }
        for (j = 0; j < 2; j++)
        {
            ywork[j] = y[j] + 0.5 * k0y[j];
        }
        for (j = 0; j < 2; j++)
        { /*k2の計算とyの変化量の記憶*/
            k1y[j] = dt * functionY(ywork, j);
        }
        for (j = 0; j < 2; j++)
        {
            ywork[j] = y[j] + 0.5 * k1y[j];
        }
        for (j = 0; j < 2; j++)
        { /*k3の計算とyの変化量の記憶*/
            k2y[j] = dt * functionY(ywork, j);
        }
        for (j = 0; j < 2; j++)
        {
            ywork[j] = y[j] + k2y[j];
        }
        for (j = 0; j < 2; j++)
        { /*k4の計算とyの計算*/
            k3y[j] = dt * functionY(ywork, j);
        }
        for (j = 0; j < 2; j++)
        {
            y[j] = y[j] + (k0y[j] + 2 * k1y[j] + 2 * k2y[j] + k3y[j]) / 6;
        }
        *ty = *ty + dt;
    }

int main(void)
{
    FILE *fp;
    if ((fp = fopen("22501900110_MotoshiUSA_21.txt", "w")) == NULL)
    {
        printf("Cannot open the file\n");
        exit(1);
    }

    printf("積分区間は0～2です。\n");  /*積分範囲の確認*/
    printf("刻み幅dtは0.005です。\n"); /*刻み幅の確認*/
    dt = 0.05;
    n = 1 / dt;
    n_int = n;

    tx = 0;
    ty=0;
    x[0] = 0; /*初期値の設定*/
    x[1] = v0 * cos(30);
    y[0] = 0; /*初期値の設定*/
    y[1] = v0 * sin(30);

    printf("入力された値は以下の通りです。\n積分区間は[%lf,%lf]\n", T0, T); /*入力事項の確認*/

    for (i = 0; i < n_int; i++)
    {
        Xstorage[0][i] = 0;
        Xstorage[1][i] = 0;
        Ystorage[0][i] = 0;
        Ystorage[1][i] = 0;
    }

    for (i = 0; i < n_int; i++)
    {
        rungekuttaX(&tx, x, dt);
        Xstorage[0][i] = x[0];
        Xstorage[1][i] = x[1];
    }

    for (i = 0; i < n_int; i++)
    {
        rungekuttaY(&ty, y, dt);
        Ystorage[0][i] = y[0];
        Ystorage[1][i] = y[1];
    }
    for (i = 0; i < n_int; i++)
    {
        printf("t=%lf\tx[1][%d]=%lf\tx[2][%d]=%lf\ty[1][%d]=%lf\ty[2][%d]=%lf\n", i * 0.005 + 0.005, i, Xstorage[0][i], i, Xstorage[1][i], i, Ystorage[0][i], i, Xstorage[1][i]);
    }

    fclose(fp);
    return 0;
}