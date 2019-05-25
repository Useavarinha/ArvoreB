
#pragma once

#define TIPO char

#define T 2           /*N�mero que define m�nimo e m�ximo de chaves!*/
#define NOT_FOUND -1  /*Valor retornado quando o n� n�o existe!*/
#define TRUE 1        /*Booleano para verdadeiro!*/
#define FALSE 0       /*Booleano para falso!*/

/*Estrutura b�sica para uma �rvore B: */
typedef struct _node
{
  int n; /*N�mero de chaves armazenadas no n�!*/
  int folha; /*Booleano que indica se o n� � folha ou n�o!*/
  TIPO chaves [2 * T - 1]; /*N�mero m�ximo de chaves {tipo char} em um n�!*/
  struct _node* filhos [2 * T]; /*Ponteiros para os filhos de cada n�!*/
} No, Arvore;

Arvore* criar ();

void imprimir(Arvore* a, int nivel);/*Fun��o para imprimir uma �rvore B:*/

int buscar(Arvore* a, TIPO chave);/*Fun��o para buscar uma chave em uma �rvore B:*/

Arvore* dividir_no(Arvore* x, int i, Arvore* y);/*Descri��o: ????*/

Arvore* inserir_arvore_nao_cheia(Arvore* x, TIPO k);/*Descri��o: ????*/

Arvore* inserir(Arvore* raiz, TIPO chave);/*Fun��o para inserir uma chave em uma �rvore B:*/
