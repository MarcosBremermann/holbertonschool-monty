

#include "monty.h"



/**
 * pushFunction - pushes a value on a stack
 * @stack: the stack
 * @line_number: the number to push
 */
void pushFunction(stack_t **stack, unsigned int line_number)
{
	stack_t *new = malloc(sizeof(stack_t));
	char *number;
	int i;

	if (!new)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	number = strtok(NULL, " \n");
	/*
	 * hay que checkear si el strok no dio null,
	 * y si el numero es 0, que sea un '0' y no un error
	 */
	if (!number)
	{
		fprintf(stderr, "L%i: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	for (i = 0; number[i]; i++)
	{
		if (number[i] < '0' || number[i] > '9')
		{
			fprintf(stderr, "L%i: usage: push integer\n",
					line_number);
			exit(EXIT_FAILURE);
		}
	}
	new->n = atoi(number);
	new->prev = NULL;
	if (*stack)
	{
		new->next = *stack;
		(*stack)->prev = new;
	}
	else
	{
		new->next = NULL;
	}
	*stack = new;
}


/**
 * pallFunction2 - recursion
 * @stack: the stack to print
 */
void pallFunction2(stack_t *stack)
{
	if (stack == NULL)
		return;
	printf("%i\n", (*stack).n);
	pallFunction2(stack->next);
}


/**
 * pallFunction - prints a stack
 * @stack: the stack
 * @line_number: dummy
 */
void pallFunction(stack_t **stack, unsigned int line_number)
{
	(void)line_number;

	pallFunction2(*stack);
}


/**
 * nopFunction - nothing
 * @stack: dummy
 * @line_number: dummy
 */
void nopFunction(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}


/**
 * pintFunction - prints the value at the top of the stack
 * @stack: the stack
 * @line_number: the line number
 */
void pintFunction(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", (*stack)->n);
}


/**
 * popFunction - removes the top element of the stack
 * @stack: the stack
 * @line_number: the line number
 */
void popFunction(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }

    stack_t *temp = *stack;
    *stack = (*stack)->next;

    if (*stack != NULL)
        (*stack)->prev = NULL;

    free(temp);
}


/**
 * swapFunction - swaps the top two elements of the stack
 * @stack: the stack
 * @line_number: the line number
 */
void swapFunction(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    stack_t *first = *stack;
    stack_t *second = first->next;

    first->next = second->next;
    if (second->next != NULL)
        second->next->prev = first;

    second->prev = NULL;
    second->next = first;

    first->prev = second;

    *stack = second;
}
