#include <stdio.h>
#include <stdlib.h>
typedef struct tipoRegistro
{
    char titulo[80];
    char director[48];
    int anioEstreno;
} tipoRegistro;

typedef tipoRegistro *tipoRegistroRef;

typedef struct tipoNodo
{
    tipoRegistro info;
    struct tipoNodo *sig;
} tipoNodo;

typedef tipoNodo *ListaEnlazada;
typedef ListaEnlazada *ListaEnlazadaRef;

int escribirListaEnFIcheroporAnio(ListaEnlazadaRef raiz, char *nombreFichero, int anioInicio, int anioFin)
{

    if (raiz == NULL || nombreFichero == NULL)
    {
        return -1;
    }
    else if (anioInicio > anioFin)
    {
        int temp = anioInicio;
        anioInicio = anioFin;
        anioFin = temp;
    }
    int escritos = 0;
    FILE *f = (nombreFichero, "w");
    if (!f)
    {
        return -2;
    }

    tipoNodo *p = *raiz;
    tipoNodo *prev;

    while (p)
    {
        if (p->info.anioEstreno >= anioInicio && p->info.anioEstreno <= anioFin)
        {

            fprintf(f,
                    "%-79.79s"
                    "%44.44s"
                    "%4d",
                    p->info.titulo,
                    p->info.director,
                    p->info.anioEstreno);
            tipoNodo *aux = *p;
            if (p->info.anioEstreno == anioFin)
            {
                prev->sig = p->sig;
                p = p->sig;
                free(*aux);
                escritos++;
                break;
            }

            prev->sig = p->sig;
            p = p->sig;
            free(*aux);
            escritos++;
        }
        else
        {
            prev = p;
            p = p->sig;
        }
    }
    fclose(f);
    return escritos;
}

ListaEnlazada crearListaOrdenadaPorAnio(tipoRegistro **registros, int *numError)
{

    if (registros == NULL || numError == NULL)
    {
        if (numError)
        {
            *numError = -1;
        }

        return NULL;
    }

    ListaEnlazada raiz = NULL;

    for (int i = 0; registros[i] != NULL; i++)
    {
        tipoNodo *nuevo = malloc(sizeof *nuevo);
        if (!nuevo)
        {
            tipoNodo *tmp;
            while (raiz)
            {
                tmp = raiz;
                raiz = raiz->sig;
                free(tmp);
            }
            *numError = -2;
            return NULL;
        }

        nuevo->info.titulo = registros[i]->titulo;
        nuevo->info.director = registros[i]->director;
        nuevo->info.anioEstreno = registros[i]->anioEstreno;
        nuevo->sig = NULL;

        if (raiz == NULL || (raiz)->info.anioEstreno > nuevo->info.anioEstreno)
        {
            nuevo->sig = *raiz;
            *raiz = nuevo;
            (*numError)++;
        }
        else
        {
            tipoNodo *p = raiz;
            tipoNodo *prev = NULL;
            while (p)
            {
                if (p->info.anioEstreno < nuevo->info.anioEstreno)
                {
                    prev = p;
                    p = p->sig;
                }
                else
                {
                    prev->sig = nuevo;
                    nuevo->sig = p;
                    p = p->sig;
                    (*numError)++;
                }
            }
        }
    }

    for (int i = 0; registros[i]; i++)
    {
        free(registros[i]);
    }
    free(registros);
    return raiz;
}