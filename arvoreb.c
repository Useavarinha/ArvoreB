#include <stdio.h>
#include <stdlib.h>

#include "arvoreb.h"

/*Função para criar e inicializar uma árvore B:*/
Arvore* criar()
{
    Arvore* a = (Arvore*) malloc(sizeof(Arvore));
    a->n = 0;
    a->folha = TRUE;
    return a;
}

void imprimir(Arvore* a, int nivel)
{
    int i;

    /*Imprime recuo para definir o nível do nó: */
    for (i = 0; i < nivel; i++)
        printf("  ");

    /*Imprime as chaves armazenadas no nó: */
    printf("|");
    for (i = 0; i < a->n; i++)
      printf("%c|", a->chaves [i]); //printf("%02d|", a->chaves[i]); //para inteiros

    printf("\n");

    /*Recursivamente imprime as chaves dos filhos: */
    for (i = 0; i <= a->n; i++)
    {
      if (a->folha == FALSE)
         imprimir(a->filhos [i], nivel + 1);
    }
}

int buscar(Arvore* a, TIPO chave)
{
    int i = 0;

   /*Procurando a chave no vetor de chaves: */
    while ( (i < a->n) && (chave > a->chaves [i]) )
        i++;

    if (  (i < a->n) && (chave == a->chaves [i]) ) //Não tinha a parte do "(i < a->n)", ia dar errado?
        return i;

    if (a->folha)
        return NOT_FOUND;

    return buscar(a->filhos [i], chave);
}

/* TA QUASE PRONTO */
Arvore* dividir_no(Arvore* x, int i, Arvore* y)
{
    int j;
    int mediana = T - 1;
    Arvore* z = criar();

    z->folha = y->folha;
    z->n = mediana;
    y->n = mediana;

    for (j = 0; j < mediana; j++) /* copia da metade pra frente do primeiro nó */
        z->chaves [j] = y->chaves [T + j];

    if (!y->folha) /* se não for folha tem que copiar os filhos também */
    {
        for (j = 0; j < T; j++)
            z->filhos [j] = y->filhos [T + j];
    }

    for (j = x->n; j > i; j--) /* move os filhos para frente para poder dar lugar ao novo */
        x->filhos [j + 1] = x->filhos [j];

    x->filhos [i + 1] = z;

    for (j = x->n; j > i; j--) /* move as chaves para frente para poder dar lugar a nova */
        x->chaves [j] = x->chaves [j - 1];

    x->chaves [i] = y->chaves [mediana];
    x->n++;

    return x;
}

/* PARECE TA PRONTO */
Arvore* inserir_arvore_nao_cheia(Arvore* x, TIPO k)
{
    int i;
    int chave_final = x->n - 1;

    if (x->folha)
    {
        for (i = chave_final; (i >= 0) && (k < x->chaves [i]); i--) //Percorre de frente pra trás
            x->chaves [i+1] = x->chaves [i]; //Desloca as chaves pra frente pra dar espaço pra nova

        x->chaves [i+1] = k;
        x->n++;

        return x;
    }

    i = 0;
    while (k > x->chaves [i] && i < x->n) /* Acha o filho certo */
        i++;

    if (x->filhos [i]->n == (2*T - 1)) /* Se este estiver cheio */
    {
        dividir_no(x, i, x->filhos [i]);

        if (k > x->chaves [i])
            i++;
    }

    x->filhos [i] = inserir_arvore_nao_cheia(x->filhos [i], k);

    return x;
}

Arvore *inserir(Arvore* raiz, TIPO chave)
{
    Arvore* r = raiz;
    if (r->n == (2*T - 1)) //Se o nó está cheio
    {
      Arvore *s = criar();
      s->folha = FALSE;
      s->filhos [0] = r;
      s = dividir_no(s, 0, r);
      s = inserir_arvore_nao_cheia(s, chave);
      return s;
    }

    return inserir_arvore_nao_cheia(r, chave);
}


