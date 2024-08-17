// 1.7 Elemento M´aximo y su Posici´on
// Desarrolla una funci´on en C que encuentre el elemento m´aximo en un vector
// dado y devuelva su posici´on.

#include <stdio.h>

int duplicate(int vector[], int length){

    int maxVal=vector[0];
    int maxValPos =0;

    for (int i = 0; i < length; i++){
        if (vector[i] > maxVal){
            maxVal = vector[i];
            maxValPos = i;
        }
    }
    return maxValPos;
}

int main(){
    int vector[5]={10,-2,33,4,-5};
    int length = sizeof(vector) / sizeof(vector[0]);

    int maxPos = duplicate(vector, length);

    printf("%d", maxPos);
    return 0;
}