#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Punto
{
    float x;
    float y;
};

void leer_punto(struct Punto *c)
{

    printf("Introduce el valor de x: ");
    scanf("%f", &c -> x);
    printf("Introduce el valor de y: ");
    scanf("%f", &c -> y);
}

void mostrar_punto(struct Punto c)
{

    printf("Coordenada: (%f, %f)\n", c.x, c.y);               /*Pablo Andérica Torrado*/
}

float calcular_distancia(struct Punto p1, struct Punto p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int main(void)
{

    struct Punto p1, p2;

    printf("Ingrese el primer punto:\n");
    leer_punto(&p1);

    printf("\nIngrese el segundo punto:\n");
    leer_punto(&p2);

    printf("\nEl primer punto es: ");
    mostrar_punto(p1);

    printf("El segundo punto es: ");
    mostrar_punto(p2);

    printf("\nLa distancia entre los puntos es: %.2f\n", calcular_distancia(p1,p2));

    return 0;
}
