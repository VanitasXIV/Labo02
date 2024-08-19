
#include <stdio.h>

int vector[5] = {10, -2, 33, 4, -5};
int lengthy = sizeof(vector) / sizeof(vector[0]);


void printVector(int vector[]) {
  for (int i = 0; i < lengthy; i++) {
    printf("%d,", vector[i]);
  }
  printf("\n");
}

void invertVector(int vector[]){
int *first = vector; // apunta al primer elemento del arreglo
int *end = vector + lengthy -1; // apunta al ultimo elemento del arreglo
int temp;

while (first<end){
temp=*first;
*first = *end;
*end = temp;

first++;
end--;
}

}

int main() {
  printVector(vector);
  invertVector(vector);
  printVector(vector);
  return 0;
}
