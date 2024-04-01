#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define SEED    0x12345678
#include "../include/libfacom.h"

uint32_t hashf(const char* str, uint32_t h){
    /* One-byte-at-a-time Murmur hash 
    Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp */
    for (; *str; ++str) {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}


int hash_insere(thash * h, void * bucket){
    return EXIT_SUCCESS;
}



int hash_constroi(thash * h,int nbuckets, char * (*get_key)(void *) ){
    return EXIT_SUCCESS;

}


void * hash_busca(thash h, const char * key){
    return NULL;

}

int hash_remove(thash * h, const char * key){
    return EXIT_FAILURE;

}

void hash_apaga(thash *h){
}


