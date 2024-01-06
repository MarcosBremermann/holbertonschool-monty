
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
	unsigned int current_line = 1;
	size_t len = 0;
	void (*temp)(stack_t **stack, unsigned int line_number);
	stack_t *stack = NULL;
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
		if (getline(&line, &len, input) == -1)
			break;
		opcode = strtok(line, " \t\n");
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
	free(line);
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
 *
*int _getline(char **buf, size_t *len, FILE *fil)
*{
*	if (*buf == NULL)
*	{
*		*buf = malloc(32);
*		*len = 32;
*	}
*	if (fgets(*buf, *len, fil) == NULL)
*		return (-1);
*
*	if (strchr(*buf, '\n') == NULL)
*	{
*		fseek(fil, -(*len), SEEK_CUR);
*		free(*buf);
*		*len += 32;
*		*buf = malloc(*len);
*		if (!(*buf))
*		{
*			fprintf(stderr, "Error, malloc failed\n");
*			exit(EXIT_FAILURE);
*		}
*		return (_getline(buf, len, fil));
*	}
*	return (0);
*}
*/
