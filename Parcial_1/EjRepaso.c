#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_COCHES 20

enum colores
{
    otros = 0,
    azul,
    rojo,
    negro,
    blanco,
    verde,
    naranja,
    amarillo,
    morado,
    marron
};

typedef struct
{

    char matricula[8];
    int color;
    float peso;

} estructuraCoche;

typedef struct
{

    int idTaller;
    estructuraCoche coches[20];

} estructuraTalleres;
// aray de talleres                          dimension           arrayEnteros                                                  idTaller        NumBlancos              orden de pesos
int organizacionCoches(estructuraTalleres *talleresSalamanca, int numeroTalleres, int *cochesColor, char *matricula, int *taller, int *cochesBlancos, float *pesosTaller12Orden,
                       float *cochePesado)
{

    if (talleresSalamanca == NULL)
    {
        return -1;
    }
    else if (cochesColor == NULL || pesosTaller12Orden == NULL)
    {

        return -2;
    }
    else if (sizeof(talleresSalamanca) <= 0)
    {

        return -3;
    }
    // inicializar
    for (int i = 0; i < 10; i++)
    {
        cochesColor[i] = 0;
    }

    // colores
    int color = 0;
    for (int i = 0; i < numeroTalleres; i++)
    {
        for (int j = 0; j < NUM_COCHES; j++)
        {

            color = talleresSalamanca[i].coches[j].color;
            cochesColor[color]++;
        }
    }

    *taller = 0;
    for (int i = 0; i < numeroTalleres; i++)
    {
        for (int j = 0; j < NUM_COCHES; j++)
        {

            if (strcmp(talleresSalamanca[i].coches[j].matricula, matricula) == 0)
            {
                *taller = talleresSalamanca[i].idTaller;
                return 0;
            }
        }
    }

    float maxPesado = 0.0;

    for (int i = 0; i < numeroTalleres; i++)
    {
        for (int j = 0; j < NUM_COCHES; j++)
        {
            if (talleresSalamanca[i].coches[j].peso > maxPesado)
            {
                *cochePesado = talleresSalamanca[i].coches[j].peso;
            }
        }
    }

    return 0;
}

int main()
{

    estructuraTalleres talleresSalamanca[12] = {
        {1, {{"1234ABC", azul, 1200.0}, {"5678DEF", rojo, 1300.0}, {"9101GHI", negro, 1400.0}, {"1121JKL", blanco, 1500.0}}},
        {2, {{"AAAA111", azul, 1100.0}, {"BBBB222", rojo, 1250.0}, {"CCCC333", negro, 1350.0}, {"DDDD444", blanco, 1450.0}}},
        {12, {{"AAAA111", azul, 1100.0}, {"BBBB222", rojo, 1250.0}, {"CCCC333", negro, 1350.0}, {"DDDD444", blanco, 1450.0}, {"EEEE555", verde, 1550.0},
              {"FFFF666", naranja, 1650.0}, {"GGGG777", amarillo, 1750.0}, {"HHHH888", morado, 1850.0}, {"IIII999", marron, 1950.0}, {"JJJJ000", otros, 2050.0},
              {"KKKK111", azul, 2150.0}, {"LLLL222", rojo, 2250.0}, {"MMMM333", negro, 2350.0}, {"NNNN444", blanco, 2450.0}, {"OOOO555", verde, 2550.0},
              {"PPPP666", naranja, 2650.0}, {"QQQQ777", amarillo, 2750.0}, {"RRRR888", morado, 2850.0}, {"SSSS999", marron, 2950.0}, {"TTTT000", otros, 3050.0}}}};

    int cochesColor[10] = {0};
    int taller = 0;
    char matricula[] = "5678DEF";
    int cochesBlancos = 0;
    float pesosTaller12Orden[NUM_COCHES] = {0};
    float cochePesado = 0.0;

    organizacionCoches(talleresSalamanca, 12, cochesColor, matricula, &taller, &cochesBlancos, pesosTaller12Orden, &cochePesado);




    return 0;
}