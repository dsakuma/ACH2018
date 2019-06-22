#include "cauchy.h"

double epsilon; /* >0 */
double delta = 0.001; /* incremento dos passos sobre a função*/
double a; /* inicio da plotagem*/
double b; /* fim da plotagem */
FILE *dat; /* ponteiro para o arquivo temporario para o gnuplot */

/* cria arquivo temporario para plotagem */
void criar_arq_tmp (){

  if((dat = fopen("serie.dat", "w")) == NULL)
  {
      perror("\nNao foi possivel criar o arquivo temporario");
      exit(1);
  }
}

/* calcula fatorial de x */
double factorial(int x) {
    double fac = 1.0;
    int i;
    for (i=2; i<=x; i++) fac *= i;
    //printf("fatorial de %d = %d\n ", x, fac);
    return fac;
}

/* imprime menu inicial */
void imprime_menu(){
  printf("Análise de uma série pelo Critério de Cauchy\n");
  printf("Escolha uma funcao:\n\n");
  printf("1 - cos(x)\n");
  printf("2 - sen(x)\n");
  printf("3 - log(1+x)\n");
  printf("4 - e^x\n");
  printf("\nEscolha uma opcao (0 para sair): ");
}

/* calcula fn de x de grau n */
double calcula_fn(int n, double x, int opcao){
  int i = 1;
  double fn = 0.0;

  switch(opcao) {
    case 1: /* cos(x) */
      while(i<=n){ fn = fn + ( pow(-1,i-1) / factorial(2*(i-1)) ) * pow(x,2*(i-1)); i++;}
      break;
    case 2: /* sen(x) */
      while(i<=n){ fn = fn + ( pow(-1,i-1) / factorial((2*(i-1)) +1 ) * pow(x,(2*(i-1)) + 1) ); i++;}
      break;
    case 3: /* log(1+x) */
      while(i<=n){
        printf("AAAAAAA %lf e %lf \n", pow(x+1,i), factorial(i));
        fn = fn + ( pow(-1,i-1)*( pow(x+1,i) / factorial(i)) ); i++;}
      break;
    case 4: /* e^x */
      while(i<=n){ fn = fn + (pow(x,i-1)) / (factorial(i-1)); i++;}
      break;
  }
  //printf("fn = %lf\n", fn);
  return fn;
}


void le_parametros(){
  printf("\nEntre com o valor de epsilon: ");
  scanf("%lf", &epsilon);

//  printf("Entre com o valor do passo: ");
//  scanf("%lf", &delta);

  printf("Entre com o valor de a: ");
  scanf("%lf", &a);

  printf("Entre com o valor de b (b>a): ");
  scanf("%lf", &b);

  printf("\n");
}

void grava_serie(int n, int opcao) {
  double x;
  double fn = 0.0;
  double ini, fim;

  /* configura grafico 40% maior na esquerda e 40% maior na direita */
  ini = a - ( 0.4 * fabs(b-a) );
  fim = b + ( 0.4 * fabs(b-a) );

  for(x=ini; x<=fim+delta*0.1 ; x=x+delta){ fprintf(dat, "%lf\t%lf\n", x, calcula_fn(n,x,opcao)); }
  //for(x=ini; x<=fim+delta*0.1 ; x=x+delta){ fprintf(dat, "%lf\t%lf\t%lf\t%lf\n", x, calcula_fn(n,x,opcao), calcula_fn(n-1,x,opcao), calcula_fn(n-2,x,opcao)); }
}

void imprime_instrucoes(int opcao){
  printf("\nSugestão de comando para visualizar a sua serie no gnuplot:\n\n");
  switch(opcao) {
    case 1: /* cos(x) */
      printf("plot 'serie.dat' using 1:2 title 'serie' with lines, cos(x), cos(x)+%lf with dots linecolor rgb 'blue', cos(x)-%lf with dots linecolor rgb 'blue'\n", epsilon, epsilon);
      break;
    case 2: /* sen(x) */
      printf("plot 'serie.dat' using 1:2 title 'serie' with lines, sin(x), sin(x)+%lf with dots linecolor rgb 'blue', sin(x)-%lf with dots linecolor rgb 'blue'\n", epsilon, epsilon);
      break;
    case 3: /* log(1+x) */
      printf("plot 'serie.dat' using 1:2 title 'serie' with lines, log(1+x), log(1+x)+%lf with dots linecolor rgb 'blue', log(1+x)-%lf with dots linecolor rgb 'blue'\n", epsilon, epsilon);
      break;
    case 4: /* e^x */
      printf("plot 'serie.dat' using 1:2 title 'serie' with lines, exp(x), exp(x)+%lf with dots linecolor rgb 'blue', exp(x)-%lf with dots linecolor rgb 'blue'\n", epsilon, epsilon);
      break;
  }
}

void serie(int opcao){
  double x; /* variavel dentro da serie */
  int n = 2; /* grau do polinomio */
  double fn; /* resultado da serie com polinomio de grau n*/
  double fn_ant = 0.0; /* resultado da serie com polinomio de grau n-1*/
  double tmp_x; /* variavel com valor temporario de x */
  double tst; /* variavel que guarda o valor para o criterio de cauchy */
  int cauchy = 1; /* controle do criterio de cauchy */

  criar_arq_tmp();
  le_parametros();

  tst = epsilon+1.0;
  tmp_x = a;
  while (tst >= epsilon && n<=50){ /*looping p aumentar o grau*/
    printf(">>>> Testando polinomio de grau %d\n", n);
    tst = 0.0;
    cauchy = 1;
    x = tmp_x;
    while (cauchy == 1 && x<=b){ /*looping para testar de 'a' ateh 'b'*/
      fn = calcula_fn(n,x,opcao);
      fn_ant = calcula_fn(n-1,x,opcao); /* otimizar este calculo... */
      tst = fabs(fn - fn_ant);
      if (tst >= epsilon) {
        cauchy = 0;
        printf("Teste do Criterio de Cauchy falhou no ponto x = %lf\n", x);
      }
      tmp_x = x;
      x=x+delta;
      fn_ant = fn;
    }
    n++;
  }

  if(cauchy==1){
    printf("\nFoi ncontrada serie com polinomio de grau %d com precisão epsilon!!\n", n-1);
    //printf("grau %d\n", n-1);
    grava_serie(n-1,opcao);
    imprime_instrucoes(opcao);
  }
  else printf("\nFoi testado um polinomio de grau 50 e nao foi encontrado a serie com uma precisão epsilon\n");
}
