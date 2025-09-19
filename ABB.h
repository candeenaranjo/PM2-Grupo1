#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <malloc.h>
#include "Alumno.h"

typedef struct nodo
{
    Alumno alumno;
    struct nodo *hijoDer;
    struct nodo *hijoIzq;
} Nodo;

typedef struct Arbol
{

    Nodo* raiz;
    Nodo* cursor;
    Nodo* padre;
    int cant;
} Arbol;

void InitABB(Arbol *a)
{
    a->raiz=NULL;
    a->padre=NULL;
    a->cursor=NULL;
    a->cant=0;
}
void LiberarABB(Nodo* nodo)
{
    if (nodo == NULL)
    {
        return;
    }
    LiberarABB(nodo->hijoIzq);
    LiberarABB(nodo->hijoDer);
    free(nodo);
}

int LocalizarABB(char codigo[], Arbol* ABB, float *celdas)
{
    ABB->cursor = ABB->raiz;
    ABB->padre = ABB->raiz;

    while((ABB->cursor != NULL) && (strcmp(ABB->cursor->alumno.codigo, codigo) != 0))
    {

        if(strcmp(ABB->cursor->alumno.codigo, codigo)>0 )
        {
            ABB->padre = ABB->cursor;
            ABB->cursor = ABB->cursor->hijoIzq;
        }
        else
        {
            ABB->padre = ABB->cursor;
            ABB->cursor = ABB->cursor->hijoDer;
        }
        (*celdas) += 1;

    }

    if(ABB->cursor != NULL)
    {
        (*celdas) += 1;
        return 0;               //localizacion exitosa
    }
    else
    {
        return 1;               //localizacion no exitosa
    }
}

int AltaABB(Alumno nuevo, Arbol* ABB, float *modificaciones)
{

    float celdas = 0.0;
    Nodo *aux= (Nodo*)malloc(sizeof(Nodo));
    if (aux == NULL)
    {
        return 2;               //fallo de asignacion de memoria
    }
    else
    {
        if(LocalizarABB(nuevo.codigo, ABB, &celdas) == 1)
        {
            aux->alumno = nuevo;
            aux->hijoDer = NULL;
            aux->hijoIzq = NULL;
            if(ABB->raiz == NULL)
            {
                ABB->raiz = aux;
                (*modificaciones) +=0.5;
                return 0;           //alta exitosa
            }
            else if(strcmp(ABB->padre->alumno.codigo, aux->alumno.codigo) > 0 )
            {
                ABB->padre->hijoIzq = aux;
            }
            else
            {
                ABB->padre->hijoDer = aux;
            }
            (*modificaciones) +=0.5;
            return 0;               //alta exitosa
        }
        else
        {
            free((void*)aux);
            return 1;               //alta no exitosa
        }
    }
}

int BajaABB(Alumno eliminar,Arbol* ABB,float *modificaciones){

}

int EvocarABB(Arbol *ABB, char codigo[], Alumno *alumno, float *celdas)
{
    Nodo* pos = ABB->raiz;
    Nodo* aux = NULL;

    if(LocalizarABB(codigo, ABB, celdas)==0)
    {
        (*alumno) = ABB->cursor->alumno;             //PREGUNTAR-> le estoy asignando el dato? o la direccion?
        return 0;               //evocacion exitosa
    }
    return 1;                   //evocacion no exitosa
}

void BarridoPreorden(Nodo* nodo)
{
    if(nodo!=NULL)
    {
        BarridoPreorden(nodo->hijoIzq);
        BarridoPreorden(nodo->hijoDer);
        free(nodo);
    }
}

void Barrido(Nodo* nodo, int *i)
{

    if (nodo != NULL)
    {
        printf("Codigo: %s\nNombre: %s\nCorreo: %s\nNota: %d\nCondicion: %s\n", nodo->alumno.codigo, nodo->alumno.nombre, nodo->alumno.correo, nodo->alumno.nota, nodo->alumno.condicion);
        if(nodo->hijoIzq!=NULL)printf("Hijo izquierdo: %s\n", nodo->hijoIzq->alumno.codigo);
        else printf("Hijo izquierdo: No tiene\n");
        if(nodo->hijoDer!=NULL)printf("Hijo derecho: %s\n\n", nodo->hijoDer->alumno.codigo);
        else printf("Hijo derecho: No tiene\n\n");

        if(*i%3==0)
        {
            system("pause");
            printf("\n");
        }
        (*i)++;

        Barrido(nodo->hijoIzq, i);
        Barrido(nodo->hijoDer, i);
    }
}


#endif // ABB_H_INCLUDED
