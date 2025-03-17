#include <stdio.h>
#include <stdlib.h>

typedef struct
{

    char nombre[50];
    int edad;
    float altura;

} Persona;

int main()
{

    Persona p1 = {"Pablo", 21, 1.78};

    printf("%d\n", p1.edad);

    Persona *ptr = &p1;

    printf("%d\n", ptr->edad);

    Persona personas[3] = {
        {"Pablo", 21, 1.78},
        {"Ana", 22, 1.65},
        {"Luis", 23, 1.80}};
    for (int i = 0; i < 3; i++)
    {
        printf("Persona %d: Nombre: %s, Edad: %d, Altura: %.2f\n", i + 1, personas[i].nombre, personas[i].edad, personas[i].altura);
    }

    return 0;
}