#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

/*
simbolos:
c = cos
s = sen
t = tan
p = pow
(
)
*/

typedef struct estr
{
        int var;     /* 0 se nao eh uma variavel, e 1 se for uma variavel*/
        int numerico; /* 0 se eh um operador e 1 se eh um operando*/
        char simbolo; /* caracter correspondente ao simbolo */
        float valor_op; /* valor numerico do operando */
} NO;


/* funcoes a implementar em trabalho.cpp */
float calculate(char *argv[], char *argpos[]);
void plot(float epsilon, int ini, int fim, int precisao, char *argv[], char *argpos[]);
