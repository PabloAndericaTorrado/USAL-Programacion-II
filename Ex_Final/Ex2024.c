#include <stdio.h>
#include <stdlib.h>

typedef struct matInt
{
    int **m;    // puntero a un array de punteros (matriz)
    int numFil; // número de filas = nº de días
    int numCol; // número de columnas = nº de horas
} matInt;

typedef struct tipoInfo
{
    int dia;     // día del mes
    int horas;   // nº de horas en ese día con producción ≥ umbral
    float media; // media de energía generada en esas horas
} tipoInfo;

typedef struct tipoNodo
{   
    tipoInfo info;
    struct tipoNodo *sig;
} tipoNodo;

typedef tipoNodo *ListaEnlazada;

int escribirListaEnFichero(ListaEnlazada *lista, int minHoras, const char *nombreFichero);

int obtenerGeneraMinMes(matInt *mat, int generaMin, ListaEnlazada *lista)
{

    if (mat == NULL || mat->m == NULL || mat->numFil < 0 || mat->numCol < 0)
    {
        return -1;
    }

    *lista = NULL;
    int cont = 0;

    for (int i = 0; i < mat->numFil; i++)
    {
        int cuenta = 0;
        long suma = 0;

        /* 1) Contar y sumar horas que cumplen el umbral */
        for (int j = 0; j < mat->numCol; j++)
        {
            int val = mat->m[i][j];
            if (val >= generaMin)
            {
                cuenta++;
                suma += val;
            }
        }

        if (cuenta > 0)
        {
            tipoNodo *nuevo = malloc(sizeof(*nuevo));
            if (!nuevo)
            {
                tipoNodo *tmp;
                while (*lista)
                {
                    tmp = *lista;
                    *lista = (*lista)->sig;
                    free(tmp);
                }
                return 0;
            }
            *nuevo->info.dia = i + 1;
            *nuevo->info.horas = suma;
            *nuevo->info.media = (float)(suma / cuenta);
            *nuevo->sig = NULL;

            if (*lista == NULL)
            {
                *lista = nuevo;
            }
            else
            {
                tipoNodo *p = *lista;
                while (p->sig)
                {
                    p = p->sig;
                }
                p->sig = nuevo;
            }
            cont++;
        }
    }

    return cont;
}

int escribirListaEnFichero(ListaEnlazada *lista, int minHoras, const char *nombreFichero)
{

    if (lista == NULL || nombreFichero == NULL)
    {
        return -1;
    }

    FILE *f = fopen(nombreFichero, "w");

    if (!f)
    {
        return -2;
    }

    tipoNodo *p = *lista;
    tipoNodo *prev = NULL;
    int escritos = 0;

    while (p)
    {
        if (p->info.horas >= minHoras)
        {
            fprintf(f, "%3d"
                      "%10.2f"
                      "%7d",
                   p->info.dia, p->info.media, p->info.horas);
            escritos++;
            tipoNodo *aux = p;
            if (p == *lista)
            {
                *lista = p->sig;
                p = p->sig;
                free(aux);
            }
            else
            {
                prev->sig = p->sig;
                p = p->sig;
                free(aux);
            }
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
