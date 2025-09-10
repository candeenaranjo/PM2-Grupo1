#include <stdio.h>
#include <stdlib.h>
#include "LSO.h"

int Precarga(Alumno LSO[], int *cant)
{
    int i;
    Alumno aux;
    FILE* fp = fopen("Operaciones.txt", "r");
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

            if(aux.nota>=0 && aux.nota<=10)
            {
                AltaLSO(aux,LSO,cant);
            }

        }
        fclose(fp);
        return 1;
    }
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
    char codigo[8];
    int opcion,condicion;
    int cant=0,i, exito;
    Alumno aux;


    //Menu
    do
    {
        printf("Seleccione una opcion\n");
        printf("1- Ingresar Nuevo Alumno\n");
        printf("2- Eliminar Alumno existente\n");
        printf("3- Modificar datos de un Alumno\n");
        printf("4- Consultar informacion de un Alumno\n");
        printf("5- Memorizacion Previa\n");
        printf("6- Mostrar Estructura\n");
        printf("7- Salir\n");
        printf("Opcion: ");
        scanf("%d",&opcion);
        fflush(stdin);

        system("cls");
        switch (opcion)
        {
        case 1:
            if(cant==TAM)
            {
                printf("No se puede dar de Alta la estructura esta llena\n");
            }
            else
            {
                do
                {
                    printf("\nIngrese el codigo de Alumno: ");
                    scanf(" %[^\n]",aux.codigo);
                }
                while(strlen(aux.codigo)>7 || strlen(aux.codigo)<1);
                printf("%d",strlen(aux.codigo));
                printf("\nIngrese Nombre y Apellido del Alumno: ");
                scanf(" %[^\n]",aux.nombre);
                printf("\nIngrese correo electronico del Alumno: ");
                scanf(" %[^\n]",aux.correo);
                printf("\nIngrese la nota del Alumno: ");
                scanf("%d",&aux.nota);
                fflush(stdin);
                while(aux.nota<0 || aux.nota>10)
                {
                    printf("Nota invalida.\nIngrese una nota entre 0 y 10 :");
                    scanf("%d",&aux.nota);
                }
                fflush(stdin);
                printf("\nIngrese condicion del Alumno\n1.Promocion\n2.Regular\n3.Libre\n4.Ausente\n->");
                scanf("%d",&condicion);
                fflush(stdin);
                while(condicion<1 || condicion>4)
                {
                    printf("\nCondicion no valida.\nIngrese condicion del Alumno\n1.Promocion\n2.Regular\n3.Libre\n4.Ausente\n->");
                    scanf(" %d",&condicion);
                }
                fflush(stdin);

                switch(condicion)
                {
                case 1:
                    strcpy(aux.condicion,"Promocion");
                    break;
                case 2:
                    strcpy(aux.condicion,"Regular");
                    break;
                case 3:
                    strcpy(aux.condicion,"Libre");
                    break;
                case 4:
                    strcpy(aux.condicion,"Ausente");
                    break;
                }


                //Esto es para controles de Mayusculas y Minusculas
                for(i=0; aux.codigo[i] != '\0'; i++)
                    aux.codigo[i]=toupper(aux.codigo[i]);
                for(i=0; aux.nombre[i] != '\0'; i++)
                    aux.nombre[i]=toupper(aux.nombre[i]);
                for(i=0; aux.correo[i] != '\0'; i++)
                    aux.correo[i]=toupper(aux.correo[i]);

                //Alta del alumno a la LSO
                exito = AltaLSO(aux,LSO,&cant);
            }
            if(exito==1)
            {
                printf("Alumno repetido (Alta no exitosa)\n");
            }
            else
            {
                if(exito==0)
                {
                    printf("El Alumno se ha cargado correctamente\n");
                }
            }
            system("pause");
            system("cls");
            break;
        case 2:

            if(cant==0)
            {
                printf("No hay datos de Alumnos cargados en el sistema\n");
                system("pause");
            }
            else
            {
                printf("\nIngrese el codigo del Alumno que desea eliminar: ");
                scanf(" %[^\n]",aux.codigo);
                for(i=0; aux.codigo[i] != '\0'; i++)
                    aux.codigo[i]=toupper(aux.codigo[i]);
                system("cls");

                //Baja del alumno a eliminar
                exito=BajaLSO(aux,LSO,&cant);

                if(exito==0)
                {
                    printf("Se elimino el Alumno correctamente\n");
                }
                if(exito==2)
                {
                    printf("No se encontro Alumno con el codigo ingresado (Baja no exitosa)\n");
                }
                if(exito==1)
                {
                    printf("Operacion cancelada\n");
                }
                system("pause");
            }
            system("cls");
            break;
        case 3:
            if(cant==0)
            {
                printf("No hay datos de Alumnos cargados en el sistema\n");
                system("pause");
            }
            else
            {
                printf("\nIngrese el codigo del Alumno que quiere modificar: ");
                scanf(" %[^\n]",codigo);
                for(i=0; codigo[i] != '\0'; i++)
                    codigo[i]=toupper(codigo[i]);

                //Modificar el alumno
                exito=ModificarLSO(LSO,codigo,cant);

                if(exito==1)
                {
                    printf("No se encontro Alumno con el codigo ingresado\n");
                }
                system("pause");
            }
            system("cls");
            break;
        case 4:
            if(cant==0)
            {
                printf("No hay datos de Alumnos cargados en el sistema\n");
                system("pause");
            }
            else
            {

                printf("\nIngrese el codigo del Alumno que quiere consultar: ");
                scanf(" %[^\n]",codigo);
                for(i=0; codigo[i] != '\0'; i++)
                    codigo[i]=toupper(codigo[i]);


                //Evocar al alumno
                if(EvocarLSO(&aux,LSO,codigo,cant)==0)
                {
                    printf("\nLos datos del Alumno ingresado son:");
                    printf("\nCodigo del Alumno: %s", aux.codigo);
                    printf("\nNombre y Apellido: %s", aux.nombre);
                    printf("\nCorreo electronico: %s", aux.correo);
                    printf("\nNota: %d", aux.nota);
                    printf("\nCondicion Final: %s\n", aux.condicion);
                }
                else printf("\nNo se encontro Alumno con el codigo ingresado (Evocacion no Exitosa)\n");
                system("pause");
            }
            system("cls");
            break;
        case 5:
            if(cant==TAM)
            {
                printf("Sistema lleno\n");
                system("pause");
                system("cls");
            }
            else
            {
                if(Precarga(LSO, &cant)==1)
                {
                    printf("\nTodos los Alumnos fueron cargados con exito\n");
                    system("pause");
                    system("cls");
                }
            }
            break;

        case 6:
            if(cant == 0)
            {
                printf("No hay datos de Alumnos cargados en el sistema\n");
                system("pause");
            }
            else
            {
                MostraLSO(LSO,cant);
            }
            system("cls");
            break;


        }
    }
    while (opcion!=7);

    return 0;
}
