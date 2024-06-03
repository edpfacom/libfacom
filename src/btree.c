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
void merge(tarv *parv, tnode *x, int cpos){
    tnode *y;
    tnode *z;
    int i;
    y = x->c[cpos];
    z = x->c[cpos+1];
    /*copia elementos e chaves de z em y */
    y->chaves[y->n] = x->chaves[cpos];
    for (i = 0;i<z->n;i++){
        y->chaves[y->n+1+i] = z->chaves[i];
    }
    if (!y->folha){
        for (i = 0;i<=z->n;i++)
            y->c[y->n+1+i] = z->c[i];
    }
    y->n = 2*(parv->t)-1;
    /*arruma x com o elemento a menos */
    for (i=cpos;i<x->n-1;i++){
        x->chaves[i] = x->chaves[i+1];
        x->c[i+1] = x->c[i+2];
    }
    x->n -= 1;
    if (x->n == 0){ /* trata o caso quando o merge apaga o faz join com o ultimo elemento de x*/
        for (i=0;i<y->n;i++){
            x->chaves[i] = y->chaves[i];
            x->c[i] = y->c[i];
        }
        x->c[i] = y->c[i];
        x->folha = y->folha;
        x->n = 2*(parv->t) -1;
        free(y);
    }
    free(z);
}

void pega_emprestado_irmao(tnode *x, int cpos,int irmao){
    int i;
    tnode *y,*z;
    if (cpos < irmao){ /* irmao a direita*/
        y = x->c[cpos];
        z = x->c[cpos+1];
        y->chaves[y->n] = x->chaves[cpos];
        x->chaves[cpos] = z->chaves[0];
        y->c[y->n+1] = z->c[0];
        for (i=0;i < z->n-1;i++){
            z->chaves[i] = z->chaves[i+1];
            z->c[i] = z->c[i+1];
        }
        z->c[i] = z->c[i+1];
        z->n-=1;
        y->n+=1;
    }else{ /*irmao a esquerda*/
        cpos -=1;
        y = x->c[cpos];
        z = x->c[cpos+1];
        for (i=z->n;i>0;i--){
            z->chaves[i] = z->chaves[i-1];
            z->c[i+1] = z->c[i];
        }
        z->chaves[0] = x->chaves[cpos];
        z->c[0] = y->c[y->n];
        x->chaves[cpos] = y->chaves[y->n-1];
        y->n-=1;
        z->n+=1;
    }
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
            remove_chave(x,ik);
        }else{ 
            y = x->c[ik];
            z = x->c[ik+1];
            if (y->n >= t){ /* b  tenta no irmao esquerda*/
                klinha = predecessor(x,k);
                x->chaves[ik] = klinha;
                ret = _btree_remove(parv,y,klinha);

            }else if (z->n >= t){ /* b tenta no irmao direta*/
                klinha = sucessor(x,k);
                x->chaves[ik] = klinha;
                ret = _btree_remove(parv,z,klinha);
            }else if ((y->n == t -1) && (z->n == t-1)){ /* c faz merge */
                merge(parv,x,ik);
                ret = _btree_remove(parv,x,k);
            }
        }
    }else{ /* nos intermediarios */
        if (x->folha == TRUE){
            ret = 0;
        }else{
            i = procura_ic(x,k);
            if (x->c[i]->n == t-1){
                iirmao_maior = pega_irmao_maior(x,i);
                if (x->c[iirmao_maior]->n >=t){            /* a */
                    pega_emprestado_irmao(x,i,iirmao_maior);
                   ret = _btree_remove(parv,x->c[i],k);
                }else if (x->c[iirmao_maior]->n == t-1){   /* b */
                    merge(parv,x,menor(i,iirmao_maior)); 
                   ret = _btree_remove(parv,x,k);
                }
            }else{
                ret = _btree_remove(parv,x->c[i],k);
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


