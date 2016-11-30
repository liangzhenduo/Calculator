#ifndef __CAL_H__
#define __CAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define MAXTOKENLENGTH 512
#define MAXPRECISION 20
#define DEFAULTPRECISION 5

struct Preferences
{
	struct Display
	{
		unsigned char tokens;
		unsigned char postfix;
	} display;
	
	int precision;
	int maxtokenlength;
} prefs;

typedef char* token;


Stack s;

char* ufgets(FILE* stream);
int tokenize(char *str, char *(**tokensRef));
void postfix(token *tokens, int numTokens);

#endif
