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
	int opt, i;
	int numIndent = 0;

	while ((opt = getopt(argc, argv, "i:")) != -1)
	{
		switch(opt)
		{
			case 'i':
			indent = TRUE;
				if (optarg)
					numIndent = atoi(optarg);
				break;
		}

	}


	in.getline(inputs, BUFSIZ - 1);
	orig = inputs;

	 if (indent)
		for (i = 0; i < numIndent; i++)
			cout << "<DL>\n<DD>\n";

	while (stillGood)
	{
		if (stillGood == NEXT_TO_LAST)
			stillGood = LAST;
		if (orig.isBlank())
		{
			if (pbegin)
			{
				cout << "<P>\n";
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
				cout << "<P>\n";
				cout << inputs << "<BR>\n";
				firstLine = FALSE;
				pbegin = FALSE;
		}
		else
		{
			if (pend)
			{
				cout << "</P>\n<P>\n";
				cout << inputs << "<BR>\n";
				pend = FALSE;
				if (! stillGood)
				{
					cout << "</P>\n";
				}

			}		
			else
				if (! stillGood)
				{
					cout << inputs << "<BR>\n";
					cout << "</P>\n";
				}
				else
					cout << inputs << "<BR>\n";
			cout.flush();
		}

		in.getline(inputs, BUFSIZ - 1);
		orig = inputs;
		if (! in.good() && stillGood)
			stillGood = NEXT_TO_LAST;
	}
	if (pend)
		cout << "</P>\n";
	if (indent)
		for (i = 0; i < numIndent; i++)
			cout << "</DD>\n</DL>\n";
}

