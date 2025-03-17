#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Fraccion
{
    float numerador;
    float denominador;
};

void leer_fraccion(struct Fraccion *f)
{

    printf("Introduce el valor del numerador: ");
    scanf("%f", &f->numerador);
    printf("Introduce el valor del denominador: ");
    do
    {
        scanf("%f", &f->denominador);
        if (f->denominador == 0)
        {
            printf("El denominador no puede ser 0");
        }
    } while (f->denominador == 0);
}
void mostrar_fraccion(struct Fraccion f)
{
    printf("Fracción: %.2f / %.2f\n", f.numerador, f.denominador);
}

int mcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    //printf("%d/n",a);
    return a; 
}

int mcm(int a, int b) {
    return (a * b) / mcd(a, b); 
}

struct Fraccion operarFracciones(struct Fraccion f1, char opcion, struct Fraccion f2) {     /*Pablo Andérica Torrado*/
    struct Fraccion resultado;
    int mcm_denominador;
    switch(opcion) {
        case '+':
            mcm_denominador = mcm(f1.denominador, f2.denominador); // mcm de los denominadores
            resultado.numerador = (f1.numerador * (mcm_denominador / f1.denominador)) + (f2.numerador * (mcm_denominador / f2.denominador)); 
            resultado.denominador = mcm_denominador; 
            break;
        case '-':
            mcm_denominador = mcm(f1.denominador, f2.denominador); // mcm de los denominadores
            resultado.numerador = (f1.numerador * (mcm_denominador / f1.denominador)) - (f2.numerador * (mcm_denominador / f2.denominador));
            resultado.denominador = mcm_denominador;
            break;
        case '*':
            resultado.numerador = f1.numerador * f2.numerador;
            resultado.denominador = f1.denominador * f2.denominador;
            break;
        case '/':
            if(f2.numerador == 0) {
                printf("Error: No se puede dividir entre una fracción con numerador 0.\n");
                exit(1); 
            }
            resultado.numerador = f1.numerador * f2.denominador;
            resultado.denominador = f1.denominador * f2.numerador; 
            break;
        default:
            printf("Operación no válida.\n");
            exit(1); 
    }
    return resultado; 
}


int main(void)
{

    struct Fraccion f1, f2, resultado;
    char operacion;

    printf("Ingrese la primera fracción:\n");
    leer_fraccion(&f1);

    printf("\nIngrese la segunda fracción:\n");
    leer_fraccion(&f2);

    printf("\nLa primera fracción es: ");
    mostrar_fraccion(f1);

    printf("La segunda fracción es: ");
    mostrar_fraccion(f2);

    printf("\nIngrese la operación (+, -, *, /): ");
    scanf(" %c", &operacion);

    resultado = operarFracciones(f1, operacion, f2);
    mostrar_fraccion(resultado);


    return 0;
}
