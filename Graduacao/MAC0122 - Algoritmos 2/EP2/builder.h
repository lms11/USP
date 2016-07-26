/***************************************************************/
/**                                                           **/
/**   Luca Tornato Serafini                         9373434   **/
/**   Lucas Moreira Santos                          9345064   **/
/**   Mardem Humberto Santos Junior 				9065976   **/
/**   Exercício-Programa 01                                   **/
/**   Professor:  Fernando Mário de Oliveira Filho            **/
/**   MAC0122 - Princípios de Desenvolvimento de Algoritmos   **/
/**                                                           **/
/***************************************************************/

/*
  algorithm.h

  Onde a mágica acontece. Aqui transformamos as etapas dos algoritmos em árvores.
*/

#ifndef __BUILDER_H__
#define __BUILDER_H__

#include "graphics.h"
#include "tree.h"

// Calcula a largura de cada nó recursivamente
void calculateWidth(Node *node, double scale_x, double thickness);

// Recebe a árvore e cria os pontos necessários na imagem (drawing)
void build(Drawing draw, Node *node, double scale_x, double scale_y, double thickness);

// Insere um nó no desenho (recursivamente)
void insertNode(Drawing d, Node *node, double offsetY, double offsetX, double scale_y, double thickness);

#endif