#include <stdlib.h>
#include <stdio.h>
#include "listaEnlazadaSimple.h"

int guardarListaEnlazadaTexto(ListaEnlazada raiz, char *nombreFichero)
{

    FILE *f = fopen(nombreFichero, "w");

    if (!f)
    {
        return -1;
    }

    tipoNodo *p = raiz;
    int escritos = 0;

    while (p)
    {
        fprintf(f, "%d ", p->info);
        escritos++;
        p = p->sig;
    }

    fclose(f);
    return escritos;
}

int cargarListaEnlazadaTexto(ListaEnlazadaRef raiz, char *nombreFichero)
{

    if (raiz == NULL || nombreFichero == NULL)
    {
        return -1;
    }

    FILE *f = fopen(nombreFichero, "r");

    if (!f)
    {
        fclose(f);
        return -1;
    }

    tipoNodo *nuevo, *p;
    *nuevo == NULL;
    *p == NULL;
    int leidos = 0, valor, ret;

    while ((ret = fscanf(f, "%d", &valor)) != EOF)
    {
        *nuevo = malloc(sizeof *nuevo);

        if (nuevo == NULL)
        {
            fclose(f);
            return -1;
        }

        if (ret != 1)
        {
            fclose(f);
            *raiz = *nuevo;
            return -2;
        }

        nuevo->info = valor;
        nuevo->sig = NULL;

        if (*raiz == NULL || (*raiz)->info > valor)
        {
            nuevo->sig = *raiz;
            *raiz = nuevo;
            leidos++;
        }
        else
        {

            *p = *raiz;

            while (p && p->info < valor)
            {
                p = p->sig;
            }

            nuevo->sig = p->sig;
            p->sig = nuevo;

            leidos++;
        }
    }
    fclose(f);
    return leidos;
}
