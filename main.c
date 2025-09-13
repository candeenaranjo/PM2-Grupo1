#include <stdio.h>
#include <stdlib.h>
#include "LSO.h"
#include "LIBB.h"

void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}


int compararEstructuras(Alumno LSO[], Alumno *LIBT[], int *cantLSO, int *cantLIBT)
{
    int i, op=0;
    char codigo[8];
    Alumno aux;
    FILE* fp = fopen("Prueba.txt", "r");

    (*cantLSO)=0;
    (*cantLIBT)=0;

    LimpiarListaDePunteros(LIBT,cantLIBT);

    //Variable costos LSO
    int altaLSO=0, bajaLSO=0, evocarLSO=0, maxaltaLSO=0, maxbajaLSO=0, maxevocarELSO=0, maxevocarFLSO=0;
    float sumaAltaLSO=0, sumaBajaLSO=0, sumaEvocarELSO=0, sumaEvocarFLSO=0;
    int cantAltaLSO=0, cantBajaLSO=0, cantEvocarELSO=0, cantEvocarFLSO=0;

    //Variables costos LIBT
    int altaLIBT=0, bajaLIBT=0, evocarLIBT=0, maxaltaLIBT=0, maxbajaLIBT=0, maxevocarELIBT=0, maxevocarFLIBT=0;
    float sumaAltaLIBT=0, sumaBajaLIBT=0, sumaEvocarELIBT=0, sumaEvocarFLIBT=0;
    int cantAltaLIBT=0, cantBajaLIBT=0, cantEvocarELIBT=0, cantEvocarFLIBT=0;

    if(fp==NULL)
    {
        printf("No se encontro el archivo\n");
        system("pause");
        system("cls");
        return -1;
    }
    else
    {
        rewind(fp);

        while(!feof(fp))
        {
            fscanf(fp, "%d", &op);

            //se fija que numero hay en el archivo para hacer las altas y bajass
            if(op== 1|| op==2)
            {

                do
                {
                    fscanf(fp," %[^\n]",aux.codigo);
                }
                while(strlen(aux.codigo)>7 || strlen(aux.codigo)<1);

                fscanf(fp," %[^\n]",aux.nombre);

                fscanf(fp," %[^\n]",aux.correo);

                fscanf(fp," %d",&aux.nota);

                fscanf(fp," %[^\n]",aux.condicion);

                for(int i = 0; aux.codigo[i] != '\0'; i++)
                    aux.codigo[i] = toupper(aux.codigo[i]);
                for(int i = 0; aux.nombre[i] != '\0'; i++)
                    aux.nombre[i] = toupper(aux.nombre[i]);
                for(int i = 0; aux.correo[i] != '\0'; i++)
                    aux.correo[i] = toupper(aux.correo[i]);
                for(int i = 0; aux.condicion[i] != '\0'; i++)
                    aux.condicion[i] = toupper(aux.condicion[i]);

                if(op==1)                              //Alta
                {
                    //ALTA LSO
                    if(AltaLSO(aux,LSO,cantLSO,&altaLSO)==0)
                    {

                        //sumar para el promedio
                        sumaAltaLSO = sumaAltaLSO + altaLSO;

                        //calcular el maximo
                        if(altaLSO>maxaltaLSO)
                        {
                            maxaltaLSO = altaLSO;
                        }
                        cantAltaLSO++;
                    }
                    //init
                    altaLSO = 0;

                    //ALTA LIBT
                    if(AltaLIBT(aux,LIBT,cantLIBT,&altaLIBT)==0)
                    {

                        //sumar para el promedio
                        sumaAltaLIBT = sumaAltaLIBT + altaLIBT;

                        //calcular el maximo
                        if(altaLIBT>maxaltaLIBT)
                        {
                            maxaltaLIBT = altaLIBT;
                        }
                        cantAltaLIBT++;
                    }
                    //init
                    altaLIBT = 0;
                }
                else                                    //Baja
                {
                    //BAJA LSO
                    if(BajaLSO(aux,LSO,cantLSO,&bajaLSO)==0)
                    {

                        //sumar para el promedio
                        sumaBajaLSO = sumaBajaLSO + bajaLSO;

                        //calcular el maximo
                        if(bajaLSO>maxbajaLSO)
                        {
                            maxbajaLSO = bajaLSO;
                        }
                        cantBajaLSO++;
                    }
                    //init
                    bajaLSO = 0;

                    //BAJA LIBT
                    if(BajaLIBT(aux,LIBT,cantLIBT,&bajaLIBT)==0)
                    {

                        //sumar para el promedio
                        sumaBajaLIBT = sumaBajaLIBT + bajaLIBT;

                        //calcular el maximo
                        if(bajaLIBT>maxbajaLIBT)
                        {
                            maxbajaLIBT = bajaLIBT;
                        }
                        cantBajaLIBT++;
                    }

                    bajaLIBT = 0;
                }

            }

        else
        {
            fscanf(fp, " %[^\n]", codigo);
            for(int i = 0; codigo[i] != '\0'; i++)
                codigo[i] = toupper(codigo[i]);

            //EVOCAR LSO
            if(EvocarLSO(&aux,LSO,codigo,*cantLSO, &evocarLSO)==0)      //Evocar Exitoso
            {

                //sumar para promedio
                sumaEvocarELSO = sumaEvocarELSO + evocarLSO;

                //calcular el maximo
                if(evocarLSO>maxevocarELSO)
                {
                    maxevocarELSO = evocarLSO;
                }
                cantEvocarELSO++;
            }
            else                                                         //Evocar Fracaso
            {

                //sumar para el promedio
                sumaEvocarFLSO = sumaEvocarFLSO + evocarLSO;

                //calculucar el maximo
                if(evocarLSO>maxevocarFLSO)
                {
                    maxevocarFLSO = evocarLSO;
                }
                cantEvocarFLSO++;
            }

            evocarLSO = 0;

            //EVOCAR LIBT
            if(EvocarLIBT(&aux,LIBT,codigo,*cantLIBT, &evocarLIBT)==0)      //Evocar Exitoso
            {

                //sumar para promedio
                sumaEvocarELIBT = sumaEvocarELIBT + evocarLIBT;

                //calcular el maximo
                if(evocarLIBT>maxevocarELIBT)
                {
                    maxevocarELIBT = evocarLIBT;
                }
                cantEvocarELIBT++;
            }
            else                                                         //Evocar Fracaso
            {

                //sumar para el promedio
                sumaEvocarFLIBT = sumaEvocarFLIBT + evocarLIBT;

                //calculucar el maximo
                if(evocarLIBT>maxevocarFLIBT)
                {
                    maxevocarFLIBT = evocarLIBT;
                }
                cantEvocarFLIBT++;
            }

            evocarLIBT = 0;
        }

    }
    fclose(fp);

    //LSO
    printf("// Lista secuencial ordenada con busqueda binaria\n");
    gotoxy(0,2);

    //COSTOS MAXIMOS
    printf("// Costos maximos ->");
    gotoxy(25,2);
    printf("Evocacion Exitosa= %d", maxevocarELSO);
    gotoxy(55,2);
    printf("Evocacion Fracaso= %d", maxevocarFLSO);
    gotoxy(85,2);
    printf("Alta= %d", maxaltaLSO);
    gotoxy(100,2);
    printf("Baja= %d", maxbajaLSO);
    gotoxy(0,3);

    //COSTOS MEDIOS
    printf("// Costos Medios  ->");
    gotoxy(25,3);
    if(cantEvocarELSO!=0)
    {
        printf("Evocacion Exitosa= %.2f", sumaEvocarELSO/cantEvocarELSO);
    }
    else
    {
        printf("Evocacion Exitosa= 0");
    }
    gotoxy(55,3);
    if(cantEvocarFLSO!=0)
    {
        printf("Evocacion Fracaso= %.2f", sumaEvocarFLSO/cantEvocarFLSO);
    }
    else
    {
        printf("Evocacion Fracaso= 0");
    }
    gotoxy(85,3);
    if(cantAltaLSO!=0)
    {
        printf("Alta= %.2f", sumaAltaLSO/cantAltaLSO);
    }
    else
    {
        printf("Alta= 0");
    }
    gotoxy(100,3);
    if(cantBajaLSO!=0)
    {
        printf("Baja= %.2f", sumaBajaLSO/cantBajaLSO);
    }
    else
    {
        printf("Baja= 0");
    }

    //LIBT
    gotoxy(0,5);
    printf("// Lista Invertida con Busqueda por Triseccion");
    gotoxy(0,6);

    //COSTOS MAXIMOS
    printf("// Costos maximos ->");
    gotoxy(25,6);
    printf("Evocacion Exitosa= %d", maxevocarELIBT);
    gotoxy(55,6);
    printf("Evocacion Fracaso= %d", maxevocarFLIBT);
    gotoxy(85,6);
    printf("Alta= %d", maxaltaLIBT);
    gotoxy(100,6);
    printf("Baja= %d", maxbajaLIBT);
    gotoxy(0,7);
    printf("// Costos Medios  ->");
    gotoxy(25,7);

    //COSTOS MEDIOS
    if(cantEvocarELIBT!=0)
    {
        printf("Evocacion Exitosa= %.2f", sumaEvocarELIBT/cantEvocarELIBT);
    }
    else
    {
        printf("Evocacion Exitosa= 0");
    }
    gotoxy(55,7);
    if(cantEvocarFLIBT)
    {
        printf("Evocacion Fracaso= %.2f", sumaEvocarFLIBT/cantEvocarFLIBT);
    }
    else
    {
        printf("Evocacion Fracaso= 0");
    }
    gotoxy(85,7);
    if(cantAltaLIBT!=0)
    {
        printf("Alta= %.2f", sumaAltaLIBT/cantAltaLIBT);
    }
    else
    {
        printf("Alta= 0");
    }
    gotoxy(100,7);
    if(cantBajaLIBT!=0)
    {
        printf("Baja= %.2f", sumaBajaLIBT/cantBajaLIBT);
    }
    else
    {
        printf("Baja= 0");
    }

    /*gotoxy(0,9);
    printf("// Arbol binario de busqueda");
    gotoxy(0,10);
    printf("// Costos maximos ->");
    gotoxy(25,10);
    printf("Evocacion Exitosa= %d", maxEvoABE);
    gotoxy(55,10);
    printf("Evocacion Fracaso= %d", maxEvoABF);
    gotoxy(85,10);
    printf("Alta= %.2f", maxAltaAB);
    gotoxy(100,10);
    printf("Baja= %.2f", maxBajaAB);
    gotoxy(0,11);
    printf("// Costos Medios  ->");
    gotoxy(25,11);

    if(cantEvoEABB!=0) printf("Evocacion Exitosa= %.2f", sumaEvoABE/cantEvoEABB);
    else printf("Evocacion Exitosa= 0");

    gotoxy(55,11);
    if(cantEvoFABB!=0) printf("Evocacion Fracaso= %.2f", sumaEvoABF/cantEvoFABB);
    else printf("Evocacion Fracaso= 0");

    gotoxy(85,11);
    if(cantAltaABB!=0) printf("Alta= %.2f", sumaAltaAB/cantAltaABB);
    else printf("Alta= 0");

    gotoxy(100,11);
    if(cantBajaABB!=0) printf("Baja= %.2f", sumaBajaAB/cantBajaABB);
    else printf("Baja= 0");*/

    gotoxy(0,13);
}
return 1;
}

void MostraLSO(Alumno lso[],int cant)
{
    int i,opcion,contador=1;
    for(i=0; i<(cant); i++)
    {
        printf("\nAlumno Numero %d",i+1);
        printf("\nCodigo del Alumno: %s",lso[i].codigo);
        printf("\nNombre y Apellido: %s",lso[i].nombre);
        printf("\nCorreo: %s",lso[i].correo);
        printf("\nNota: %d",lso[i].nota);
        printf("\nCondicion: %s \n",lso[i].condicion);

        if(contador==3)
        {
            contador = 0;
            system("pause");
            system("cls");
        }
        contador ++;
    }
    system("pause");
}


int main()
{
    Alumno LSO[TAM];
    Alumno *LIBT[TAM];
    char codigo[8];
    int opcion;
    int cantLSO=0, cantLIBT=0;
    Alumno aux;


    //Menu
    do
    {
        printf("Seleccione una opcion\n");
        printf("1- Comparar Estructuras\n");
        printf("2- Mostrar Lista Secuencial Ordenada\n");
        printf("3- Mostrar Lista Invertida con Busqueda Binaria\n");
        printf("4- Mostrar Arbol Binario de busqueda\n");
        printf("5- Salir\n");
        printf("Opcion: ");
        scanf("%d",&opcion);
        fflush(stdin);

        system("cls");
        switch (opcion)
        {
        case 1:
            compararEstructuras(LSO,LIBT,&cantLSO,&cantLIBT);
            system("pause");
            system("cls");
            break;
        case 2:
            MostraLSO(LSO,cantLSO);
            break;


        }
    }
    while (opcion!=5);

    return 0;
}
