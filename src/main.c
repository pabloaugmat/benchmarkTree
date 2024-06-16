#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"
#include "rubroNegra.h"

#define NUM_ELEMENTS 10000
#define NUM_SEARCHES 1000

void benchmark_avl()
{
    avl *avl_tree = avl_criaArvore();
    clock_t start, end;

    // Inserção de elementos
    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        avl_insereNo(avl_tree, i);
    }
    end = clock();
    printf("AVL inserção: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Remoção de elementos
    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        avl_removeNo(avl_tree, i);
    }
    end = clock();
    printf("AVL remoção: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Busca de elementos aleatórios
    start = clock();
    for (int i = 0; i < NUM_SEARCHES; i++)
    {
        int value = rand() % NUM_ELEMENTS;
        avl_buscaNo(avl_tree, value);
    }
    end = clock();
    printf("AVL busca: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_rb()
{
    rb *rb_tree = rb_criaArvore();
    clock_t start, end;

    // Inserção de elementos
    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        rb_insereNo(rb_tree, i);
    }
    end = clock();
    printf("RB inserção: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Remoção de elementos
    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        rb_removeNo(rb_tree, i);
    }
    end = clock();
    printf("RB remoção: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Busca de elementos aleatórios
    start = clock();
    for (int i = 0; i < NUM_SEARCHES; i++)
    {
        int value = rand() % NUM_ELEMENTS;
        rb_buscaNo(rb_tree, value);
    }
    end = clock();
    printf("RB busca: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main()
{
    srand(02062016);

    printf("Benchmark AVL:\n");
    benchmark_avl();

    printf("Benchmark Rubro-Negra:\n");
    benchmark_rb();

    return 0;
}
