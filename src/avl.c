#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int rotacoes_avl = 0;

typedef struct no
{
    int chave;
    int fb; // fator de balanceamento
    struct no *Fesq;
    struct no *Fdir;
    struct no *pai;
} no;

typedef struct avl
{
    no *sentinela;
    int numElementos;
} avl;

void reset_rotacoes_avl()
{
    rotacoes_avl = 0;
}

int get_rotacoes_avl()
{
    return rotacoes_avl;
}

avl *avl_criaArvore()
{
    avl *arv = (avl *)malloc(sizeof(avl));
    arv->sentinela = (no *)malloc(sizeof(no));
    arv->sentinela->chave = -1000;
    arv->sentinela->Fesq = NULL;
    arv->sentinela->Fdir = NULL;
    arv->sentinela->pai = NULL;
    arv->numElementos = 0;
    return arv;
}

void avl_rotacaoEsq(no *noDesbalanceado)
{
    no *FilhoDaDireita = noDesbalanceado->Fdir;
    noDesbalanceado->Fdir = FilhoDaDireita->Fesq;
    if (FilhoDaDireita->Fesq != NULL)
        FilhoDaDireita->Fesq->pai = noDesbalanceado;
    FilhoDaDireita->pai = noDesbalanceado->pai;

    if (noDesbalanceado == noDesbalanceado->pai->Fesq)
        noDesbalanceado->pai->Fesq = FilhoDaDireita;
    else
        noDesbalanceado->pai->Fdir = FilhoDaDireita;

    FilhoDaDireita->Fesq = noDesbalanceado;
    noDesbalanceado->pai = FilhoDaDireita;
    noDesbalanceado->fb = 0;
    FilhoDaDireita->fb = 0;
    rotacoes_avl++;
}

void avl_rotacaoDir(no *noDesbalanceado)
{
    no *FilhoDaEsquerda = noDesbalanceado->Fesq;
    noDesbalanceado->Fesq = FilhoDaEsquerda->Fdir;
    if (FilhoDaEsquerda->Fdir != NULL)
        FilhoDaEsquerda->Fdir->pai = noDesbalanceado;
    FilhoDaEsquerda->pai = noDesbalanceado->pai;

    if (noDesbalanceado == noDesbalanceado->pai->Fdir)
        noDesbalanceado->pai->Fdir = FilhoDaEsquerda;
    else
        noDesbalanceado->pai->Fesq = FilhoDaEsquerda;

    FilhoDaEsquerda->Fdir = noDesbalanceado;
    noDesbalanceado->pai = FilhoDaEsquerda;
    noDesbalanceado->fb = 0;
    FilhoDaEsquerda->fb = 0;
    rotacoes_avl++;
}

void avl_balanceamento(avl *arv, no *noDesbalanceado)
{
    no *filho;
    if (noDesbalanceado->fb == 2)
    {
        filho = noDesbalanceado->Fdir;
        if (filho->fb == -1)
        {
            int fbNeto = filho->Fesq->fb;
            avl_rotacaoDir(filho);
            avl_rotacaoEsq(noDesbalanceado);

            if (fbNeto == 0)
            {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else if (fbNeto == -1)
            {
                noDesbalanceado->fb = 0;
                filho->fb = 1;
            }
            else if (fbNeto == 1)
            {
                noDesbalanceado->fb = -1;
                filho->fb = 0;
            }
        }
        else
        {
            int fbFilho = filho->fb;
            avl_rotacaoEsq(noDesbalanceado);

            if (fbFilho == 0)
            {
                noDesbalanceado->fb = 1;
                filho->fb = -1;
            }
            else if (fbFilho == 1)
            {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
        }
    }
    else if (noDesbalanceado->fb == -2)
    {
        filho = noDesbalanceado->Fesq;
        if (filho->fb == 1)
        {
            int fbNeto = filho->Fdir->fb;
            avl_rotacaoEsq(filho);
            avl_rotacaoDir(noDesbalanceado);

            if (fbNeto == 0)
            {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else if (fbNeto == -1)
            {
                noDesbalanceado->fb = 1;
                filho->fb = 0;
            }
            else if (fbNeto == 1)
            {
                noDesbalanceado->fb = 0;
                filho->fb = -1;
            }
        }
        else
        {
            int fbFilho = filho->fb;
            avl_rotacaoDir(noDesbalanceado);

            if (fbFilho == 0)
            {
                noDesbalanceado->fb = -1;
                filho->fb = 1;
            }
            else if (fbFilho == -1)
            {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
        }
    }
}

void avl_atualizaFB_Insercao(avl *arv, no *novoNo)
{
    no *aux = novoNo;
    do
    {
        if (aux->pai->chave > aux->chave)
            aux->pai->fb--;
        else
            aux->pai->fb++;

        aux = aux->pai;
    } while (aux->pai->chave != -1000 && aux->fb != 0 && aux->fb != 2 && aux->fb != -2);

    if (aux->fb == 2 || aux->fb == -2)
        avl_balanceamento(arv, aux);
}

int avl_insereNo(avl *arv, int valor)
{
    no *NewNode = (no *)malloc(sizeof(no));
    NewNode->chave = valor;
    NewNode->Fesq = NULL;
    NewNode->Fdir = NULL;
    NewNode->fb = 0;
    NewNode->pai = arv->sentinela;

    if (arv->sentinela->Fdir == NULL)
    {
        arv->sentinela->Fdir = NewNode;
        arv->numElementos++;
        return 1;
    }

    no *atual = arv->sentinela->Fdir;
    while (atual != NULL)
    {
        if (atual->chave > valor && atual->Fesq == NULL)
        {
            NewNode->pai = atual;
            atual->Fesq = NewNode;
            arv->numElementos++;
            avl_atualizaFB_Insercao(arv, NewNode);
            return 1;
        }
        else if (atual->chave < valor && atual->Fdir == NULL)
        {
            NewNode->pai = atual;
            atual->Fdir = NewNode;
            arv->numElementos++;
            avl_atualizaFB_Insercao(arv, NewNode);
            return 1;
        }

        if (atual->chave > valor)
            atual = atual->Fesq;
        else
            atual = atual->Fdir;
    }
    return 0;
}

void avl_imprimeOrdem(no *raiz)
{
    if (raiz != NULL)
    {
        avl_imprimeOrdem(raiz->Fesq);
        printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        avl_imprimeOrdem(raiz->Fdir);
    }
}

void avl_imprimePreOrdem(no *raiz)
{
    if (raiz != NULL)
    {
        printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        avl_imprimePreOrdem(raiz->Fesq);
        avl_imprimePreOrdem(raiz->Fdir);
    }
}

no *avl_getRaiz(avl *arv)
{
    return arv->sentinela->Fdir;
}

int avl_getNumElementos(avl *arv)
{
    return arv->numElementos;
}

int avl_processaCarga(avl *arv, char *nomeArquivo, int tipo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return -2;
    }

    int valor;
    while (fscanf(arquivo, "%d", &valor) == 1)
    {
        if (tipo == 1)
            avl_insereNo(arv, valor);
        else if (tipo == 2)
            avl_removeNo(arv, valor);
    }

    fclose(arquivo);
    return 1;
}

int avl_removeNo(avl *arv, int valor)
{
    if (arv == NULL)
        return 0;

    no *atual = arv->sentinela->Fdir;
    no *aux;

    while (atual != NULL)
    {
        if (atual->chave == valor)
        {
            if (atual->Fesq == NULL && atual->Fdir == NULL)
            {
                if (atual->pai->chave > atual->chave)
                    atual->pai->Fesq = NULL;
                else
                    atual->pai->Fdir = NULL;
                avl_atualizaFB_remocao(arv, atual->pai, atual->chave);
                free(atual);
                arv->numElementos--;
                return 1;
            }
            else if (atual->Fesq == NULL || atual->Fdir == NULL)
            {
                aux = (atual->Fesq != NULL) ? atual->Fesq : atual->Fdir;
                if (atual->pai->chave > atual->chave)
                    atual->pai->Fesq = aux;
                else
                    atual->pai->Fdir = aux;
                aux->pai = atual->pai;
                avl_atualizaFB_remocao(arv, atual->pai, atual->chave);
                free(atual);
                arv->numElementos--;
                return 1;
            }
            else
            {
                no *sucessor = atual->Fdir;
                while (sucessor->Fesq != NULL)
                    sucessor = sucessor->Fesq;
                int chaveSucessor = sucessor->chave;
                avl_removeNo(arv, sucessor->chave);
                atual->chave = chaveSucessor;
                return 1;
            }
        }

        if (atual->chave < valor)
            atual = atual->Fdir;
        else
            atual = atual->Fesq;
    }
    return -1;
}

void avl_atualizaFB_remocao(avl *arv, no *pai, int chaveRemovida)
{
    no *filho;
    no *aux = pai;
    if (aux->chave == -1000)
        return;

    do
    {
        if (aux->chave > chaveRemovida)
        {
            aux->fb++;
            if ((aux->fb == 0 || aux->fb == 2 || aux->fb == -2) && aux->pai != arv->sentinela)
                aux->pai->fb--;
        }
        else
        {
            aux->fb--;
            if ((aux->fb == 0 || aux->fb == 2 || aux->fb == -2) && aux->pai != arv->sentinela)
                aux->pai->fb++;
        }
        filho = aux;
        aux = aux->pai;
    } while (aux->chave != -1000 && filho->fb != 1 && filho->fb != -1 && filho->fb != 2 && filho->fb != -2);

    if (filho->fb == 2 || filho->fb == -2)
    {
        avl_balanceamento(arv, filho);
        if (filho->pai != arv->sentinela && filho->pai->fb != 0)
            avl_atualizaFB_remocao(arv, filho->pai->pai, chaveRemovida);
    }
}

#include "avl.h"

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

// Função pública para buscar um nó com a chave especificada na árvore AVL
no *avl_buscaNo(avl *arv, int chave)
{
    if (arv == NULL || arv->sentinela == NULL)
    {
        return NULL;
    }

    // Inicia a busca a partir da raiz (ignorando o sentinela)
    return buscaNoRecursivo(arv->sentinela->Fesq, chave);
}
