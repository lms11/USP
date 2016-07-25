/***************************************************************/
/**                                                           **/
/**   Lucas Moreira Santos                          9345064   **/
/**   Exercício-Programa 02                                   **/
/**   Professor:  Fernando Mário de Oliveira Filho            **/
/**   Turma: 05                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

/**
 Recebe number, retorna número de digitos
 **/
int no_digits(int number) {
    int n = 0, b = number;
    while (b != 0) { b /= 10; n++; }
    return n;
}

/**
 Recebe a e b, retorna a^b
 **/
int power(int a, int b) {
    int i, power = 1;
    for(i = 0; i < b; i++) power *= a;
    return power;
}

/**
 Recebe o valor e retorna o seu absoluto
 **/
int abs(int valor) {
    return (valor < 0 ? (-valor) : valor);
}

/**
 Recebe number, digit e retorna o digito na casa "digit" de "number"
 Exemplo: number = 7594
 4 = digit 0, 9 = digit 1, 5 = digit 2, 7 = digit 3
 **/
int no_at_digit(int number, int digit) {
    return abs((number / power(10, digit)) % 10);
}

/**
 Recebe o numero da forma [mantissa][sinal][expoente] e retorna [X] (X pode ser mantissa ou expoente, com sinal adequado)
 **/
int get_mantissa(int valor) {
    return (valor / 1000);
}

int get_sinal_expoente(int valor) {
    return (abs(valor % 1000) / 100);
}

int get_expoente(int valor) {
    int novo_valor = abs(valor % 100);
    /* Checa se o expoente é negativo. Se for, coloca ele como negativo. */
    if (get_sinal_expoente(valor) == 1 || get_sinal_expoente(valor) == 5) novo_valor *= -1;
    return novo_valor;
}


/**
 Recebe um valor e verifica se ele tem erro (0 não tem erro, 1 houve OVERFLOW, 2 houve UNDERFLOW)
 **/
int validate_error(int mantissa) {
    int sinal_expoente = abs(get_sinal_expoente(mantissa));
    if (sinal_expoente == 4) {
        printf("*** AVISO: ocorreu um overflow no expoente. ***\n");
        return 1;
        
    } else if (sinal_expoente == 5) {
        printf("*** AVISO: ocorreu um underflow no expoente. ***\n");
        return 2;
    }
    
    return 0;
}


/**
 Recebe a mantissa 1, mantissa 2, expoente 1, expoente 2
 Devolve a soma
**/
int soma(int mantissa_1, int expoente_1, int mantissa_2, int expoente_2, int operacao) {
    int sinal_operacao, mantissa_tmp = 0, expoente_tmp = 0, did_swap = 0;
    
    /*
     ===== ===== =====
     (I) Caso o expoente de 2 seja maior que o de 1,
     Inverte-se os valores de modo a mandar EXPOENTE 1 > EXPOENTE 2
     ===== ===== =====
     */
    
    if (expoente_1 < expoente_2) {
        expoente_tmp = expoente_2;
        mantissa_tmp = mantissa_2;
        
        expoente_2 = expoente_1;
        mantissa_2 = mantissa_1;
        
        expoente_1 = expoente_tmp;
        mantissa_1 = mantissa_tmp;
        
        did_swap = 1;
    }
    
    /*
     ===== ===== =====
     Diminui o maior expoente até: (a) chegar ao menor, (b) a mantissa tiver 6 algarismos/digitos
     ===== ===== =====
     */
    
    while (no_digits(mantissa_1) < 6 && expoente_1 > expoente_2) {
        mantissa_1 *= 10;
        expoente_1--;
    }
    
    
    /*
     ===== ===== =====
     Se a mantissa chegar a 6 dígitos antes do expoente ficar igual ao do menor, então será preciso cortar dígitos da mantissa do número de menor expoente, incrementando o seu expoente até que ele fique igual ao valor atual do maior expoente (e isso pode transformar a mantissa do número em zero se ele for muito pequeno em comparação ao outro número)
     ===== ===== =====
     */
    
    if (no_digits(mantissa_1) == 6 && expoente_1 > expoente_2) {
        while (expoente_1 > expoente_2) {
            mantissa_2 /= 10;
            expoente_2++;
        }
    }
    
    
    /*
     ===== ===== =====
     Realiza a soma/subtração normalmente
     ===== ===== =====
     */
    
    sinal_operacao = operacao == 1 ? 1 : (-1);
    mantissa_1 += sinal_operacao * mantissa_2;
    
    while ((mantissa_1 != 0 && mantissa_1 % 10 == 0) || no_digits(mantissa_1) > 6) {
        mantissa_1 /= 10;
        expoente_1++;
    }

    
    /*
     ===== ===== =====
     Retorna o resultado
     Se o 3 digito (direita -> esquerda) for 4, então houve overflow. Se for 5, então houve underflow
     ===== ===== =====
     */
    
    if (expoente_1 > 99) {
        mantissa_1 = 999999499 * (mantissa_1 < 0 ? -1 : 1);
        
    } else if (expoente_1 < -99) {
        mantissa_1 = 999999599 * (mantissa_1 < 0 ? -1 : 1);
    
    } else {
        sinal_operacao = (mantissa_1 < 0) ? -1 : 1;
        mantissa_1 *= 1000;
        if (expoente_1 < 0)
            mantissa_1 += 100 * sinal_operacao;
        mantissa_1 += abs(expoente_1) * sinal_operacao;
        
    }
    
    
    /*
     ===== ===== =====
     Como trocamos A <=> B para satisfazer a condição (I),
     então a subtração está trocada (está calculando A - B, ao invés de B - A).
     Logo, multiplica-se o valor por -1 ((A - B) * -1 = B - A)
     ===== ===== =====
     */
    
    if (operacao == 2 && did_swap == 1)
        mantissa_1 *= -1;
    
    return mantissa_1;
}


/**
 Recebe o número da forma [mantissa][sinal do expoente][expoente] e normaliza ele (deixa da forma mais simplificada possivel)
 **/
int normaliza(int valor) {
    int mantissa = get_mantissa(valor), expoente = get_expoente(valor);
    
    while ((mantissa != 0 && mantissa % 10 == 0) || no_digits(mantissa) > 6) {
        mantissa /= 10;
        expoente++;
    }
    
    return soma(mantissa, expoente, 0, 0, 1); /* usa-se a função soma para compor o número na forma [mantissa][sinal do expoente][expoente] */
}


/**
 Função main
 **/
int main() {
    int operacao = 5, index, sum, error = 0, mantissa_alt = 0, expoente_alt = 0, mantissa_1 = 0, expoente_1 = 0, mantissa_2 = 0, expoente_2 = 0;
    
    printf("MAC2166 - EP2 - Calculadora para Numeros de Ponto Flutuante\n\n");
    
    while (operacao != 6) {
        if (operacao == 5) {
            /* OPERAÇÃO: RESETAR */
            
            printf("Operando 1...................: ");
            scanf("%d", &mantissa_1);
            printf("\n");
            
            mantissa_1 = normaliza(mantissa_1);
            expoente_1 = get_expoente(mantissa_1);
            mantissa_1 = get_mantissa(mantissa_1);
            
            
            
            
        } else if (operacao < 5) {
            printf("Operando 2...................: ");
            scanf("%d", &mantissa_2);
            printf("\n");
            
            mantissa_2 = normaliza(mantissa_2);
            expoente_2 = get_expoente(mantissa_2);
            mantissa_2 = get_mantissa(mantissa_2);
            
            
            if (operacao == 1 || operacao == 2) {
                /* OPERAÇÃO: SOMAR / SUBTRAÇÃO */
                
                mantissa_1 = soma(mantissa_1, expoente_1, mantissa_2, expoente_2, operacao);
                
                error = validate_error(mantissa_1);
                if (error == 1)
                    mantissa_1 = (999999099 + ((get_expoente(mantissa_1) - 4) == 1 ? 100 : 0)) * (mantissa_1 < 0 ? -1 : 1);
                else if (error == 2) mantissa_1 = 0;
                
                
            } else if (operacao == 3) {
                /* OPERAÇÃO: MULTIPLICAÇÃO */
                
                /*
                 ===== ===== =====
                 Caso o expoente de 2 seja maior que o de 1, inverte-se os valores de modo a mandar EXPOENTE 1 > EXPOENTE 2
                 ===== ===== =====
                 */
                
                if (expoente_1 < expoente_2) {
                    expoente_alt = expoente_2;
                    mantissa_alt = mantissa_2;
                    
                    expoente_2 = expoente_1;
                    mantissa_2 = mantissa_1;
                    
                    expoente_1 = expoente_alt;
                    mantissa_1 = mantissa_alt;
                }
                
                for (index = 0, sum = 0; index < no_digits(mantissa_2); index++) {
                    expoente_alt = expoente_1 + (expoente_2 + index);
                    mantissa_alt = abs(mantissa_1) * no_at_digit(mantissa_2, index);
                    
                    while ((mantissa_alt != 0 && mantissa_alt % 10 == 0) || no_digits(mantissa_alt) > 6) {
                        mantissa_alt /= 10;
                        expoente_alt++;
                    }
                    
                    sum = soma(get_mantissa(sum), get_expoente(sum), mantissa_alt, expoente_alt, 1);
                    
                    error = validate_error(sum);
                    if (error == 1) {
                        sum += 400 * (sum < 0 ? 1 : -1); /* Quando tem erro de overflow/underflow, a 3a casa fica 4 ou 5 (dependendo do sinal da mantissa), então subtraimos 4 */
                        break;
                    } else if (error == 2) {
                        sum = 0;
                        break;
                    }
                }
                
                /* Regra de sinal: (++ ou -- => +), (+- ou -+ => -) */
                if ((mantissa_1 < 0 && mantissa_2 > 0) || (mantissa_1 > 0 && mantissa_2 < 0))
                    sum *= -1;
                
                mantissa_1 = sum;
                
                
            } else if (operacao == 4) {
                /* OPERAÇÃO: DIVISÃO (_alt => resto) */
                
                expoente_alt = expoente_1;
                mantissa_alt = mantissa_1;
                
                if (mantissa_2 == 0) {
                    printf("*** ERRO: nao é possivel dividir por zero. ***\n\n");
                    /* Mantissa 1 estava decomposto. Recompõe para printar no final (depois de printado, será decomposto novamente) */
                    mantissa_1 = soma(0, 0, mantissa_1, expoente_1, 1);
                    
                    error = 7;
                    
                } else {
                    sum = 0;
                    
                    while (mantissa_alt != 0 && no_digits(get_mantissa(sum)) != 6) {
                        sum = soma(get_mantissa(sum), get_expoente(sum), mantissa_alt / mantissa_2, expoente_alt - expoente_2, 1);
                        mantissa_alt = (mantissa_alt % mantissa_2) * 10;
                        expoente_alt--;
                        
                        error = validate_error(sum);
                        if (error == 1) {
                            sum += 400 * (sum < 0 ? 1 : -1);
                            break;
                        } else if (error == 2) {
                            sum = 0;
                            break;
                        }
                    }
                    
                    expoente_alt = get_expoente(sum);
                    mantissa_alt = get_mantissa(sum);
                    
                    while ((mantissa_alt != 0 && mantissa_alt % 10 == 0) || no_digits(mantissa_alt) > 6) {
                        mantissa_alt /= 10;
                        expoente_alt++;
                    }
                    
                    mantissa_1 = soma(0, 0, mantissa_alt, expoente_alt, 1);
                }
                
            }
            
            if (error != 7) printf("Resultado (e novo operando 1): %d\n\n", mantissa_1);
            error = 0;
            expoente_1 = get_expoente(mantissa_1);
            mantissa_1 = get_mantissa(mantissa_1);
        }
        
        printf("Operacoes disponiveis: 1 (+), 2 (-), 3 (*), 4 (/), 5 (limpar), 6 (parar)\nNumero da operacao desejada..: ");
        scanf("%d", &operacao);
        printf("\n");
    }
    
    printf("Tchau!\n");
    return 0;
}
