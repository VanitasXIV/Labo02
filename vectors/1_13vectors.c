//1.13 Rotaci´on de Elementos
//Desarrolla una funci´on en C que rote los elementos de un vector dado hacia la
//izquierda un n´umero espec´ıfico de veces.

#include <stdio.h>

int vector[5] = {10, -2, 33, 4, -5};
int lengthy = sizeof(vector) / sizeof(vector[0]);
int times=0;

void rotateLeftOnce(int vector[]){
int temp=vector[0];

for(int i = 0; i<lengthy; i++){
vector[i]=vector[i+1];
}
vector[lengthy-1]=temp;

}

void rotateLeft(int vector[], int times){
    for (int i=0; i<times;i++){
        rotateLeftOnce(vector);
    }
}

void printVector(int vector[]) {
  for (int i = 0; i < lengthy; i++) {
    printf("%d,", vector[i]);
  }
  printf("\n");
}

int main() {
  printVector(vector);
  printf("How many times you want to rotate the vector?:");
  scanf("%d", &times);
  rotateLeft(vector, times);
  printVector(vector);
  return 0;
}