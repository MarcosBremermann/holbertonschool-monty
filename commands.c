

#include "monty.h"



/**
 * pushFunction - pushes a value on a stack
 * @stack: the stack
 * @line_number: the number to push
 */
void pushFunction(stack_t **stack, unsigned int line_number)
{
    stack_t *new = malloc(sizeof(stack_t));

    if (!new)
        exit(1);

    if (line_number == 0)
    {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    char num_str[12]; //Asumiendo que es un int de 32-bit, que se interpreta en 12 characters creo (?)

    sprintf(num_str, "%u", line_number); // Convertir el unsigned int a str

    new->n = atoi(num_str);
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

    return;
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
	return;
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

	return;
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
	return;
}
