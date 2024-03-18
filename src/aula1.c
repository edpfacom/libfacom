#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int pai(int n){
    return (n-1)/2;
}

int filho_esq(int n){
    return 2*n+1;
}
int filho_dir(int n){
    return 2*n+2;
}

void troca(int *a,int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}
void desce(int v[],int n, int max_size){
    int e,d,maior;
    e = filho_esq(n);
    d = filho_dir(n);
    maior = n;
    if (e < max_size && v[e] > v[maior] ) maior = e; 
    if (d < max_size && v[d] > v[maior] ) maior = d; 
    if (maior!=n){
        troca(&v[maior],&v[n]);
        desce(v,maior,max_size);
    }
}

void constroi_heap(int v[], int max_size){
    int i;
    for (i=pai(max_size-1);i>=0;i--)
        desce(v,i,max_size);
}

void sobe(int v[], int pos){
}

int acessa_max(int v[]){
}

int extrai_max(int v[], int * tam){
}
int insere_elemento(int v[], int *tam, int max, int novo){
}
int altera_prioridade(int v[],int tam, int pos, int novo){
}
void heapsort(int v[], int tam){
}
void test_pai(){
    /*inicializacao */
    int r;
    /*chamada e verificacao*/
    r = pai(6);
    assert(r == 2);
    r = pai(5);
    assert(r == 2);
    r = pai(0);
    assert(r == 0);
}

void test_filho_esq(){
    /*inicializacao*/
    int r;
    /*chamada e verificacao*/
    r = filho_esq(0);
    assert(r==1);
    r = filho_esq(1);
    assert(r==3);
    r = filho_esq(2);
    assert(r==5);
}
void test_filho_dir(){
    /*inicializacao*/
    int r;
    /*chamada e verificacao*/
    r = filho_dir(0);
    assert(r==2);
    r = filho_dir(1);
    assert(r==4);
    r = filho_dir(2);
    assert(r==6);
}


void test_desce(){
    /*inicializacao*/
    int entrada[] = {1,5,3,4,10,2,0};
    int saida[]   = {5,10,3,4,1,2,0};
    int i;
    int max_size = sizeof(entrada)/sizeof(entrada[0]);
    /*chamada*/
    desce(entrada,0,max_size);
    /*verificacao*/
    for (i=0;i<max_size;i++){
        assert(entrada[i]==saida[i]);
    }
}

void test_constroi_heap(){
    /*inicializacao*/
    int entrada[] = {1,50,20,62,60,25,30};
    int saida[]   = {62,60,30,50,1,25,20};
    int i;
    int max_size = sizeof(entrada)/sizeof(entrada[0]);
    /*chamada*/
    constroi_heap(entrada,max_size);
    /*verificacao*/
    for (i=0;i<max_size;i++){
        assert(entrada[i]==saida[i]);
    }

}

void test_sobe(){
    /*inicializacao*/
    int entrada[] = {62,60,30,50,100,25,20};
    int saida[]   = {100,62,30,50,60,25,20};
    int i;
    int max_size = sizeof(entrada)/sizeof(entrada[0]);
    /*chamada*/
    sobe(entrada,4);
    /*verificacao*/
    for (i=0;i<max_size;i++){
        assert(entrada[i]==saida[i]);
    }
}

void test_acessa_max(){
    int v[]   = {100,62,30,50,60,25,20};
    assert(acessa_max(v) == 100);
}
void test_extrai_max(){
    /*inicializacao*/
    int entrada[] = {100,62,30,50,60,25,20};
    int saida1[]   = {62,60,30,50,20,25};
    int saida2[]   = {60,50,30,25,20};

    int i;
    int max_size = sizeof(entrada)/sizeof(entrada[0]);
    /*chamada*/
    assert(extrai_max(entrada,&max_size)==100);
    assert(max_size == 6);
    
    /*verificacao*/
    for (i=0;i<max_size;i++){
        assert(entrada[i]==saida1[i]);
    }
    /*chamada*/
    assert(extrai_max(entrada,&max_size)==62);
    assert(max_size == 5);
    
    /*verificacao*/
    for (i=0;i<max_size;i++){
        assert(entrada[i]==saida2[i]);
    }
}
void test_insere_elemento(){
    /*inicializacao*/
    int max_size = 10;
    int entrada[10] = {100,62,30,50,60,25,20};
    int saida1[]   = {100,70,30,62,60,25,20,50};
    int saida2[]   = {150,100,30,70,60,25,20,62};;

    int i;
    int tam = sizeof(entrada)/sizeof(entrada[0]);
    /*chamada*/
    assert(insere_elemento(entrada,&tam,max_size,70)==EXIT_SUCCESS);
    assert(tam == 8);
    
    /*verificacao*/
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida1[i]);
    }
    /*chamada*/
    assert(insere_elemento(entrada,&tam,max_size,150)==EXIT_SUCCESS);
    assert(tam == 9);
    
    /*verificacao*/
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida2[i]);
    }
}

void test_altera_prioridade(){
    /*inicializacao*/
    int max_size = 10;
    int entrada[10] = {100,62,30,50,60,25,20};
    int saida1[]    = {105,100,30,50,60,25,20};
    int saida2[]    = {100,60,30,50,1,25,20};
    int i;
    int tam = sizeof(entrada)/sizeof(entrada[0]);
    /*chamada*/
    assert(altera_prioridade(entrada,tam,1,105)==EXIT_SUCCESS);
    /*verificacao*/
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida1[i]);
    }
    /*chamada*/
    assert(altera_prioridade(entrada,tam,0,1)==EXIT_SUCCESS);
    /*verificacao*/
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida2[i]);
    }
}
void test_heapsort(){
    int entrada[]   = {100,62,30,50,60,25,20};
    int saida[]     = {20 ,25,30,50,60,62,100};
    int tam = sizeof(entrada)/sizeof(entrada[0]);
    int i;
    heapsort(entrada,tam);
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida[i]);
    }
}

int main(void){
    test_pai();
    test_filho_esq();
    test_filho_dir();
    test_desce();
    test_constroi_heap();
    test_sobe();
    test_acessa_max();
    test_extrai_max();
    test_insere_elemento();
    test_altera_prioridade();
    test_heapsort();
	return EXIT_SUCCESS;
}
