
#include "monty.h"



/**
 * main - monty interpreter
 */
int main(int argc, char **argv)
{
	char *opcode, *line = NULL;
	unsigned int current_line = 1;
	size_t len = 0;
	void (*temp)(stack_t **stack, unsigned int line_number);
	stack_t *stack = NULL;
	FILE *input;

	if (argc != 2)
	{
		printf("USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	input = fopen(argv[1], "r");
	if (!input)
	{
		printf("Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		if (getline(&line, &len, input) == -1)
			break;

		opcode = strtok(line, " \n");

		if (opcode == NULL)
			continue; // Pa ignorar las lineas vacias

		temp = getFunction(opcode);
		if (temp == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n",
					current_line, opcode);
			exit(EXIT_FAILURE);
		}

		temp(&stack, current_line);

		current_line++;
	}

	free(line);  //Liberar lamemoria
	return (EXIT_SUCCESS);
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
	return (NULL);
}
