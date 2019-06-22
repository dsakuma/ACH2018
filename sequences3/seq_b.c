/* Program: Sequences Analyser
 *    Autor: Daniel Sakuma
 *    Last modification: April 8 2011*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void plotGraphic (char gnucommad[]);
int factorial (int x);

int main(){

  float epsilon, precisao;
  float ini, fim; /* inicio e fim do intervalo */
  float *ar; /* arranjo com o resultado da funcao*/
  int intervalo; /* tamanho do intervalo do grafico*/
  int i; /* variavel para controle do arranjo */
  float j; /* variavel para controle do passo */
  int min; /*posicao a partir da qual ar[n+p]-ar[n] ficar menor que epsilon */
  int converge = 0;


  /* leitura dos parametros de entrada */
  printf("\nEntre com o valor de epsilon: ");
  scanf("%f", &epsilon);

  printf("Entre com o valor de inicio: ");
  scanf("%f", &ini);

  printf("Entre com o valor de fim: ");
  scanf("%f", &fim);

  printf("Entre com o valor da precisao: ");
  scanf("%f", &precisao);

  intervalo = fim-ini+1;


  /* alocacao de memoria para o arranjo */
  ar = malloc((intervalo / precisao) * sizeof(float)); 


  /* log para debug 
  printf("VALORES UTILIZADOS:\n");
  printf("epsilon = %f\n", epsilon);
  printf("precisao = %f\n", precisao);
  printf("ini = %f\n", ini);
  printf("fim = %f\n", fim);
  printf("intervalo = %d\n", intervalo);*/

  FILE *dat; /* ponteiro para o arquivo temporario para o gnuplot */


  /* cria arquivo para plot */
  if((dat = fopen("seq_b.dat", "w")) == NULL)
  {
      perror("\nNao foi possivel criar o arquivo temporario");
      exit(1);
  }


  /* preenche array de resultados */
  i = 0;
  for(j=ini;j<intervalo+ini;j=j+precisao){
    ar[i] = (1. / j );
    /* printf("ar[%d]=%f\n", i, ar[i]); */
    i++;
  }


  /* encontra uma distancia menor que epsilon */
  i = 0;
  float fa; /* f(n)*/
  float fb; /* f(n+p)*/
  for(j=ini;j<intervalo+ini;j=j+precisao){
    if( fabs(ar[i] - ar[i+1]) < epsilon) {
	printf("\nPosicao em que a f[n+p]-f[n] fica menor que epsilon:\n");
        printf("f(%f)=%f\tf(%f)=%f\tdistancia = %f\n", j,  ar[i], j+precisao, ar[i+1], fabs(ar[i] - ar[i+1])); 
        if (ar[i]<ar[i+1]) { fa = ar[i]; fb = ar[i+1]; }
        else { fa = ar[i+1]; fb = ar[i]; }
	converge = 1;
        break;
     }
     i++;
   }


  /* imprime sequencia no console 
  i = 0;
  printf("\n");
  for(j=ini;j<=intervalo;j=j+precisao){
    printf("%f\t%f\n", j, ar[i]);
    i++;
  }*/


  /* grava sequencia em arquivo temporario para o gnuplot */
  i = 0;
  if (converge == 1) {
    for(j=ini;j<intervalo+ini;j=j+precisao){
      /*printf("%f\n",j);*/
      fprintf(dat, "%f\t%f\t%f\n", j, ar[i], 0.0);
      i++;
    }
  }
  else {
    for(j=ini;j<intervalo+ini;j=j+precisao){
      fprintf(dat, "%f\t%f\n", j, ar[i]);
      i++;
    }
  }


  /* criar o comando para o gnuplot*/
  int trange_a = -100;
  int trange_b = 100;
  int xrange_a = -1;
  int xrange_b = 100;
  int yrange_a = -1; /* ajuste manualmente */
  int yrange_b = 6; /* ajuste manualmente */
  int fa_epslilon;

  float fa_epsilon = fa + epsilon;


  char command[2048];
  sprintf(command, "set parametric;\
	    	    set trange[%d:%d]; \
		    set xrange[%d:%d]; \
                    set yrange[%d:%d]; \
		    fa = %f; \
		    fb = %f; \
                    fa_epsilon = %f; \
                    plot fa,t, \
                         fb,t, \
                         fa_epsilon,t, \
		         'seq_b.dat' using 1:2 with lines title 'f(x) = 1 / x', \
                         'seq_b.dat' using 1:3 with lines title 'convergencia'", trange_a, trange_b, xrange_a, xrange_b, yrange_a, yrange_b, fa, fb, fa_epsilon);
  /*printf(command);*/
 
  /* plota grafico da sequencia */
  if (converge == 1) plotGraphic(command);
  else printf("\nNao ha pontos validos");


  return 0;

}

void plotGraphic(char gnucommand[]){
    char syscommand[2048];
    sprintf(syscommand, "echo \"%s\" | gnuplot -persist", gnucommand);
    system(syscommand);
}


int factorial(int x) {
    int fac = 1;
    int i;
    for (i=2; i<=x; i++) fac *= i;
    return fac;
}
