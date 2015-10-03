/***************************************************************/
/**                                                           **/
/**   Lucas Moreira Santos                          9345064   **/
/**   Exercício-Programa 01                                   **/
/**   Professor:  Fernando Mário de Oliveira Filho            **/
/**   MAC0122 - Princípios de Desenvolvimento de Algoritmos   **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include "graphics.h"
#include "tree.h"

// TODO editar isso deixando customizavel

#define SPACE_HORIZONTAL		3
#define SPACE_VERTICAL			15

#define RADIUS(thickness)						(0.75 * thickness)
#define SPACE_PER_NODE_X(thickness, scale_x) 	(scale_x * 2 * (thickness + 2 * RADIUS(thickness) + SPACE_HORIZONTAL))
#define SPACE_PER_NODE_Y(scale_y) 				(scale_y * SPACE_VERTICAL)

double nodeWidth(Node *node) {
	return node ? node->width : SPACE_HORIZONTAL;
}

void calculateWidth(Node *node, double scale_x, double thickness) {
	if (!node->left && !node->right) {
		node->width = SPACE_PER_NODE_X(thickness, scale_x);

	} else {
		double width = SPACE_HORIZONTAL;

		if (node->left) {
			calculateWidth(node->left, scale_x, thickness);
			width += node->left->width;
		}

		if (node->right) {
			calculateWidth(node->right, scale_x, thickness);
			width += node->right->width;
		}

		node->width = width;
	}
}

void insertNode(Drawing d, Node *node, double offsetY, double offsetX, double scale_y, double thickness) {
	if (!node) return;

	add_circle(d, offsetX + node->width / 2.0, offsetY, RADIUS(thickness), thickness, 1);
	node->x = offsetX + node->width / 2.0;
	node->y = offsetY;

	if (node->left) {
		insertNode(d, node->left, offsetY + SPACE_PER_NODE_Y(scale_y), offsetX, scale_y, thickness);
		add_line_segment(d, node->x, node->y, node->left->x, node->left->y, thickness);
	}

	if (node->right) {
		insertNode(d, node->right, offsetY + SPACE_PER_NODE_Y(scale_y), offsetX + nodeWidth(node->left), scale_y, thickness);
		add_line_segment(d, node->x, node->y, node->right->x, node->right->y, thickness);
	}
}

void build(Drawing draw, Node *node, double scale_x, double scale_y, double thickness) {
	calculateWidth(node, scale_x, thickness);
	insertNode(draw, node, 0, 0, scale_y, thickness);
}



