/*
  graphics.h

  A simple graphics library.
*/

#ifndef __STACK_H__
#define __STACK_H__


// Max size of string
#define STACK_STRING_LENGTH   30

// Stack's item object.
typedef struct stack_struct *Stack;

// Stack object.
typedef struct stack_struct {
  int size;
  double value;
  struct stack_struct *next;
} StackItem;


/*
  Creates an empty stack and returns it.
*/
Stack stack_init();

/*
  Destroys a stack, freeing all memory occupied by it.
*/
void stack_destroy(Stack s);

/*
  Push a string to the stack.

  ARGUMENTS:

  - s -- the stack to which the string will be added.

  - string -- string to be added.

  Returns nonzero on success, zero if it fails to add the item.
*/
int stack_push(Stack s, double value);

/*
  Remove stack's top element and return it
*/
double stack_pop(Stack s);

/*
  Returns stack's size
*/
int stack_size(Stack s);


#endif