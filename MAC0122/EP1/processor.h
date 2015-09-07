/***************************************************************/
/**                                                           **/
/**   Luca Tornato Serafini                         9345064   **/
/**   Lucas Moreira Santos                          9345064   **/
/**   Exercício-Programa 01                                   **/
/**   Professor:  Fernando Mário de Oliveira Filho            **/
/**   MAC0122 - Princípios de Desenvolvimento de Algoritmos   **/
/**                                                           **/
/***************************************************************/

#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "stack.h"
#include "graphics.h"


/*
  Possible results
*/
typedef enum PROCESSOR_RESULT {
  PROCESSOR_SUCCESS = 400,
  PROCESSOR_ERROR_UNKNOWN,
  PROCESSOR_ERROR_ILEGAL_OP,
  PROCESSOR_ERROR_SUM,              /* Notice that starting here, the order must be the same as in OPS_AVAILABLE */
  PROCESSOR_ERROR_SUBTRACTION,
  PROCESSOR_ERROR_MULTIPLICATION,
  PROCESSOR_ERROR_DIVISION,
  PROCESSOR_ERROR_PI,
  PROCESSOR_ERROR_SIN,
  PROCESSOR_ERROR_COS,
  PROCESSOR_ERROR_DEG,
  PROCESSOR_ERROR_CM,
  PROCESSOR_ERROR_MM,
  PROCESSOR_ERROR_PT,
  PROCESSOR_ERROR_COPY,
  PROCESSOR_ERROR_TRANSLATE,
  PROCESSOR_ERROR_MTRANSLATE,
  PROCESSOR_ERROR_ROTATE,
  PROCESSOR_ERROR_MROTATE,
  PROCESSOR_ERROR_LINE,
  PROCESSOR_ERROR_CIRCLE,
  PROCESSOR_ERROR_FILL_CIRCLE,
  PROCESSOR_ERROR_SHOW,
  PROCESSOR_ERROR_TAN,
  PROCESSOR_ERROR_ARCSIN,
  PROCESSOR_ERROR_ARCCOS,
  PROCESSOR_ERROR_ARCTAN,
  PROCESSOR_ERROR_ERASELINE,
  PROCESSOR_ERROR_E,
  PROCESSOR_ERROR_LG,
  PROCESSOR_ERROR_LN,
  PROCESSOR_ERROR_LOG,
  PROCESSOR_ERROR_ABS
} PROCESSOR_RESULT;


/*
  AVAILABLE OPERATIONS
*/
#define N_OPS_AVAILABLE 30
#define N_OPS_LENGTH    15

static const char OPS_AVAILABLE[N_OPS_AVAILABLE][N_OPS_LENGTH] = {
  "+", "-", "*", "/", "pi", 
  "sin", "cos", "deg", "cm", "mm", 
  "pt", "copy", "translate", "mtranslate", "rotate", 
  "mrotate", "line", "circle", "fillcircle", "show",
  "tan", "arcsin", "arccos", "arctan", "eraseline",
  "e", "lg", "ln", "log", "abs",
};


/*
  Constants
*/
#define CONST_PI      3.14159265358979
#define CONST_PT      0.03527
#define CONST_E       2.71828182845904


/*
  Process input
*/
int processInput(Drawing d, FILE *input);
int processOperator(Drawing d, char *op);


/*
  Throw an error to user's output and return error code
*/
int throw_error(char error[], PROCESSOR_RESULT result);

/*
  Processors
*/
int process_sum(Stack s);
int process_subtraction(Stack s);
int process_multiplication(Stack s);
int process_division(Stack s);
int process_pi(Stack s);
int process_sin(Stack s);
int process_cos(Stack s);
int process_deg(Stack s);
int process_cm(Stack s);
int process_mm(Stack s);
int process_pt(Stack s);
int process_copy(Stack s);
int process_translate_general(Stack s, int n, PROCESSOR_RESULT possibleError);
int process_translate(Stack s);
int process_mtranslate(Stack s);
int process_rotate_general(Stack s, int n, PROCESSOR_RESULT result);
int process_rotate(Stack s);
int process_mrotate(Stack s);
int process_line(Drawing d);
int process_circle_general(Drawing d, int fill, PROCESSOR_RESULT possibleError);
int process_circle(Drawing d);
int process_fillcircle(Drawing d);
int process_show(Stack s);


/*
  Extra processor
*/
int process_tan(Stack s);
int process_arcsin(Stack s);
int process_arccos(Stack s);
int process_arctan(Stack s);
int process_eraseline(Drawing d);
int process_e(Stack s);
int process_lg(Stack s);
int process_ln(Stack s);
int process_log(Stack s); // Let the stack be (top first): a b. Then it will substitute it to log(b) in base a
int process_abs(Stack s);


#endif