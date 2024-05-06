#ifndef __AVL__
#define  __AVL__

typedef int titem;

typedef struct _node{
    titem item;
    struct _node *esq;
    struct _node *dir;
    int h;
}tnode;

void avl_insere(tnode ** parv,titem reg);
void avl_remove(tnode ** parv,titem reg);

void _rd(tnode ** pparv);
void _re(tnode ** pparv);
void _avl_rebalancear(tnode ** pparv);

#endif
