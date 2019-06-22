#include "riemann.h"

double epsilon; /* precisao */
double precisao = 0.0001; /* incremento */
double a; /* inicio da plotagem*/
double b; /* fim da plotagem */

double factorial(int x) {
  double fac = 1.0;
  int i;
  for (i=2; i<=x; i++) fac *= i;
  return fac;
}

void imprime_menu(){
  printf("Integral de Riemann\n");
  printf("Escolha uma funcao:\n\n");
  printf("1 - cos(x)\n");
  printf("2 - sen(x)\n");
  printf("3 - e^x\n");
  printf("\nEscolha uma opcao (0 para sair): ");
}

void le_parametros(){
  printf("\nEntre com o valor de epsilon: ");
  scanf("%lf", &epsilon);

  printf("Entre com o valor de a: ");
  scanf("%lf", &a);

  printf("Entre com o valor de b (b>a): ");
  scanf("%lf", &b);

  printf("\n");
}

double encontra_max(double ini, double fim, int opcao){
  double max_x;
  double tmp;
  double i = ini;
  double fx = 0;

  while (i<fim){

    tmp = cos(i);
    if ( fabs(tmp) > fabs(fx) ) {

        fx = tmp;
        max_x = i;
    }
    i = i+precisao;
  }
  return max_x;
}

double encontra_min(double ini, double fim, int opcao){
  double x = ini;
  double min_x = x;
  double fx = cos(x);

  while (x<fim){
    if ( fabs(cos(x)) < fabs(fx) ) {
        fx = cos(x);
        min_x = x;
    }
    x = x+precisao;
  }
  return min_x;
}

double calcula_sup(long intervalos, int opcao){
  double result = 0;
  double ini = a;
  double fim;
  double max;
  double tamanho_total = b - a;
  double passo = tamanho_total / intervalos;

  fim = ini+passo;

  while (fim <= b+(passo*0.1)) {
    max = encontra_max(ini, fim, opcao);
    result = result + (passo * cos(max));
    ini = ini + passo;
    fim = fim + passo;
  }

  return result;
}


double calcula_inf(long intervalos, int opcao){
  double result = 0;
  double ini = a;
  double fim;
  double min;
  double tamanho_total = b - a;
  double passo = tamanho_total / intervalos;

  fim = ini+passo;

  while (fim <= b+(passo*0.1)) {
    min = encontra_min(ini, fim, opcao);
    result = result + (passo * cos(min));
    ini = ini + passo;
    fim = fim + passo;
  }

  return result;
}

int testa_cauchy(long intervalos, int opcao){
  printf("Testando com %ld intervalos\n", intervalos);
  double sup, inf;
  int cauchy = 0;

  sup = calcula_sup(intervalos, opcao);
  inf = calcula_inf(intervalos, opcao);

  if (fabs(fabs(sup)-fabs(inf)) < epsilon) {
    cauchy = 1;
    printf("\nUtilizando %d intervalos:\n", intervalos);
    printf("Ainf = %lf e Asup = %lf\n", inf, sup);
  }
  return cauchy;
}

long calcula_intervalos(int opcao){
  //printf("Calculando intevalos\n");
  int encontrou = 0;
  long intervalos = 10;

  printf("Testando Criterio de Cauchy...\n", intervalos);
  while (encontrou == 0){
    encontrou = testa_cauchy(intervalos, opcao);
    intervalos++;
  }
  return intervalos - 1;
}

void riemann(int opcao){
  long n;
  le_parametros();
  n = calcula_intervalos(opcao);
  //calcula_integral();
  //grava_plot(n);
  //printf("intervalos = %ld\n", n);
}


/*void teste(){
  a = -2;
  b = -1;
  epsilon = 0.001;
  int opcao = 1;
  long tst = calcula_intervalos(opcao);

  printf("intervalos = %ld", tst);
}*/

/*void teste(){
  a = -2;
  b = -1;
  epsilon = 0.001;
  int opcao = 1;
  double tst = calcula_inf(20,opcao);

  printf("area = %lf", tst);
}*/

/*void teste(){
  a = -1.5;
  b = -1;
  epsilon = 0.01;
  int opcao = 1;
  double tst = encontra_min(-2, -1, 1);

  printf("%lf", tst);
}*/
