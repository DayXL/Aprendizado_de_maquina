#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "../../Perceptron/perceptron.h"

void preencher_e_modificar(Neuronio *neu, char *str, char *arq){
    FILE *f = fopen(arq, "r");

    if (f == NULL) {
        printf("erro com o arquivo\n");
        exit(1);
    }
    char aux[256];
    int cont = 0;

    while(fscanf(f, "%s", aux) != EOF) {
        int i = 0, j = 0;
        char palavra[20];

        for(int k = 0; k < 20; k++)
            palavra[k] = '\0';

        while(aux[i] != '\0') {
            if(aux[i] != ','){
                palavra[j] = aux[i];
                j++;
            }
            else {
                montar_vetor(criar_bloco(atof(palavra)), neu, cont);

                for(int k = 0; k <= j; k++)
                    palavra[k] = '\0';

                j = 0;
            }
            i++;
        }

        montar_vetor(criar_bloco(0.0), neu, cont);
        montar_vetor(criar_bloco(strcmp(str, palavra) == 0? 1 : 0), neu, cont);
        cont++;

    }

    fclose(f);

}

double f(Bloco* valores, Bloco* referencia, double h, double o) {
    double distancia = 0;
    
    for(Bloco* i = valores; i != NULL; i = i->prox) {
        distancia += pow(i->value - referencia->value, 2);
        referencia = referencia->prox;
    }

    distancia = sqrt(distancia);

    return h * exp(-(pow(distancia, 2) / ( 2 * pow(o, 2))));
}

void flores(Neuronio* neu, char* flor, char* arq) {
    int tentativas = 1000;
    double taxa = 0, ea = 0;
    char arq_txt[12];
    sprintf(arq_txt, "../%s.txt", arq);

    printf("%s: \n", flor);
    preencher_e_modificar(neu, flor, arq_txt);

    //Escolhido aleatoriamente
    Bloco* referencia = neu->xn[7];

    for(int i = 1; i <= 150; i++) {
        Bloco *aux = neu->xn[i - 1];
        aux->prox->prox->prox->prox->value = f(aux->prox, referencia, 2.0, 2.0);

    }

    sortear_pesos(neu, 6);
    ea = controlar_aprendizado(neu, tentativas, 6);

    mostrar_pesos(neu, 6);

    taxa = calc_taxa_aprend(neu, ea);

    printf("Taxa de aprendizado foi de: %.0f%%. \n", taxa);
}

int main(void) {
    srand(time(NULL));

    Neuronio* neu1 = preencher_neu(150, 6, 0.01, 1);
    Neuronio* neu2 = preencher_neu(150, 6, 0.01, 1);
    Neuronio* neu3 = preencher_neu(150, 6, 0.01, 1);

    int tentativas = 1000;
    double taxa = 0, ea = 0;

    flores(neu1, "iris_setosa", "iris");
    flores(neu2, "iris_versicolor", "iris");
    flores(neu3, "iris_virginica", "iris");

    return 0;
}

