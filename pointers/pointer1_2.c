// 1.2 Mayor entre dos n´umeros
// Desarrollar un programa que encuentre el mayor entre dos n´umeros ingresados
// por el usuario utilizando punteros.

#include <stdio.h>

int main(){
    int number1;
    int number2;
    int *nump1;
    int *nump2;

    nump1=&number1;
    nump2=&number2;

    printf("Mayor entre dos números\n");
    printf("Escriba dos numeros enteros:\n");
    printf("Primer numero:\n");
    scanf("%d", nump1);
    printf("\nSegundo numero:\n");
    scanf("%d", nump2);

printf("\nEl mayor numero:");

if(*nump1 > *nump2){
    printf("%d",*nump1);
}else {
    printf("%d",*nump2);
}

    return 0;

}
