#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct Tarea{
int TareaID;//Numérico autoincremental comenzando en 1000
char *Descripcion; //
int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo{
Tarea T;
struct Nodo *Siguiente;
} Nodo;

Nodo *crearListaVacia();

Nodo *crearNodo(int cont);

void insertarAlInicio(Nodo **start, Nodo *nuevoNodo);

void insertarAlFinal(Nodo *start, Nodo *nuevoNodo);

void mostrarLista(Nodo *start);

Nodo *eliminarNodo(Nodo **start, int id);

Nodo *buscarNodo(Nodo *start, int id, char *palabra);

void liberarMemoria(Nodo **start);

int main(){
    Nodo *tareasRealiz, *tareasPend, *nuevoNodo, *moverNodo, *buscarNod;
    int cont = 1000, respuesta, id;
    char *palabra;
    tareasRealiz = crearListaVacia();
    tareasPend = crearListaVacia();

    printf("Desea ingresar una tarea: ");
    scanf("%d", &respuesta);

    while (respuesta != 0)
    {
        nuevoNodo = crearNodo(cont);
        cont++;
        if (tareasPend == NULL){
            insertarAlInicio(&tareasPend, nuevoNodo);
        } else {
            insertarAlFinal(tareasPend, nuevoNodo);
        }
        printf("Desea ingresar una tarea: ");
        scanf("%d", &respuesta);
    }

    printf("Ingresar Id: ");
    scanf("%d", &id);
    moverNodo = eliminarNodo(&tareasPend, id);
    if (tareasRealiz == NULL){
            insertarAlInicio(&tareasRealiz, moverNodo);
        } else {
            insertarAlFinal(tareasRealiz, moverNodo);
        }

    printf("Desea buscar por id(1) o por palabra(0): ");
    scanf("%d", &respuesta);
    if (respuesta)
    {
        printf("Ingresar Id: ");
        scanf("%d", &id);
        palabra = NULL;
        buscarNod = buscarNodo(tareasPend, id, palabra);
        if (buscarNod)
        {
            printf("Tarea de ID: %d\n", buscarNod->T.TareaID);
            printf("Descripcion: ");
            puts(buscarNod->T.Descripcion);
            printf("Duracion: %d\n", buscarNod->T.Duracion);
            printf("Se encuentra en listas pendientes");
        } else {
            buscarNod = buscarNodo(tareasRealiz, id, palabra);
            if (buscarNod)
            {
                printf("Tarea de ID: %d\n", buscarNod->T.TareaID);
                printf("Descripcion: ");
                puts(buscarNod->T.Descripcion);
                printf("Duracion: %d\n", buscarNod->T.Duracion);
                printf("Se encuentra en listas realizadas");
            } else {
                printf("No se encontro");
            }
        }
    } else {
        palabra = (char *)malloc(50 * sizeof(char));
        printf("Ingrese la palabra clave: ");
        fflush(stdin);
        gets(palabra);
        id = 0;
        buscarNod = buscarNodo(tareasPend, id, palabra);
        if (buscarNod)
        {
            printf("\n");
            printf("Tarea de ID: %d\n", buscarNod->T.TareaID);
            printf("Descripcion: ");
            puts(buscarNod->T.Descripcion);
            printf("Duracion: %d\n", buscarNod->T.Duracion);
            printf("Se encuentra en listas pendientes");
        } else {
            buscarNod = buscarNodo(tareasRealiz, id, palabra);
            if (buscarNod)
            {
                printf("\n");
                printf("Tarea de ID: %d\n", buscarNod->T.TareaID);
                printf("Descripcion: ");
                puts(buscarNod->T.Descripcion);
                printf("Duracion: %d\n", buscarNod->T.Duracion);
                printf("Se encuentra en listas realizadas");
            } else {
                printf("No se encontro");
            }
        }
    }

    printf("\n");
    mostrarLista(tareasPend);
    printf("\n");
    mostrarLista(tareasRealiz);
    free(palabra);
    liberarMemoria(&tareasPend);
    liberarMemoria(&tareasRealiz);

    return 0;
}

Nodo *crearListaVacia(){
    return NULL;
}

Nodo *crearNodo(int cont){
    srand(time(NULL));
    Nodo *pNodo = (Nodo *)malloc(sizeof(Nodo));
    pNodo->T.TareaID = cont;
    pNodo->T.Descripcion = (char *)malloc(50 * sizeof(char));
    printf("Ingresar descripcion: ");
    fflush(stdin);
    gets(pNodo->T.Descripcion);
    pNodo->T.Duracion = 10 + rand() % 91;
    pNodo->Siguiente = NULL;

    return pNodo;
}

void insertarAlInicio(Nodo **start, Nodo *nuevoNodo){
nuevoNodo->Siguiente = *start;
*start = nuevoNodo;
}

void insertarAlFinal(Nodo *start, Nodo *nuevoNodo){
Nodo *pAux = start;
    while (pAux->Siguiente)
    {
        pAux = pAux->Siguiente;
    }
    pAux->Siguiente = nuevoNodo;
}

void mostrarLista(Nodo *start){
    Nodo *pAux = start;
    while (pAux)
    {
        printf("\n");
        printf("Tarea de ID: %d\n", pAux->T.TareaID);
        printf("Descripcion: ");
        puts(pAux->T.Descripcion);
        printf("Duracion: %d", pAux->T.Duracion);
        pAux = pAux->Siguiente;
    }
}

Nodo *eliminarNodo(Nodo **start, int id){
    Nodo *pAux = *start, *pAnterior = NULL;
    while (pAux && pAux->T.TareaID != id)
    {
        pAnterior = pAux;
        pAux = pAux->Siguiente;
    }
    if (pAux){
        if (pAux == *start){
            *start = pAux->Siguiente;
        } else {
            pAnterior->Siguiente = pAux->Siguiente;
        }
        pAux->Siguiente = NULL;
    }
    return pAux;
}

Nodo *buscarNodo(Nodo *start, int id, char *palabra){
    Nodo *pAux = start, *pAnterior = NULL;
    
    if (id){
        while (pAux && pAux->T.TareaID != id )
        {
            pAux = pAux->Siguiente;
        }
        
        return pAux;
    } else if (palabra){
        while (pAux && strcmp(palabra, pAux->T.Descripcion) != 0)
        {
            pAux = pAux->Siguiente;
        }

        return pAux;
    }
}

void liberarMemoria(Nodo **start){
    Nodo *pAux = *start, *pAnt = NULL, *nodoExtraido;

    while (pAux)
    {
        pAnt = pAux;
        pAux = pAux->Siguiente;
        *start = pAnt->Siguiente;
        nodoExtraido = pAnt;
        if (nodoExtraido)
        {
            printf("\n");
            printf("Liberando memoria");
            free(nodoExtraido->T.Descripcion);
            free(nodoExtraido);
        }
    }
}