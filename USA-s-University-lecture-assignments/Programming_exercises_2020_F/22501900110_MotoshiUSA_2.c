#include <stdio.h>
#include <stdlib.h>

int main (void)
{

  int i,j,k,l=3,n,m;

    printf("n×3行列Aのnの値を入力します\n");
        scanf("%d",&n);


        printf("3×m行列Bのmの値を入力します\n");
        scanf("%d",&m);



if(n<m){
    if(m>3){
        l=m;
    }
}
if(m<n){
    if(n>3){
        l=n;
    }
}

int data[l+1][l+1];
int A[n][3],B[3][m],C[n][m];
FILE *fp1,*fp2,*fp3;

fp1=fopen("a.txt","r");
fp2=fopen("b.txt","r");
fp3=fopen("c.txt","w");

if(fp1==NULL){
printf("ファイルがありません\n");
return 0;
}

for(i=0;i<n;i++){
    for(j=0;j<3;j++){
        fscanf(fp1,"%d",&data[i][j]);
    }
}

printf("配列Aは以下です\n");

for(i=0;i<n;i++){
    for(j=0;j<3;j++){
        A[i][j]=data[i][j];
        printf("%d ",A[i][j]);
    }
    printf("\n");
}

if(fp2==NULL){
printf("ファイルがありません\n");
return 0;
}

for(i=0;i<3;i++){
    for(j=0;j<m;j++){
        fscanf(fp2,"%d",&data[i][j]);
    }
}

printf("配列Bは以下です\n");

for(i=0;i<3;i++){
    for(j=0;j<m;j++){
        B[i][j]=data[i][j];
        printf("%d ",B[i][j]);
    }
    printf("\n");
}

/*C内初期化*/
  for(i=0; i<n; i++){
    for(j=0; j<m; j++){
      for(k=0; k<3; k++){
	      C[i][j]=0;
      }
    }
  }

 /* 行列の積の計算 */
  for(i=0; i<n; i++){
    for(j=0; j<m; j++){
      for(k=0; k<3; k++){
	      C[i][j]+=A[i][k]*B[k][j];
      }
    }
  }

  printf("行列Cを出力します\n");
  for(i=0; i<n; i++){
     for(j=0; j<m; j++){
       printf("%d ",C[i][j]);
     }
     printf("\n");
  }

if(fp3==NULL){
printf("ファイルがありません\n");
return 0;
}

for(i=0;i<n;i++){
  for(j=0;j<m;j++){
      fprintf(fp3,"%d ",C[i][j]);
  }
    fprintf(fp3,"\n",C[i][j]);
}



fclose(fp1);
fclose(fp2);
fclose(fp3);
return 0;
}