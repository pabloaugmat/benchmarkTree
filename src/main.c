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
    reset_rotacoes_avl();
    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        avl_insereNo(avl_tree, i);
    }
    end = clock();
    printf("AVL inserção: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("AVL rotações na inserção: %d\n", get_rotacoes_avl());

    // Remoção de elementos
    reset_rotacoes_avl(); // Reinicia a contagem de rotações para remoção
    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        avl_removeNo(avl_tree, i);
    }
    end = clock();
    printf("AVL remoção: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("AVL rotações na remoção: %d\n", get_rotacoes_avl());

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
    reset_rotacoes_rb();
    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        rb_insereNo(rb_tree, i);
    }
    end = clock();
    printf("RB inserção: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("RB rotações na inserção: %d\n", get_rotacoes_rb());

    // Remoção de elementos
    reset_rotacoes_rb(); // Reinicia a contagem de rotações para remoção
    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        rb_removeNo(rb_tree, i);
    }
    end = clock();
    printf("RB remoção: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("RB rotações na remoção: %d\n", get_rotacoes_rb());

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
