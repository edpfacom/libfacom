
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/libfacom.h"

typedef struct{ 
    char nome[30];
    char  cpf[11];
}taluno;

typedef struct{
    char placa[10];
    char modelo[30];
}tcarro;

char * get_key(void * reg){
    return (*((taluno *)reg)).nome;
}
char * get_key_carro(void * reg){
    return (*((tcarro *)reg)).placa;
}



void * aloca_aluno(char * nome, char * cpf){
    taluno * aluno = malloc(sizeof(taluno));
    strcpy(aluno->nome,nome);
    strcpy(aluno->cpf,cpf);
    return aluno;
}

void * aloca_carro(char * placa, char * modelo){
    tcarro * carro = malloc(sizeof(tcarro));
    strcpy(carro->placa,placa);
    strcpy(carro->modelo,modelo);
    return carro;
}




void test_insere(){
    thash h;
    int nbuckets = 10;
    hash_constroi(&h,nbuckets,get_key);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_FAILURE);
    hash_apaga(&h);
}
void test_search(){
    thash h;
    int nbuckets = 10;
    taluno * aluno;
    hash_constroi(&h,nbuckets,get_key);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("takashi","1123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("matsubara","2123456789"))==EXIT_SUCCESS);

    aluno = hash_busca(h,"edson");
    assert(aluno->cpf[0]=='0');
    aluno = hash_busca(h,"takashi");
    assert(aluno->cpf[0]=='1');
    aluno = hash_busca(h,"matsubara");
    assert(aluno->cpf[0]=='2');
    aluno = hash_busca(h,"patricia");
    assert(aluno == NULL);

    hash_apaga(&h);
}

void test_remove(){
    thash h;
    int nbuckets = 10;
    taluno * aluno;
    hash_constroi(&h,nbuckets,get_key);
    assert(hash_insere(&h,aloca_aluno("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("takashi","1123456789"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_aluno("matsubara","2123456789"))==EXIT_SUCCESS);

    aluno = hash_busca(h,"edson");
    assert(aluno->cpf[0]=='0');
    aluno = hash_busca(h,"takashi");
    assert(aluno->cpf[0]=='1');
    aluno = hash_busca(h,"matsubara");
    assert(aluno->cpf[0]=='2');
    aluno = hash_busca(h,"patricia");
    assert(aluno == NULL);

    assert(h.size == 3);
    assert(hash_remove(&h,"edson")==EXIT_SUCCESS);
    aluno = hash_busca(h,"edson");
    assert(aluno == NULL);
    assert(h.size == 2);

    assert(hash_remove(&h,"edson")==EXIT_FAILURE);

    aluno = hash_busca(h,"matsubara");
    assert(aluno->cpf[0]=='2');


    hash_apaga(&h);

}

void test_remove_carro(){
    thash h;
    int nbuckets = 10;
    tcarro * carro;
    hash_constroi(&h,nbuckets,get_key_carro);
    assert(hash_insere(&h,aloca_carro("htj0073","vw fox"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_carro("ook7308","honda fit"))==EXIT_SUCCESS);
    assert(hash_insere(&h,aloca_carro("ook1234","fusca"))==EXIT_SUCCESS);

    carro = hash_busca(h,"ook1234");
    assert(strcmp(carro->modelo,"fusca")==0);
    assert(h.size == 3);
    carro = hash_busca(h,"ooo1234");
    assert(carro == NULL);
    hash_apaga(&h);

}



int main(int argc, char* argv[]){
    test_insere();
    test_search();
    test_remove();
    test_remove_carro();
    return 0;
}
