#include<stdio.h>
#include<stdlib.h>
#include"../include/btree.h"

tnode * aloca_node(tarv * parv){
    tnode * aux;
    aux = (tnode *)malloc(sizeof(tnode));
    if (aux != NULL){
        aux->n = 0;
        aux->folha=0;
    }
    return aux;
}

void btree_constroi(tarv * parv, int t){
    parv->t = t;
    parv->raiz = aloca_node(parv);
    parv->raiz->n = 0;
    parv->raiz->folha = TRUE;
}

int btree_split(tarv * parv,tnode * x, int i){
    tnode * z;
    tnode * y;
    int t;
    int j;
    int ret;
    z = aloca_node(parv);
    y = x->c[i];
    t = parv->t;
    ret = 0;
    if (z!=NULL){ /* if memory is not full */
        z->folha = y->folha;
        z->n     = t-1;
        for (j=0;j<t-1;j++)
            z->chaves[j] = y->chaves[j+t];
        if (!y->folha){   /* copia os ponteiros caso z e y nao sejam folhas*/
            for (j = 0;j<t;j++){
                z->c[j] = y->c[j+t];
            }
        }
        y->n = t-1;
        for (j = x->n;j>=i+1;j--)
            x->c[j+1] = x->c[j];
        x->c[i+1] = z;

        for(j = x->n-1;j>=i;j--)
            x->chaves[j+1] = x->chaves[j];
        x->chaves[i] = y->chaves[t-1];
        x->n +=1;
        x->folha = FALSE;
        ret = 1;
    }
    return ret;
}


int btree_insere_naocheio(tarv *parv, tnode * x, tchave k){
    int i,t,ret;
    i = x->n;
    t = parv->t;
    ret = 1;
    if (x->folha == TRUE){
        while(i>0 && k < x->chaves[i-1]){
            x->chaves[i] = x->chaves[i-1];
            i = i - 1;
        }
        x->chaves[i] = k;
        x->n = x->n+1;
    }else{
        i -= 1;
        while(i>=0 && k < x->chaves[i]){
            i = i - 1;
        }
        i+=1;

        if (x->c[i]->n == 2*t -1){
            ret = btree_split(parv,x,i);
            if (k > x->chaves[i])
                i = i+1;
        }
        ret = btree_insere_naocheio(parv,x->c[i],k);
    }
    return ret;
}

int btree_insere(tarv *parv, tchave k){
    
}


