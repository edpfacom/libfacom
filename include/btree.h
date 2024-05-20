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

#endif
