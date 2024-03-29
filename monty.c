
#include "monty.h"



/**
 * main - monty interpreter
 * @argc: argument count
 * @argv: argument list
 *
 * Return: success
 */
int main(int argc, char **argv)
{
	char *opcode, *line = NULL;
	size_t len = 0, current_line = 1;
	void (*temp)(stack_t **stack, unsigned int line_number);
	stack_t *tempStack, *stack = NULL;
	FILE *input;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	input = fopen(argv[1], "r");
	if (!input)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (_getline(&line, &len, input) == -1)
			break;
		opcode = strtok(line, " \n");
		temp = getFunction(opcode);
		if (temp == NULL)
		{
			fprintf(stderr, "L%ld: unknown instruction %s\n",
					current_line, opcode);
			exit(EXIT_FAILURE);
		}
		temp(&stack, current_line++);
	}
	free(line);
	while (stack)
	{
		tempStack = stack;
		stack = stack->next;
		free(tempStack);
	}
	fclose(input);
	return (EXIT_SUCCESS);
}


/**
 * getFunction - takes an opcode and returns its corresponding function
 * @opcode: the opcode
 *
 * Return: the function
 */
void (*getFunction(char *opcode))(stack_t **stack, unsigned int line_number)
{
	instruction_t opcodeList[] = {
	{"push", pushFunction},
	{"pall", pallFunction},
	{"nop", nopFunction},
	{"pint", pintFunction},
	{"pop", popFunction},
	{"swap", swapFunction},
	{"add", addFunction},
	{NULL, NULL}
	};
	int i = 0;

	if (opcode == NULL)
		return (nopFunction);

	while (opcodeList[i].opcode != NULL)
	{
		if (strcmp(opcodeList[i].opcode, opcode) == 0)
			return (opcodeList[i].f);
		i++;
	}
	return (NULL);
}



/**
 * _getline - custom getline, no realloc
 * @buf: buffer
 * @len: length
 * @fil: file
 * Return: -1 if EOF
 */
int _getline(char **buf, size_t *len, FILE *fil)
{
	if (*buf == NULL)
	{
		*buf = malloc(32);
		if (!(*buf))
		{
			fprintf(stderr, "Error, malloc failed\n");
			exit(EXIT_FAILURE);
		}
		*len = 32;
	}
	while (1)
	{
		if (fgets(*buf, *len, fil) == NULL)
			return (-1);
		if (strchr(*buf, '\n') != NULL)
			return (0);
		fseek(fil, -(*len) + 1, SEEK_CUR);
		free(*buf);
		*len += 32;
		*buf = malloc(*len);
		if (!(*buf))
		{
			fprintf(stderr, "Error, malloc failed\n");
			exit(EXIT_FAILURE);
		}
	}
}
