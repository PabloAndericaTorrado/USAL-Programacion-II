#include <stdio.h>
#include <stdlib.h>
#include "listaEnlazadaSimple.h"

int guardarListaEnlazadaTexto(ListaEnlazada raiz, char *nombreFichero){

    //La función debe crear un fichero de texto, usando la ruta que se pasa como argumento a través del segundo parámetro

    FILE *f = fopen(nombreFichero, "w");
    if (!f) {
        return -1;  /* no se pudo crear/abrir */
    }
    
    int escritos = 0;
    ListaEnlazada p = raiz;
    while (p  != NULL)
    {
        fprintf(f,"%d ",p->info);
        escritos++;
        p = p->sig;
    }
    
    fclose(f);

    return escritos;
}

int cargarListaEnlazadaTexto (ListaEnlazadaRef raiz, char *nombreFichero){

    if (nombreFichero == NULL || raiz == NULL) {
        return -1;
    }

    FILE *f = fopen(nombreFichero, "r");
    if (!f) {
        return -1;  /* error al abrir el fichero */
    }
    *raiz == NULL;
    int nodosCreados = 0, valor,leer;
    tipoNodo *aux,*p;

    while ((leer = fscanf(f,"%d",&valor)) != EOF)
    {
        if (leer != 1)
        {
            fclose(f);
            return -2;
        }
        tipoNodo *nuevo = malloc(sizeof *nuevo);
         if (!nuevo) {
            fclose(f);
            return -2;
        }
        nuevo->info = valor;
        nuevo->sig = NULL;

        if (raiz == NULL || (*raiz)->info > valor)
        {
            nuevo->sig = *raiz;
            *raiz = nuevo;
        }else{

            p = *raiz;
            while (p && p->info < valor)
            {
                p=p->sig;
            }
            *aux = p;
            p = p->sig;
            aux->sig = nuevo;
            nuevo->sig = p;
        }
        nodosCreados++;
    }

    fclose(f);
    return nodosCreados;
}
