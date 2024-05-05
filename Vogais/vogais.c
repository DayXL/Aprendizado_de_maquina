#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../Perceptron/perceptron.h"

int main(void) {
    srand(time(NULL));

    Neuronio* neuA = preencher_neu(5, 26, 0.01, 1);
    Neuronio* neuE = preencher_neu(5, 26, 0.01, 1);
    Neuronio* neuI = preencher_neu(5, 26, 0.01, 1);

    int tentativas = 100;
    double taxa = 0, ea = 0;

    printf("Letra A: \n");
    recuperar(neuA, "A", "./Vogais/vogais.txt");

    sortear_pesos(neuA, 26);
    ea = controlar_aprendizado(neuA, tentativas, 26);

    mostrar_pesos(neuA, 26);

    taxa = calc_taxa_aprend(neuA, ea);

    printf("Taxa de aprendizado foi de: %.0f%%. \n", taxa);
     
    taxa = 0, ea = 0;

    printf("Letra E: \n");
    recuperar(neuE, "E", "./Vogais/vogais.txt");

    sortear_pesos(neuE, 26);
    ea = controlar_aprendizado(neuE, tentativas, 26);

    mostrar_pesos(neuE, 26);

    taxa = calc_taxa_aprend(neuE, ea);

    printf("Taxa de aprendizado foi de: %.0f%%. \n", taxa);

    taxa = 0, ea = 0;

    printf("Letra I: \n");
    recuperar(neuI, "I", "./Vogais/vogais.txt");

    sortear_pesos(neuI, 26);
    ea = controlar_aprendizado(neuI, tentativas, 26);

    mostrar_pesos(neuI, 26);

    taxa = calc_taxa_aprend(neuI, ea);

    printf("Taxa de aprendizado foi de: %.0f%%. \n", taxa);

    return 0;
}

