
#include <stdio.h>
#include <stdlib.h>
#include "rubroNegra.h"

int rotacoes_rb = 0;

struct no
{
    int chave;
    char cor;
    struct no *Fesq;
    struct no *Fdir;
    struct no *pai;
};
;
;

struct rb
{
    struct no *sentinelaFolha;
    struct no *sentinela;
    int numElementos;
};

void reset_rotacoes_rb()
{
    rotacoes_rb = 0;
}

int get_rotacoes_rb()
{
    return rotacoes_rb;
}

rb *rb_criaArvore()
{
    rb *a = (rb *)malloc(sizeof(rb));
    no *sentinelaa = (no *)malloc(sizeof(no));
    no *sentinela = (no *)malloc(sizeof(no));
    sentinela->cor = 'P';
    sentinelaa->cor = 'P';
    sentinelaa->chave = -1000;
    sentinelaa->pai = NULL;
    sentinelaa->Fesq = NULL;
    sentinelaa->Fdir = NULL;
    a->numElementos = 0;
    a->sentinela = sentinelaa;
    a->sentinelaFolha = sentinela;
    return a;
}
int rb_insereNo(rb *arv, int valor)
{
    if (arv == NULL)
    {
        return 0;
    }
    no *novo = (no *)malloc(sizeof(no));
    if (novo == NULL)
    {
        return 0;
    }
    novo->cor = 'V';
    novo->chave = valor;
    novo->Fesq = NULL;
    novo->Fdir = NULL;
    if (arv->sentinela->Fdir == NULL)
    {
        novo->cor = 'P';
        novo->pai = arv->sentinela;
        arv->sentinela->Fdir = novo;
        arv->numElementos++;
        return 1;
    }
    else
    {
        no *atual = arv->sentinela->Fdir;
        no *ant = NULL;
        while (atual != NULL)
        {
            ant = atual;
            if (valor < atual->chave)
            {
                atual = atual->Fesq;
            }
            else
            {
                atual = atual->Fdir;
            }
        }
        novo->pai = ant;
        if (valor < ant->chave)
        {
            ant->Fesq = novo;
        }
        else
        {
            ant->Fdir = novo;
        }
    }
    arv->numElementos++;
    rb_balanceamentoInsercao(arv, novo);
    return 1;
}
int rb_removeNo(rb *arv, int valor)
{

    if (arv == NULL)
        return 0;

    no *aux;
    no *atual = arv->sentinela->Fdir;
    no *maisEsquerda;

    while (atual != NULL)
    {
        if (atual->chave == valor)
        {
            if (atual->cor == 'P')
            {
                if (atual->Fesq == NULL && atual->Fdir == NULL)
                {
                    if (atual->pai->chave > atual->chave)
                        atual->pai->Fesq = NULL;
                    else
                        atual->pai->Fdir = NULL;

                    if (arv->numElementos != 1)
                        rb_balanceamentoRemocao(arv, atual, atual->pai, valor);

                    free(atual);
                    arv->numElementos--;
                    return 1;
                }
                else if (atual->Fesq == NULL && atual->Fdir != NULL)
                {
                    aux = atual->Fdir;
                    if (atual->pai->chave > atual->chave)
                        aux->pai->pai->Fesq = atual->Fdir;
                    else
                        aux->pai->pai->Fdir = atual->Fdir;
                    aux->pai = atual->pai;

                    maisEsquerda = atual->Fdir;
                    while (maisEsquerda->Fesq != NULL)
                        maisEsquerda = maisEsquerda->Fesq;

                    int a = maisEsquerda->chave;
                    if (arv->numElementos != 1)
                        rb_balanceamentoRemocao(arv, maisEsquerda, atual->pai, valor);
                    atual->chave = a;

                    free(atual);
                    arv->numElementos--;
                    return 1;
                }
                else if (atual->Fesq != NULL && atual->Fdir == NULL)
                {
                    aux = atual->Fesq;
                    if (atual->pai->chave > atual->chave)
                        aux->pai->pai->Fesq = atual->Fesq;
                    else
                        aux->pai->pai->Fdir = atual->Fesq;
                    aux->pai = atual->pai;

                    maisEsquerda = atual->Fesq;

                    int a = maisEsquerda->chave;
                    if (arv->numElementos != 1)
                        rb_balanceamentoRemocao(arv, maisEsquerda, atual->pai, valor);
                    atual->chave = a;

                    free(atual);
                    arv->numElementos--;
                    return 1;
                }
                else
                {
                    maisEsquerda = atual->Fdir;
                    while (maisEsquerda->Fesq != NULL)
                        maisEsquerda = maisEsquerda->Fesq;

                    int a = maisEsquerda->chave;
                    rb_removeNo(arv, maisEsquerda->chave);
                    atual->chave = a;
                }
            }
            else
            {
                if (atual->Fesq == NULL && atual->Fdir == NULL)
                {
                    if (atual->pai->chave > atual->chave)
                        atual->pai->Fesq = NULL;
                    else
                        atual->pai->Fdir = NULL;

                    free(atual);
                    arv->numElementos--;
                    return 1;
                }
                else if (atual->Fesq == NULL && atual->Fdir != NULL)
                {
                    aux = atual->Fdir;
                    if (atual->pai->chave > atual->chave)
                        aux->pai->pai->Fesq = atual->Fdir;
                    else
                        aux->pai->pai->Fdir = atual->Fdir;
                    aux->pai = atual->pai;

                    maisEsquerda = atual->Fdir;
                    while (maisEsquerda->Fesq != NULL)
                        maisEsquerda = maisEsquerda->Fesq;
                    free(atual);
                    arv->numElementos--;
                    return 1;
                }
                else if (atual->Fesq != NULL && atual->Fdir == NULL)
                {
                    aux = atual->Fesq;
                    if (atual->pai->chave > atual->chave)
                        aux->pai->pai->Fesq = atual->Fesq;
                    else
                        aux->pai->pai->Fdir = atual->Fesq;
                    aux->pai = atual->pai;

                    free(atual);
                    arv->numElementos--;
                    return 1;
                }
                else
                {
                    maisEsquerda = atual->Fdir;
                    while (maisEsquerda->Fesq != NULL)
                        maisEsquerda = maisEsquerda->Fesq;

                    int a = maisEsquerda->chave;
                    rb_removeNo(arv, maisEsquerda->chave);
                    atual->chave = a;
                }
            }
        }
        if (atual->chave < valor)
            atual = atual->Fdir;
        else
            atual = atual->Fesq;
    }
    return -1;
}

void rb_imprimeOrdem(no *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    if (raiz != NULL)
    {
        rb_imprimeOrdem(raiz->Fesq);
        printf("%d - %d\n", raiz->chave, raiz->pai->chave);
        rb_imprimeOrdem(raiz->Fdir);
    }
}
void rb_imprimePreOrdem(rb *arv, no *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    if (raiz != NULL)
    {
        printf("%d: %c -- %d\n", raiz->chave, raiz->cor, raiz->pai->chave);
        rb_imprimePreOrdem(arv, raiz->Fesq);
        rb_imprimePreOrdem(arv, raiz->Fdir);
    }
}
no *rb_getRaiz(rb *arv)
{
    return arv->sentinela->Fdir;
}
int rb_getNumElementos(rb *arv)
{
    return arv->numElementos;
}
int rb_processaCarga(rb *arv, char *nomeArquivo, int tipo)
{
    int retorno;
    FILE *arq;
    int a;
    arq = fopen(nomeArquivo, "r");
    if (arq == NULL)
    {
        return -2;
    }
    if (tipo == 1)
    {
        while (!feof(arq))
        {
            fscanf(arq, "%d", &a);
            retorno = rb_insereNo(arv, a);
            if (retorno == 0)
            {
                return 0;
            }
        }
    }
    else
    {
        while (!feof(arq))
        {
            fscanf(arq, "%d", &a);
            retorno = rb_removeNo(arv, a);
            if (retorno == 0)
            {
                return 0;
            }
        }
    }
    fclose(arq);
    return 1;
}

void rb_balanceamentoInsercao(rb *arv, no *noDesbal)
{
    if (noDesbal != arv->sentinela->Fdir)
    {
        no *vo;
        no *tio;
        no *pai;

        pai = noDesbal->pai;
        vo = pai->pai;
        if (pai->chave < vo->chave)
        {
            tio = vo->Fdir;
        }
        else
        {
            tio = vo->Fesq;
        }
        if (tio == NULL || tio == arv->sentinelaFolha)
        {
            tio = arv->sentinelaFolha;
            tio->cor = 'P';
        }
        // esquerda do vô
        if (vo->chave > noDesbal->chave)
        {
            // caso 1
            if (tio->cor == 'V')
            {
                // printf("caso1esq");
                pai->cor = 'P';
                tio->cor = 'P';
                vo->cor = 'V';
                rb_balanceamentoInsercao(arv, vo);
            }
            // caso 2
            else if (tio->cor == 'P' && pai->cor == 'V' && pai->Fdir == noDesbal)
            {
                // printf("caso2esq");
                rb_rotacaoEsq(arv, pai);
                rb_balanceamentoInsercao(arv, pai);
            }
            // caso 3
            else if (tio->cor == 'P' && pai->cor == 'V' && pai->Fesq == noDesbal)
            {
                // printf("caso3esq");
                pai->cor = 'P';
                vo->cor = 'V';
                rb_rotacaoDir(arv, vo);
            }
        }
        // direita do vô
        else
        {
            // caso 1
            if (tio->cor == 'V')
            {
                // printf("caso1dir");
                pai->cor = 'P';
                tio->cor = 'P';
                vo->cor = 'V';
                rb_balanceamentoInsercao(arv, vo);
            }
            // caso 2
            else if (tio->cor == 'P' && pai->cor == 'V' && pai->Fesq == noDesbal)
            {
                // printf("caso2dir");
                rb_rotacaoDir(arv, pai);
                rb_balanceamentoInsercao(arv, pai);
            }
            // caso 3
            else if (tio->cor == 'P' && pai->cor == 'V' && pai->Fdir == noDesbal)
            {
                // printf("caso3dir");
                pai->cor = 'P';
                vo->cor = 'V';
                rb_rotacaoEsq(arv, vo);
            }
        }
        arv->sentinela->Fdir->cor = 'P';
    }
}

void rb_rotacaoDir(rb *arv, no *noDesbal)
{
    no *aux = noDesbal->Fesq;
    noDesbal->Fesq = aux->Fdir;
    if (aux->Fdir != NULL)
    {
        aux->Fdir->pai = noDesbal;
    }
    aux->pai = noDesbal->pai;
    if (noDesbal == noDesbal->pai->Fesq)
    {
        noDesbal->pai->Fesq = aux;
    }
    else
    {
        noDesbal->pai->Fdir = aux;
    }
    aux->Fdir = noDesbal;
    noDesbal->pai = aux;
    rotacoes_rb++;
}
void rb_rotacaoEsq(rb *arv, no *noDesbal)
{
    no *aux = noDesbal->Fdir;
    noDesbal->Fdir = aux->Fesq;
    if (aux->Fesq != NULL)
    {
        aux->Fesq->pai = noDesbal;
    }
    aux->pai = noDesbal->pai;
    if (noDesbal == noDesbal->pai->Fesq)
    {
        noDesbal->pai->Fesq = aux;
    }
    else
    {
        noDesbal->pai->Fdir = aux;
    }
    aux->Fesq = noDesbal;
    noDesbal->pai = aux;
    rotacoes_rb++;
}

void rb_balanceamentoRemocao(rb *arv, no *noDesbal, no *pai, int valor)
{
    while (noDesbal != arv->sentinela->Fdir && (noDesbal == NULL || noDesbal->cor == 'P'))
    {
        if (noDesbal == pai->Fesq || pai->Fesq == NULL)
        {
            no *irmao = pai->Fdir;

            if (irmao == NULL)
                irmao = arv->sentinelaFolha;

            if (irmao->cor == 'V')
            {
                irmao->cor = 'P';
                pai->cor = 'V';
                rb_rotacaoEsq(arv, pai);
                irmao = pai->Fdir;
            }

            if ((irmao->Fesq == NULL || irmao->Fesq->cor == 'P') &&
                (irmao->Fdir == NULL || irmao->Fdir->cor == 'P'))
            {
                irmao->cor = 'V';
                noDesbal = pai;
                pai = noDesbal->pai;
            }
            else
            {
                if (irmao->Fdir == NULL || irmao->Fdir->cor == 'P')
                {
                    if (irmao->Fesq != NULL)
                        irmao->Fesq->cor = 'P';
                    irmao->cor = 'V';
                    rb_rotacaoDir(arv, irmao);
                    irmao = pai->Fdir;
                }
                irmao->cor = pai->cor;
                pai->cor = 'P';
                if (irmao->Fdir != NULL)
                    irmao->Fdir->cor = 'P';
                rb_rotacaoEsq(arv, pai);
                noDesbal = arv->sentinela->Fdir;
                break;
            }
        }
        else
        {
            no *irmao = pai->Fesq;

            if (irmao == NULL)
                irmao = arv->sentinelaFolha;

            if (irmao->cor == 'V')
            {
                irmao->cor = 'P';
                pai->cor = 'V';
                rb_rotacaoDir(arv, pai);
                irmao = pai->Fesq;
            }

            if ((irmao->Fesq == NULL || irmao->Fesq->cor == 'P') &&
                (irmao->Fdir == NULL || irmao->Fdir->cor == 'P'))
            {
                irmao->cor = 'V';
                noDesbal = pai;
                pai = noDesbal->pai;
            }
            else
            {
                if (irmao->Fesq == NULL || irmao->Fesq->cor == 'P')
                {
                    if (irmao->Fdir != NULL)
                        irmao->Fdir->cor = 'P';
                    irmao->cor = 'V';
                    rb_rotacaoEsq(arv, irmao);
                    irmao = pai->Fesq;
                }
                irmao->cor = pai->cor;
                pai->cor = 'P';
                if (irmao->Fesq != NULL)
                    irmao->Fesq->cor = 'P';
                rb_rotacaoDir(arv, pai);
                noDesbal = arv->sentinela->Fdir;
                break;
            }
        }
    }

    if (noDesbal != NULL)
        noDesbal->cor = 'P';
}

#include "rubroNegra.h"

// Função auxiliar recursiva para buscar o nó com a chave desejada
static no *buscaNoRecursivo(no *raiz, int chave)
{
    if (raiz == NULL || raiz->chave == chave)
    {
        return raiz;
    }

    if (chave < raiz->chave)
    {
        return buscaNoRecursivo(raiz->Fesq, chave);
    }
    else
    {
        return buscaNoRecursivo(raiz->Fdir, chave);
    }
}

// Função pública para buscar um nó com a chave especificada na árvore Rubro-Negra
no *rb_buscaNo(rb *arv, int chave)
{
    if (arv == NULL || arv->sentinela == NULL)
    {
        return NULL;
    }

    // Inicia a busca a partir da raiz (ignorando o sentinela)
    return buscaNoRecursivo(arv->sentinela->Fesq, chave);
}
