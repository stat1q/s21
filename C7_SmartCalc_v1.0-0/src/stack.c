#include "parser.h"

void add_toend(symb_st **head, expr value) {
  symb_st *tmp = malloc(sizeof(symb_st));
  tmp->value = value;
  tmp->next = NULL;
  symb_st *ptr = (*head);
  if (*head == NULL) {
    *head = tmp;
  } else {
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
    ptr->next = tmp;
  }
}

void push(symb_st **head, expr value) {
  symb_st *tmp = malloc(sizeof(symb_st));
  tmp->next = *head;
  tmp->value = value;
  *head = tmp;
}

expr pop(symb_st **head) {
  symb_st *out;
  expr value;
  out = *head;
  *head = (*head)->next;
  value = out->value;
  free(out);
  return value;
}

symb_st *free_stack(symb_st **head) {
  while ((*head) != NULL) {
    symb_st *tmp = *head;
    *head = (*head)->next;
    free(tmp);
  }
  *head = NULL;
  return *head;
}

symb_st *reverse(symb_st *input_stack) {
  symb_st *reversed_stack = NULL;
  while (input_stack != NULL) {
    push(&reversed_stack, pop(&input_stack));
  }
  return reversed_stack;
}
