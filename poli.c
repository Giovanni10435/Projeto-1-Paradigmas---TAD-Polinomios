#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "poli.h"

polinomio * poli_create(int grau){
    // Implementado aqui a solucao para operacao create

    polinomio *p = malloc(sizeof(polinomio));
    if(p == NULL) return NULL;

    p -> grau = grau; // Aloca o grau
    p -> termos = 0;   // Inicializa os termos como 0

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
    // Implementado aqui a solucao para operacao destroy
    if(p == NULL || *p == NULL) return;

    free((*p) -> coeficientes);
    
    free(*p);
    *p = NULL;
    
    return;
}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    // Implementado aqui a solucao para operacao insere coeficiente

    if (exp >= 0 && exp <= p->grau) {
        p->coeficientes[exp] = coef;
        p->termos += 1;
        return 1;
    } 

    return 0;
}

int poli_get_termo(polinomio *p, int exp, int *coef){
    // Implementado aqui a solucao para operacao get coeficiente

    if (exp >= 0 && exp <= p->grau) {
        if (p->coeficientes[exp] == 0) {
            return 0;
        }
        *coef = p->coeficientes[exp];
        return 1;
    }

    return 0;
}

int calcula_px(polinomio *p, int x){
    // Implementado aqui a solucao para operacao calcula o valor de P(x)
    
    int calc = 0;
    for (int i = p->grau; i >= 0; i--) {
        int pot = 1;
            if (p->coeficientes[i] != 0) {
                for (int j = 0; j < i; j++) { // Apenas para calcular a potência (Evitando usar biblioteca math, sem uso no gcc)
                pot *= x;
            }
            calc += p->coeficientes[i] * pot;
        }
    }

    return calc;
    
    return 0;
}

polinomio * poli_soma(polinomio *p, polinomio *q){
    // Implementado aqui a solucao para operacao que soma dois polinomios e gera um terceiro

    int grau_max;

    // Definindo tamanho do plonimio 3
    if (p->grau >= q->grau) {
        grau_max = p->grau;
    } else {
        grau_max = q->grau;
    }

    // Cria o polinomio 3
    polinomio *p3 = poli_create(grau_max);

    // Passa por cada coeficiente fazendo a soma
    for (int i = grau_max; i >= 0; i--) {
        int coef_p = 0;
        int coef_q = 0;

        if (i <= p->grau) {
            coef_p = p->coeficientes[i];
        }

        if (i <= q->grau) {
            coef_q = q->coeficientes[i];
        }

        p3->coeficientes[i] = coef_p + coef_q; // Realiza a soma
    }

    return p3;

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


