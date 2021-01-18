/*-----------------------------------------------
 * Gauss-Jordan法で，行列・ベクトルで与えられた連立
 * 一次方程式を解く。部分選択を使用して，ピボットを
 * 選択するが，選択できなかった場合には ERROR (-1)を，
 * 正常終了の場合には NORMAL (0) を返す。
 */
#include <stdio.h>
#include <stdlib.h>
#define ERROR -1                         /* エラーリターン値 */
#define NORMAL 0                         /* ノーマルリターン値 */
#define mabs(x) (((x) > 0) ? (x) : -(x)) /* 絶対値を返すマクロ \
                                          */
#define DBL_EPSILON 0.0000000001
int Gauss_J(int, double *, double *);
int partial(int, int, double *, double *);
int mswap(double *, double *);

int main(void)
{

    int n = 0, i, j, k = 0; /*変数宣言,領域確保*/
    FILE *fp;
    if((fp=fopen("22501900110_MotoshiUSA_16.txt","w"))==NULL){
     printf("Cannot open the file\n");
     exit(1);
    }
    printf("変数の数は幾つですか？\n");
    fprintf(fp,"変数の数は幾つですか？\n");
    scanf("%d", &n);
    fprintf(fp,"%d\n",n);
    double b[n], a[n * n];

    for (i = 0; i < n * n; i++) /*配列の初期化*/
    {
        a[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        b[i] = 0;
    }

    printf("係数を値を入力してください。\n"); /*係数取得とその確認*/
    for (i = 0; i < n * n; i++)
    {
        scanf("%d", &j);
        a[i] = j;
        printf("%lfと入力されました\n", a[i]);
    }

    printf("右辺の値を値を入力してください。\n"); /*係数取得とその確認*/
    for (i = 0; i < n; i++)
    {
        scanf("%d", &j);
        b[i] = j;
        printf("%lfと入力されました\n", b[i]);
    }

    printf("入力された値は以下の通りです\n", n); /**/
    fprintf(fp,"入力された値は以下の通りです\n", n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            printf("%lfx_%d+", a[k], j);
            fprintf(fp,"%lfx_%d+", a[k], j);
            k++;
        }
        printf("%lfx_%d=", a[k], j + 1);
        fprintf(fp,"%lfx_%d=", a[k], j + 1);
        k++;
        printf("%lf\n", b[i]);
        fprintf(fp,"%lf\n", b[i]);
    }

    Gauss_J(i, a, b); /*方程式の計算*/

    if (Gauss_J(i, a, b) == ERROR)
    {
        printf("エラーを検出しました。プログラムを終了します。/n");
        fprintf(fp,"エラーを検出しました。プログラムを終了します。/n");
        exit(1);
    }
    printf("結果は以下のようになります。\n");
    for (i = 0; i < n; i++)
    {
        printf("x_%d=%f\n", i, b[i]);
        fprintf(fp,"x_%d=%f\n", i, b[i]);
    }
    fclose(fp);
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