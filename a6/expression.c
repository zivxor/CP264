#include "common.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Convert infix expression string to postfix expression reprsented by queue
 * data structure.
 * @param infixstr - string of infix expression.
 * @return - postfix expression in queue of QUEUE type.
 */
QUEUE infix_to_postfix(char *infixstr) {
  QUEUE que = {0, NULL, NULL};
  STACK st = {0, NULL};
  int num = 0, sign = 1;
  int in_number = 0; // track if we are building a number
  char *p = infixstr;

  while (*p) {
    if (*p == '-' && (p == infixstr || *(p - 1) == '(')) {
      sign = -1;
    } else if (mytype(*p) == 0) {
      // digit
      in_number = 1;
      num = num * 10 + (*p - '0');
    } else {
      // non-digit: if we were building a number, enqueue it now
      if (in_number) {
        enqueue(&que, new_node(num * sign, 0)); // type 0 = operand
        num = 0;
        sign = 1;
        in_number = 0;
      }

      if (mytype(*p) == 1) {
        // operator: pop higher/equal precedence operators from stack
        while (st.top && mytype(st.top->data) == 1 &&
               priority(st.top->data) >= priority(*p)) {
          enqueue(&que, pop(&st));
        }
        push(&st, new_node(*p, 1)); // type 1 = operator

      } else if (mytype(*p) == 2) {
        // '('
        push(&st, new_node(*p, 2)); // type 2 = left paren

      } else if (mytype(*p) == 3) {
        // ')': pop until '('
        while (st.top && st.top->data != '(') {
          enqueue(&que, pop(&st));
        }
        if (st.top && st.top->data == '(') {
          free(pop(&st)); // discard '('
        }
      }
    }
    p++;
  }

  // If the expression ended while building a number
  if (in_number) {
    enqueue(&que, new_node(num * sign, 0));
  }

  // Pop remaining operators
  while (st.top) {
    enqueue(&que, pop(&st));
  }

  return que;
}

/*
 * Evaluate and return the value postfix expression passed by queue.
 * @parame queue - postfix expression in queue of QUEUE type.
 ^ @return - value of postfix expression
*/
int evaluate_postfix(QUEUE queue) {
  NODE *curr = queue.front;
  STACK st = {0, NULL};
  int type = 0;

  while (curr) {
    type = curr->type;
    if (type == 0) {
      // operand
      push(&st, new_node(curr->data, 0));
    } else if (type == 1) {
      // operator
      NODE *nb = pop(&st);
      NODE *na = pop(&st);
      if (!na || !nb) {
        // malformed postfix; avoid segfault
        return 0;
      }
      int b = nb->data;
      int a = na->data;
      free(na);
      free(nb);

      int result = 0;
      switch (curr->data) {
      case '+':
        result = a + b;
        break;
      case '-':
        result = a - b;
        break;
      case '*':
        result = a * b;
        break;
      case '/':
        result = a / b;
        break;
      }

      // result is an operand
      push(&st, new_node(result, 0));
    }
    curr = curr->next;
  }

  NODE *res = pop(&st);
  if (!res)
    return 0;
  int final_result = res->data;
  free(res);
  return final_result;
}

/*
 * Evaluate and return the value of infix expression passed by string
 * infixstr, using infix_to_postfix() and evaluate_postfix() functions.
 * @param infixstr - string of infix expression.
 * @return - value of the infix expression.
 */
int evaluate_infix(char *infixstr) {
  QUEUE que = infix_to_postfix(infixstr);
  int result = evaluate_postfix(que);
  clean_queue(&que);
  return result;
}