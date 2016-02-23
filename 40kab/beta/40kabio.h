#ifndef _40K_IO_H_
#define _40K_IO_H_

#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "mstring.h"

#define 	RET_CHOICE_NUM 	0
#define		RET_CHOICE_NAME 1
#define 	CLR_SCR printf("\033[2J");
#define 	TOP_SCR printf("\033[0;OH");

int getChoiceInt(char *title, char *arglist, int numChoices, int totalCost, int currCost);
char *getChoiceName(char *title, char *arglist, int numChoices, int totalCost, int currCost);

int getChoiceInta(char *title, char *arglist, int numChoices);
char *getChoiceNamea(char *title, char *arglist, int numChoices);

#endif
