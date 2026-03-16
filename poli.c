#include <stdlib.h>
#include <stdio.h>
#include "poli.h"

polinomio * poli_create(int grau){
    // TODO: Implemente aqui a solucao para operacao create

    polinomio *p = malloc(sizeof(polinomio));
    if(p == NULL) return NULL;

    p -> grau = grau; // Aloca o grau
    p -> termo = 0;   // Inicializa os termos como 0

    p->coeficientes = malloc((grau + 1) * sizeof(int)); // Aloca dinamicamente o vetor p/ a quantidade de coeficientes
    if(p -> coeficientes == NULL){
        free(p);
        free(p -> coeficientes);
        return NULL;
    }

    for(int i = 0; i <= grau; ++i) {
        p -> coeficientes[i] = 0;
    }

    return p;
}

void poli_destroy(polinomio **p){
    // TODO: Implemente aqui a solucao para operacao destroy
    if(p == NULL || *p == NULL) return;

    free((*p) -> coeficientes);
    
    free(*p);
    *p = NULL;
    
    return;
}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    // TODO: Implemente aqui a solucao para operacao insere coeficiente

    return 0;
}

int poli_get_termo(polinomio *p, int exp, int *coef){
    // TODO: Implemente aqui a solucao para operacao get coeficiente

    return 0;
}

int calcula_px(polinomio *p, int x){
    // TODO: Implemente aqui a solucao para operacao calcula o valor de P(x)     
    
    return 0;
}

polinomio * poli_soma(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que soma dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_mult(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que multiplica dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro

    return NULL;
}


