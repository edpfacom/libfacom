#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include "../include/avl.h"

void test_rotacao(){
    tnode * x;
    tnode * y;
    tnode * a;
    tnode * b;
    tnode * c;
    tnode * arv;
    arv = NULL;
    assert(arv == NULL);
    x = malloc(sizeof(tnode));
    y = malloc(sizeof(tnode));
    a = malloc(sizeof(tnode));
    b = malloc(sizeof(tnode));
    c = malloc(sizeof(tnode));
    x->item = 5;
    y->item = 10;
    a->item = 3;
    b->item = 7;
    c->item = 12;
    x->esq = a;
    x->dir = b;
    y->esq = x;
    y->dir = c;
    arv = y;
    _rd(&arv);
    assert(arv->item == 5);
    assert(arv->esq->item ==3);
    assert(arv->dir->item ==10);
    assert(arv->dir->dir->item == 12);
    assert(arv->dir->esq->item == 7);
    _re(&arv);
    assert(arv->item == 10);
    assert(arv->esq->item ==5);
    assert(arv->dir->item ==12);
    assert(arv->esq->dir->item == 7);
    assert(arv->esq->esq->item == 3);
 }

void test_insere(){
    tnode * arv;
    arv = NULL;
    assert(arv == NULL);
    
    /* teste caso 1 --> ->*/
    avl_insere(&arv,10);    
    avl_insere(&arv,15);
    avl_insere(&arv,20);
    assert(arv->item == 15);
    assert(arv->esq->item == 10);
    assert(arv->dir->item == 20);

    /* teste caso 2 --> <- */
    avl_insere(&arv,50);
    avl_insere(&arv,23);
    assert(arv->item == 15);
    assert(arv->esq->item == 10);
    assert(arv->dir->item == 23);
    assert(arv->dir->esq->item == 20);
    assert(arv->dir->dir->item == 50);

    /* teste caso 3 <-- <- */
    avl_insere(&arv,5);
    avl_insere(&arv,30);
    avl_insere(&arv,25);
    assert(arv->item == 15);
    assert(arv->esq->item == 10);
    assert(arv->esq->esq->item == 5);
    assert(arv->dir->item == 23);
    assert(arv->dir->esq->item == 20);
    assert(arv->dir->dir->item == 30);
    assert(arv->dir->dir->esq->item == 25);
    assert(arv->dir->dir->dir->item == 50);

    /* teste caso 4 <-- -> */
    avl_insere(&arv,7);
    assert(arv->item == 15);
    assert(arv->esq->item == 7);
    assert(arv->esq->esq->item == 5);
    assert(arv->esq->dir->item == 10);
    assert(arv->dir->item == 23);
    assert(arv->dir->esq->item == 20);
    assert(arv->dir->dir->item == 30);
    assert(arv->dir->dir->dir->item == 50);
    assert(arv->dir->dir->esq->item == 25);
}

void test_remove(){
    tnode * arv;
    arv = NULL;
    assert(arv == NULL);
    avl_insere(&arv,10);    
    avl_insere(&arv,15);
    avl_insere(&arv,20);
    avl_insere(&arv,50);
    avl_insere(&arv,23);
    avl_insere(&arv,5);
    avl_insere(&arv,30);
    avl_insere(&arv,25);
    
    avl_remove(&arv,15);
    assert(arv->item == 20);
    assert(arv->dir->item == 30);
    assert(arv->esq->item == 10);
    
    assert(arv->esq->esq->item == 5);

    assert(arv->dir->dir->item == 50);
    assert(arv->dir->esq->item == 23);
    assert(arv->dir->esq->dir->item == 25);

    avl_remove(&arv,20);
    assert(arv->item == 23);
    assert(arv->dir->item == 30);
    assert(arv->esq->item == 10);
    
    assert(arv->esq->esq->item == 5);

    assert(arv->dir->dir->item == 50);
    assert(arv->dir->esq->item == 25);


    avl_remove(&arv,10);
    assert(arv->item == 23);
    assert(arv->dir->item == 30);
    assert(arv->esq->item ==5);
    assert(arv->dir->dir->item == 50);
    assert(arv->dir->esq->item == 25);

   
}

int main(void){
    test_rotacao();
    test_insere();
    test_remove();
    return EXIT_SUCCESS;
}
