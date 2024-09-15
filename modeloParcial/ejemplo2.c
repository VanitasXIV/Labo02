#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int artQty=0;
float totalIncomes=0;
struct articulo {
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
    printf("7. Guardar\n");//Imprime en txt y guarda en .dat
    printf("8. Cargar\n"); //Carga al struct los elementos guardados
    printf("9. Salir\n");
    printf("¿Qué desea hacer?");

}
//TODO
//El examen no lo pide pero sería ideal realizar una validación de los datos ingresados
struct articulo* inputArticle(struct articulo *articulos) {
    articulos = (struct articulo*) realloc(articulos, (artQty + 1) * sizeof(struct articulo));

    if (articulos == NULL) {
        printf("Error al asignar memoria.\n");
        return NULL;
    }

    printf("Ingrese datos del articulo nª%d \n", artQty + 1);
    printf("Nombre del articulo:\n");
    fflush(stdin);
    fgets(articulos[artQty].nombre, 50, stdin);
    articulos[artQty].nombre[strcspn(articulos[artQty].nombre, "\n")] = '\0';
    printf("Codigo del producto:\n");
    fflush(stdin);
    scanf("%d", &articulos[artQty].codigo_producto);
    printf("Precio:\n");
    fflush(stdin);
    scanf("%f", &articulos[artQty].precio);
    printf("Cantidad disponible:\n");
    fflush(stdin);
    scanf("%d", &articulos[artQty].cantidad_disponible);
    articulos[artQty].cantidad_vendida = 0;  // Inicializar cantidad vendida a 0
    return articulos;
}

struct articulo* inputData(struct articulo *articulos) {
    char answer = 0;

    do {
        articulos = inputArticle(articulos);

        if (articulos == NULL) {
            printf("Error al ingresar datos.\n");
            return NULL;
        }
        artQty++;

        printf("Presione S para agregar otro artículo u otra tecla para finalizar el ingreso:");
        fflush(stdin);
        scanf("%c", &answer);
    }while(answer=='s' || answer=='S');

    return articulos;
}

void printArticle(struct articulo * ptr) {
    printf("\n---------------------\n");
    printf("Articulo:%s\n", ptr->nombre);
    printf("Codigo del producto:%d\n", ptr->codigo_producto);
    printf("Precio: %f\n", ptr->precio);
    printf("Cantidad disponible:%d\n",ptr->cantidad_disponible);
    printf("Cantidad vendida:%d\n", ptr->cantidad_vendida);
    printf("\n---------------------\n");
}

void printData(struct articulo *articulos) {
    struct articulo *ptr=articulos;
    struct articulo *end=articulos+artQty;

    int count = 0;

    if(artQty>0) {
        while(ptr<end) {
            printf("Articulo nª%d", count+1);
            printArticle(ptr);
            ptr++;
            count++;
        }
    }
}

struct articulo* searchProductByCode(struct articulo *articulos) {
    int code=0;
    bool found = 0;
    printf("\nIngrese el codigo del producto: ");
    fflush(stdin);
    scanf("%d", &code);

    struct articulo *ptr = articulos;
    const struct articulo *end = articulos + artQty;

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
}

void editProduct(struct articulo *articulos) {
    struct articulo *modify = searchProductByCode(articulos);
    printf("Nombre del articulo:\n");
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

void sellProduct(struct articulo *articulos) {
    int quantity=0;
    struct articulo *sold= searchProductByCode(articulos);
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

//TODO
//se puede realizar otra versión, yo calculo los ingresos totales en una variable global
//cada vez que realizo una venta. Pero también se podría recorrer el arreglo de estructuras
//con un for o punteros e ir multiplicando cantidad vendida por el precio y el resultado lo
//vas acumulando
void calculateIncomings() {
    printf("\nTotal recaudado: %f pesos", totalIncomes);

}

struct articulo* deleteProducts(struct articulo *articulos) {
    int position=0;
    printf("\nCuál producto desea eliminar?");
    fflush(stdin);
    scanf("%d", &position);

    if(position<=artQty) {
        struct articulo *ptr = articulos+position-1;
        struct articulo *end = articulos+artQty;
        struct articulo *next = articulos+1;

        while(next<end) {
            *ptr = *next;
            ptr++;
            next++;
        }
        artQty--;

        articulos = (struct articulo*) realloc(articulos, artQty * sizeof(struct articulo));
        if (articulos == NULL && artQty > 0) {
            printf("Error al reducir el tamaño del array.\n");
            return NULL;
        }
        printf("Articulo eliminado.\n");
    }
    return articulos;
}

struct articulos* loadData(struct articulo *articulos) {
    FILE* pFile = fopen("articulos.dat", "rb");
    if (pFile == NULL) {
        printf("Error al abrir el archivo.\n");
        return articulos;
    }

    fseek(pFile, 0, SEEK_END);
    int qArt = ftell(pFile) / sizeof(struct articulo);
    rewind(pFile);

    articulos = (struct articulo*) realloc(articulos, qArt * sizeof(struct articulo));
    fread(articulos, sizeof(struct articulo), qArt, pFile);
    fclose(pFile);

    artQty = qArt;
    printf("Inventario cargado desde articulos.dat.\n");

    return articulos;
}

void saveData(struct articulo *articulos) {
    FILE* pFile = fopen("articulos.txt", "w");
    if (pFile == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < artQty; i++) {
        fprintf(pFile, "Articulo %d:\n", i + 1);
        fprintf(pFile, "Código: %d\n", articulos[i].codigo_producto);
        fprintf(pFile, "Nombre: %s\n", articulos[i].nombre);
        fprintf(pFile, "Precio: %.2f\n", articulos[i].precio);
        fprintf(pFile, "Cantidad disponible: %d\n", articulos[i].cantidad_disponible);
        fprintf(pFile, "Cantidad vendida: %d\n", articulos[i].cantidad_vendida);
        fprintf(pFile, "\n");
    }

    fclose(pFile);
    printf("Inventario guardado en articulos.txt.\n");

    // Guardar el archivo binario
    FILE* pFile2 = fopen("articulos.dat", "wb");
    if (pFile2 == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(articulos, sizeof(struct articulo), artQty, pFile2);
    fclose(pFile2);
    printf("Inventario guardado en articulos.dat.\n");
}



int main(void)
{
    struct articulo *articulos = NULL;
    int option=0;

    printf("Bienvenido/a al gestor\n");

    do {
        printMenu();
        scanf("%d", &option);
        switch (option) {
            default:printf("Ingrese una opción válida");break;
            case 1: articulos= inputData(articulos);break;
            case 2: printData(articulos);break;
            case 3: editProduct(articulos);break;
            case 4: sellProduct(articulos);break;
            case 5: calculateIncomings();break;
            case 6: printData(articulos);articulos=deleteProducts(articulos);break;
            case 7: saveData(articulos);break;
            case 8: articulos=loadData(articulos);break;
            case 9: printf("Saliendo del programa\n"); break;

        }

    }while(option!=9);

    free(articulos);
    return 0;
}
