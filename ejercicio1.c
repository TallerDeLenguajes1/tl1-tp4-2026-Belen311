#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

int main(){
    Nodo *tareasRealiz, *tareasPend, *nuevoNodo, *moverNodo;
    int cont = 1000, respuesta, id;

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
    
    mostrarLista(tareasPend);
    mostrarLista(tareasRealiz);

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
            pAnterior = pAux->Siguiente;
        }
        pAux->Siguiente = NULL;
    }
    return pAux;
}