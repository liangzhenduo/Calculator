#ifndef __CAL_H__
#define __CAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define MAXTOKENLENGTH 512
#define MAXPRECISION 20
#define DEFAULTPRECISION 5
#define true 1
#define false 0

typedef unsigned char bool;

struct Preferences
{
	struct Display
	{
		bool tokens;
		bool postfix;
	} display;
	
	int precision;
	int maxtokenlength;
} prefs;

typedef char* token;

typedef double number;



#endif
