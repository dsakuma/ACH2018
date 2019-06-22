/* Program: Sequences Analyser
   Autor: Daniel Sakuma
   Last modification: April 4 2011*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void sequencia();
void somatoria();
void plotGraphic(char gnucommand[]);
int factorial(int x);

int main (){

    int escolha = 1;
    int feito = 0;

    while (feito != 1){

        printf("\n1 -- Analisar uma sequencia ");
        printf("\n2 -- Analisar a somatoria de uma sequencia de funcoes ");
        printf("\n\nEscolha uma opcao (0 para sair): ");
        scanf("%d",&escolha);

        switch(escolha) {
            case 0:
            {
                feito = 1;
                break;
            }
            case 1:
            {
                feito = 1;
                sequencia();
                break;
            }
            case 2:
            {
                feito = 1;
                somatoria();
                break;
            }
            default:
            {
                printf("\nEscolha invalida\n");
                continue;
            }

        }

    }

    return 0;

}

void sequencia(){

  float epsilon;
  int n, N;

  printf("\nEntre com o valor de epsilon: ");
  scanf("%f", &epsilon);

  printf("Entre com o valor de n: ");
  scanf("%d", &n);

  printf("Entre com o valor de N com n<N: ");
  scanf("%d", &N);


  float *ar; /* arranjo com o resultado da funcao*/
  ar = malloc(N * sizeof(float));
  int i;
  FILE *dat;
  int plotable = 0;

  /* cria arquivo para plot */
  if((dat = fopen("/tmp/sequences.dat", "w")) == NULL)
  {
      perror("\nNao foi possivel criar o arquivo temporario");
      exit(1);
  }

  /* preenche array de resultados */
  for(i=n;i<N;i++){
    ar[i] = 3. + (1. / i);
  }


  /* imprime valor no console */
  for(i=n;i<N;i++){
    if( fabs(ar[i] - ar[i+1]) < epsilon) {
        printf("ar[%d] = %f\tar[%d] = %f\tdistancia = %f\n", i,  ar[i], i+1, ar[i+1], fabs(ar[i] - ar[i+1]));
        plotable = 1;
        break;
    }
  }

  /* grava sequencia em arquivo temporario para o gnuplot */
  for(i=n;i<N;i++){
    if( fabs(ar[i] - ar[i+1]) < epsilon)
        fprintf(dat, "%d\t%f\t%f\t%f\n", i, ar[i], fabs(ar[i] - ar[i+1]), ar[i] );
    else{
        fprintf(dat, "%d\t%f\t%f\n", i, ar[i], fabs(ar[i] - ar[i+1]) );
    }
  }

  fclose(dat);

  /* plota grafico da sequencia */
  if (plotable == 1){
    plotGraphic("plot '/tmp/sequences.dat' using 1:2 title 'Sequencia', '/tmp/sequences.dat' using 1:4 title 'Menor que epsilon'");}
  else{
    printf("\nNao ha pontos validos\n");}

}


void somatoria(){

  float epsilon;
  int n, N;
  float x;

  printf("\nEntre com o valor de epsilon: ");
  scanf("%f", &epsilon);

  printf("Entre com o valor de n: ");
  scanf("%d", &n);

  printf("Entre com o valor de N com n<N: ");
  scanf("%d", &N);

  printf("Entre com o valor de x: ");
  scanf("%f", &x);


  float *ar; /* arranjo com o resultado da funcao*/
  ar = malloc(N * sizeof(float));
  int i;
  FILE *dat;
  int plotable = 0;

  /* cria arquivo para plot */
  if((dat = fopen("/tmp/sequences.dat", "w")) == NULL)
  {
      perror("\nNao foi possivel criar o arquivo temporario");
      exit(1);
  }

  /* preenche array de resultados */
  ar[0]=0.0;
  for(i=n;i<N;i++){
    ar[i] = ar[i-1] + ( (pow(x,i-1)) / factorial(i-1) );
  }

  /* imprime valor no console */
  for(i=n;i<N;i++){
    if( fabs(ar[i] - ar[i+1]) < epsilon) {
        printf("ar[%d] = %f\tar[%d] = %f\tdistancia = %f\n",i , ar[i], i+1, ar[i+1], fabs(ar[i] - ar[i+1]));
        plotable = 1;
        break;
    }
  }

  /* grava sequencia em arquivo temporario para o gnuplot */
  for(i=n;i<N;i++){
    printf("%d\t%f\t%f\t%f\n", i, ar[i], fabs(ar[i] - ar[i+1]), ar[i]);
    if( fabs(ar[i] - ar[i+1]) < epsilon)
        fprintf(dat, "%d\t%f\t%f\t%f\n", i, ar[i], fabs(ar[i] - ar[i+1]), ar[i] );
    else{
        fprintf(dat, "%d\t%f\t%f\n", i, ar[i], fabs(ar[i] - ar[i+1]) );
    }
  }

  fclose(dat);

  /* plota grafico da sequencia */
  if (plotable == 1){
    plotGraphic("plot '/tmp/sequences.dat' using 1:2 title 'Sequencia', '/tmp/sequences.dat' using 1:4 title 'Menor que epsilon'");}
  else{
    printf("\nNao ha pontos validos\n");}

}



void plotGraphic(char gnucommand[]){
    char syscommand[1024];
    sprintf(syscommand, "echo \"%s\" | gnuplot -persist", gnucommand);
    system(syscommand);
}


int factorial(int x) {
    int fac = 1;
    int i;
    for (i=2; i<=x; i++) fac *= i;
    return fac;
}
