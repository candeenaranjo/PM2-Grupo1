#ifndef LIBB_H_INCLUDED
#define LIBB_H_INCLUDED
#include "Alumno.h"

int LocalizarLIBT(char codigo[], Alumno LIBT[], int* pos, int cant, int* celdas){
    (*pos)=0;
    int li, ls, m;
    li = 0;
    ls = cant-1;
    m = (li+ls+1)/2;

    while(li<ls && strcmp(LIBT[m]->codigo,codigo)!=0){

        if(strcmp(LIBT[m]->codigo,codigo)<0){
            li = m+1;
        }else{
            ls = m-1;
        }

        m = (li+ls+1)/2;
        (*celdas)++;
    }
    (*pos)= m;
    if (strcmp(LIBT[m]->codigo,codigo)==0){
        (*celdas)++;
        return 0;               //localizacion exitosa
    }else{
        return 1;               //localizacion no exitosa
    }
}



#endif // LIBB_H_INCLUDED
