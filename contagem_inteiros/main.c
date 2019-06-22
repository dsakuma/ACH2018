#include <stdio.h>
#include <stdlib.h>

int main()
{
    int opcao;
    int opcao_correta = 0;

    printf("===Contagem dos numeros inteiros====\n");
    /* O conjunto dos numeros inteiros eh contavel.
       Um */

    while (!opcao_correta){
        printf("Digite a sua opcao:\n");
        printf("1 - Encontrar o inteiro de uma posicao an\n");
        printf("2 - Encontrar os inteiros de um range\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {opcao_correta = 1; especifico(); }
        else if (opcao == 2) {opcao_correta = 1; range(); }
        else printf("...Opcao invalida...\n\n\n");
    }

    return 0;
}


especifico(){
    printf("Encontrar inteiro da posicao an");
    int n;
    int m;

    //Entrada dos parametros
    printf("Digite o valor de n: ");
    scanf("%d", &n);
    printf("\n");

    //Calculo do inteiro da posicao an
    if (n <= 0) { printf("n nao eh natural");}
    else if (n == 1) { printf("An = 0");}
    else if (n%2 == 0) {
        // n = 2m
        m = n/2;
        printf("An = %d", m);
    }
    else {
        // n = 2m - 1
        // -m
        m = (n - 1) / 2;
        m = m * (-1);
        printf("An = %d", m);
    }

}

range(){
    printf("Encontrar os inteiros de um range");
    int ini;
    int end;
    int n;
    int m;

    printf("Digite o valor An inicial: ");
    scanf("%d", &ini);
    printf("Digite o valor An final: ");
    scanf("%d", &end);

    n = ini;

    while (n < end){

        if (n <= 0) { printf("n nao eh natural");}
        else if (n == 1) { printf("A1 = 0\n");}
        else if (n%2 == 0) {
            // n = 2m
            m = n/2;
            printf("A%d = %d\n", n, m);
        }
        else {
            // n = 2m - 1
            // -m
            m = (n - 1) / 2;
            m = m * (-1);
            printf("A%d = %d\n", n, m);
        }
        n = n +1;
    }


}

