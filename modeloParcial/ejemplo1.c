#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int noteQuantity = 0;

struct notebook{
    int codigo_maquina;
    char nombre_prestado[20];
    long int dni;
    char fecha_prestamo[12]; //25-06-2024
    char fecha_expiracion[12]; //30-06-2024
    float valor_asegurado;
};

void printMenu() {
    printf("1. Ingresar Notebooks\n");
    printf("2. Imprimir datos\n");
    printf("3. Modificar fecha de expiracion\n");
    printf("4. Modificar parámetros de notebook\n");
    printf("5. Borrar usuario\n");
    printf("6. Guardar\n");
    printf("7. Cargar datos\n");
    printf("8. Salir\n");
    printf("¿Qué acción desea realizar?:");
}

void dataInput(struct notebook *notebooks) {
    printf("\n Nombre del usuario: ");
    fflush(stdin);
    fgets(&notebooks->nombre_prestado, 20, stdin);
    notebooks->nombre_prestado[strcspn(&notebooks->nombre_prestado, "\n")] = '\0';

    printf("\n DNI del usuario:");
    fflush(stdin);
    scanf("%d", &notebooks->dni);

    printf("\n Fecha del prestamo: ");
    fflush(stdin);
    fgets(&notebooks->fecha_prestamo, 12, stdin);
    notebooks->fecha_prestamo[strcspn(notebooks->fecha_prestamo, "\n")] = '\0';

    printf("\n Fecha de expiracion: ");
    fflush(stdin);
    fgets(notebooks->fecha_expiracion, 12, stdin);
    notebooks->fecha_expiracion[strcspn(notebooks->fecha_expiracion, "\n")] = '\0';

    printf("\n Valor asegurado:");
    fflush(stdin);
    scanf("%f", &notebooks->valor_asegurado);
}

void ingresarNotebooks(struct notebook *notebooks) {
    char answer;

    do {
        printf("Ingrese datos de la notebook %d: \n", noteQuantity+1);
        printf("\nCodigo de maquina:");
        fflush(stdin);
        scanf("%d", &notebooks[noteQuantity].codigo_maquina);

        dataInput(notebooks+noteQuantity);

        noteQuantity++;

        printf("Desea ingresar otra persona? (S/N): ");
        scanf(" %c", &answer);
    }while(answer== 's' || answer=='S');
}

void printNotebook(struct notebook *ptr) {
    printf("\n---------------------");
    printf("\nCodigo de la maquina: %d", ptr->codigo_maquina);
    printf("\nNombre del usuario: %s", ptr->nombre_prestado);
    printf("\nDNI del usuario: %ld", ptr->dni);
    printf("\nFecha del prestamo: %s", ptr->fecha_prestamo);
    printf("\nFecha de expiracion: %s", ptr->fecha_expiracion);
    printf("\nValor asegurado: %f", ptr->valor_asegurado);
    printf("\n---------------------");

}

void printDatos(struct notebook *notebooks) {
    struct notebook *ptr = notebooks;
    struct notebook *end = notebooks + noteQuantity;
    int count = 0;
    if(noteQuantity>0) {
    while(ptr<end) {
        printf("\nPersona: %d", count + 1);
        printNotebook(ptr);
        ptr++;
        count++;
}
    }
}

//Devuelve el puntero
struct notebook* searchPerson(struct notebook *notebooks) {
    int dniToSearch=0;

    printf("\nIngrese el DNI de la persona");
    fflush(stdin);
    scanf("%ld",&dniToSearch);

    struct notebook *ptr = notebooks;
    struct notebook *end = notebooks + noteQuantity;

    while(ptr < end) {

        if(ptr->dni==dniToSearch) {
            printf("Encontrado");
            return ptr;
        }
        ptr++;
    }

    printf("Persona no encontrada");

}


void modificarExpiracion(struct notebook *notebooks) {
    struct notebook *found = searchPerson(notebooks);

        printNotebook(found);
        printf("\n Nueva fecha de expiracion: ");
        fflush(stdin);
        fgets(found->fecha_expiracion, 12, stdin);
        found->fecha_expiracion[strcspn(*found->fecha_expiracion, "\n")] = '\0';
}



void modificarParametrosNotebook(struct notebook *notebooks) {

    int codeToSearch=0;
    int position=0;
    bool found = 0;
    printf("\nIngresar el código de máquina.");
    fflush(stdin);
    scanf("%d",&codeToSearch);

    struct notebook *ptr = notebooks;
    struct notebook *end = notebooks + noteQuantity;

    while(ptr < end) {

        if(ptr->codigo_maquina==codeToSearch) {
            printf("Encontrado");
            found = 1;
            break;
        }
        ptr++;
        position++;
    }

    if(found) {
        printNotebook(ptr);
        printf("\nNuevos datos a ingresar");
        dataInput(ptr);


    }else {
        printf("Persona no encontrada.\n");

    }
}

void deleteUser(struct notebook *notebooks) {
    printf("\n ¿A quién desea borrar?");
    printDatos(notebooks);

    int position=0;

    printf("\nIngrese la posicion de la persona a eliminar: ");
    fflush(stdin);
    scanf("%d", &position);

    struct notebook *ptr = notebooks+position-1;
    struct notebook *end = notebooks +noteQuantity;
    struct notebook *next = ptr + 1;
           while(next < end) {
               *ptr = *next;
               ptr++;
               next++;
           }
           noteQuantity--;
           printf("Persona eliminada.\n");
       }


void loadData(struct notebook *notebooks) {
    FILE *pFile = fopen("notebooks.dat", "rb");  // Abrir el archivo para lectura binaria
    if (pFile == NULL) {
        printf("Error al abrir el archivo para cargar.\n");
        return;
    }

    // Leer la cantidad de notebooks del archivo
    fread(&noteQuantity, sizeof(int), 1, pFile);

    // Leer los datos de los notebooks del archivo
    fread(notebooks, sizeof(struct notebook), noteQuantity, pFile);

    fclose(pFile);  // Cerrar el archivo después de leer los datos
    printf("Datos cargados exitosamente desde notebooks.dat. Cantidad de notebooks: %d\n", noteQuantity);
}


void saveData(struct notebook *notebooks) {
    FILE *pFile = fopen("notebooks.txt", "w");
    struct notebook *ptr = notebooks;
    struct notebook *end = notebooks + noteQuantity;
    if(noteQuantity>0) {
        while(ptr<end) {
            fprintf(pFile,"\n---------------------");
            fprintf(pFile,"\nCodigo de la maquina: %d", ptr->codigo_maquina);
            fprintf(pFile,"\nNombre del usuario: %s", ptr->nombre_prestado);
            fprintf(pFile,"\nDNI del usuario: %ld", ptr->dni);
            fprintf(pFile,"\nFecha del prestamo: %s", ptr->fecha_prestamo);
            fprintf(pFile,"\nFecha de expiracion: %s", ptr->fecha_expiracion);
            fprintf(pFile,"\nValor asegurado: %f", ptr->valor_asegurado);
            fprintf(pFile,"\n---------------------");
            ptr++;
        }
    }
    fclose(pFile);

    pFile = fopen("notebooks.dat","wb");
    if(pFile==NULL) {
        printf("No se pudo abrir el archivo\n");
    }

    fwrite(&noteQuantity, sizeof(int), 1, pFile);
    fwrite(notebooks, sizeof(struct notebook), noteQuantity, pFile);



}

int main(void)
{
    int option=0;
    struct notebook *notebooks = (struct notebook*) malloc(100 * sizeof(struct notebook));



    do {
        printf("\nManejo de inventarios\n");
        printMenu();
        fflush(stdin);
        scanf("%d",&option);
        switch(option) {
            default:
                printf("Ingrese una opción valida");
                break;
            case 1:
                ingresarNotebooks(notebooks);
                break;
            case 2:
                printDatos(notebooks);
                break;
            case 3:
                modificarExpiracion(notebooks);
                break;
            case 4:
                modificarParametrosNotebook(notebooks);
                break;
            case 5:
                deleteUser(notebooks);
                break;
            case 6:
                saveData(notebooks);//Guarda los datos en un txt y en un binario

                break;
            case 7:
                loadData(notebooks);
                break;
            case 8:
                printf("Saliendo del programa...\n");
                break;
        }

    }while(option!=8);



}
