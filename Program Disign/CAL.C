#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"

int error = 0;
int prec, tmp;
double num, result, ret;
unsigned char *str;

char * expr; 

char prevchar;
char lastchar;

int nextchar()
{
	while (isspace(*expr) && *expr != 0)
	{
		expr++;
	}
	prevchar = lastchar;
	if (*expr == 0)
		return lastchar = -1;

	lastchar = *expr;
	expr++;
	return lastchar;
}
 
Stack * operators; 
Stack * operands;

int precedence(char ch)
{
	if (ch == '*' || ch == '/')
		return 2;
	else if (ch == '+' || ch == '-')
		return 1;
	else
		return 0;
}

double bin_op(char op)
{
	double a, b;
	pop(operands, &b);
	pop(operands, &a);

	switch (op)
	{
		case '+': return a+b;
		case '-': return a-b;
		case '*': return a*b;
		case '/': return a/b;
	}
}

unsigned char *calc(unsigned char *input)
{
	error = 0;
	prevchar = 0;
	lastchar = 0;
	expr = input;
/*
	operators = stack_new(sizeof(char));
	operands = stack_new(sizeof(double));
	if (nextchar() == -1)
		error = 1;

	while (lastchar > 0 && !error)
	{
		if (isdigit(lastchar) || lastchar == '.')
		{
			char buff[32];
			char * snum = buff;
			
			do
			{
				*snum = lastchar;
				snum++;
				nextchar();
			} while (isdigit(lastchar) || lastchar == '.');


			*snum = 0;
			num = atof(buff);
			push(operands, &num);

			continue;
		}
		else
		{
			switch (lastchar)
			{
			
			case '+':
			case '-':
			case '*':
			case '/':
				if ((prevchar ==  0) && (lastchar == '-' || lastchar == '+'))
				{
					double v = 0;
					push(operands, &v);
					push(operators, &lastchar);
					break;
				}
				prec = precedence(lastchar);
				while (operators->top > 0)
				{
					char op;
					peek(operators, &op);
					tmp = precedence(op);
					if (tmp >= prec)
					{
						pop(operators, &op);
						result = bin_op(op);
						push(operands, &result);
					}
					else
					{
						break;
					}
				}
				push(operators, &lastchar);
				break;
			default:
				error = 1;
				break;
			}
		}
		nextchar();
	}
	while (operators->top > 0)
	{
		char op;
		pop(operators, &op);
		
		result = bin_op(op);
		push(operands, &result);
	}

	
	
	pop(operands, &ret);

	stack_free(operators);
	stack_free(operands);
	
	str = input;
	//sprintf(str,"%g",ret);
	return str;*/
	return expr;
}
