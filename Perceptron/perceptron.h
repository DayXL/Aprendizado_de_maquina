typedef struct bloco {
    double value;
    struct bloco *prox;
} Bloco;

typedef struct neuronio {
    int linhas;
    double *w;
    double *bw;
    Bloco **xn;
    double n;
    float b;

} Neuronio;

void embaralhar(Neuronio* neu);
double learn(Neuronio* neu, int n, int max);
Bloco* criar_bloco(double value);
void montar_vetor(Bloco *bloco, Neuronio *neu, int pos);
void recuperar(Neuronio *neu, char *str);
Neuronio* preencher_neu(int linhas, double w, double n, float b);
double controlar_aprendizado(Neuronio* neu, int tentativas);
void mostrar_pesos(Neuronio* neu, int tam);
double calc_taxa_aprend(Neuronio* neu, double e);
void sortear_pesos(Neuronio* neu, int quant);