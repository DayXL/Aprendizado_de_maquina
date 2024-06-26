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

double learn(Neuronio* neu, int n, int max) {
    int true = 0, tentativa = 0, con = 0;
    double menor = 0;

    while (true == 0 && con <= max) {
        embaralhar(neu);
        tentativa++;
        con++;
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

        menor = e;

    }

    return menor;
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

void recuperar(Neuronio *neu, char *str, char *arq){
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
        montar_vetor(criar_bloco(strcmp(str, palavra) == 0? 1 : 0), neu, cont);
        cont++;

    }

    fclose(f);

}

Neuronio* preencher_neu(int linhas, double w, double n, float b) {
    Neuronio* neu = malloc(sizeof(Neuronio));
    neu->n = n;
    neu->linhas = linhas;
    neu->w = malloc(sizeof(double*) * w);
    neu->bw = malloc(sizeof(double*) * w);
    neu->xn = malloc(sizeof(double*) * neu->linhas);
    neu->b = b;

    return neu;
}

double controlar_aprendizado(Neuronio* neu, int tentativas, int pesos) {
    double ea = neu->linhas, en = 0, taxa = 0;
    int t = 0;

    do {
        en = learn(neu, pesos - 1, tentativas);

        if (en < ea) {
            ea = en;

            for (int i = 0; i < pesos; i++ ) {
                neu->bw[i] = neu->w[i];
            }

        }

        neu->n = neu->n / 10;
        tentativas = tentativas * 2;
        t++;

    } while(t < 10 && en != 0);

    return ea;
}

void mostrar_pesos(Neuronio* neu, int tam) {
    for (int i = 0; i < tam; i++ ) {
        if (i != tam -1) {
            printf("W%d = %f\n", i + 1, neu->bw[i]);
        }
        else {
            printf("WB = %f\n", neu->bw[i]);
        }
        

    }
}

double calc_taxa_aprend(Neuronio* neu, double e) {
    double taxa = (e * 100) / neu->linhas;
    taxa = 100 - taxa;
    return taxa;
}

void sortear_pesos(Neuronio* neu, int quant) {
    for (int i = 0; i < quant; i++ ) {
        neu->w[i] = (rand() / (double)RAND_MAX) * 2 - 1;
    }
}