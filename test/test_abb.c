#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include"../include/libfacom.h"

typedef struct {
    int rga;
    char nome[30];
}taluno;


int cmp(void *t1, void *t2){
    return ((taluno *) t1)->rga - ((taluno *) t2)->rga ;
}

void abb_constroi(tarv *parv, int (*cmp)(void *, void *)){
    parv->raiz = NULL;
    parv->cmp  = cmp;
}

taluno * aloca_aluno(int rga, char nome[]){
    taluno * paluno;
    paluno = malloc(sizeof(taluno));
    paluno->rga = rga;
    strcpy(paluno->nome,nome);
    return paluno;
}

int abb_insere_node(tarv * parv,tnode ** ppnode,void *reg){
    if (*ppnode == NULL){
         *ppnode = malloc(sizeof(tnode));
         (*ppnode)->reg = reg;
         (*ppnode)->esq = NULL;
         (*ppnode)->dir = NULL;
    }else if (parv->cmp((*ppnode)->reg,reg) > 0){ /* esquerda*/
        abb_insere_node(parv,&((*ppnode)->esq),reg);
    }else{ /*direita*/
        abb_insere_node(parv,&((*ppnode)->dir),reg);
    }
}

int   abb_insere(tarv * parv,  void * reg){
    return abb_insere_node(parv,&parv->raiz,reg);
}

void * abb_busca_node(tarv * parv,tnode * pnode,void *reg){
    tnode * ret;
    if (pnode == NULL){
        ret = NULL;
    }else if (parv->cmp(pnode->reg,reg) > 0){ /* esquerda*/
        ret = abb_busca_node(parv,pnode->esq,reg);
    }else if (parv->cmp(pnode->reg,reg) < 0) { /*direita*/
        ret = abb_busca_node(parv,pnode->dir,reg);
    }else{
        ret = pnode->reg;
    }
    return ret;
}

void *   abb_busca(tarv * parv,  void * reg){
    return abb_busca_node(parv,parv->raiz,reg);
}



void test_compara(){
    taluno t1;
    taluno t2;
    taluno t3;
    taluno t4;
    t1.rga = 10;
    t2.rga = 20;
    t3.rga = 10;
    t4.rga = 5;
    assert(cmp(&t1,&t2)<0);  /*t1 < t2*/
    assert(cmp(&t1,&t3)==0); /* t1 == t2*/
    assert(cmp(&t1,&t4)>0);  /*t1 > t2 */
}
void test_constroi(){
    tarv arv;
    abb_constroi(&arv,cmp);
    assert(arv.raiz == NULL);
    taluno t1;
    taluno t2;
    taluno t3;
    taluno t4;
    t1.rga = 10;
    t2.rga = 20;
    t3.rga = 10;
    t4.rga = 5;
    assert(arv.cmp(&t1,&t2)<0);  /*t1 < t2*/
    assert(arv.cmp(&t1,&t3)==0); /* t1 == t2*/
    assert(arv.cmp(&t1,&t4)>0);  /*t1 > t2 */
}
void test_insere(){
    taluno * no;
    tarv arv;
    no = aloca_aluno(10,"edson");
    abb_constroi(&arv,cmp);
    abb_insere(&arv,no);
    assert(((taluno *)arv.raiz->reg)->rga == 10);
    assert(arv.raiz->esq == NULL);
    assert(arv.raiz->dir == NULL);

    no = aloca_aluno(20,"takashi");
    abb_insere(&arv,no);
    assert(((taluno *)arv.raiz->reg)->rga == 10);
    assert(arv.raiz->esq == NULL);
    assert(((taluno *)arv.raiz->dir->reg)->rga == 20);

    no = aloca_aluno(5,"matsubara");
    abb_insere(&arv,no);
    assert(((taluno *)arv.raiz->reg)->rga == 10);
    assert(((taluno *)arv.raiz->dir->reg)->rga == 20);
    assert(((taluno *)arv.raiz->esq->reg)->rga == 5);
    assert(((taluno *)arv.raiz->dir->reg)->rga == 20);

}
void test_busca(){
    taluno * no;
    int rga;
    tarv arv;
    abb_constroi(&arv,cmp);
    
    no = aloca_aluno(10,"edson");
    abb_insere(&arv,no);
    
    no = aloca_aluno(20,"takashi");
    abb_insere(&arv,no);

    no = aloca_aluno(5,"matsubara");
    abb_insere(&arv,no);
    
    rga = 10;
    no = abb_busca(&arv,&rga);
    assert(no->rga == rga);

    rga = 7;
    no = abb_busca(&arv,&rga);
    assert(no == NULL);

    rga = 5;
    no = abb_busca(&arv,&rga);
    assert(no->rga == rga);

    rga = 20;
    no = abb_busca(&arv,&rga);
    assert(no->rga == rga);


}



int main(void){

    test_compara();
    test_constroi();
    test_insere();
    test_busca();
    return EXIT_SUCCESS;
}
