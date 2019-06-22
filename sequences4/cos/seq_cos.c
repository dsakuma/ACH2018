/*  Program: Analisador de somatoria de funcoes
 *    Autor: Daniel Sakuma
 *    Last modification: April 8 2011*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void plotGraphic (char gnucommad[]);
int factorial (int x);

int main(){

  int i; /* variavel que define o tamanho do dominio */
  int k; /* tamanho do polinomio */
  int fim;
  int tamanho_ini;
  int tamanho_fim;
  float soma = 0.0;

  FILE *dat; /* ponteiro para o arquivo temporario para o gnuplot */

  /* cria arquivo para plot */
  if((dat = fopen("seq_cos.dat", "w")) == NULL)
  {
      perror("\nNao foi possivel criar o arquivo temporario");
      exit(1);
  }

  /* leitura dos parametros de entrada */
  printf("Entre com o ultimo valor de plotagem: ");
  scanf("%d", &fim);

  printf("Entre com o tamanho de polinomio inicial: ");
  scanf("%d", &tamanho_ini);

  printf("Entre com o tamanho de polinomio final: ");
  scanf("%d", &tamanho_fim);


  /* imprime valores no console */
  for(i = 0; i <= fim; i++){
    fprintf(dat, "%d\t", i);
    for(k = 1; k <= tamanho_fim; k++){
      //(-1^k) * (x^(2k)) / fact(2k)
      soma += ( pow(-1,k) * pow(i,(2*k)) ) / factorial(2*k);
      if(k>=tamanho_ini) fprintf(dat, "%f\t", soma);
    }
    soma = 0;
    fprintf(dat, "\n");
  }

  return 0;

}


int factorial(int x) {
    int fac = 1;
    int i;
    for (i=2; i<=x; i++) fac *= i;
    return fac;
}
