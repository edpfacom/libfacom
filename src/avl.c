#include<stdio.h>
#include<stdlib.h>
#include "avl.h"

int max(int a,int b){
    return a>b?a:b;
}

int altura(tnode *arv){
    int ret;
    if (arv==NULL){
        ret = 0;
    }else{
        ret = arv->h;
    }
    return ret;
}


void avl_insere(tnode ** parv,titem item){
    if (*parv == NULL){
        *parv = (tnode *) malloc(sizeof(tnode));
        (*parv)->item = item;
        (*parv)->esq = NULL;
        (*parv)->dir = NULL;
        (*parv)->h = 1;

    }else if(((*parv)->item - item)>0){
        avl_insere(&(*parv)->esq,item);
    }else{
        avl_insere(&(*parv)->dir,item);
    }
    (*parv)->h = max(altura((*parv)->esq),altura((*parv)->dir)) + 1;
    avl_rebalancear(parv);
}

void RD(tnode **parv){
    tnode * y = *parv; 
    tnode * x = y->esq;
    tnode * A = x->esq;
    tnode * B = x->dir;
    tnode * C = y->dir;

    y->esq = B; 
    x->dir = y;
    *parv  = x;
    y->h = max(altura(B),altura(C)) + 1;
    x->h = max(altura(A),altura(y)) + 1;
}

void RE(tnode **parv){
    tnode * x = *parv; 
    tnode * y = x->dir;
    tnode * A = x->esq;
    tnode * B = y->esq;
    tnode * C = y->dir;

    x->dir = B;
    y->esq = x; 
    *parv  = y;
    x->h = max(altura(A),altura(B)) + 1;
    y->h = max(altura(x),altura(C)) + 1;
}


void avl_rebalancear(tnode **parv){
    int fb;
    int fbf;
    tnode * filho;
    fb = altura((*parv)->esq) - altura((*parv)->dir);

    if (fb  == -2){
        filho = (*parv)->dir;
        fbf = altura(filho->esq) - altura(filho->dir);
        if (fbf <= 0){ /* Caso 1  --> ->*/
            RE(parv);
        }else{   /* Caso 2  --> <-*/
            RD(&(*parv)->dir);
            RE(parv);
        }
    }else if (fb == 2){  
        filho = (*parv)->esq;
        fbf = altura(filho->esq) - altura(filho->dir);
        if (fbf >=0){ /* Caso 3  <-- <-*/
            RD(parv);
        }else{  /* Caso 4  <-- ->*/
            RE(&(*parv)->esq);
            RD(parv);
        }
    }
}

tnode ** percorre_esq(tnode ** arv){
    tnode * aux = *arv;
    if (aux->esq  == NULL){
        return arv;
    }else{
        while (aux->esq->esq != NULL)
            aux = aux->esq;
        return &(aux->esq);
    }
}
void avl_remove(tnode **parv, titem reg){
    int cmp;
    tnode *aux;
    tnode **sucessor;
    if (*parv != NULL){
        cmp  = (*parv)->item  - reg;
        if (cmp > 0){ /* ir esquerda*/
            avl_remove(&((*parv)->esq), reg);
        }else if (cmp < 0){ /*ir direita*/
            avl_remove(&((*parv)->dir), reg);
        }else{ /* ACHOU  */
            if ((*parv)->esq == NULL && (*parv)->dir == NULL){   /* no folha */
                free(*parv);
                *parv = NULL;
            }else if ((*parv)->esq == NULL || (*parv)->dir == NULL){ /* tem um filho*/
                aux = *parv;
                if ((*parv)->esq == NULL){
                    *parv = (*parv)->dir;
                }else{
                    *parv = (*parv)->esq;
                }
                free(aux);
            }else{ /* tem dois filhos */
                sucessor = percorre_esq(&(*parv)->dir);
                (*parv)->item = (*sucessor)->item;
                avl_remove(&(*parv)->dir,(*sucessor)->item);
            }

        }
        if (*parv != NULL){
            (*parv)->h = max(altura((*parv)->esq),altura((*parv)->dir)) + 1;
            avl_rebalancear(parv);
        }
    }
}
