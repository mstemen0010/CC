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


	in.getline(inputs, BUFSIZ - 1);
	orig = inputs;
	if (inputs) 
		cout << "<NL>\n";
	while (in.good())
	while (stillGood)
	{
		if (stillGood == NEXT_TO_LAST)
			stillGood = LAST;
		if (orig.isBlank())
		{
			if (pbegin)
			{
				cout << "<LI>\n";
				pbegin = FALSE;
				firstLine = FALSE;
			}
			else 
			{
				if (! pend)
					pend = TRUE;
			}

		}
		else if (firstLine)
		{
				cout << "<LI>\n";
				cout << inputs << "\n";
				firstLine = FALSE;
				pbegin = FALSE;
		}
		else
		{
			if (pend)
			{
				cout << "</LI>\n<LI>\n";
				cout << inputs << "\n";
				pend = FALSE;
				if (! stillGood)
				{
					cout << "</LI>\n";
				}

			}		
			else
				if (! stillGood)
				{
					cout << inputs << "\n";
					cout << "</LI>\n";
				}
				else
					cout << inputs << "\n";
			cout.flush();
		}

		in.getline(inputs, BUFSIZ - 1);
		orig = inputs;
		if (! in.good() && stillGood)
			stillGood = NEXT_TO_LAST;
	}
	if (pend)
		cout << "</LI>\n";
	cout << "</NL>\n";
}

