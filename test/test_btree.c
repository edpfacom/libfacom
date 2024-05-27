#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"../include/btree.h"
void imprime_arvore(tnode * x,int prof,int i){
    int anda = 3;
    int j;
    int k;
    if (x->folha==TRUE){
        for (j=0;j<prof;j++)
            printf(" ");
        for (j=0;j<x->n;j++)
            printf("%d ",x->chaves[j]);
        printf("\n");

    }else{
        imprime_arvore(x->c[0],prof+anda,0);
        for (k=0;k<x->n;k++){ 
            for (j=0;j<prof;j++)
                printf(" ");
            printf("%d\n",x->chaves[k]);
            imprime_arvore(x->c[k+1],prof+anda,k+1);
        }
        if (prof == 0)
            printf("------\n");
    }
}

void test_btree_split(){
    tarv arv;
    int t = 3;
    tnode * x;
    tnode * y;
    tnode * z;

    btree_constroi(&arv,t);
    x = arv.raiz;
    y = aloca_node(&arv);

    y->folha = TRUE;
    y->n = 5;
    y->chaves[0] = 10;
    y->chaves[1] = 20;
    y->chaves[2] = 30;
    y->chaves[3] = 40;
    y->chaves[4] = 50;
    
    x->c[0] = y;
    x->n = 0;
    x->folha = FALSE;
    arv.raiz = x;

    btree_split(&arv,x,0);

    x = arv.raiz;
    y = x->c[0];
    z = x->c[1];
    assert(x->chaves[0] == 30);
    assert(x->folha == FALSE);
    assert(x->n == 1);

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha  == TRUE);

    assert(z->chaves[0] == 40);
    assert(z->chaves[1] == 50);
    assert(z->n == 2);
    assert(z->folha  == TRUE);
}

void test_btree_insere_naocheio(){
    tarv arv;
    int t = 3;

    tnode * x;
    tnode * y;

    btree_constroi(&arv,t);
    x = arv.raiz;
    y = aloca_node(&arv);

    y->folha = TRUE;
    y->n = 5;
    y->chaves[0] = 10;
    y->chaves[1] = 20;
    y->chaves[2] = 30;
    y->chaves[3] = 40;
    y->chaves[4] = 50;
    
    x->c[0] = y;
    x->n = 0;
    x->folha = FALSE;
    arv.raiz = x;

    btree_split(&arv,x,0);

    btree_insere_naocheio(&arv,x,23);

    y = x->c[0];

    
    assert(y->chaves[2] == 23);
    assert(y->n == 3);

    btree_insere_naocheio(&arv,x,24);

    y = x->c[0];
    assert(y->chaves[3] == 24);
    assert(y->n == 4);

    btree_insere_naocheio(&arv,x,25);
    btree_insere_naocheio(&arv,x,26);

    x = arv.raiz; 


    assert(x->chaves[0] == 23);
    assert(x->chaves[1] == 30);
    assert(x->n == 2);
    assert(x->folha == FALSE);


    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 24);
    assert(y->chaves[1] == 25);
    assert(y->chaves[2] == 26);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    y = x->c[2];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->n == 2);
    assert(y->folha == TRUE);
}


void test_btree_insere(){
    tarv arv;
    tnode *x, *y;
    int t; 
    int i;
    t = 3;

    btree_constroi(&arv,t);

    for (i=10;i<=60;i+=10)
        btree_insere(&arv,i);

    x=arv.raiz;
    assert(x->chaves[0] == 30);
    assert(x->n == 1);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha==TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->chaves[2] == 60);
    assert(y->n == 3);
    assert(y->folha==TRUE);


    
    for (i=70;i<100;i+=10)
        btree_insere(&arv,i);

    x=arv.raiz;
    assert(x->chaves[0] == 30);
    assert(x->chaves[1] == 60);
    assert(x->n == 2);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha==TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->n == 2);
    assert(y->folha==TRUE);

    y = x->c[2];

    assert(y->chaves[0] == 70);
    assert(y->chaves[1] == 80);
    assert(y->chaves[2] == 90);
    assert(y->n == 3);
    assert(y->folha==TRUE);


    btree_insere(&arv,21);
    btree_insere(&arv,22);
    btree_insere(&arv,23);
    btree_insere(&arv,24);

    x=arv.raiz;
    assert(x->chaves[0] == 21);
    assert(x->chaves[1] == 30);
    assert(x->chaves[2] == 60);
    assert(x->n == 3);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha==TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 22);
    assert(y->chaves[1] == 23);
    assert(y->chaves[2] == 24);
    assert(y->n == 3);
    assert(y->folha==TRUE);

    btree_insere(&arv,51);
    btree_insere(&arv,52);
    btree_insere(&arv,53);
    btree_insere(&arv,54);

    btree_insere(&arv,91);
    btree_insere(&arv,92);
    btree_insere(&arv,93);
    btree_insere(&arv,94);

    x=arv.raiz;
    assert(x->chaves[0] == 51);
    assert(x->n == 1);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 21);
    assert(y->chaves[1] == 30);
    assert(y->n == 2);
    assert(y->folha==FALSE);

    y = x->c[1];

    assert(y->chaves[0] == 60);
    assert(y->chaves[1] == 90);
    assert(y->n == 2);
    assert(y->folha==FALSE);

    imprime_arvore(arv.raiz,0,0);

}

int main(void){
    test_btree_split();
    test_btree_insere_naocheio();
    test_btree_insere();
}
