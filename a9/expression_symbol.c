#include "expression_symbol.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *ltrim(char *s) {
  while (*s != '\0' && isspace((unsigned char)*s)) {
    s++;
  }
  return s;
}

static void rtrim(char *s) {
  int n = (int)strlen(s);

  while (n > 0 && isspace((unsigned char)s[n - 1])) {
    s[n - 1] = '\0';
    n--;
  }
}

static void trim_semicolon(char *s) {
  rtrim(s);

  int n = (int)strlen(s);
  if (n > 0 && s[n - 1] == ';') {
    s[n - 1] = '\0';
    rtrim(s);
  }
}

static int is_identifier_char(int c) {
  return isalnum(c) || c == '_';
}

QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr) {
  QUEUE out = {0, NULL, NULL};
  STACK ops = {0, NULL};

  if (infixstr == NULL) {
    return out;
  }

  char *p = infixstr;
  int expect_operand = 1;

  while (*p != '\0') {
    if (isspace((unsigned char)*p) || *p == ';') {
      p++;
      continue;
    }

    if (isdigit((unsigned char)*p)) {
      int value = 0;

      while (isdigit((unsigned char)*p)) {
        value = value * 10 + (*p - '0');
        p++;
      }
      enqueue(&out, new_node(value, 0));
      expect_operand = 0;
      continue;
    }

    if (isalpha((unsigned char)*p) || *p == '_') {
      char key[20];
      int i = 0;

      while (*p != '\0' && is_identifier_char((unsigned char)*p)) {
        if (i < (int)sizeof(key) - 1) {
          key[i++] = *p;
        }
        p++;
      }
      key[i] = '\0';

      int value = 0;
      HNODE *found = hashtable_search(ht, key);
      if (found != NULL) {
        value = found->data.value;
      }

      enqueue(&out, new_node(value, 0));
      expect_operand = 0;
      continue;
    }

    if (*p == '(') {
      push(&ops, new_node(*p, 2));
      expect_operand = 1;
      p++;
      continue;
    }

    if (*p == ')') {
      while (ops.top != NULL && ops.top->data != '(') {
        enqueue(&out, pop(&ops));
      }
      if (ops.top != NULL && ops.top->data == '(') {
        NODE *left = pop(&ops);
        free(left);
      }
      expect_operand = 0;
      p++;
      continue;
    }

    if (mytype(*p) == 1) {
      char op = *p;

      if (op == '-' && expect_operand) {
        enqueue(&out, new_node(0, 0));
      }

      while (ops.top != NULL && mytype((char)ops.top->data) == 1 &&
             priority((char)ops.top->data) >= priority(op)) {
        enqueue(&out, pop(&ops));
      }
      push(&ops, new_node(op, 1));
      expect_operand = 1;
      p++;
      continue;
    }

    p++;
  }

  while (ops.top != NULL) {
    enqueue(&out, pop(&ops));
  }

  return out;
}

int evaluate_postfix(QUEUE queue) {
  STACK st = {0, NULL};
  NODE *cur = queue.front;

  while (cur != NULL) {
    if (cur->type == 0) {
      push(&st, new_node(cur->data, 0));
    } else if (cur->type == 1) {
      NODE *nb = pop(&st);
      NODE *na = pop(&st);

      if (na == NULL || nb == NULL) {
        free(na);
        free(nb);
        clean_stack(&st);
        return 0;
      }

      int a = na->data;
      int b = nb->data;
      free(na);
      free(nb);

      int value = 0;
      switch (cur->data) {
      case '+':
        value = a + b;
        break;
      case '-':
        value = a - b;
        break;
      case '*':
        value = a * b;
        break;
      case '/':
        value = (b == 0) ? 0 : (a / b);
        break;
      case '%':
        value = (b == 0) ? 0 : (a % b);
        break;
      default:
        value = 0;
        break;
      }

      push(&st, new_node(value, 0));
    }
    cur = cur->next;
  }

  NODE *res = pop(&st);
  int out = 0;

  if (res != NULL) {
    out = res->data;
    free(res);
  }

  clean_stack(&st);
  return out;
}

int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr) {
  QUEUE q = infix_to_postfix_symbol(ht, infixstr);
  int value = evaluate_postfix(q);
  clean_queue(&q);
  return value;
}

DATA evaluate_statement(HASHTABLE *ht, char *statement) {
  DATA out;
  out.key[0] = '\0';
  out.value = 0;

  if (statement == NULL || ht == NULL) {
    return out;
  }

  char line[512];
  strncpy(line, statement, sizeof(line) - 1);
  line[sizeof(line) - 1] = '\0';

  trim_semicolon(line);
  char *s = ltrim(line);
  rtrim(s);

  if (*s == '\0') {
    return out;
  }

  char *eq = strchr(s, '=');

  if (eq == NULL) {
    char key[20];
    strncpy(key, s, sizeof(key) - 1);
    key[sizeof(key) - 1] = '\0';
    rtrim(key);

    HNODE *found = hashtable_search(ht, key);
    if (found != NULL) {
      out = found->data;
    }
    return out;
  }

  *eq = '\0';
  char *left = ltrim(s);
  rtrim(left);

  char *right = ltrim(eq + 1);
  rtrim(right);

  if (*left == '\0') {
    return out;
  }

  strncpy(out.key, left, sizeof(out.key) - 1);
  out.key[sizeof(out.key) - 1] = '\0';
  out.value = evaluate_infix_symbol(ht, right);

  hashtable_insert(ht, out);
  return out;
}
