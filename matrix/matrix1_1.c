//1.1 Ingreso de datos y funci´on por valor
//Escribe un programa que solicite al usuario ingresar datos para una matriz
//cuadrada de tama˜no N × N. Luego, pasa esta matriz a una funci´on por valor
//que calcule la suma de los elementos en la diagonal principal y en la diagonal
//secundaria, e imprima ambos resultados junto con la matriz ingresada.

//sumaDeElementos float
#include <stdio.h>
#define N 3

int matriz[N][N]={{1,2,3},{4,5,6},{7,8,9}};

//Matrices con punteros
//matriz = matriz [ 0 ] = & matriz[ 0 ][ 0 ]
//matriz+1=matriz [ 1 ] = & matriz[ 1 ][ 0 ]

void printMatrix(int *matriz) {
    int *ptr=matriz;
    int *end=matriz+ N * N;

    while(ptr<end) {
        printf("%d ", *ptr);
        ptr++;

        if((ptr-matriz)% N ==0) {
            printf("\n");
        }
    }

}

void addDiagonals(int matriz[N][N]) {
    int sumaA=0;
    int sumaB=0;
    for(int i=0; i<N;i++) {
        sumaA+=matriz[i][i];
    }
    printf("Diagonal principal: %d\n", sumaA);

    for(int i=0; i<N;i++) {
        sumaB+=matriz[i][N-i-1];
    }
    printf("Diagonal secundaria: %d\n", sumaB);
}


int main(){
    printf("MATRIZ CREADA\n");
    printMatrix(matriz);
    addDiagonals(matriz);
return 0;
}
