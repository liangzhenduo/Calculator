#include <stdio.h>
#include <stdlib.h>
#include "cal.h"

unsigned int toDigit(char ch)
{
	return ch - '0';
}

number buildNumber(token str)
{
	number result = 0;
	result = strtod(str, NULL);
	return result;
}

token num2Str(number num)
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

token doOp(Stack *s,token op)
{
	token roperand = (token)stackPop(s);
	token loperand = (token)stackPop(s);
	number lside = buildNumber(loperand);
	number rside = buildNumber(roperand);
	number ret;
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
	//return 0;
}

/*
 * Similar to fgets(), but handles automatic reallocation of the buffer.
 * Only parameter is the input stream.
 * Return value is a string. Don't forget to free it.
 */
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
	while((ch = *ptr++))
	{
		//if(type(ch) == invalid) // Stop tokenizing when we encounter an invalid character
		//	break;

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
						// Assemble an n-character (plus null-terminator) number token
						{
							int len = 1;
							bool hasDecimal = false;
							bool hasExponent = false;

							if(ch == '.') // Allow numbers to start with decimal
							{
								//printf("Decimal\n");
								hasDecimal = true;
								len++;
								tmpToken[0] = '0';
								tmpToken[1] = '.';
							}
							else // Numbers that do not start with decimal
							{
								tmpToken[len-1] = ch;
							}

							// Assemble rest of number
							for(; // Don't change len
								*ptr // There is a next character and it is not null
								&& len <= prefs.maxtokenlength
								&& ((*ptr >= '0' && *ptr <= '9') // The next character is a digit
								 	|| ((*ptr == '.' // Or the next character is a decimal
								 		&& hasDecimal == 0)) // But we have not added a decimal
								 	//|| ((*ptr == 'E' || *ptr == 'e') // Or the next character is an exponent
								 	//	&& hasExponent == false) // But we have not added an exponent yet
								|| ((*ptr == '+' || *ptr == '-') && hasExponent == true)); // Exponent with sign
								++len)
							{
								if(*ptr == '.')
									hasDecimal = true;
								//else if(*ptr == 'E' || *ptr == 'e')
								//	hasExponent = true;
								tmpToken[len] = *ptr++;
							}

							// Append null-terminator
							tmpToken[len] = '\0';
						}
						break;
					}
					// If it's not part of a number, it's an op - fall through
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
				// Assemble an n-character (plus null-terminator) number token
				{
					int len = 1;
					bool hasDecimal = false;
					bool hasExponent = false;

					if(ch == '.') // Allow numbers to start with decimal
					{
						//printf("Decimal\n");
						hasDecimal = true;
						len++;
						tmpToken[0] = '0';
						tmpToken[1] = '.';
					}
					else // Numbers that do not start with decimal
					{
						tmpToken[len-1] = ch;
					}

					// Assemble rest of number
					for(; // Don't change len
						*ptr // There is a next character and it is not null
						&& len <= prefs.maxtokenlength
						&& ((*ptr>='0' && *ptr<='9') // The next character is a digit
						 	|| ((*ptr == '.' // Or the next character is a decimal
						 		&& hasDecimal == 0)) // But we have not added a decimal
						 	//|| ((*ptr == 'E' || *ptr == 'e') // Or the next character is an exponent
						 	//	&& hasExponent == false) // But we have not added an exponent yet
						 	|| ((*ptr == '+' || *ptr == '-') && hasExponent == true)); // Exponent with sign
						++len)
					{
						if(*ptr == '.')
							hasDecimal = true;
						//else if(*ptr == 'E' || *ptr == 'e')
						//	hasExponent = true;
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

void evalStackPush(Stack *s, token val)
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
				if(stackSize(s) >= 2)
					val = doOp(s, val);
				stackPush(s, val);
			}
			break;
		case 0:
			{
				stackPush(s, val);
			}
			break;
		default:
			break;
	}
}

bool postfix(token *tokens, int numTokens, Stack *output)
{
	Stack operators, intermediate;
	int i;
	bool err = false;
	stackInit(&operators, numTokens);
	stackInit(&intermediate, numTokens);
	for(i = 0; i < numTokens; i++)
	{
		// From Wikipedia/Shunting-yard_algorithm:
		switch(tokenType(tokens[i]))
		{
			case 0:
				{
					// If the token is a number, then add it to the output queue.
					//printf("Adding number %s to output stack\n", tokens[i]);
					evalStackPush(output, tokens[i]);
				}
				break;
			
			
			case '+':
			case '-':
			case '*':
			case '/':
				{
					/*
					 * If the token is an operator, op1, then:
					 *	 while there is an operator token, op2, at the top of the stack, and
					 *			 either op1 is left-associative and its precedence is less than or equal to that of op2,
					 *			 or op1 is right-associative and its precedence is less than that of op2,
					 *		 pop op2 off the stack, onto the output queue
					 *	 push op1 onto the stack
					 */
					while(stackSize(&operators) > 0
						&& (tokenType((char*)stackTop(&operators)) == '+' || tokenType((char*)stackTop(&operators)) == '-' 
						|| tokenType((char*)stackTop(&operators)) == '*' || tokenType((char*)stackTop(&operators)) == '/')
						&& (precedence(tokens[i], (char*)stackTop(&operators)) <= 0))
					{
						//printf("Moving operator %s from operator stack to output stack\n", (char*)stackTop(&operators));
						evalStackPush(output, stackPop(&operators));
						stackPush(&intermediate, stackTop(output));
					}
					//printf("Adding operator %s to operator stack\n", tokens[i]);
					stackPush(&operators, tokens[i]);
				}
				break;
			
			default:
				break;
		}
	}
	/*
	 * When there are no more tokens to read:
	 *	 While there are still operator tokens on the stack:
	 *		 If the operator token on the top of the stack is a paren, then there are mismatched parens
	 *		 Pop the operator onto the output queue
	 */
	while(stackSize(&operators) > 0)
	{
		evalStackPush(output, stackPop(&operators));
		stackPush(&intermediate, stackTop(output));
	}
	// pop result from intermediate stack
	stackPop(&intermediate);
	// free remaining intermediate results
	while (stackSize(&intermediate) > 0)
	{
		stackPop(&intermediate);
	}
	if (err == true)
	{
		while (stackSize(&operators) > 0)
		{
			token s = stackPop(&operators);
			//printf("Freeing %s from operators stack\n", s);
			free(s);
		}
	}
	stackFree(&intermediate);
	stackFree(&operators);
	return err;
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

bool strBeginsWith(char *haystack, char *needle)
{
	bool result;
	if(strlen(haystack) < strlen(needle))
	{
		return false;
	}
	else
	{
		char *sub = substr(haystack, 0, strlen(needle));
		result = (strcmp(sub, needle) == 0);
		free(sub);
		sub = NULL;
	}
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
