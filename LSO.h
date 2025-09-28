#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#include "Alumno.h"

int LocalizarLSO (char codigo[], Alumno lso[], int *pos, int cant, int *celdas)
{

    (*pos)=0;
    (*celdas)=0;

    while((*pos)<cant && strcmp(codigo,lso[*pos].codigo)>0)
    {
        (*pos)++;
        (*celdas)++;
    }

    if((*pos)<cant && strcmp(codigo,lso[*pos].codigo)==0)
    {
        (*celdas)++;
        return 0;   //localizado
    }
    else
    {
        return 1;   //no localizado
    }
}

int AltaLSO(Alumno aux, Alumno lso[], int *cant, int *corrimientos)
{
    int pos, i;
    int celdas=0;

    if((*cant)==TAM)
    {
        return 2;   //lista llena no se puede dar de alta
    }
    else
    {
        if(LocalizarLSO(aux.codigo,lso,&pos,*cant,&celdas)==1)
        {
            for(i=(*cant); i>pos; i--)
            {
                lso[i]=lso[i-1];
                (*corrimientos)++;

            }

            lso[pos]=aux;
            (*cant)++;
            return 0;   //alta exitosa del alumno
        }
        else
        {
            return 1;   //no se pudo dar de alta porque el alumno ya estaba cargado
        }
    }
}

int BajaLSO(Alumno aux, Alumno lso[], int *cant, int *corrimientos)
{

    int pos, i, confirmacion;
    int celdas = 0;

    if(LocalizarLSO(aux.codigo,lso,&pos,*cant,&celdas)==0 && strcmp(aux.codigo,lso[pos].codigo)==0 && strcmp(aux.condicion,lso[pos].condicion)==0 && strcmp(aux.correo,lso[pos].correo)==0 && strcmp(aux.nombre,lso[pos].nombre)==0 && aux.nota == lso[pos].nota)
    {

            for(i=pos; i<(*cant)-1;i++)     //consultar por el cant - 1
            {
                lso[i]=lso[i+1];
                (*corrimientos)++;
            }
            (*cant)--;
            return 0;   //baja exitosa del alumno
    }
    else
    {
        return 2;   //no se localizo el alumno
    }
}

int EvocarLSO(Alumno *aux, Alumno lso[], char codigo[], int cant, int *celdas)
{
    int pos;

    if(LocalizarLSO(codigo,lso,&pos,cant,celdas)==0)
    {
        *aux = lso[pos];
        return 0;   //evocacion exitosa
    }
    return 1;   //no se encontro el alumno

}

#endif // LSO_H_INCLUDED
