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

int escribirListaEnFicheroPorAnio(ListaEnlazadaRef raiz, char *nombreFichero, int anioInicio, int anioFin)
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

    FILE *f = fopen(nombreFichero, "w"); 

    if (!f)
    {
        return -2;
    }

    tipoNodo *p = *raiz;
    tipoNodo *prev = NULL;
    int escrito = 0;

    while (p)
    {
        if (p->info.anioEstreno >= anioInicio && p->info.anioEstreno <= anioFin)
        {
            fprintf(f,
                    "%-79.79s" /* título, left-justified ancho=79 */
                    "%44.44s"  /* director, right-justified ancho=44 */
                    "%4d\n",   /* año, right-justified ancho=4 */
                    p->info.titulo,
                    p->info.director,
                    p->info.anioEstreno);
            escrito++;
            tipoNodo *aux = p;
            int anio = p->info.anioEstreno;
            if (p == *raiz)
            {
                *raiz = p->sig;
                p = p->sig;
                free(aux);
            }
            else
            {
                prev->sig = p->sig;
                p = p->sig;
                free(aux);
            }

            if (anio == anioFin)
            {
                break;
            }
        }
        else
        {
            prev = p;
            p = p->sig;
        }
    }
    fclose(f);
    return escrito;
}
