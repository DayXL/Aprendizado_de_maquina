#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "../Perceptron/perceptron.h"

double f(double x, double u, double h, double o) {
    return h * exp(-(pow((x - u), 2) / ( 2 * pow(o, 2))));
}

int main(void) {
    srand(time(NULL));

    Neuronio* n1 = preencher_neu(12, 3, 0.1, 1);

    int tentativas = 10000;
    double taxa = 0, ea = 0;

    recuperar(n1, "1", "teste.txt");

    do {
        taxa = 0, ea = 0;
        double var = rand() % 100;
        var = var / 100;
        int u = (rand() % 11) + 1;
        double h = 2.0;
        var = var + (double)u;
        double o = 2.0;

        for(int i = 1; i < 13; i++) {
            Bloco *aux = n1->xn[i - 1];
            aux->prox->value = f(aux->value, var, h, o);

        }

        sortear_pesos(n1, 3);

        ea = learn(n1, 2, tentativas);

        taxa = calc_taxa_aprend(n1, ea);

        printf("Para u = %lf a taxa de aprendizado foi de: %.0f%%. \n", var, taxa);

    } while(taxa < 100.0);

    return 0;
}