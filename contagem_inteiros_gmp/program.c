/* Contagem dos numeros inteiros
Autor: Daniel Sakuma

Teorema: O conjunto dos numeros inteiros eh contavel. 

Exemplo: 

pos  num 
1     0
2     1
3    -1
4     2
5    -2
*/


#include <stdio.h>
#include <gmp.h>

int find_integer(){
    mpz_t n;
    mpz_t m;
    mpz_t aux;
    mpz_init(n);
    mpz_init(m);
    mpz_init(aux);

    //Entrada dos parametros
    printf("\nDigite o valor da posicao que deseja encontrar: ");
    gmp_scanf("%Zd", n);
    printf("\n");

    if (mpz_cmp_ui(n, 0) < 0) { printf("O numero n nao eh > 0\n"); }
    else if (mpz_cmp_ui(n, 1) == 0) { printf("An = 0\n"); }
    else if (mpz_divisible_ui_p(n, 2) != 0) 
      {
         mpz_cdiv_q_ui(m, n, 2);
	 gmp_printf("Valor do inteiro: %Zd\n", m);
      }
    else 
      {
         mpz_sub_ui(aux, n, 1);
         mpz_cdiv_q_ui(m, aux, 2);
         mpz_mul_si(m, m, -1);
         gmp_printf("Valor do inteiro: %Zd\n", m);
      }
}

int main(void)
{
    int op;
    int op_ok = 0;

    printf("===Contagem dos numeros inteiros====\n");

    while (!op_ok)
      {
        printf("Digite a sua opcao:\n");
        printf("1 - Encontrar o inteiro de uma posicao an\n");
        printf("2 - Encontrar os inteiros de um range\n");
        printf("Opcao: ");
        scanf("%d", &op  );

        if (op == 1) {op_ok = 1; find_integer(); }
        //else if (op == 2) {op_ok = 1; range(); }
        else printf("...Opcao invalida...\n\n\n");
      }
    return 0;
}
