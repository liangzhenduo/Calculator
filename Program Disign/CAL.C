#include <stdio.h>
#include <stdlib.h>
#include "cal.h"
#include "stack.h"

token num2Str(double num)
{
	int len = 0;
	int precision = MAXPRECISION;
	if (prefs.precision >= 0 && prefs.precision < precision)
		precision = prefs.precision;
	token str = (token)malloc(prefs.maxtokenlength*sizeof(char));
	len = snprintf(str, prefs.maxtokenlength-1, "%.*f", precision, num);
	if (prefs.precision == -1)
	{
		while (str[len-1] == '0')
		{
			len = snprintf(str, prefs.maxtokenlength-1, "%.*f", --precision, num);
		}
	}

	return str;
}

token doOp(token op)
{
	token roperand = stackPop(&s);
	token loperand = stackPop(&s);
	double lside = strtod(loperand, NULL);
	double rside = strtod(roperand, NULL);
	double ret;
	switch(*op)
	{
		case '*':
			ret = lside * rside;
			break;
		case '/':
			ret = lside / rside;
			break;
		case '+':
			ret = lside + rside;
			break;
		case '-':
			ret = lside - rside;
			break;
	}
	return num2Str(ret);
}

char* ufgets(FILE* stream)
{
	unsigned int maxlen = 128, size = 128;
	char* buffer = (char*)malloc(maxlen);

	if(buffer != NULL) /* NULL if malloc() fails */
	{
		char ch = EOF;
		int pos = 0;

		/* Read input one character at a time, resizing the buffer as necessary */
		while((ch = getchar()) != EOF && ch != '\n')
		{
			buffer[pos++] = ch;
			if(pos == size) /* Next character to be inserted needs more memory */
			{
				size = pos + maxlen;
				buffer = (char*)realloc(buffer, size);
			}
		}
		buffer[pos] = '\0'; /* Null-terminate the completed string */
	}
	return buffer;
}

int tokenType(token tk)
{
	if (!tk)
		return 127;
	unsigned int ret = *tk;
	switch(ret)
	{
		case '+':
		case '-':
			if(*tk == '-' && strlen(tk) > 1)
				ret = tokenType(tk+1);
			break;
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			ret = 0;
			break;
		default:
			break;
	}
	return ret;
}

int tokenize(char *str, char *(**tokensRef))
{
	int i = 0;
	char** tokens = NULL;
	char** tmp = NULL;
	char* ptr = str;
	char ch = '\0';
	int numTokens = 0;
	char* tmpToken = malloc((prefs.maxtokenlength+1) * sizeof(char));
	if (!tmpToken)
	{
		fprintf(stderr, "Malloc of temporary buffer failed\n");
		return 0;
	}
	while((ch = *ptr++)){
		token newToken = NULL;
		tmpToken[0] = '\0';
		switch(ch)
		{
			case '+':
			case '-':
				{
					// Check if this is a negative
					if(ch == '-'
						&& (numTokens == 0
							||(tokenType(tokens[numTokens-1]) == '+' || tokenType(tokens[numTokens-1]) == '-'
							|| tokenType(tokens[numTokens-1]) == '*' || tokenType(tokens[numTokens-1]) == '/')))
					{
						// Assemble an n-character (plus null-terminator) double token
						{
							int len = 1;
							unsigned char fraction = 0;
							//bool hasExponent = false;

							if(ch == '.') // Allow doubles to start with decimal
							{
								//printf("Decimal\n");
								fraction = 1;
								len++;
								tmpToken[0] = '0';
								tmpToken[1] = '.';
							}
							else // Numbers that do not start with decimal
							{
								tmpToken[len-1] = ch;
							}

							// Assemble rest of double
							for(; // Don't change len
								*ptr // There is a next character and it is not null
								&& len <= prefs.maxtokenlength
								&& ((*ptr >= '0' && *ptr <= '9') // The next character is a digit
								 	|| ((*ptr == '.' && fraction == 0))); // Exponent with sign
								++len)
							{
								if(*ptr == '.')
									fraction = 1;
								//else if(*ptr == 'E' || *ptr == 'e')
								//	hasExponent = true;
								tmpToken[len] = *ptr++;
							}

							// Append null-terminator
							tmpToken[len] = '\0';
						}
						break;
					}
					// If it's not part of a double, it's an op - fall through
				}
			case '*':
			case '/':
				{
					tmpToken[0] = ch;
					tmpToken[1] = '\0';
				}
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '.':
				// Assemble an n-character (plus null-terminator) double token
				{
					int len = 1;
					unsigned char fraction = 0;
					//bool hasExponent = false;

					if(ch == '.') // Allow doubles to start with decimal
					{
						//printf("Decimal\n");
						fraction = 1;
						len++;
						tmpToken[0] = '0';
						tmpToken[1] = '.';
					}
					else // Numbers that do not start with decimal
					{
						tmpToken[len-1] = ch;
					}

					// Assemble rest of double
					for(;*ptr // There is a next character and it is not null
						&& len <= prefs.maxtokenlength
						&& ((*ptr>='0' && *ptr<='9') // The next character is a digit
						 	|| ((*ptr == '.' // Or the next character is a decimal
						 		&& fraction == 0))); // Exponent with sign
						++len)
					{
						if(*ptr == '.')
							fraction = 1;
						tmpToken[len] = *ptr++;
					}

					// Append null-terminator
					tmpToken[len] = '\0';
				}
				break;
			
			default:
				break;
		}
		// Add to list of tokens
		if(tmpToken[0] != '\0' && strlen(tmpToken) > 0)
		{
			numTokens++;
			
			
			newToken = malloc((strlen(tmpToken)+1) * sizeof(char));
			if (!newToken)
			{
				numTokens--;
				break;
			}
			strcpy(newToken, tmpToken);
			newToken[strlen(tmpToken)] = '\0';
			tmp = (char**)realloc(tokens, numTokens * sizeof(char*));
			if (tmp == NULL)
			{
				free(newToken);
				if (tokens != NULL)
				{
					for(i=0;i<numTokens-1;i++)
					{
						if (tokens[i] != NULL)
							free(tokens[i]);
					}
					free(tokens);
				}
				*tokensRef = NULL;
				free(newToken);
				free(tmpToken);
				return 0;
			}
			tokens = tmp;
			tmp = NULL;
			tokens[numTokens - 1] = newToken;
		}
	}
	*tokensRef = tokens; // Send back out
	free(tmpToken);
	tmpToken = NULL;
	return numTokens;
}

int precedence(token op1, token op2)
{
	int ret = 0;

	if (op2 == NULL)
		ret = 1;
	else if(tokenType(op1) == tokenType(op2)) // Equal precedence
		ret = 0;
	else if((tokenType(op1) == '+' || tokenType(op1) == '-')
			&& (tokenType(op2) == '*' || tokenType(op2) == '/')) // op1 has lower precedence
		ret = -1;
	else if((tokenType(op2) == '+' || tokenType(op2) == '-')
			&& (tokenType(op1) == '*' || tokenType(op1) == '/')) // op1 has higher precedence
		ret = 1;
	
	return ret;
}

void evalStackPush(token val)
{
	if(prefs.display.postfix)
		printf("\t%s\n", val);

	switch(tokenType(val))
	{
		case '+':
		case '-':
		case '*':
		case '/':
			{
				if(stackSize(&s) >= 2)
					val = doOp(val);
				stackPush(&s, val);
			}
			break;
		case 0:
			{
				stackPush(&s, val);
			}
			break;
		default:
			break;
	}
}

void postfix(token *tokens, int numTokens)
{
	Stack operators, intermediate;
	int i;
	stackInit(&operators, numTokens);
	stackInit(&intermediate, numTokens);
	for(i = 0; i < numTokens; i++)
	{
		// From Wikipedia/Shunting-yard_algorithm:
		switch(tokenType(tokens[i]))
		{
			case 0:
				{
					evalStackPush(tokens[i]);
				}
				break;
			
			
			case '+':
			case '-':
			case '*':
			case '/':
				{
					while(stackSize(&operators) > 0
						&& (tokenType(stackTop(&operators)) == '+' || tokenType(stackTop(&operators)) == '-' 
						|| tokenType(stackTop(&operators)) == '*' || tokenType(stackTop(&operators)) == '/')
						&& (precedence(tokens[i], stackTop(&operators)) <= 0))
					{
						//printf("Moving operator %s from operator stack to output stack\n", (char*)stackTop(&operators));
						evalStackPush(stackPop(&operators));
						stackPush(&intermediate, stackTop(&s));
					}
					//printf("Adding operator %s to operator stack\n", tokens[i]);
					stackPush(&operators, tokens[i]);
				}
				break;
			
			default:
				break;
		}
	}
	while(stackSize(&operators) > 0)
	{
		evalStackPush(stackPop(&operators));
		stackPush(&intermediate, stackTop(&s));
	}
	// pop result from intermediate stack
	stackPop(&intermediate);
	// free remaining intermediate results
	while (stackSize(&intermediate) > 0)
	{
		stackPop(&intermediate);
	}
	stackFree(&intermediate);
	stackFree(&operators);
}

char* substr(char *str, size_t begin, size_t len)
{
	if(str == NULL
		|| strlen(str) == 0
		|| strlen(str) < (begin+len))
		return NULL;

	char *result = (char*)malloc((len + 1) * sizeof(char));
	int i;
	for(i = 0; i < len; i++)
		result[i] = str[begin+i];
	result[i] = '\0';
	return result;
}

int strSplit(char *str, const char split, char *(**partsRef))
{
	char **parts = NULL;
	char **tmpparts = NULL;
	char *ptr = str;
	char *part = NULL;
	char *tmppart = NULL;
	int numParts = 0;
	char ch;
	int len = 0;
	while(1)
	{
		ch = *ptr++;

		if((ch == '\0' || ch == split) && part != NULL) // End of part
		{
			// Add null terminator
			tmppart = (char*)realloc(part, (len+1) * sizeof(char));
			// if realloc fails, free current part and all previous parts
			if (tmppart == NULL)
			{
				free(part);
				part = NULL;
				for(len=0;len<numParts;len++)
				{
					if (parts[len])
						free(parts[len]);
				}
				if (parts)
					free(parts);
				parts = NULL;
				numParts = 0;
				break;
			}
			part = tmppart;
			part[len] = '\0';

			// Add to parts
			numParts++;
			if(parts == NULL)
				parts = (char**)malloc(sizeof(char**));
			else
			{
				tmpparts = (char**)realloc(parts, numParts * sizeof(char*));
				// if relloc fails, free current and previous parts
				if (tmpparts == NULL)
				{
					free(part);
					part = NULL;
					for(len=0;len<numParts-1;len++)
					{
						if (parts[len])
							free(parts[len]);
					}
					if (parts)
						free(parts);
					parts = NULL;
					numParts = 0;
					break;
				}
				parts = tmpparts;
			}
			parts[numParts - 1] = part;
			part = NULL;
			len = 0;
		}
		else // Add to part
		{
			len++;
			if(part == NULL)
			{
				part = (char*)malloc(sizeof(char));
			}
			else
			{
				tmppart = (char*)realloc(part, len * sizeof(char));
				// if relloc fails, free current and previous parts
				if (tmppart == NULL)
				{
					free(part);
					part = NULL;
					for(len=0;len<numParts;len++)
					{
						if (parts[len])
							free(parts[len]);
					}
					free(parts);
					numParts = 0;
					parts = NULL;
					break;
				}
				part = tmppart;
			}
			part[len - 1] = ch;
		}

		if(ch == '\0')
			break;
	}
	*partsRef = parts;
	return numParts;
}
