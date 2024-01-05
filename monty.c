
#include "monty.h"

/**
 * main - monty interpreter
 */
int main()
{
    char *line = NULL;
    size_t len = 0;
    stack_t *stack = NULL;


    while (1)
    {
        if (getline(&line, &len, stdin) == -1)
            exit(1);

        char *opcode = strtok(line, " \n");

        if (opcode == NULL)
            continue; // Pa ignorar las lineas vacias

        void (*temp)(stack_t **stack, unsigned int line_number) = getFunction(opcode);
        if (temp == NULL)
        {
            fprintf(stderr, "L%d: unknown instruction %s\n", 1, opcode);
            exit(EXIT_FAILURE);
        }

        temp(&stack, 1);
    }

    free(line);  //Liberar lamemoria

    return 0;
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
