#include "40kabchr.h"

character::character(fstream &file)
{
	char 	inputBuffer[BUFSIZ];
	int		success = TRUE;
	
