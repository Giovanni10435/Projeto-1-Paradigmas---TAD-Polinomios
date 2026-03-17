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
    int grau_resultado_mult = p -> grau + q -> grau;
    int coef_resultado_mult;
    polinomio *r;

    r = poli_create(grau_resultado_mult);
    if(r == NULL) return NULL;

    for(int i = 0; i <= p -> grau; i++){
        for(int j = 0; j <= q -> grau; j++){
            coef_resultado_mult = p -> coeficientes[i] * q -> coeficientes[j];

            int pr = r -> coeficientes[i + j];

            r -> coeficientes[i + j] += coef_resultado_mult;

            int dp = r -> coeficientes[i + j];

            if(pr == 0 && dp != 0) r -> termos++;
            if(pr != 0 && dp == 0) r -> termos--;
        }
    }

    return r;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro
    polinomio *r;
    int coef_resposta;
    int exp;
    int coef_lider_resto;
    int coef_lider_q;

    if(p == NULL || q == NULL) return NULL;             // Valida P e Q (não nulos)
    if(q -> termos == 0) return NULL;                   // Erro conceitual --> Divisão Inválida
    if(p -> grau < q -> grau){
        r = poli_create(0);                             // Retorna um polinômio zerado --> Indivisível
        return r;
    }
    int grau_resultado_div = (p -> grau) - (q -> grau); // Calcula o grau do resultado da divisao

    r = poli_create(grau_resultado_div);                // Cria o polinômio com grau calculado
    if(r == NULL) return NULL;                          // Se estiver vazio, retorna erro
    r -> termos = 0;
    
    for(int B = 0; B <= grau_resultado_div; B++){
        r -> coeficientes[B] = 0;
    }
    
    int grau_resto = p -> grau;                         // Cria o grau do resto
    polinomio *resto = poli_create(p -> grau);          // Cria o polinômio resto (cópia do original P)
    if(resto == NULL) return NULL;

    for(int i = p -> grau; i >= 0; i--){
        resto -> coeficientes[i] = p -> coeficientes[i];
    }
    resto -> termos = p -> termos;


    while(grau_resto >= q -> grau) {
        coef_lider_resto = resto -> coeficientes[grau_resto];       // Calcula o maior coeficiente possível (RESTO)
        coef_lider_q = q -> coeficientes[q -> grau];    // Calcula o maior coeficiente possivel (Q(x))

        if(coef_lider_q == 0) return NULL;
        coef_resposta = (coef_lider_resto / coef_lider_q);         // Calcula o coeficiente para o resultado
        exp = grau_resto - (q -> grau);                 // Calcula o expoente para cada coeficiente

        int pr = r->coeficientes[exp];               // Armazena o valor antes

        
        r -> coeficientes[exp] += coef_resposta;
        
        if (pr == 0 && r->coeficientes[exp] != 0) r->termos++;
        
        for(int i = 0; i <= q -> grau; i++){
            int aux = i + exp;
            resto -> coeficientes[aux] -= (coef_resposta * q -> coeficientes[i]);
        }
        
        while (grau_resto >= 0 && resto->coeficientes[grau_resto] == 0) grau_resto--;
    }
    
    poli_destroy(&resto);
    return r;
}