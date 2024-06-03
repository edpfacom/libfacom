#ifndef __btree__
#define __btree__

#define TRUE 1
#define FALSE 0

typedef int tchave;

typedef struct _node{
    int folha; /*se eh folha*/
    int n;     /* numero chaves */
    /*
    tchave * chaves;
    struct _node ** c;
     */
    tchave chaves[5];    /* t = 3*/
    struct _node * c[6];
}tnode;

typedef struct _arv{
    tnode * raiz;
    int t;  
}tarv;

int btree_split(tarv *parv, tnode * x, int i);
int btree_insere_naocheio(tarv *parv, tnode * x, tchave k);
int btree_insere(tarv *parv, tchave k);

tnode * aloca_node(tarv * parv);
void btree_constroi(tarv * parv, int t);

int procura_chave(tnode *x, tchave k);
int pega_irmao_maior(tnode *x, int cpos);
int procura_ic(tnode *x, tchave k);


void merge(tarv *parv, tnode *x, int cpos);
void pega_emprestado_irmao(tnode *x, int cpos,int irmao);
int btree_remove(tarv *parv, tchave k);

#endif
