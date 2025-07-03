#include <stdlib.h>
#include <stdio.h>

typedef struct tipoRegistro {
    char  titulo[80];
    char  director[48];
    int   anioEstreno;
} tipoRegistro;

typedef struct tipoNodo {
    tipoRegistro     info;
    struct tipoNodo *sig;
} tipoNodo;

typedef tipoNodo *ListaEnlazada;

ListaEnlazada crearListaOrdenadaPorAnio(tipoRegistro **registros, int *numError){

    if (registros == NULL || numError == NULL)
    {
        *numError = -1;
        return NULL;
    }

    tipoNodo *raiz = NULL;
    

    for (int i = 0; registros[i] != NULL; i++)
    {
        tipoNodo *nuevo = malloc(sizeof *nuevo);
        nuevo->info.titulo = registros[i]->titulo;
        nuevo->info.director = registros[i]->director;
        nuevo->info.anioEstreno = registros[i]->anioEstreno;
    }
    

    












}