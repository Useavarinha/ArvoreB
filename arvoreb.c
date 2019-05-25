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

    else if (a->folha)
        return NOT_FOUND;

    return buscar(a->filhos [i], chave);
}

/* TA QUASE PRONTO */
Arvore* dividir_no(Arvore* x, int i, Arvore* y)
{
    int j;
    int mediana = (2*T - 1)/2;

    x->chaves [0] = y->chaves [mediana];
    x->filhos [1] = criar();

    for (i = mediana + 1, j = 0; i < y->n; i++, j++)
    {
        x->filhos [1] = inserir_arvore_nao_cheia(x->filhos [1], y->chaves [i]);
        (x->filhos [1])->filhos [j] = y->filhos [i];
    }
    (x->filhos [1])->filhos [j] = y->filhos [i];

    y->n -= mediana + 1;
    x->n += mediana;

    return x;
}

/* PARECE TA PRONTO */
Arvore* inserir_arvore_nao_cheia(Arvore* x, TIPO k)
{
    int i;

    if (x->folha)
    {
        for (i = x->n - 1; (i >= 0) && (k < x->chaves [i]); i--) //Percorre de frente pra trás
            x->chaves [i+1] = x->chaves [i]; //Desloca as chaves pra frente pra dar espaço pra nova

        x->chaves [i+1] = k;
        x->n++;

        return x;
    }

    i = 0;
    while (k > x->chaves [i])//Dá pra usar a buscar aqui?
        i++;

    return inserir(x->filhos[i], k);
}

Arvore *inserir(Arvore* raiz, TIPO chave)
{
    Arvore* r = raiz; //pra que isso?
    if (r->n == (2*T - 1)) //Se o nó está cheio
    {
      Arvore *s = criar();
      s->folha = FALSE;
      s->filhos [0] = r;
      s = dividir_no(s, 0, r); //Não to usando esse 0, não entendi o que é
      s = inserir_arvore_nao_cheia(s, chave);
      return s;
    }

    return inserir_arvore_nao_cheia(r, chave);
}
