#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Empleado.h"

int parser_parseEmpleados(char* fileName, LinkedList* listaEmpleados)
{
    Empleado* empleadoAux;
    int retorno=-1;
    int r;
    char auxId[50];
    char auxHorasTrabajadas[50];
    char auxNombre[50];
    char auxSueldo[50];
    int cantidadEstructuras=0;

    if(listaEmpleados!=NULL)
    {
        FILE *pFile;

        pFile=fopen(fileName,"r");
        if(pFile!=NULL)
        {
            do
            {
                r=fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
                if(r==4)
                {
                    cantidadEstructuras++;
                }
            }
            while(!feof(pFile));

            //Creo el puntero y asigno memoria de acuerdo a la cantidad de datos

            Empleado* auxEmpleado;
            auxEmpleado=(Empleado*)malloc(sizeof(Empleado)*cantidadEstructuras);

            rewind(pFile); //volver el indicador de posici�n al principio del archivo

            do
            {
                r=fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
                if(r==4)
                {
                    empleadoAux = employee_newParametros(auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
                    if(empleadoAux!=NULL)
                    {
                        ll_add(listaEmpleados,empleadoAux);
                    }
                }
                else
                {
                    break;
                }
            }
            while(!feof(pFile));
            fclose(pFile);
            retorno=1;
        }
    }
    return retorno;//return 1;
    //return 1; // OK
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    Empleado* empleado;
    int retorno=-1;
    int r;
    char auxId[50];
    char auxHorasTrabajadas[50];
    char auxNombre[50];
    char auxSueldo[50];

    empleado = employee_new();

    if(pFile!=NULL && pArrayListEmployee!=NULL)
    {
        r=fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo);

        do
        {
            r=fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
            if(r==4)
            {
                empleado = employee_newParametros(auxId,auxNombre,auxHorasTrabajadas,auxSueldo);

                if(empleado!=NULL)
                {
                    ll_add(pArrayListEmployee,empleado);
                    retorno=0;
                }
            }
            else
            {
                break;
            }

        }
        while(!feof(pFile));
    }
    return retorno;//return 1;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
    Empleado* empleado;
    int retorno=-1;
    int cantidad;

    if(pFile!=NULL && pArrayListEmployee!=NULL)
    {
        do
        {
            empleado=employee_new();
            cantidad=fread(empleado,sizeof(Empleado),1,pFile);
            if(empleado!=NULL && cantidad==1)
            {
                ll_add(pArrayListEmployee,empleado);
                retorno=0;
            }
        }
        while(!feof(pFile));
    }
    return retorno;//return 1;
}
