//gcc-8 -o matrix_lapack2 matrix_lapack2.c /opt/OpenBLAS/lib/libopenblas.a -lpthread -lm;./matrix_lapack2

/*for complex quantities*/
#include "stdio.h"
#include "stdlib.h"
#include "complex.h"
#include "sys/time.h"
#include "time.h"

//extern void dsymv_(char*, int*, double*, double*, int*, double*, int*, double*, double*, int*);
//extern double ddot_(int*, double*, int*, double*, int*);

extern void zspmv_(char*, int*, double complex*, double complex*, double complex*, int*, double complex*, double complex*, int*);
extern double complex zdotu_(int*, double complex*, int*, double complex*, int*);

int N=257;
double *list1;
double *list2;
double complex *list;
char uplo = 'L';
int inc = 1;
double complex alpha = 1.;
double complex beta = 0.;
int count;

int main(void)
{

/*Reading the tables*/
list1 = (double*)malloc(sizeof(double) * (N*(N+1)/2));
list2 = (double*)malloc(sizeof(double) * (N*(N+1)/2));
list = (double complex*)malloc(sizeof(double complex) * (N*(N+1)/2));
FILE *FileIn;
FileIn = fopen("/home/ksardase/Work/class_2.6.3_PT/pt_matrices/M22oneline_N256.dat", "r");    
for (count=0; count < (N)*(N+1)/2; count++){
   fscanf(FileIn, "%lf", &list1[count]);
}
for (count=0; count < (N)*(N+1)/2; count++){
   fscanf(FileIn, "%lf", &list2[count]);
}
fclose(FileIn);

for (count=0; count < (N)*(N+1)/2; count++){
   list[count] = list1[count] + I * list2[count];
   //printf("list1_real=%e list1_imag=%e\n",creal(list1[count]),cimag(list1[count]));
}

/*Construct vector*/
double complex *x;
double complex *y;
x = (double complex *)malloc(sizeof(double complex)*N);
y = (double complex *)malloc(sizeof(double complex)*N);
for (count=0; count < N; count++){
   x[count]=2.;
   y[count]=0.;
   //printf("x_i=%e\n",x[count]);
}

int start=clock();
zspmv_(&uplo, &N, &alpha, list, x, &inc, &beta, y, &inc);
/*for (count=0; count < N; count++){
printf("y_real=%e y_imag=%e\n",creal(y[count]),cimag(y[count]));
}*/
double complex c;
c=zdotu_(&N, x, &inc, y, &inc);
printf("output_real=%e output_image=%e\n",creal(c),cimag(c));

int end=clock();
printf("Rate_total=%d\n",end-start);
printf("Rate_per_second=%ld\n",CLOCKS_PER_SEC);

free(x);
free(y);
free(list1);
return 0;
}
