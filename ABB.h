#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <malloc.h>
#include "Alumno.h"

typedef struct nodo{
    Alumno alumno;
    struct nodo *hijoDer;
    struct nodo *hijoIzq;
} Nodo;

typedef struct Arbol{

       Nodo* raiz;
       Nodo* cursor;
       Nodo* padre;
       int cant;
} Arbol;

void InitABB(Arbol *a){
    a->raiz=NULL;
    a->padre=NULL;
    a->cursor=NULL;
    a->cant=0;
}
void LiberarABB(Nodo* nodo) {
    if (nodo == NULL) {
        return;
    }
    liberarABB(nodo->hijoIzq);
    liberarABB(nodo->hijoDer);
    free(nodo);
}

void barridoFree(NodoABB* nodo){
    if(nodo!=NULL){
        barridoFree(nodo->izquierda);
        barridoFree(nodo->derecha);
        free(nodo);
    }
}

// HOLA NALA :)

#endif // ABB_H_INCLUDED
