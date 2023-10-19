#include "monty.h"

/**
  * pick_func - Select the function that relates to the Monty instruction
  *
  * @s: The instruction to be executed
  *
  * Return: A pointer to the function to be executed or
  * NULL if the function don't exists
*/
void (*pick_execute(char *s))(stack_t **, unsigned int)
{
    instruction_t instruction[] = {
        { "push", op_push },
        { "push_queue", op_push_queue },
        { "pall", op_pall },
        { "pint", op_pint },
        { "pop", op_pop },
        { "swap", op_swap },
        { "add", op_add },
        { "sub", op_sub },
        { "div", op_div },
        { "mul", op_mul },
        { "mod", op_mod },
        { "pchar", op_pchar },
        { "pstr", op_pstr },
        { "rotl", op_rotl },
        { "rotr", op_rotr },
        { NULL, NULL }
    };
    int i = 0;
    
    while (instruction[i].opcode)
	{
		if (strcmp(s, instruction[i].opcode) == 0)
			return (instruction[i].f);

		++i;
	}

	return (NULL);
}

/**
  * handle_execution - Manages the operations to be executed by the interpreter
  * @op_code: The operation code to manage
  * @op_param: The parameter of the instruction
  * @line: The line on which the error occurred
  * @m: The method to be used by the interpreter
  *
  * Return: 0 if the operation was executed correctly or errcode if is invalid
  */
int handle_execution(char *op_code, char *op_param, unsigned int line, int m)
{
	int status_op = 0;
	void (*oprt)(stack_t **, unsigned int);

	if (strcmp(op_code, "stack") == 0)
		return (METH_STACK);
	else if (strcmp(op_code, "queue") == 0)
		return (METH_QUEUE);

	oprt = pick_func(op_code);
	if (oprt)
	{
		if (strcmp(op_code, "push") == 0)
		{
			status_op = check_push_param(op_param);
			if (status_op == ERR_PUSH_USG)
				return (ERR_PUSH_USG);

			if (m != 0 && m == METH_QUEUE)
				oprt = pick_func("push_queue");

			oprt(&head, atoi(op_param));
		}
		else
		{
			oprt(&head, line);
		}

		return (m);
	}

	return (ERR_BAD_INST);
}