#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int drugQty=0;
struct farmaco {
    int codigo_producto;
    char nombre[50];
    float precio;
    int cantidad_disponible;
    int cantidad_vendida;
};

void printMenu() {
    printf("_________________________\n");
    printf("1. Ingresar datos\n");
    printf("2. Imprimir datos\n");
    printf("3. Modificar producto\n");
    printf("4. Vender producto\n");
    printf("5. Calcular recaudación total\n");
    printf("6. Borrar producto\n");
    printf("7. Farmaco más vendido\n");
    printf("8. Realizar pedido a distribuidora\n");
    printf("9. Guardar datos\n");
    printf("10. Cargar datos\n");
    printf("11. Salir\n");
    printf("¿Qué desea hacer?");

}

struct farmaco *inputDrug(struct farmaco *farmacos) {
    farmacos = (struct farmacos*) realloc(farmacos, (drugQty+1)*sizeof(struct farmaco));

    if(farmacos==NULL) {
        printf("Error al asignar memoria.\n");
        return NULL;
    }

    printf("Ingrese datos de la droga.\n");
    printf("\nCodigo del producto: ");
    fflush(stdin);
    scanf("%d", &farmacos[drugQty].codigo_producto);
    printf("\nNombre:");
    fflush(stdin);
    fgets(farmacos[drugQty].nombre, 50, stdin);
    farmacos[drugQty].nombre[strcspn(farmacos[drugQty].nombre,"\n")]='\0';
    printf("\nPrecio: ");
    fflush(stdin);
    scanf("%d", &farmacos[drugQty].precio);
    printf("Cantidad disponible:\n");
    fflush(stdin);
    scanf("%d", &farmacos[drugQty].cantidad_disponible);
    farmacos[drugQty].cantidad_vendida = 0;  // Inicializar cantidad vendida a 0
    return farmacos;
}

struct farmaco * inputData(struct farmaco * farmacos) {
    char answer = 0;

    do {
        farmacos = inputDrug(farmacos);

        if(farmacos==NULL) {
            printf("Error al ingresar datos\n");
            return NULL;
        }
        drugQty++;

        printf("Presione S para agregar drogas\n");
        fflush(stdin);
        scanf("%c", &answer);

    }while(answer =='s' || answer=='S');

    return farmacos;
}

void printDrug(struct farmaco * ptr) {
    printf("\n---------------------\n");
    printf("Codigo del producto:%d\n", ptr->codigo_producto);
    printf("Nombre:%s\n", ptr->nombre);
    printf("Precio: %f\n", ptr->precio);
    printf("Cantidad disponible:%d\n",ptr->cantidad_disponible);
    printf("Cantidad vendida:%d\n", ptr->cantidad_vendida);
    printf("\n---------------------\n");
}

void printData(struct farmaco * farmaco) {
    if(farmaco==NULL) {
        printf("No hay data que imprimir\n");
        return;
    }

    struct farmaco *ptr = farmaco;
    struct farmaco *end = farmaco+drugQty;
    if(drugQty>0) {
        while(ptr<end) {
            int count = 0;
            printf("Droga nª%d", count+1);
            printDrug(ptr);
            ptr++;
            count++;
        }
    }
}

struct farmaco * searchDrugByCode(struct farmaco * farmaco) {
    if(farmaco!=NULL) {
        int code=0;
        bool found = 0;
        printf("\nIngrese el codigo del producto: ");
        fflush(stdin);
        scanf("%d", &code);

        struct farmaco *ptr = farmaco;
        const struct farmaco *end = farmaco+drugQty;

        while(ptr<end) {
            if(ptr->codigo_producto==code) {
                found=1;
                break;
            }
            ptr++;
        }

        if(found) {
            return ptr;
        }
        printf("No pudo encontrarse el producto");
        return NULL;
    }
return NULL;

}

void editDrug(struct farmaco * farmaco) {
    if(farmaco!=NULL) {
        struct farmaco *modify = searchDrugByCode(farmaco);
        printf("Nombre de la droga:\n");
        fflush(stdin);
        fgets(modify->nombre, 50, stdin);
        modify->nombre[strcspn(modify->nombre,"\n")] = '\0';
        printf("Codigo del producto:\n");
        fflush(stdin);
        scanf("%d",&modify->codigo_producto);
        printf("Precio:\n");
        fflush(stdin);
        scanf("%f", &modify->precio);
        printf("Cantidad disponible:\n");
        fflush(stdin);
        scanf("%d", &modify->cantidad_disponible);
    }
}

float totalIncomes=0.0;

void sellDrug(struct farmaco * farmaco) {
    if(farmaco!=NULL) {
        int quantity=0;
        struct farmaco *sold= searchDrugByCode(farmaco);
        printf("Cuántos desea vender?");
        fflush(stdin);
        scanf("%d", &quantity);
        if(sold->cantidad_disponible==0) {
            printf("\nNo hay más stock\n");
        }else if((sold->cantidad_disponible-quantity)>0) {
            sold->cantidad_vendida= sold->cantidad_vendida+quantity;
            totalIncomes+=(sold->precio*quantity);
            sold->cantidad_disponible=sold->cantidad_disponible-quantity;
        }else {
            char answer;
            printf("\nSe disponen solamente de %d unidades.", sold->cantidad_disponible);
            printf("Desea vender esa cantidad? S/N");
            fflush(stdin);
            scanf("%c", &answer);

            if(answer=='s' || answer=='S') {
                sold->cantidad_vendida= sold->cantidad_vendida+sold->cantidad_disponible;
                totalIncomes+=(sold->precio*sold->cantidad_disponible);
                sold->cantidad_disponible=sold->cantidad_disponible-sold->cantidad_disponible; //Podría forzarlo a 0 pero la idea es que funcione adecuadamente
            }
        }
    }


}

void calculateIncomings(void) {
    printf("\nTotal recaudado: %f pesos", totalIncomes);
}

struct farmaco *deleteDrug(struct farmaco * farmaco) {
    printData(farmaco);
    int position=0;
    printf("\nCuál producto desea eliminar?");
    fflush(stdin);
    scanf("%d", &position);

    if(position<=drugQty) {
        struct farmaco *ptr = farmaco+position-1;
        struct farmaco *end = farmaco+drugQty;
        struct farmaco *next = farmaco+1;

        while(next<end) {
            *ptr = *next;
            ptr++;
            next++;
        }
        drugQty--;

        farmaco = (struct farmaco*) realloc(farmaco, drugQty * sizeof(struct farmaco));
        if (farmaco == NULL && drugQty > 0) {
            printf("Error al reducir el tamaño del array.\n");
            return NULL;
        }
        printf("Droga eliminada.\n");
    }
    return farmaco;
}

void mostSoldDrug(struct farmaco * farmaco) {
    if(farmaco!=NULL) {
        struct farmaco *ptr = farmaco;
        struct farmaco *end= farmaco+drugQty;
        struct farmaco *mostSold=NULL;
        int bestSeller=0;

        while(ptr<end) {
            if((ptr->cantidad_vendida > bestSeller)) {
                bestSeller=ptr->cantidad_vendida;
                mostSold=ptr;
            }
        }
        printDrug(mostSold);
    }
}

void prepareOrder(struct farmaco * farmaco) {
    FILE* pFile = fopen("farmacos.txt", "w");
    if (pFile == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < drugQty; i++) {
        if(farmaco[i].cantidad_disponible<5 && farmaco[i]) {
            fprintf(pFile, "Nombre: %s\n", farmaco[i].nombre);


        }
    }

    fclose(pFile);
    printf("Orden guardada en farmacos.txt.\n");

}

void saveData(struct farmaco * farmaco) {
    FILE* pFile = fopen("farmacos.dat", "wb");
    if (pFile == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(farmaco, sizeof(struct farmaco), drugQty, pFile);
    fclose(pFile);
    printf("Inventario guardado en articulos.dat.\n");
}

struct farmaco *loadData(struct farmaco * farmaco) {
    FILE* pFile = fopen("farmacos.dat", "rb");
    if (pFile == NULL) {
        printf("Error al abrir el archivo.\n");
        return farmaco;
    }

    fseek(pFile, 0, SEEK_END);
    int qArt = ftell(pFile) / sizeof(struct farmaco);
    rewind(pFile);

    farmaco = (struct articulo*) realloc(farmaco, qArt * sizeof(struct farmaco));
    fread(farmaco, sizeof(struct farmaco), qArt, pFile);
    fclose(pFile);

    drugQty = qArt;
    printf("Inventario cargado desde articulos.dat.\n");

    return farmaco;
}

int main(){
    struct farmaco *farmacos = NULL;
    int option=0;
    printf("Bienvenido/a al programa de gestión de drogas\n");

    do {
        printMenu();
        scanf("%d", &option);
        switch(option) {
            case 1: farmacos = inputData(farmacos);break;
            case 2: printData(farmacos);break;
            case 3: editDrug(farmacos);break;
            case 4: sellDrug(farmacos);break;
            case 5: calculateIncomings(); break;
            case 6: farmacos=deleteDrug(farmacos);break;
            case 7: mostSoldDrug(farmacos);break;
            case 8: prepareOrder(farmacos);break;
            case 9: saveData(farmacos);break;
            case 10: farmacos=loadData(farmacos);break;
            case 11: printf("Saliendo del programa\n"); break;

            default: printf("Ingrese una opción válida\n"); break;
        }
    }while(option !=11);
    free(farmacos);
    return 0;
}
