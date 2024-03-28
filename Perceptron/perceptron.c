#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "perceptron.h"

void embaralhar(Neuronio* neu) {
    for (int i = 0; i < neu->linhas; i++) {
        int j = rand() % neu->linhas;

        Bloco *temp = neu->xn[i];
        neu->xn[i] = neu->xn[j];
        neu->xn[j] = temp;
    }
}

void learn(Neuronio* neu, int n) {
    int true = 0, tentativa = 0;

    while (true == 0) {
        embaralhar(neu);
        tentativa++;
        true = 1;
        double e = 0;

        for(int j = 0; j < neu->linhas; j++) {
            double v = neu->w[n] * neu->b;
            Bloco* aux = neu->xn[j];

            for(int i = 0; i < n; i++) {
                v = v + neu->w[i] * aux->value;
                aux = aux->prox;
            }

            double y = v > 0? 1 : 0;
            double d = aux->value;
            e += (d - y) < 0? (d - y) * -1 : (d - y);

            if (y != d) {

                aux = neu->xn[j];
                for(int i = 0; i < n; i++) {
                    neu->w[i] = neu->w[i] + neu->n * (d - y) * aux->value;
                    aux = aux->prox;

                }
                neu->w[n] = neu->w[n] + neu->n * (d - y);
                true = 0;
            }

        }

        printf("Erro: %f\n", e);

    }

    printf("Tentativas: %d \n", tentativa);
    printf("W1 = %f, W2 = %f, W3 = %f, W4 = %f, W5 = %f\n", neu->w[0], neu->w[1], neu->w[2], neu->w[3], neu->w[4]);

}

Bloco* criar_bloco(double value) {
    Bloco *bloco = malloc(sizeof(Bloco));
    bloco->value = value;
    bloco->prox = NULL;

    return bloco;
}

void montar_vetor(Bloco *bloco, Neuronio *neu, int pos) {
    Bloco *aux = neu->xn[pos];

    if (aux == NULL) {
        neu->xn[pos] = bloco;
    } else {
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = bloco;
    }

}

void recuperar(Neuronio *neu, char *str){
    FILE *f = fopen("dados.txt", "r");
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
        montar_vetor(criar_bloco(strcmp(str, palavra) == 0? 1 : 0), neu, cont);
        cont++;

    }

}

Neuronio* preencher_neu(int linhas, double w, double n, float b) {
    Neuronio* neu = malloc(sizeof(Neuronio));
    neu->n = n;
    neu->linhas = linhas;
    neu->w = malloc(sizeof(double*) * w);
    neu->xn = malloc(sizeof(double*) * neu->linhas);
    neu->b = b;

    for (int i = 0; i < w; i++ ) {
        neu->w[i] = (rand() / (double)RAND_MAX) * 2 - 1;
    }

    return neu;
}

int main(void) {
    srand(time(NULL));

    Neuronio* neu1 = preencher_neu(150, 5, 0.01, 1);

    printf("Iris setosa: \n");
    recuperar(neu1, "iris_setosa");

    learn(neu1, 4);
     
    return 0;
}

