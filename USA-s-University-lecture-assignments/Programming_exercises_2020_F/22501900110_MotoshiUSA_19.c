#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double dv(double t, double v, double k)
{
    double m = 0.1;                //質量
    double g = 9.8;                //重力加速度
    double dv = g - ((k * v) / m); //運動方程式
    return (dv);
}

double runge(double t, double y, double h, double k)
{
    double k1, k2, k3, k4;
    double h2 = h / 2.0;
    k1 = dv(t, y, k);
    k2 = dv(t + h2, y + (h2 * k1), k);
    k3 = dv(t + h2, y + (h2 * k2), k);
    k4 = dv(t + h, y + (h * k3), k);
    y = y + (h / 6.0) * ((k1 + (2.0 * k2) + (2.0 * k3) + k4));
    return (y);
}

int main(void)
{
    double y = 0.0;
    double h = 0.0005;
    double t = 0.0;
    double k[4] = {0, 0.1, 0.15, 0.3};
    double a[4][11000];
    int i, j;
    FILE *fp, *fp_csv;
    if ((fp = fopen("22501900110_MotoshiUSA_19.txt", "w")) == NULL)
    {
        printf("Cannot open the file\n");
        exit(1);
    }
    if ((fp_csv = fopen("22501900110_MotoshiUSA_19.csv", "w")) == NULL)
    {
        printf("Cannot open the csvfile\n");
        exit(1);
    }

    for (j = 0; j < 4; j++)
    {
        for (i = 0; i < 11000; i++)
        {
            a[j][i] = 0;
        }
    }

    for (j = 0; j < 4; j++)
    {
        t = 0;
        y = 0;
        for (i = 0; i < 11000; i++)
        {
            t = t + h;
            y = runge(t, y, h, k[j]);
            a[j][i] = y;
        }
    }
    t = 0;
    fprintf(fp_csv, "x,k=0.01,k=0.1,k=0.15,k=0.3\n");
    fprintf(fp_csv, "0,0,0,0,0\n");
    for (i = 0; i < 11000; i++)
    {
        t = t + h;
        printf("%f  %f  %f  %f  %f\n", t, a[0][i], a[1][i], a[2][i], a[3][i]);
        fprintf(fp, "%f  %f  %f  %f  %f\n", t, a[0][i], a[1][i], a[2][i], a[3][i]);
        fprintf(fp_csv, "%f,%f,%f,%f,%f\n", t, a[0][i], a[1][i], a[2][i], a[3][i]);
    }
    fclose(fp);
    return 0;
}