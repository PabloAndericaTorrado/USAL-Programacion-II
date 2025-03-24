#include <stdlib.h>
#include <stdio.h>

#define NUM_EVA_CONT 5
#define NUM_ESTUDIANTES 300

typedef struct
{
    char nombre[80];
    char dni[10];
    float pruebasContinua[NUM_EVA_CONT];
    float calificacionExamenFinal;
} tipoEstudiante;

int calcularCalificaciones(tipoEstudiante *estudiantes, int numEstudiantes,
                           float *calificacionesFinales, float *promediosPruebas,
                           int *numeroAprobados)
{

    if (estudiantes == NULL)
    {
        return -1;
    }
    else if (numEstudiantes <= 0)
    {
        return -2;
    }
    else if (calificacionesFinales == NULL || promediosPruebas == NULL || numeroAprobados == NULL)
    {
        return -3;
    }

    *numeroAprobados = 0;

    float mediaContinua = 0.0, totalContinua = 0.0;

    for (int i = 0; i < numEstudiantes; i++)
    {
        mediaContinua = 0.0;
        for (int j = 0; j < NUM_EVA_CONT; j++)
        {

            mediaContinua = mediaContinua + estudiantes[i].pruebasContinua[j];
        }

        totalContinua = mediaContinua / NUM_EVA_CONT;
        calificacionesFinales[i] = (totalContinua * 0.5) + (estudiantes[i].calificacionExamenFinal * 0.5);
        if (calificacionesFinales[i] >= 5)
        {
            (*numeroAprobados)++;
        }
    }

    float promedioContinua = 0.0;
    for (int j = 0; j < NUM_EVA_CONT; j++)
    {
        promedioContinua = 0.0;
        for (int i = 0; i < numEstudiantes; i++)
        {
            promedioContinua = promedioContinua + estudiantes[i].pruebasContinua[j];
        }

        promediosPruebas[j] = promedioContinua / numEstudiantes;
    }

    return 0;
}

int main()
{

    tipoEstudiante vectorEstudiantes[NUM_ESTUDIANTES];
    float calificacionesFinales[NUM_ESTUDIANTES];
    float promediosPruebas[NUM_EVA_CONT];
    int numEstudiantes, numAprobados;

    int resultado = calcularCalificaciones(vectorEstudiantes, numEstudiantes, calificacionesFinales, promediosPruebas, &numAprobados);

    if (resultado == 0)
    {
        printf("Todo Correcto");
    }

    return 0;
}
