#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#define TAM 130

typedef struct{
    char codigo[8];
    char nombre[81];
    char correo[24];
    int nota;
    char condicion[11];
}Alumno;


#endif // ALUMNO_H_INCLUDED
