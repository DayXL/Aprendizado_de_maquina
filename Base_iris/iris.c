#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../Perceptron/perceptron.h"

int main(void) {
    srand(time(NULL));

    Neuronio* neu1 = preencher_neu(150, 5, 0.01, 1);
    Neuronio* neu2 = preencher_neu(150, 5, 0.01, 1);
    Neuronio* neu3 = preencher_neu(150, 5, 0.01, 1);
    int tentativas = 100;
    double taxa = 0, ea = 0;

    printf("Iris setosa: \n");
    recuperar(neu1, "iris_setosa", "./Base_iris/iris.txt");

    sortear_pesos(neu1, 5);
    ea = controlar_aprendizado(neu1, tentativas, 5);

    mostrar_pesos(neu1, 5);

    taxa = calc_taxa_aprend(neu1, ea);

    printf("Taxa de aprendizado foi de: %.0f%%. \n", taxa);

    printf("\nIris versicolor: \n");
    recuperar(neu2, "iris_versicolor", "./Base_iris/iris.txt");

    sortear_pesos(neu2, 5);
    ea = controlar_aprendizado(neu2, tentativas, 5);

    mostrar_pesos(neu2, 5);

    taxa = calc_taxa_aprend(neu2, ea);

    printf("Taxa de aprendizado foi de: %.0f%%. \n", taxa);

    printf("\nIris virginica: \n");
    recuperar(neu3, "iris_virginica", "./Base_iris/iris.txt");

    sortear_pesos(neu3, 5);
    ea = controlar_aprendizado(neu3, tentativas, 5);

    mostrar_pesos(neu3, 5);

    taxa = calc_taxa_aprend(neu3, ea);

    printf("Taxa de aprendizado foi de: %.2f%%. \n", taxa);
     
    return 0;
}

