#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../../Perceptron/perceptron.h"

int main(void) {
    srand(time(NULL));

    Neuronio* neu1 = preencher_neu(4, 3, 0.01, 1);

    int tentativas = 100;
    double taxa = 0, ea = 0;

    printf("Porta OR: \n");
    recuperar(neu1, "1", "./Portas_lógicas/or/or.txt");

    sortear_pesos(neu1, 3);
    ea = controlar_aprendizado(neu1, tentativas, 3);

    mostrar_pesos(neu1, 3);

    taxa = calc_taxa_aprend(neu1, ea);

    printf("Taxa de aprendizado foi de: %.0f%%. \n", taxa);
     
    return 0;
}

