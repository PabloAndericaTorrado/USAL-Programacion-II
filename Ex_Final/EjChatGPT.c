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

int leerFicheroEnListaPorAnio(ListaEnlazadaRef raiz, char *nombreFichero, int anioInicio, int anioFin)
{

    if (raiz == NULL || nombreFichero == NULL)
    {
        return -1;
    }
    if (anioInicio > anioFin)
    {
        int temp = anioInicio;
        anioInicio = anioFin;
        anioFin = temp;
    }

    FILE *f = fopen(nombreFichero, "r");
    if (!f)
    {
        return -2;
    }

    char titulo[80], director[48];
    int anio, ret, leidos = 0;
    while ((ret = fscanf(f, "%79c"
                            "%44c"
                            "%4d\n",
                         titulo, director, &anio)) == 3)
    {
        if (anio >= anioInicio && anio <= anioFin)
        {
            tipoNodo *nuevo = malloc(sizeof(*nuevo));
            if (!nuevo)
            {

                fclose(f);
                return -2;
            }

            nuevo->info.titulo = titulo;
            nuevo->info.director = director;
            nuevo->info.anioEstreno = anio;
            nuevo->sig = NULL;

            tipoNodo *p = *raiz;
            tipoNodo *prev = NULL;

            if (*raiz == NULL || (*raiz)->info.anioEstreno > anio)
            {
                nuevo->sig = *raiz;
                *raiz = nuevo;
                leidos++;
            }
            else if (p->info.anioEstreno > anioFin)
            {
                fclose(f);
                break;
            }
            else
            {

                while (p && p->info.anioEstreno < anio)
                {
                    prev = p;
                    p = p->sig;
                }
                prev->sig = nuevo;
                nuevo->sig = p;
                leidos++;
            }
        }
    }
    fclose(f);
    return leidos;
}