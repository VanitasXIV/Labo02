//1.5 Factorial de un n´umero
//Escribir un programa que calcule el factorial de un n´umero ingresado por el
//usuario utilizando punteros.

#include<stdio.h>

int main() {
    int number, factorial = 1;
    int *pnumber=&number;
    int *pfactorial=&factorial;

    printf("Enter a number: ");
    scanf("%d",pnumber);

    for(int i=1; i<=number; i++) {
        *pfactorial = *pfactorial * i;
    }

    printf("Factorial of %d is: %d",*pnumber, *pfactorial);
    return 0;
}