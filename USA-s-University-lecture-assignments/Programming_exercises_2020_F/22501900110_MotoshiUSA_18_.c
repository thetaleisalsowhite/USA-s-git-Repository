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

double x[11] ;
double y[11] ;
double A[4], S[6], T[4] ,accuracy=0;

int main(void)
{
    int n = 0, i, j, k = 0; /*変数宣言,領域確保*/

    FILE *fp, *fp_csv;
    if ((fp = fopen("22501900110_MotoshiUSA_18_.txt", "w")) == NULL)
    {
        printf("Cannot open the file\n");
        exit(1);
    }
    if ((fp_csv = fopen("22501900110_MotoshiUSA_18_.csv", "w")) == NULL)
    {
        printf("Cannot open the csvfile\n");
        exit(1);
    }

    printf("何次式で近似しますか？\n");
    fprintf(fp, "何次式で近似しますか？\n");
    scanf("%d", &n);
    fprintf(fp, "%d\n", n);
    n++;
    double b[n], a[n * n];

    printf("xの値を入力してください。\n");
    for (i = 0; i < 11; i++) /*与えられた数値の入力*/
    {
        scanf("%lf",&x[i]);
    }
    printf("yの値を入力してください。\n");
    for (i = 0; i < 11; i++) 
    {
        scanf("%lf",&y[i]);
    }
    
    printf("与えられた座標は以下のものです\n");
    for (i = 0; i < 11; i++) /*与えられた数値の確認*/
    {
        printf("%lf, ",x[i]);
    }
    printf("\n");
    for (i = 0; i < 11; i++) 
    {
        printf("%lf, ",y[i]);
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

    Gauss_J(i, a, b); /*方程式の計算*/

    if (Gauss_J(i, a, b) == ERROR) /*計算中のエラー判定*/
    {
        printf("エラーを検出しました。プログラムを終了します。\n");
        fprintf(fp, "エラーを検出しました。プログラムを終了します。\n");
        exit(1);
    }

    printf("結果は以下のようになります。\n"); /*精度の計算*/
    if (n - 1 == 1)                           /*1次式の精度の計算*/
    {
        for (i = 0; i < 11; i++)
        {
            accuracy=accuracy+pow(y[i]-(b[0]+b[1]*x[i]), 2);
        }
    }
    if (n - 1 == 2) /*2次式の精度の計算*/
    {
        for (i = 0; i < 11; i++)
        {
            accuracy=accuracy+pow(y[i]-(b[0]+b[1]*x[i]+b[2]*(pow(x[i],2))), 2);
        }
    }
    if (n - 1 == 3) /*3次式の精度の計算*/
    {
        for (i = 0; i < 11; i++)
        {
            accuracy=accuracy+pow(y[i]-(b[0]+b[1]*x[i]+b[2]*(pow(x[i],2))+b[3]*(pow(x[i],3))), 2);
        }
    }

    printf("結果は以下のようになります。\n"); /*結果表示*/
    if (n - 1 == 1)                           /*1次式の結果表示*/
    {
        for (i = 0; i < n; i++)
        {
            printf("A_%d=%f\n", i, b[i]);
            fprintf(fp, "A_%d=%f\n", i, b[i]);
        }

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
            printf("\n精度の確認：差分は%lfです。",  accuracy);
            fprintf(fp, "\n精度の確認：差分は%lfです。", accuracy);

        for (i = 0; i < 11; i++)
        {
            fprintf(fp_csv, "%lf,", x[i]);
            fprintf(fp_csv, "%lf,", y[i]);
            fprintf(fp_csv, "%lf\n", b[0] * (pow(x[i], 0)) + b[1] * (pow(x[i], 1)));
        }
    }
    if (n - 1 == 2) /*2次式の結果表示*/
    {
        for (i = 0; i < n; i++)
        {
            printf("A_%d=%f\n", i, b[i]);
            fprintf(fp, "A_%d=%f\n", i, b[i]);
        }

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
            printf("\n精度の確認：差分は%lfです。",  accuracy);
            fprintf(fp, "\n精度の確認：差分は%lfです。", accuracy);

        for (i = 0; i < 11; i++)
        {
            fprintf(fp_csv, "%lf,", x[i]);
            fprintf(fp_csv, "%lf,", y[i]);
            fprintf(fp_csv, "%lf\n", b[0] * (pow(x[i], 0)) + b[1] * (pow(x[i], 1)) + b[2] * (pow(x[i], 2)));
        }
    }
    if (n - 1 == 3) /*3次式の結果表示*/
    {
        for (i = 0; i < n; i++)
        {
            printf("A_%d=%f\n", i, b[i]);
            fprintf(fp, "A_%d=%f\n", i, b[i]);
        }

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
            printf("\n精度の確認：差分は%lfです。",  accuracy);
            fprintf(fp, "\n精度の確認：差分は%lfです。", accuracy);

        for (i = 0; i < 11; i++)
        {
            fprintf(fp_csv, "%lf,", x[i]);
            fprintf(fp_csv, "%lf,", y[i]);
            fprintf(fp_csv, "%lf\n", b[0] * (pow(x[i], 0)) + b[1] * (pow(x[i], 1)) + b[2] * (pow(x[i], 2)) + b[3] * (pow(x[i], 3)));
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