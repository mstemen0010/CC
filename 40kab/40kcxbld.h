#ifndef _40K_CXBLD_H_
#define _40K_CXBLD_H_

#include <iostream.h>
#include <stdio.h>
#include "40kabio.h"

int addFig(char *filename);
int addSqd(char *filename);
int addSpt(char *filename);
int addList(char *filename);
int addCard(char *filename);
int newLine(FILE *file, char *item, char *def);

#endif

