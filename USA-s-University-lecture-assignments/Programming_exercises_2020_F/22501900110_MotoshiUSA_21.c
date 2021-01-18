#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void rungekuttaX(float *tx, float *x, float dt);
float functionX(float tx, float *x, int j);
void rungekuttaY(float *ty, float *y, float dt);
float functionY(float ty, float *y, int j);

#define ERROR -1                         /* エラーリターン値 */
#define NORMAL 0                         /* ノーマルリターン値 */
#define mabs(X) (((X) > 0) ? (X) : -(X)) /* 絶対値を返すマクロ \
                                          */
#define DBL_EPSILON 0.0000000001
int Gauss_J(int, double *, double *);
int partial(int, int, double *, double *);
int mswap(double *, double *);

double X[20];
double Y[20];
double A[3], S[5], T[3], accuracy = 0;

int main(void)
{
    float dt;
    int i = 0, n_int, initial_int, end_int; /*カウンタと表示の単純化*/
    float tx, ty, x[2], y[2], initial = 0, end = 0, n, v0 = 20;
    float txinstant[20], tyinstant[20];

    printf("積分区間は0~2です。\n");
    initial = 0;
    end = 2;
    initial_int = initial;
    end_int = end;
    printf("刻み幅dtは0.1です。\n");
    dt = 0.1;
    n = 2 / dt;
    n_int = n;
    float Xstorage[2][20], Ystorage[2][20];

    tx = 0;
    ty = 0;

    x[0] = 0;
    x[1] = v0 * cos((M_PI) / 6);
    y[0] = 0;
    y[1] = v0 * sin((M_PI) / 6);

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

    int j, k = 0;

    FILE *fp, *fp_csv;
    if ((fp = fopen("22501900110_MotoshiUSA_21.txt", "w")) == NULL)
    {
        printf("Cannot open the file\n");
        exit(1);
    }
    if ((fp_csv = fopen("22501900110_MotoshiUSA_21.csv", "w")) == NULL)
    {
        printf("Cannot open the csvfile\n");
        exit(1);
    }
    n = 2 + 1; //以下、ｎは分割の個数ではなく、（近似式の次数＋１）の値を示す。
    double b[3], a[9];

    for (i = 0; i < 20; i++) /*Xの入力*/
    {
        X[i] = Xstorage[0][i];
    }
    for (i = 0; i < 20; i++)
    {
        Y[i] = Ystorage[0][i];
    }

    for (i = 0; i < n * n; i++) /*配列の初期化*/
    {
        a[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        b[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        A[i] = 0;
    }
    for (i = 0; i < 2 * n - 1; i++)
    {
        S[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        T[i] = 0;
    }

    for (i = 0; i < 5; i++)
    {
        printf("s[%d]=%lf\n", i, S[i]);
    }
    for (i = 0; i < 3; i++)
    {
        printf("T[%d]=%lf\n", i, T[i]);
    }
    for (i = 0; i < 9; i++)
    {
        printf("a[%d]=%lf\n", i, a[i]);
    }
    for (i = 0; i < 3; i++)
    {
        printf("b[%d]=%lf\n", i, b[i]);
    }

    for (i = 0; i < (2 * n - 1); i++) /*配列S,Tを計算*/
    {
        for (j = 0; j < 20; j++)
        {
            S[i] = S[i] + pow(X[j], i);
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 20; j++)
        {
            T[i] = T[i] + Y[j] * pow(X[j], i);
        }
    }

    for (i = 0; i < n; i++) /*配列S,Tを配列a,bに対応*/
    {
        for (j = 0; j < n; j++)
        {
            a[k] = S[i + j];
            k++;
        }
        b[i] = T[i];
    }
    for (i = 0; i < 5; i++)
    {
        printf("s[%d]=%lf\n", i, S[i]);
    }
    for (i = 0; i < 3; i++)
    {
        printf("T[%d]=%lf\n", i, T[i]);
    }
    for (i = 0; i < 9; i++)
    {
        printf("a[%d]=%lf\n", i, a[i]);
    }
    for (i = 0; i < 3; i++)
    {
        printf("b[%d]=%lf\n", i, b[i]);
    }
    Gauss_J(i, a, b); /*方程式の計算*/

    if (Gauss_J(i, a, b) == ERROR) /*計算中のエラー判定*/
    {
        printf("エラーを検出しました。プログラムを終了します。\n");
        fprintf(fp, "エラーを検出しました。プログラムを終了します。\n");
        exit(1);
    }

    for (i = 0; i < 20; i++)
    {
        accuracy = accuracy + pow(Y[i] - (b[0] + b[1] * X[i] + b[2] * (pow(X[i], 2))), 2);
    }

    printf("結果は以下のようになります。\n"); /*結果表示*/

    printf("y=f(x)=");
    fprintf(fp, "y=f(x)=");
    for (i = 0; i < n; i++)
    {
        printf("+%lf*(x^%d)", b[i], i);
        fprintf(fp, "+%lf*(x^%d)", b[i], i);
    }
    printf("\n精度の確認：差分は%lfです。", accuracy);
    fprintf(fp, "\n精度の確認：差分は%lfです。", accuracy);

    for (i = 0; i < 2000; i++)
    {
        fprintf(fp_csv, "%lf,", i * 0.001);
        fprintf(fp_csv, "%lf\n", b[0] * (pow(i * 0.001, 0)) + b[1] * (pow(i * 0.001, 1)) + b[2] * (pow(i * 0.001, 2)));
    }

    n = 0.15;
    n = v0 * cos((M_PI) / 6) * n;
    printf("\nt=%fにおいてｙ＝%lf", n, b[0] * (pow(n, 0)) + b[1] * (pow(n, 1)) + b[2] * (pow(n, 2)));
    fprintf(fp, "\nt=%fにおいてｙ＝%lf", n, b[0] * (pow(n, 0)) + b[1] * (pow(n, 1)) + b[2] * (pow(n, 2)));
    n = 0.195;
    n = v0 * cos((M_PI) / 6) * n;
    printf("\nt=%fにおいてｙ＝%lf", n, b[0] * (pow(n, 0)) + b[1] * (pow(n, 1)) + b[2] * (pow(n, 2)));
    fprintf(fp, "\nt=%fにおいてｙ＝%lf", n, b[0] * (pow(n, 0)) + b[1] * (pow(n, 1)) + b[2] * (pow(n, 2)));

    fclose(fp);
    fclose(fp_csv);
    return 0;
}

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

/* ------------------------------------------------------ *
GJ法 : Gauss_J
*/
int Gauss_J(int n, double *a, double *b)
{
    int p, i, j, l;  /* カウンタ */
    double pivot, c; /* ピボット値 */

    for (p = 0; p < n; p++) /* 1行目から n行目まで繰り返す */
    {
        if ((partial(n, p, a, b)) == ERROR)
        { /* 部分選択の結果エラーなら ERROR(-1)を返す */
            return (ERROR);
        }
        pivot = a[p * n + p];   /* ピボットを取得する */
        for (i = p; i < n; i++) /* p行目の p列目から n列目まで*/
        {
            a[p * n + i] /= pivot; /* 係数行列の p行を pivotで割る */
        }
        b[p] /= pivot; /* 定数ベクトルの p行を pivotで割る */

        for (l = 0; l < n; l++) /* 1行目から n行目まで */
        {
            if (l != p) /* p行を除いて */
            {
                c = a[l * n + p]; /* 掃き出す */
                for (j = p; j < n; j++)
                {
                    a[l * n + j] -= c * a[p * n + j];
                }
                b[l] -= c * b[p];
            }
        }
    }
    return (NORMAL);
}
/* ------------------------------------------------------ *
 部分選択関数：partial
 * 与えられた行列の p行目以降の p列を部分選択する。
 * 選択された要素が DBL_EPSILON より小さければ，
 * ERROR (-1) を，そうでなければ NORMAL (0) を返す。
 */
int partial(int n, int p, double *a, double *b)
{
    int l, m, max;
    /*l:カウンタ max:絶対値が最大の係数をもつ行*/
    double pivot; /* ピボット */

    for (l = max = p, pivot = a[p * n + p]; l < n; l++)
    { /* n行目までで p列の絶対値が最大のものを選ぶ */
        if (mabs(pivot) < mabs(a[l * n + p]))
        {
            max = l;
            pivot = a[l * n + p];
        }
    }
    if (mabs(pivot) < DBL_EPSILON) /* 選ばれたピボットが */
    {                              /* 小なら ERROR(-1)を返す */
        return (ERROR);
    }
    if (p != max) /* 選ばれた行が p行でなければ，行の交換を行う */
    {
        for (m = 0; m < n; m++) /* 係数行列の pと maxを交換 */
        {
            mswap(&a[p * n + m], &a[max * n + m]);
        }
        mswap(&b[p], &b[max]); /* 定数の p行と max行を交換 */
    }
    return (NORMAL);
}
/* ------------------------------------------------------ *
 double型の値を交換する関数：mswap
 * 与えられた値の入れ替えを行う。
 */
int mswap(double *a, double *b)
{
    double temp;

    temp = *a;
    *a = *b;
    *b = temp;

    return (NORMAL);
}