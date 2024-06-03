#include<stdio.h>
#include<stdlib.h>
#include"../include/btree.h"
int menor(int a,int b){
    return a<b?a:b;
}

void remove_chave(tnode *x, tchave ik){
    int i;
    for (i=ik;i<x->n-1;i++){
            x->chaves[i] = x->chaves[i+1];
    }
    x->n -= 1;
}

tchave sucessor(tnode *x, tchave k){
    int ik;
    tnode * aux;
    ik = procura_chave(x,k);
    aux = x->c[ik+1];
    while(!aux->folha)
        aux = x->c[0];
    return aux->chaves[0];
}

tchave predecessor(tnode *x, tchave k){
    int ik;
    tnode * aux;
    ik = procura_chave(x,k);
    aux = x->c[ik];
    while(!aux->folha)
        aux = x->c[x->n];
    return aux->chaves[aux->n-1];
}



tnode * aloca_node(tarv * parv){
    tnode * aux;
    aux = (tnode *)malloc(sizeof(tnode));
    if (aux != NULL){
        aux->n = 0;
        aux->folha=0;
    }
    return aux;
}
void pega_emprestado_irmao(tnode *x, int cpos,int irmao){
    int i;
    tnode *y,*z;
    if (cpos < irmao){ /* irmao a direita*/
    }else{ /*irmao a esquerda*/
    }
}

void merge(tarv *parv, tnode *x, int cpos){
    tnode *y;
    tnode *z;
    int i;
    y = x->c[cpos];
    z = x->c[cpos+1];
    y->chaves[y->n] = x->chaves[cpos];
    /*copia elementos e chaves de z em y */
    for (i = 0;i<z->n;i++){
    
    }
    if (!y->folha){ /* se nao folha atualizar c de y*/

    }
    y->n = 2*(parv->t)-1;
    /* ERRADO !! shift right em  x  para colocar elemento que ira subir*/
    /*arruma x com o elemento a menos */
    for (i=cpos;i<x->n-1;i++){
    
    }
    x->n -= 1;
    if (x->n == 0){ /* trata o caso quando o merge apaga o faz join com o ultimo elemento de x*/
        for (i=0;i<y->n;i++){ /* copia as infos de y em x*/
        }
        free(y);
    }
    free(z);
}






int _btree_remove(tarv *parv, tnode * x, tchave k){
    int ik; /* key position */
    int t;
    int i;
    int iirmao_maior;
    tnode *y,*z;
    tchave klinha;
    int ret;
    ret = 1;
    t = parv->t;
    ik = procura_chave(x,k); 
    if (ik >=0 ){ /* k in x*/
        if (x->folha){ /* Caso a - simplesmente remove*/
        
        }else{ 
            y = x->c[ik];
            z = x->c[ik+1];
            if (y->n >= t){ /* b  tenta no irmao esquerda*/
            
            }else if (z->n >= t){ /* b tenta no irmao direta*/

            }else if ((y->n == t -1) && (z->n == t-1)){ /* c faz merge */
            
            }
        }
    }else{ /* nos intermediarios */
        if (x->folha == TRUE){
            ret = 0;
        }else{
            i = procura_ic(x,k);
            if (x->c[i]->n == t-1){ /* aumenta c[i] */
                iirmao_maior = pega_irmao_maior(x,i);
                if (x->c[iirmao_maior]->n >=t){            /* a */
                
                }else if (x->c[iirmao_maior]->n == t-1){   /* b */
                
                }
            }else{

            }
        }
    }
    return ret;
}

int btree_remove(tarv *parv, tchave k){
    printf("Removendo %d\n",k);
    return _btree_remove(parv,parv->raiz,k);
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
    tnode * r;
    tnode * s;
    int t;
    int ret = 1;
    
    r = parv->raiz;
    t = parv->t;
    if (r->n == 2*t-1){
        s = aloca_node(parv);
        parv->raiz = s;
        s->folha = FALSE;
        s->n = 0;
        s->c[0] = r;
        ret = btree_split(parv,s,0);
        if (ret)
           ret = btree_insere_naocheio(parv,s,k);
    }else{
        ret = btree_insere_naocheio(parv,r,k);
    }
    return ret;
}
int procura_chave(tnode *x, tchave k){
    int i;
    int ret = -1;
    for(i=0;i<x->n;i++){
        if (x->chaves[i] == k){
            ret = i;
        }
    }
    return ret;
}


int procura_ic(tnode *x, tchave k){
    int i;
    i = x->n-1;
    while (k < x->chaves[i] && i >= 0){
        i-=1;
    }
    i+=1;
    return i;
}

int pega_irmao_maior(tnode *x, int cpos){
    int ant;
    int pos;
    int ret;
    ant = cpos -1;
    pos = cpos +1;
    if (ant < 0){
        ret = pos;
    }else if (pos > x->n){
        ret = ant;
    }else{
        if (x->c[ant]->n > x->c[pos]->n){
            ret = ant;
        }else{
            ret = pos;
        }
    }
    return ret;


}


