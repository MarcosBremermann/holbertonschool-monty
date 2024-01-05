

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

	if (!new)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	number = strtok(NULL, " /n");

	/*
	 * hay que checkear si el strok no dio null,
	 * y si el numero es 0, que sea un '0' y no un error
	 */
	if (!number)
	{
		fprintf(stderr, "L%i: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	new->n = atoi(number);
	if (new->n == 0 && (number[0] != '0'))
	{
		fprintf(stderr, "L%i: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

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
