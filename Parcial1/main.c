#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int rocketQty=0;

struct cohete {
    int id_cohete;
    char nombre[50];
    float capacidad_carga;
    int numero_lanzamientos;
    int misiones_completadas;
};

void printMenu(void) {
    printf("_________________________\n");
    printf("1. Ingresar datos\n");
    printf("2. Imprimir datos\n");
    printf("3. Modificar cohete\n");
    printf("4. Registrar lanzamiento\n");
    printf("5. Calcular total de misiones completadas\n");
    printf("6. Borrar cohete\n");
    printf("7. Reporte\n");
    printf("8. Guardar datos\n");
    printf("9. Cargar datos\n");
    printf("10. Salir\n");
    printf("¿Qué desea hacer?");
}



struct cohete * inputRocket(struct cohete * cohetes) {
    cohetes = (struct cohete*) realloc(cohetes, (rocketQty+1)*sizeof(struct cohete));

    if(cohetes==NULL) {
        printf("Error al asignar memoria.\n");
        return NULL;
    }

    printf("Ingrese datos del cohete");
    printf("\nID del cohete:");
    fflush(stdin);
    scanf("%d", &cohetes[rocketQty].id_cohete);
    printf("\nNombre:");
    fflush(stdin);
    fgets(cohetes[rocketQty].nombre, 50, stdin);
    cohetes[rocketQty].nombre[strcspn(cohetes[rocketQty].nombre,"\n")]='\0';
    printf("\nCapacidad de carga:");
    fflush(stdin);
    scanf("%f", &cohetes[rocketQty].capacidad_carga);
    cohetes[rocketQty].numero_lanzamientos=0;
    cohetes[rocketQty].misiones_completadas=0;

    return cohetes;
}

//Se solicita una funci´on que ingrese los datos en un vector din´amico de
//estructuras del tipo ”struct cohete” hasta que el usuario decida no ingresar
//m´as cohetes.
struct cohete *inputData(struct cohete * cohetes) {
    char answer = 0;

    do {
        cohetes = inputRocket(cohetes);

        if(cohetes==NULL) {
            printf("Error al ingresar datos\n");
            return NULL;
        }
        rocketQty++;

        printf("Presione S para agregar más cohetes\n");
        fflush(stdin);
        scanf("%c", &answer);

    }while(answer =='s' || answer=='S');

    return cohetes;
}

void printRocket(struct cohete * ptr) {
    printf("\n---------------------\n");
    printf("ID del cohete:%d\n", ptr->id_cohete);
    printf("Nombre:%s\n", ptr->nombre);
    printf("Capacidad de carga: %f\n", ptr->capacidad_carga);
    printf("Numero de lanzamientos:%d\n",ptr->numero_lanzamientos);
    printf("Misiones completadas:%d\n", ptr->misiones_completadas);
    printf("\n---------------------\n");
}

void printData(struct cohete * cohetes) {
    if(cohetes==NULL) {
        printf("No hay data que imprimir\n");
        return;
    }

    struct cohete *ptr = cohetes;
    const struct cohete *end = cohetes+rocketQty;
    if(rocketQty>0) {
        int count = 0;

        while(ptr<end) {

            printf("Cohete nª%d", count+1);
            printRocket(ptr);
            ptr++;
            count+=1;
        }
    }
}

struct cohete * searchRocketByName(struct cohete * cohetes) {
    if(cohetes!=NULL) {
        char nameToFind[50];
        bool found = 0;
        printf("\nIngrese el nombre del cohete: ");
        fflush(stdin);
        fgets(nameToFind, 50, stdin);
        nameToFind[strcspn(nameToFind,"\n")]='\0';

        struct cohete *ptr = cohetes;
        const struct cohete *end = cohetes+rocketQty;

        while(ptr<end) {
            if(strcmp(ptr->nombre, nameToFind)==0) {
                found=1;
                break;
            }
            ptr++;
        }

        if(found) {
            return ptr;
        }
        printf("No pudo encontrarse el cohete");
        return NULL;
    }
    return NULL;

}

void editRocket(struct cohete * cohetes) {
    if(cohetes!=NULL) {
        struct cohete *modify = searchRocketByName(cohetes);
        if(modify!=NULL) {
            printf("Nombre del cohete:\n");
            fflush(stdin);
            fgets(modify->nombre, 50, stdin);
            modify->nombre[strcspn(modify->nombre,"\n")] = '\0';
            printf("ID del cohete:\n");
            fflush(stdin);
            scanf("%d",&modify->id_cohete);
            printf("\nCapacidad de carga:");
            fflush(stdin);
            scanf("%f", &modify->capacidad_carga);
            printf("\nNumero de lanzamientos: ");
            fflush(stdin);
            scanf("%d", &modify->numero_lanzamientos);
            printf("\nMisiones completadas: ");
            fflush(stdin);
            scanf("%d", &modify->misiones_completadas);
        }

    }
}

struct cohete * searchRocketByID(struct cohete * cohetes) {
    if(cohetes!=NULL) {
        int idToFind=0;
        bool found =0;
        printf("\nIngrese el ID del cohete: ");
        fflush(stdin);
        scanf("%d", &idToFind);

        struct cohete *ptr = cohetes;
        const struct cohete *end = cohetes+rocketQty;

        while(ptr<end) {
            if(idToFind==ptr->id_cohete) {
                found=1;
                break;
            }
            ptr++;
        }

        if(found) {
            return ptr;
        }
        printf("No pudo encontrarse el cohete");
        return NULL;
    }
    return NULL;

}

void registerLaunch(struct cohete * cohetes) {

    if(cohetes!=NULL) {
        struct cohete *search = searchRocketByID(cohetes);
        if (search!=NULL) {
            float userWeight=0;
            printf("\nIngrese el peso del piloto: ");
            scanf("%f", &userWeight);
            if(userWeight<search->capacidad_carga) {
                search->numero_lanzamientos++;
                search->misiones_completadas++;
            }else {
                search->numero_lanzamientos++;
                printf("\nEres muy gordos, ni el cohete te aguanta: MISION FALLIDA\n");
            }
        }
    }
}

void totalMissions(struct cohete *cohetes) {
    if(cohetes!=NULL) {
        int completedMissions=0;
        float average=0;
        struct cohete *ptr = cohetes;
        const struct cohete *end = cohetes + rocketQty;
        struct cohete *topRocket = cohetes;
        struct cohete *lastRocket = cohetes;



        while(ptr<end) {
            completedMissions+=ptr->misiones_completadas;
            if(ptr->misiones_completadas>topRocket->misiones_completadas) {
                topRocket=ptr;
            }
            if (ptr->misiones_completadas<lastRocket->misiones_completadas) {
                lastRocket=ptr;
            }
            ptr++;
        }
        average=completedMissions/rocketQty;
        printf("\nTotal de misiones completadas: %d", completedMissions);
        printf("\nEn promedio de los %d cohetes, cada uno completó en promedio %f misiones", rocketQty, average);
        printf("\nEl cohete con más misiones completadas es: %s con %d misiones", topRocket->nombre, topRocket->misiones_completadas);
        printf("\nEl cohete con menos misiones completadas es: %s con %d misiones\n", lastRocket->nombre, lastRocket->misiones_completadas);
    }
}

struct cohete *deleteRocket(struct cohete *cohetes) {
    printData(cohetes);
    int position=0;
    printf("\nCuál cohete desea eliminar?");
    fflush(stdin);
    scanf("%d", &position);

    if(position<=rocketQty) {
        struct cohete *ptr = cohetes+position-1;
        struct cohete *end = cohetes+rocketQty;
        struct cohete *next = cohetes+1;

        while(next<end) {
            *ptr = *next;
            ptr++;
            next++;
        }
        rocketQty--;

        cohetes = (struct cohete*) realloc(cohetes, rocketQty * sizeof(struct cohete));
        if (cohetes == NULL && rocketQty > 0) {
            printf("Error al reducir el tamaño del array.\n");
            return NULL;
        }
        printf("Cohete eliminado.\n");
    }
    return cohetes;
}

void generateReport(struct cohete * cohetes) {
    FILE* pFile = fopen("reporte.txt", "w");
    if (pFile == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < rocketQty; i++) {
        if(cohetes[i].numero_lanzamientos>5) {
            fprintf(pFile, "ID: %d\n", cohetes[i].id_cohete);
            fprintf(pFile, "Nombre: %s\n", cohetes[i].nombre);
            fprintf(pFile,"--------------");
        }
    }

    fclose(pFile);
    printf("Reporte guardado en reporte.txt.\n");

}

void saveData(struct cohete * cohetes) {
    FILE* pFile = fopen("cohetes.dat", "wb");
    if (pFile == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(cohetes, sizeof(struct cohete), rocketQty, pFile);
    fclose(pFile);
    printf("Cohetes guardado en cohetes.dat.\n");
}

struct cohete *loadData(struct cohete * cohetes) {
    FILE* pFile = fopen("cohetes.dat", "rb");
    if (pFile == NULL) {
        printf("Error al abrir el archivo.\n");
        return cohetes;
    }

    fseek(pFile, 0, SEEK_END);
    int newRocketQty = ftell(pFile) / sizeof(struct cohete);
    rewind(pFile);

    cohetes = (struct cohete*) realloc(cohetes, newRocketQty * sizeof(struct cohete));
    fread(cohetes, sizeof(struct cohete), newRocketQty, pFile);
    fclose(pFile);

    rocketQty = newRocketQty;
    printf("Cohetes cargado desde cohetes.dat.\n");

    return cohetes;
}

int main(void)
{
    struct cohete *cohetes = NULL;
    int option=0;

    printf("Bienvenido/a al programa de gestión de cohetes\n");

    do {
        printMenu();
        scanf("%d", &option);
        switch(option) {
            case 1: cohetes = inputData(cohetes);break;
            case 2: printData(cohetes);break;
            case 3: editRocket(cohetes);break;
            case 4: registerLaunch(cohetes);break;
            case 5: totalMissions(cohetes); break;
            case 6: cohetes=deleteRocket(cohetes);break;
            case 7: generateReport(cohetes);break;
            case 8: saveData(cohetes);break;
            case 9: cohetes=loadData(cohetes);break;
            case 10: printf("Saliendo del programa\n"); break;

            default: printf("Ingrese una opción válida\n"); break;
        }
    }while(option !=10);
    free(cohetes);
    return 0;
}
