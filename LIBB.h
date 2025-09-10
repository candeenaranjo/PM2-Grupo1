#ifndef LIBB_H_INCLUDED
#define LIBB_H_INCLUDED
#include "Alumos.h"

typedef struct Nodo{
    Alumno alumno;
    struct Nodo* siguiente;
}Nodo;

typedef struct{
    Nodo* direcciones[TAM];
}LIBT;


int LocalizarLIBT()



#endif // LIBB_H_INCLUDED
