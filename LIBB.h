#ifndef LIBB_H_INCLUDED
#define LIBB_H_INCLUDED
#include <malloc.h>
#include "Alumno.h"

int LocalizarLIBT(char codigo[], Alumno *LIBT[], int* pos, int cant, int *celdas)
{
    (*pos)=0;
    (*celdas)=0;
    int li, ls, m;
    li = 0;
    ls = cant-1;
    m = (li+ls+1)/2;

    while(li<=ls && strcmp(LIBT[m]->codigo,codigo)!=0)
    {

        if(strcmp(LIBT[m]->codigo,codigo)<0)
        {
            li = m+1;
        }
        else
        {
            ls = m-1;
        }

        m = (li+ls+1)/2;
        (*celdas)=(*celdas)+2;
    }
    (*pos)= m;
    if (li<=ls){
        (*celdas)=(*celdas) +2;
        return 0;               //localizacion exitosa
    }
    else
    {
        return 1;               //localizacion no exitosa
    }
}

int AltaLIBT(Alumno aux, Alumno *LIBT[], int *cant, float *corrimientos)
{
    int pos,i;
    int celdas = 0;
    if((*cant)==TAM)
    {
        return 2;                           //lista llena no se puede dar de alta
    }
    else
    {
        Alumno *aux1;
        aux1 = (Alumno *)malloc(sizeof(Alumno));
        if(aux1 == NULL)
        {
            return 3;                       //fallo de asignacion de memoria
        }
        if(LocalizarLIBT(aux.codigo,LIBT,&pos,*cant,&celdas)==1)
        {
            for(i=(*cant); i>pos; i--)
            {
                LIBT[i]=LIBT[i-1];
                (*corrimientos)=(*corrimientos)+0.5;

            }

            strcpy(aux1->codigo,aux.codigo);
            strcpy(aux1->nombre,aux.nombre);
            strcpy(aux1->correo,aux.correo);
            aux1->nota = aux.nota;
            strcpy(aux1->condicion,aux.condicion);

            LIBT[pos]=aux1;
            //(*corrimientos)=(*corrimientos)+0.5;
            (*cant)++;
            return 0;                        //alta exitosa del alumno
        }
        else
        {
            free(aux1);
            return 1;                       //no se pudo dar de alta porque el alumno ya estaba cargado
        }
    }
}

int BajaLIBT(Alumno aux, Alumno *LIBT[], int *cant, float *corrimientos)
{
    int pos,i, celdas=0;
    if(LocalizarLIBT(aux.codigo,LIBT,&pos,*cant,&celdas)==0 && LIBT[pos]->nota == aux.nota && strcmp(LIBT[pos]->codigo, aux.codigo)==0 && strcmp(LIBT[pos]->condicion, aux.condicion)==0 && strcmp(LIBT[pos]->correo, aux.correo)==0 && strcmp(LIBT[pos]->nombre, aux.nombre)==0)
    {
        Alumno *aBorrar = LIBT[pos];                // guardar puntero para liberar memoria

        for(i=pos; i<(*cant)-1; i++)                //consultar por el cant - 1
        {
            LIBT[i]=LIBT[i+1];
            (*corrimientos)=(*corrimientos)+0.5;
        }
        (*cant)--;
        free(aBorrar);
        return 0;               //baja exitosa
    }
    else
        return 1;               //baja no exitos
}

int EvocarLIBT(Alumno *aux,Alumno *LIBT[],char codigo[],int cant, int *celdas)
{
    int pos;
    printf("Costos evocacion %d",*celdas);
    if(LocalizarLIBT(codigo,LIBT,&pos,cant,celdas)==0)
    {
        *aux = *LIBT[pos];           //evocacion exitosa
        return 0;
    }

    return 1;                       //evocacion no exitosa
}

void LimpiarListaDePunteros(Alumno *Lista[], int *cantLista)
{
    for (int i = 0; i < *cantLista; i++)
    {
        free(Lista[i]);              // libera la memoria asignada dinámicamente
        Lista[i] = NULL;             // evita punteros colgados
    }
    *cantLista = 0;                 // reinicia el contador de elementos
}


#endif // LIBB_H_INCLUDED
