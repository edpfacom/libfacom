# libfacom

# compilar diretamente diversos arquivos

Se você estiver dentro da pasta de teste executar
```
gcc ../src/<algoritmo>.c <test_algoritmo>.c -o <executavel>
```

Exemplo para compilar a hash

```
gcc ../src/hash.c test_hash.c -o hash
```




# compilar dinamicamente

1. compilar os modulos objetos .o
```
gcc -c -fpic heap.c
```
verificação: veja se foram criados os modulos .o

2. criar a biblioteca
```
gcc -shared -o libfacom.so heap.o
```

3. compilar o executável
```
gcc -L. -o main main.c -lfacom 
```
4. ajustar o LD_LIBRARY_PATH
```
export LD_LIBRARY_PATH=CAMINHO_PASTA_ATUAL
```
