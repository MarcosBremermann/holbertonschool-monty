
#include "monty.h"

/**
 * main - monty interpreter
 */
int main()
{
	char *line = NULL;
	unsigned long int i;
	stack_t **stack = malloc(sizeof(stack_t *));
	void (*temp)(stack_t **stack, unsigned int line_number);

	if (!stack)
		exit(1);

	*stack = NULL;

	while (1)
	{
		if (getline(&line, &i, stdin) == -1)
			exit(1);
		
		strtok(line, " ");
		temp = getFunction(line);
		temp(stack, atoi(strtok(NULL, " ")));
	}
}



void (*getFunction(char *opcode))(stack_t **stack, unsigned int line_number)
{
	instruction_t opcodeList[] = {
	{"push", pushFunction},
	{"pall", pallFunction},
	{"nop", nopFunction},
	{NULL, NULL}
	};
	int i = 0;


	while (opcodeList[i].opcode != NULL)
	{
		if (strcmp(opcodeList[i].opcode, opcode) == 0)
			return (opcodeList[i].f);
		i++;
	}
	return (nopFunction);
}
