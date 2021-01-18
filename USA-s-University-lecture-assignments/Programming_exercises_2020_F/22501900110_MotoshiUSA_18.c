/*課題16を適応させることを考えて配列aをa、解答に用いる係数aをAとして表記していく*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ERROR -1                         /* エラーリターン値 */
#define NORMAL 0                         /* ノーマルリターン値 */
#define mabs(x) (((x) > 0) ? (x) : -(x)) /* 絶対値を返すマクロ \
                                          */
#define DBL_EPSILON 0.0000000001
int Gauss_J(int, double *, double *);
int partial(int, int, double *, double *);
int mswap(double *, double *);

double x[] = {-4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
double y[] = {13.4, 7.2, 2.7, 1.2, 0.6, 3.1, 6.9, 12.5, 20.8, 31.7, 44.0};
double A[4], S[6], T[4], Y1[1101], Y2[1101], Y3[1101];

int main(void)
{
    int n , i, j, k = 0; /*変数宣言,領域確保*/
    double b[4], a[4 * 4];
    FILE *fp, *fp_csv;
    if ((fp = fopen("22501900110_MotoshiUSA_18.txt", "w")) == NULL)
    {
        printf("Cannot open the file\n");
        exit(1);
    }
    if ((fp_csv = fopen("22501900110_MotoshiUSA_18.csv", "w")) == NULL)
    {
        printf("Cannot open the csvfile\n");
        exit(1);
    }

for (i = 0; i < 4 * 4; i++) /*配列の初期化*/
        {
            a[i] = 0;
        }
        for (i = 0; i < 4; i++)
        {
            b[i] = 0;
        }
        for (i = 0; i < 4; i++)
        {
            A[i] = 0;
        }
        for (i = 0; i < 2 * 4 - 1; i++)
        {
            S[i] = 0;
        }
        for (i = 0; i < 4; i++)
        {
            T[i] = 0;
        }

    for (n = 2; n < 5; n++)
    {
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
        for (i = 0; i < (2 * n - 1); i++) /*配列S,Tを計算*/
        {
            for (j = 0; j < 11; j++)
            {
                S[i] = S[i] + pow(x[j], i);
                printf("S[%d]=%lf\n", i, S[i]);
            }
            printf("S[%d]=%lf\n", i, S[i]);
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < 11; j++)
            {
                T[i] = T[i] + y[j] * pow(x[j], i);
            }
            printf("T[%d]=%lf\n", i, T[i]);
        }
        for (i = 0; i < n; i++) /*配列S,Tを配列a,bに対応*/
        {
            for (j = 0; j < n; j++)
            {
                a[k] = S[i + j];
                printf("a[%d]=%lf\n", k, a[k]);
                k++;
            }
            b[i] = T[i];
            printf("b[%d]=%lf\n", i + 1, b[i]);
        }
        Gauss_J(i, a, b);              /*方程式の計算*/
        if (Gauss_J(i, a, b) == ERROR) /*計算中のエラー判定*/
        {
            printf("エラーを検出しました。プログラムを終了します。\n");
            fprintf(fp, "エラーを検出しました。プログラムを終了します。\n");
            exit(1);
        }
        if (n == 2) /*1次式の場合の値の代入*/
        {
            printf("1次の近似式\n");
            fprintf(fp, "1次の近似式\n");
            for (i = 0; i < n; i++)
            {
                T[i] = b[i];
            }
            printf("y=f(x)=");
            fprintf(fp, "y=f(x)=");
            for (i = 0; i < n; i++)
            {
                printf("+%lf*(x^%d)", b[i], i);
                fprintf(fp, "+%lf*(x^%d)", b[i], i);
            }
            for (i = 0; i < 1101; i++)
            {
                Y1[i] = b[0] * (pow(x[i], 0)) + b[1] * (pow(x[i], 1));
            }
        }
        if (n  == 3) /*2次式の場合の値の代入*/
        {
            printf("2次の近似式\n");
            fprintf(fp, "2次の近似式\n");
            for (i = 0; i < n; i++)
            {
                T[i] = b[i];
            }
            printf("y=f(x)=");
            fprintf(fp, "y=f(x)=");
            for (i = 0; i < n; i++)
            {
                printf("+%lf*(x^%d)", b[i], i);
                fprintf(fp, "+%lf*(x^%d)", b[i], i);
            }
            for (i = 0; i < 1101; i++)
            {
                Y2[i] = b[0] * (pow(x[i], 0)) + b[1] * (pow(x[i], 1)) + b[2] * (pow(x[i], 2));
            }
        }
        if (n == 4) /*3次式の場合の値の代入*/
        {
            printf("3次の近似式\n");
            fprintf(fp, "3次の近似式\n");
            for (i = 0; i < n; i++)
            {
                T[i] = b[i];
            }
            printf("y=f(x)=");
            fprintf(fp, "y=f(x)=");
            for (i = 0; i < n; i++)
            {
                printf("+%lf*(x^%d)", b[i], i);
                fprintf(fp, "+%lf*(x^%d)", b[i], i);
            }
            for (i = 0; i < 1101; i++)
            {
                Y3[i] = b[0] * (pow(x[i], 0)) + b[1] * (pow(x[i], 1)) + b[2] * (pow(x[i], 2)) + b[3] * (pow(x[i], 3));
            }
        }
    }

    /*結果表示*/
    fprintf(fp_csv, "x,与えられた値,1次の近似式,2次の近似式,3次の近似式");
    for (i = 0; i < 1101; i++)
    {
        if ((i == 0) || (i == 100) || (i == 200) || (i == 300) || (i == 400) || (i == 500) || (i == 600) || (i == 700) || (i == 800) || (i == 900) || (i == 1000) || (i == 1100))
        {
            fprintf(fp_csv, "%lf,%lf,%lf,%lf,%lf,%lf", -4 + 0.01 * i, y[i], Y1[i], Y2[i], Y3[i]);
        }
        else
        {
            fprintf(fp_csv, "%lf,,%lf,%lf,%lf,%lf", -4 + 0.01 * i, Y1[i], Y2[i], Y3[i]);
        }
    }
    fclose(fp);
    fclose(fp_csv);
    return 0;
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