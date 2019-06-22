#include <stdio.h>
main()
{
    int opcao;
    int opcao_correta = 0;

    printf("=== Teorema 1.1.2 ===\n\n\n");
    /*Se a e b sao numeros reais com a < b, entao existe tanto
    um numero racional quanto um numero irracional entre a e b*/

    while (!opcao_correta){

    printf("Escolha o metodo de calculo:\n\n");
    printf("1 - Deixar o computador definir automaticamente o 'k' e 'n'\n");
    printf("2 - Configurar cada parametro manualmente\n\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) { opcao_correta = 1; automatico(); }
    else if (opcao == 2) { opcao_correta = 1; manual (); }
    else printf("...Opcao invalida...\n\n\n");
    }
    //getch();
}

automatico () //pq eu tenho que usar double para calcular r
{
   float a, b;
   float min_n;
   float r, x;
   int k, n;
   int qtd;
   int total_r, total_x;

   total_r = 0;
   total_x = 0;

   //ENTRADA DOS PARAMETROS
   printf("\n\nEntrada dos parametros: \n\n");

   printf("- Digite o valor de 'a': ");
   scanf("%f", &a);
   printf("\n");
   printf("- Digite o valor de 'b': ");
   scanf("%f", &b);
   printf("\n");
   printf("- Digite quantos numeros deseja encontrar: ");
   scanf("%d", &qtd);
   printf("\n");

   k = a - 1;
   min_n = sqrt(2) / (b - a);


   //BUSCA DOS NUMEROS RACIONAIS ENTRE A E B
   printf("\n\n--------------------------------------------------\n\n");
   printf("Buscando numeros RACIONAIS entre 'a' e 'b'... \n\n");

   n = min_n + 1;
   while (total_r < qtd) {
   r = k + (1.0 / n);
       while (r < b && total_r != qtd) {
           if (r > a) {
               printf("%f\n", r);
               total_r = total_r + 1;
           }
           r = r + (1.0 / n);
       }
    n = n + 1;
   }
   printf("\nForam encnontrados %d numeros RACIONAIS.\n", total_r);

   //BUSCA DOS NUMEROS RACIONAIS ENTRE A E B
   printf("\n--------------------------------------------------\n\n");
   printf("Buscando numeros IRRACIONAIS entre 'a' e 'b'... \n\n");

   n = min_n + 1;
   while (total_x < qtd) {
   x = k + (sqrt(2) / n);
       while (x < b && total_x != qtd) {
           if (x > a) {
               printf("%f\n", x);
               total_x = total_x + 1;
           }
           x = x + (sqrt(2) / n);
       }
    n = n + 1;
   }
   printf("\nForam encnontrados %d numeros IRRACIONAIS.\n", total_r);
   printf("\n--------------------------------------------------\n");
}

manual () //mudar k e n para int
{
   float a, b, k, n;
   float min_n;
   float r, x;
   int total_r, total_x;

   total_r = 0;
   total_x = 0;

   //ENTRADA DOS PARAMETROS
   printf("Entrada dos parametros: \n\n");

   printf("- Digite o valor de 'a': ");
   scanf("%f", &a);
   printf("\n");
   printf("- Digite o valor de 'b': ");
   scanf("%f", &b);
   printf("\n");
   printf("- Digite o valor de 'k' (deve ser um inteiro MENOR que %.1f): ", a);//falta validar
   scanf("%f", &k);
   printf("\n");
   min_n = sqrt(2) / (b - a);
   printf("- Digite o valor de 'n' (deve ser um inteiro MAIOR que %.1f): ", min_n);
   scanf("%f", &n);

   //BUSCA DOS NUMEROS RACIONAIS ENTRE A E B
   printf("\n\n--------------------------------------------------\n\n");
   printf("Buscando numeros RACIONAIS entre 'a' e 'b'... \n\n");
   r = k + (1 / n);
   while (r < b) {
       if (r > a) {
           printf("%f\n", r);
           total_r = total_r + 1;
       }
       r = r + (1 / n);
   }
   printf("\nForam encnontrados %d numeros RACIONAIS.\n", total_r);

   //BUSCA DOS NUMEROS IRRACIONAIS ENTRE A E B
   printf("\n--------------------------------------------------\n\n");
   printf("Buscando numeros IRRACIONAIS entre 'a' e 'b'... \n\n");
   x = k + (sqrt(2) / n);
   //printf("x = %f\n", x);
   //printf("n = %f\n", n);
   while (x < b) {
       if (x > a) {
           printf("%f\n", x);
           total_x = total_x + 1;
       }
       x = x + (sqrt(2) / n);
   }
   printf("\nForam encnontrados %d numeros IRRACIONAIS.\n", total_x);
   printf("\n--------------------------------------------------\n");

}
