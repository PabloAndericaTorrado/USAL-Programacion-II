#include <stdio.h>
#include <stdlib.h>

enum Meses {
    ENERO = 1, FEBRERO, MARZO, ABRIL, MAYO, JUNIO,
    JULIO, AGOSTO, SEPTIEMBRE, OCTUBRE, NOVIEMBRE, DICIEMBRE
};

struct Mes {
    char nombre[20];
    char abreviatura[4];
    int dias;
    int orden;
};

int diasTranscurridos(enum Meses mes, int dia) {
    struct Mes meses[12] = {
        {"Enero",      "Ene", 31, ENERO},
        {"Febrero",    "Feb", 28, FEBRERO},
        {"Marzo",      "Mar", 31, MARZO},
        {"Abril",      "Abr", 30, ABRIL},
        {"Mayo",       "May", 31, MAYO},
        {"Junio",      "Jun", 30, JUNIO},
        {"Julio",      "Jul", 31, JULIO},
        {"Agosto",     "Ago", 31, AGOSTO},
        {"Septiembre", "Sep", 30, SEPTIEMBRE},
        {"Octubre",    "Oct", 31, OCTUBRE},
        {"Noviembre",  "Nov", 30, NOVIEMBRE},
        {"Diciembre",  "Dic", 31, DICIEMBRE}
    };
    
    if(mes < ENERO || mes > DICIEMBRE) {
        printf("Error: El mes debe estar entre 1 y 12.\n");
        return -1;
    }
    if(dia < 1 || dia > meses[mes - 1].dias) {
        printf("Error: Dia invalido para el mes de %s.\n", meses[mes - 1].nombre);
        return -1;
    }
    
    int total = 0;
   
    for (int i = 0; i < mes - 1; i++) {
        total += meses[i].dias;
    }
    total += dia;
    
    return total;
}

int main(void) {
    int mes, dia;
    
    printf("Introduce el numero del mes (1-12): ");
    scanf("%d", &mes);
    printf("Introduce el dia del mes: ");
    scanf("%d", &dia);
    
    int totalDias = diasTranscurridos(mes, dia);
    
    if(totalDias != -1) {
        printf("Hasta el dia %d del mes %d, han transcurrido %d dias en el año.\n", dia, mes, totalDias);
    }
    
    return 0;
}