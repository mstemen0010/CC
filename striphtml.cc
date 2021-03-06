#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <strings.h>
#include "mstring.h"

#ifndef TRUE
	#define TRUE 1
	#define FALSE !TRUE
#endif

#define NEXT_TO_LAST -1
#define LAST FALSE

int main(int argc, char *argv[])
{
	fstream in(fileno(stdin));

	char inputs[BUFSIZ] = "";
	mstring orig;
	mstring copy; 
	int addnotfound = 1;
	int pbegin = TRUE, pend = FALSE;
	int stillGood = TRUE;
	int firstLine = TRUE;
	int indent = FALSE;
	extern char *optarg;
	int opt, i, index = 0;
	int numIndent = 0;
	int	keep = TRUE;


	in.getline(inputs, BUFSIZ - 1);
	orig = inputs;

	while (stillGood)
	{
		if (stillGood == NEXT_TO_LAST)
			stillGood = LAST;
		index = 0;
		while(orig[index] != NULL)
		{
			// cout << "char read is : "<<  orig[index] << "(" << (int)orig[index] << ")\n";
			if (orig[index] == '<')
				keep = FALSE;
			else if (orig[index] == '>')
				keep = TRUE;
			else if ( keep)
				cout << orig[index];
			index++;
		}
		cout << "\n";


		in.getline(inputs, BUFSIZ - 1);
		orig = inputs;
		if (! in.good() && stillGood)
			stillGood = NEXT_TO_LAST;
	}
}

