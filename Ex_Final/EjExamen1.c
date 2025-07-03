#include <stdlib.h>
#include <stdio.h>

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

ListaEnlazada crearListaOrdenadaPorAnio(tipoRegistro **registros, int *numError)
{

    if (registros == NULL || numError == NULL)
    {
        if (numError)
            *numError = -1;
        return NULL;
    }

    tipoNodo *raiz = NULL;
    tipoNodo *p = NULL;
    *numError = 0;


    for (int i = 0; registros[i] != NULL; i++)
    {
        tipoNodo *nuevo = malloc(sizeof(*nuevo));
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

        if (raiz == NULL || nuevo->info.anioEstreno < raiz->info.anioEstreno)
        {
            nuevo->sig = raiz;
            raiz = nuevo;
        }
        else
        {
            p = raiz;
            while (p->sig && p->sig->info.anioEstreno < nuevo->info.anioEstreno){
                p = p->sig;
            }
            nuevo->sig = p->sig;
            p->sig = nuevo;
        }
        (*numError)++;
    }
    for (int j = 0; registros[j] != NULL; j++)
        free(registros[j]);
    free(registros);
    return raiz;
}
