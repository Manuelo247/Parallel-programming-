#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define MAX 10
#define random rand()%(MAX+1);

void imprimirMatriz(int **mat, int filas, int columnas){

    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }

}

void llenarMatriz(int **matTemp_, int filas, int columnas){

    

    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matTemp_[i][j] = random;
        }
    }

    return;

}

int **generarmatriz(int filas, int columnas){
    
    int **matTemp_;

    matTemp_ = (int *)malloc(filas*sizeof(int)); 
	for (int i=0; i < filas; i++) matTemp_[i] = (int*)malloc(columnas*sizeof(int));

    return matTemp_;
}

int **multiplicacion(int filas, int columnas){

    int **mat, **mat2, **matr;

    mat = generarmatriz(filas, columnas);
    mat2 = generarmatriz(columnas, filas);
    matr = generarmatriz(filas, filas);

    llenarMatriz(mat, filas, columnas);
    llenarMatriz(mat2, columnas, filas);

    for(int i = 0; i < filas; i++){
        for(int j = 0; j < filas; j++){
            matr[i][j] = 0;
        }
    }

    int i, j, k;
    #pragma omp parallel for private(i, j, k) shared(mat, mat2, matr)
    for(i = 0; i < filas; i++){
        for(j = 0; j < filas; j++){
            for(k = 0; k < columnas; k++){
                matr[i][j] += mat[i][k] * mat2[k][j];
            }
        }
    }

    return matr;
}

int main(int argc, char **argv){

    int threadcnt = 1;
    if(argc > 1){
	threadcnt = atoi(argv[1]);
    }
    
    printf("OMP defined, threadct = %d\n", threadcnt);

    srand(time(NULL));

    int **matr;
    int filas = 1000;
    int columnas = 1000;
	
    omp_set_num_threads(threadcnt);
    matr = multiplicacion(filas, columnas);
}
