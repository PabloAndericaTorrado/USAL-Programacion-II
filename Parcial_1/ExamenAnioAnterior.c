#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_MESES 12
#define NUM_VIVIENDAS 10

typedef struct
{

    char idCatastro[21];
    char propietario[80];
    char direccion[128];
    float superficie;
    float consumos[NUM_MESES];
} tipoVivienda;

int procesarConsumos(tipoVivienda *viviendas, int numV,
                     float *conMedioViviendas, float *conMaxViviendas,
                     float *conMedioMeses, float *conMaxMeses)
{

    if (viviendas == NULL)
    {
        return -1;
    }
    else if (numV <= 0 || numV > NUM_VIVIENDAS)
    {
        return -2;
    }
    else if (conMaxViviendas == NULL || conMedioMeses == NULL || conMaxMeses == NULL)
    {

        return -3;
    }

    float media, maximo;
    for (int i = 0; i < numV; i++)
    {
        media = 0.0;
        maximo = 0.0;

        for (int j = 0; j < NUM_MESES; j++)
        {
            media += viviendas[i].consumos[j];
            if (maximo < viviendas[i].consumos[j])
            {
                maximo = viviendas[i].consumos[j];
            }
        }
        conMedioViviendas[i] = media / NUM_MESES;
        conMaxViviendas[i] = maximo;
    }
    float mediaMeses, maxConsumoMes;

    for (int j = 0; j < NUM_MESES; j++)
    {
        mediaMeses = 0.0;
        for (int i = 0; i < numV; i++)
        {
            mediaMeses += viviendas[i].consumos[j];
        }

        conMedioMeses[j] = mediaMeses / numV;
    }

    for (int j = 0; j < NUM_MESES; j++)
    {
        maxConsumoMes = 0.0;
        for (int i = 0; i < numV; i++)
        {
            if (maxConsumoMes < viviendas[i].consumos[j])
            {
                maxConsumoMes = viviendas[i].consumos[j];
            }
        }

        conMaxMeses[j] = maxConsumoMes;
    }

    return 0;
}

void mostrarRegistros(tipoVivienda *v, int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("Vivienda %d:\n", i + 1);
        printf("  ID Catastro: %s\n", v[i].idCatastro);
        printf("  Propietario: %s\n", v[i].propietario);
        printf("  Direccion: %s\n", v[i].direccion);
        printf("  Superficie: %.2f\n", v[i].superficie);
        printf("  Consumos de agua (m3) por mes:\n");
        for (int j = 0; j < NUM_MESES; j++)
        {
            printf("    Mes %d: %.2f\n", j + 1, v[i].consumos[j]);
        }
    }
}

void cargarRegistrosAleatorios(tipoVivienda *v, int num)
{
    srand(time(NULL));

    for (int i = 0; i < num; i++)
    {
        snprintf(v[i].idCatastro, sizeof(v[i].idCatastro), "ID%02d", i + 1);
        snprintf(v[i].propietario, sizeof(v[i].propietario), "Propietario %d", i + 1);
        snprintf(v[i].direccion, sizeof(v[i].direccion), "Direccion %d", i + 1);
        v[i].superficie = (float)(rand() % 100 + 50);

        for (int j = 0; j < NUM_MESES; j++)
        {
            v[i].consumos[j] = (float)(rand() % 100);
        }
    }
}

int main()
{

    tipoVivienda viviendas[NUM_VIVIENDAS] = {
        {"ID1", "Propietario1", "Direccion1", 100.0, {10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0}},       // Media: 65.0
        {"ID2", "Propietario2", "Direccion2", 110.0, {15.0, 25.0, 35.0, 45.0, 55.0, 65.0, 75.0, 85.0, 95.0, 105.0, 115.0, 125.0}},       // Media: 70.0
        {"ID3", "Propietario3", "Direccion3", 120.0, {20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0}},      // Media: 75.0
        {"ID4", "Propietario4", "Direccion4", 130.0, {25.0, 35.0, 45.0, 55.0, 65.0, 75.0, 85.0, 95.0, 105.0, 115.0, 125.0, 135.0}},      // Media: 80.0
        {"ID5", "Propietario5", "Direccion5", 140.0, {30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0, 140.0}},     // Media: 85.0
        {"ID6", "Propietario6", "Direccion6", 150.0, {35.0, 45.0, 55.0, 65.0, 75.0, 85.0, 95.0, 105.0, 115.0, 125.0, 135.0, 145.0}},     // Media: 90.0
        {"ID7", "Propietario7", "Direccion7", 160.0, {40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0, 140.0, 150.0}},    // Media: 95.0
        {"ID8", "Propietario8", "Direccion8", 170.0, {45.0, 55.0, 65.0, 75.0, 85.0, 95.0, 105.0, 115.0, 125.0, 135.0, 145.0, 155.0}},    // Media: 100.0
        {"ID9", "Propietario9", "Direccion9", 180.0, {50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0, 140.0, 150.0, 160.0}},   // Media: 105.0
        {"ID10", "Propietario10", "Direccion10", 190.0, {55.0, 65.0, 75.0, 85.0, 95.0, 105.0, 115.0, 125.0, 135.0, 145.0, 155.0, 165.0}} // Media: 110.0
    };
    mostrarRegistros(viviendas, NUM_VIVIENDAS);
    float conMedioViviendas[NUM_VIVIENDAS];
    float conMaxViviendas[NUM_VIVIENDAS];
    float conMedioMeses[NUM_MESES];
    float conMaxMeses[NUM_MESES];

    int resultado = procesarConsumos(viviendas, NUM_VIVIENDAS, conMedioViviendas, conMaxViviendas, conMedioMeses, conMaxMeses);

    if (resultado == 0)
    {
        printf("Procesamiento exitoso.\n");
        for (int i = 0; i < NUM_VIVIENDAS; i++)
        {
            printf("Vivienda %d - Consumo medio: %.2f, Consumo maximo: %.2f\n", i + 1, conMedioViviendas[i], conMaxViviendas[i]);
        }
        for (int j = 0; j < NUM_MESES; j++)
        {
            printf("Mes %d - Consumo medio: %.2f, Consumo maximo: %.2f\n", j + 1, conMedioMeses[j], conMaxMeses[j]);
        }
    }
    else
    {
        printf("Error en el procesamiento de consumos. Codigo de error: %d\n", resultado);
    }

    return 0;
}