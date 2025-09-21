#include <stdio.h>
#include <stdlib.h>
#include "LSO.h"
#include "LIBB.h"
#include "ABB.h"

/*
                Practico de Maquina 2 - Dones Bautista y Naranjo Candela - Grupo 1

 Lista secuencial ordenada
 Costos maximos ->    Evocacion Exitosa= 100        Evocacion Fracaso= 70         Alta= 91       Baja= 91
 Costos Medios  ->    Evocacion Exitosa= 45.13      Evocacion Fracaso= 23.19      Alta= 23.01    Baja= 22.38

 Lista Invertida con Busqueda por Triseccion
 Costos maximos ->    Evocacion Exitosa= 14         Evocacion Fracaso= 14         Alta= 45.50    Baja= 45.50
 Costos Medios  ->    Evocacion Exitosa= 11.18      Evocacion Fracaso= 10.32      Alta= 11.51    Baja= 11.19

 Arbol binario de busqueda
 Costos maximos ->    Evocacion Exitosa= 12.00      Evocacion Fracaso= 11.00      Alta= 0.50     Baja= 1.50
 Costos Medios  ->    Evocacion Exitosa= 6.28       Evocacion Fracaso= 6.14       Alta= 0.50     Baja= 1.12

 Analizando los resultados obtenidos podemos ver una gran diferencia en los costos de las listas con el ABB,
 por lo que la mejor estructura para localizaciones, altas y bajas sería el ABB (en este caso). Pero podemos
 hacer un analisis entre las dos listas. Podemos ver que la LIBT tiene costos menores que la LSO, puntualmente
 en las altas y las bajas observamos que los costos de la LSO son el doble que los de la LIBT, esto se debe a
 que la LIBT es mas eficiente al tener direcciones de memoria, por lo que las modificaciones cuestan menos al
 modificar punteros y no correr celdas. En relacion a las evocaciones, la LIBT tine costos muy bajos, ya que
 la estrategia de busqueda es mucho mas eficiciente y menos costosa. En conclusion la mejor estructura en este
 caso es el ABB, pero si hacemos una comparacion de ambas listas, la mejor seria la LIBT.
*/
void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}

int compararEstructuras(Alumno LSO[], Alumno *LIBT[],Arbol *ABB, int *cantLSO, int *cantLIBT)
{
    int i, op=0;
    char codigo[8];
    Alumno aux;
    FILE* fp = fopen("Operaciones.txt", "r");

    (*cantLSO)=0;
    (*cantLIBT)=0;

    Barrido(ABB->raiz);
    ABB->raiz = NULL;
    InitABB(ABB);
    LimpiarListaDePunteros(LIBT,cantLIBT);

    //Variable costos LSO
    int altaLSO=0, bajaLSO=0, evocarLSO=0, maxaltaLSO=0, maxbajaLSO=0, maxevocarELSO=0, maxevocarFLSO=0;
    float sumaAltaLSO=0.0, sumaBajaLSO=0.0, sumaEvocarELSO=0.0, sumaEvocarFLSO=0.0;
    int cantAltaLSO=0, cantBajaLSO=0, cantEvocarELSO=0, cantEvocarFLSO=0;

    //Variables costos LIBT
    int evocarLIBT=0, maxevocarELIBT=0, maxevocarFLIBT=0;
    float sumaAltaLIBT=0.0, sumaBajaLIBT=0.0, sumaEvocarELIBT=0.0, sumaEvocarFLIBT=0.0,altaLIBT=0.0, bajaLIBT=0.0,maxaltaLIBT=0.0, maxbajaLIBT=0.0;
    int cantAltaLIBT=0, cantBajaLIBT=0, cantEvocarELIBT=0, cantEvocarFLIBT=0;

    //Variables costos ABB
    float evocarABB=0.0, maxevocarEABB=0.0, maxevocarFABB=0.0;
    float sumaAltaABB=0.0, sumaBajaABB=0.0, sumaEvocarEABB=0.0, sumaEvocarFABB=0.0,altaABB=0.0, bajaABB=0.0,maxaltaABB=0.0, maxbajaABB=0.0;
    int cantAltaABB=0, cantBajaABB=0, cantEvocarEABB=0, cantEvocarFABB=0;

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

                    //ALTA ABB
                    if(AltaABB(aux,ABB,&altaABB)==0)
                    {

                        //sumar para el promedio
                        sumaAltaABB = sumaAltaABB + altaABB;

                        //calcular el maximo
                        if(altaABB>maxaltaABB)
                        {
                            maxaltaABB = altaABB;
                        }
                        cantAltaABB++;
                    }

                    //init
                    altaLIBT = 0;
                    altaLSO = 0;
                    altaABB = 0;
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

                    //BAJA ABB
                    if(BajaABB(aux,ABB,&bajaABB)==0)
                    {

                        //sumar para el promedio
                        sumaBajaABB = sumaBajaABB + bajaABB;

                        //calcular el maximo
                        if(bajaABB>maxbajaABB)
                        {
                            maxbajaABB = bajaABB;
                        }
                        cantBajaABB++;
                    }

                    bajaABB = 0;
                    bajaLSO = 0;
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

                //EVOCAR ABB
                if(EvocarABB(ABB,codigo,&aux,&evocarABB)==0)      //Evocar Exitoso
                {

                    //sumar para promedio
                    sumaEvocarEABB = sumaEvocarEABB + evocarABB;

                    //calcular el maximo
                    if(evocarABB>maxevocarEABB)
                    {
                        maxevocarEABB = evocarABB;
                    }
                    cantEvocarEABB++;
                }
                else                                                         //Evocar Fracaso
                {

                    //sumar para el promedio
                    sumaEvocarFABB = sumaEvocarFABB + evocarABB;

                    //calculucar el maximo
                    if(evocarABB>maxevocarFABB)
                    {
                        maxevocarFABB = evocarABB;
                    }
                    cantEvocarFABB++;
                }

                evocarABB = 0.0;
                evocarLSO = 0;
                evocarLIBT = 0;
            }

        }
        fclose(fp);

        //LSO
        printf("// Lista secuencial ordenada\n");
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
        printf("Alta= %.2f", maxaltaLIBT);
        gotoxy(100,6);
        printf("Baja= %.2f", maxbajaLIBT);
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
            printf("Alta= %.2f", sumaAltaLIBT/(float)cantAltaLIBT);
        }
        else
        {
            printf("Alta= 0");
        }
        gotoxy(100,7);
        if(cantBajaLIBT!=0)
        {
            printf("Baja= %.2f", sumaBajaLIBT/(float)cantBajaLIBT);
        }
        else
        {
            printf("Baja= 0");
        }
        //ABB
        gotoxy(0,9);
        printf("// Arbol binario de busqueda");
        gotoxy(0,10);
        //COSTOS MAXIMOS
        printf("// Costos maximos ->");
        gotoxy(25,10);
        printf("Evocacion Exitosa= %.2f", maxevocarEABB);
        gotoxy(55,10);
        printf("Evocacion Fracaso= %.2f", maxevocarFABB);
        gotoxy(85,10);
        printf("Alta= %.2f", maxaltaABB);
        gotoxy(100,10);
        printf("Baja= %.2f", maxbajaABB);
        gotoxy(0,11);
        //COSTOS MEDIOS
        printf("// Costos Medios  ->");
        gotoxy(25,11);
        if(cantEvocarEABB!=0)
        {
            printf("Evocacion Exitosa= %.2f", sumaEvocarEABB/cantEvocarEABB);
        }
        else
        {
            printf("Evocacion Exitosa= 0");
        }

        gotoxy(55,11);
        if(cantEvocarFABB!=0)
        {
            printf("Evocacion Fracaso= %.2f", sumaEvocarFABB/cantEvocarFABB);
        }
        else
        {
            printf("Evocacion Fracaso= 0");
        }

        gotoxy(85,11);
        if(cantAltaABB!=0)
        {
            printf("Alta= %.2f", sumaAltaABB/cantAltaABB);
        }
        else
        {
            printf("Alta= 0");
        }

        gotoxy(100,11);
        if(cantBajaABB!=0)
        {
            printf("Baja= %.2f", sumaBajaABB/cantBajaABB);
        }
        else
        {
            printf("Baja= 0");
        }

        gotoxy(0,13);
    }
    return 1;
}

int main()
{
    Alumno LSO[TAM];
    Alumno *LIBT[TAM];
    Arbol arbol;
    char codigo[8];
    int opcion,i=1;
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
            compararEstructuras(LSO,LIBT,&arbol,&cantLSO,&cantLIBT);
            system("pause");
            system("cls");
            break;
        case 2:
            if(cantLSO==0) printf("Lista vacia\n");
            for ( i = 0; i < cantLSO; ++i)
            {

                printf("Alumno %d\nCodigo: %s\nNombre: %s\nCorreo: %s\nNota: %d\nCondicion: %s\n\n",i+1, LSO[i].codigo, LSO[i].nombre, LSO[i].correo, LSO[i].nota,LSO[i].condicion);
                if ((i+1)%3==0)
                {
                    system("pause");
                }
            }
            system("pause");
            system("cls");
            break;
        case 3:
            if(cantLIBT==0) printf("Lista vacia\n");
            for ( i = 0; i < cantLIBT; ++i)
            {
                printf("Alumno %d\nCodigo: %s\nNombre: %s\nCorreo: %s\nNota: %d\nCondicion: %s\n\n",i+1, LIBT[i]->codigo, LIBT[i]->nombre, LIBT[i]->correo, LIBT[i]->nota,LIBT[i]->condicion);
                if ((i+1)%3==0)
                {
                    system("pause");
                }
            }
            system("pause");
            system("cls");
            break;
        case 4:
            i=1;
            if(arbol.raiz==NULL) printf("Arbol vacio\n");
            BarridoPreorden(arbol.raiz, &i);
            system("pause");
            system("cls");
            break;


        }
    }
    while (opcion!=5);

    return 0;
}
