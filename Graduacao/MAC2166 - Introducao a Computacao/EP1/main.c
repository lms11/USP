/***************************************************************/
/**                                                           **/
/**   Lucas Moreira Santos                          9345064   **/
/**   Exercício-Programa 01                                   **/
/**   Professor:  Fernando Mário de Oliveira Filho            **/
/**   Turma: 05                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

int main() {
    int number, a, power = 1;
    printf("MAC2166 - EP1 - Usando Inteiros para Representar Reais\n\nDigite os algarismos do numero..................: ");
    scanf("%d", &number);
    printf("Digite a posicao do separador das casas decimais: ");
    scanf("%d", &a);
    for (; a > 0; a--) power *= 10;
    a = number / power;
    printf("O número corresponde na notação decimal é ......: %d,", a);
    while (power /= 10) {
        printf("%d", (number / power) - (a * 10));
        a = number / power;
    }
    printf("\n");
    return 0;
}