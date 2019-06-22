/* Program: Analisador de series
 *    Autor: Daniel Sakuma
 *    Last modification: May 01 2011*/

#include "cauchy.h"

int main()
{

    int escolha = 1;
    int feito = 0;

    while (feito != 1){

        imprime_menu(); /* imprime menu */
        scanf("%d",&escolha); /* faz a leitura da opcao escolhida*/

        switch(escolha) {
            case 0:
            {
                feito = 1;
                break;
            }
            case 1: case 2: case 3: case 4:
            {
                feito = 1;
                serie(escolha);
                //teste();
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
