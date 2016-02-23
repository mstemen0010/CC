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

void main(int argc, char *argv[])
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
	int cntlMCount = 0;
	char c;


	// in.getline(inputs, BUFSIZ - 1);


	while (in.get(c))
	{
		orig = c;	
		if ((int)orig[0] == 13 && cntlMCount < 1) 
		{
			cntlMCount++;
			cout << "\n";
		}
		else if ((int)orig[0] != 13)
		{
			cntlMCount = 0;
			cout << orig[0];
		}
		else
		{
			cout << "\n";
			cntlMCount++;
		}

		cout.flush();
	}
}

