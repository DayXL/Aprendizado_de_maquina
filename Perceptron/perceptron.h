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