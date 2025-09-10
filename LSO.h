#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#include "Alumno.h"

int LocalizarLSO (char codigo[], Alumno lso[], int *pos, int cant)
{

    (*pos)=0;

    while((*pos)<cant && strcmp(codigo,lso[*pos].codigo)>0)
    {
        (*pos)++;
    }

    if((*pos)<cant && strcmp(codigo,lso[*pos].codigo)==0)
    {
        return 0;   //localizado
    }
    else
    {
        return 1;   //no localizado
    }
}

int AltaLSO(Alumno aux, Alumno lso[], int *cant)
{
    int pos, i;

    if((*cant)==TAM)
    {
        return 2;   //lista llena no se puede dar de alta
    }
    else
    {
        if(LocalizarLSO(aux.codigo,lso,&pos,*cant)==1)
        {
            for(i=(*cant); i>pos; i--)
            {
                lso[i]=lso[i-1];
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

int BajaLSO(Alumno aux, Alumno lso[], int *cant)
{

    int pos, i, confirmacion;

    if(LocalizarLSO(aux.codigo,lso,&pos,*cant)==0)
    {

        printf("\nLos datos del Alumno con codigo: %s\n", lso[pos].codigo);
        printf("Nombre y Apellido: %s\n", lso[pos].nombre);
        printf("Correo: %s\n", lso[pos].correo);
        printf("Nota: %d\n", lso[pos].nota);
        printf("Condicion: %s\n", lso[pos].condicion);
        printf("Confirma que quiere eliminar al Alumno: (1->si / 2->no)\n");
        scanf("%d", &confirmacion);
        if(confirmacion==1)
        {
            for(i=pos; i<(*cant);i++)
            {
                lso[i]=lso[i+1];
            }
            (*cant)--;
            return 0;   //baja exitosa del alumno
        }
        else
        {
            return 1;    //no quiso eliminar al alumno
        }

    }
    else
    {
        return 2;   //no se localizo el alumno
    }
}

int EvocarLSO(Alumno *aux, Alumno lso[], char codigo[],int cant)
{
    int pos;

    if(LocalizarLSO(codigo,lso,&pos,cant)==0)
    {
        *aux = lso[pos];
        return 0;   //evocacion exitosa
    }
    return 1;   //no se encontro el alumno
}

int ModificarLSO(Alumno lso[], char codigo[],int cant)
{

    int pos,op,condicion, i;

    if(LocalizarLSO(codigo,lso,&pos,cant)==0)
    {

        do
        {
            printf("\nLos datos del Alumno son:\n");
            printf("Codigo de identificacion: %s\n", lso[pos].codigo);
            printf("Nombre y Apellido: %s\n", lso[pos].nombre);
            printf("Correo: %s\n", lso[pos].correo);
            printf("Nota: %d\n", lso[pos].nota);
            printf("Condicion: %s\n", lso[pos].condicion);
            printf("\nQue desea modificar de este Alumno?\n");
            printf("1) Nombre y Apellido\n");
            printf("2) Correo\n");
            printf("3) Nota\n");
            printf("4) Condicion\n");
            printf("5) Finalizar\n");
            scanf("%d",&op);
            system("cls");
            switch(op)
            {
            case 1:
                printf("Ingrese el nuevo Nombre y Apellido del Alumno: ");
                scanf(" %[^\n]",lso[pos].nombre);
                for(i=0; lso[pos].nombre[i] != '\0'; i++)
                    lso[pos].nombre[i]=toupper(lso[pos].nombre[i]);
                printf("Se modifico el Nombre y Apellido con exito\n");
                system("pause");
                system("cls");
                break;

            case 2:
                printf("Ingrese nuevo correo del Alumno: ");
                scanf(" %[^\n]",lso[pos].correo);
                for(i=0; lso[pos].correo[i] != '\0'; i++)
                    lso[pos].correo[i]=toupper(lso[pos].correo[i]);
                printf("Se modifico el correo con exito\n");
                system("pause");
                system("cls");
                break;
            case 3:
                printf("Ingrese la nota del Alumno: ");
                scanf("%d",&lso[pos].nota);
                while(lso[pos].nota<0 || lso[pos].nota>10)
                {
                    printf("Nota invalida. Ingrese una nota entre 0 y 10");
                    scanf("%d",&lso[pos].nota);
                }
                printf("Se modifico la nota con exito\n");
                system("pause");
                system("cls");
                break;
            case 4:
                do
                {
                    printf("\nIngrese condicion del Alumno\n1.Promocion\n2.Regular\n3.Libre\n4.Ausente\n");
                    scanf(" %d",&condicion);
                }
                while(condicion<1 || condicion>4);

                switch(condicion)
                {
                case 1:
                    strcpy(lso[pos].condicion,"Promocion");
                    break;
                case 2:
                    strcpy(lso[pos].condicion,"Regular");
                    break;
                case 3:
                    strcpy(lso[pos].condicion,"Libre");
                    break;
                case 4:
                    strcpy(lso[pos].condicion,"Ausente");
                    break;
                }
                printf("Se modifico la condicion del Alumno con exito\n");
                system("pause");
                system("cls");
                break;

            }
        }
        while(op!=5);
        return 0;   //modificar exitoso
    }
    return 1;   //no se encontro el alumno a modificar
}
#endif // LSO_H_INCLUDED
