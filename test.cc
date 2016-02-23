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

	extern char *optarg;
	char inputs[BUFSIZ] = "";
	mstring orig;
	mstring copy; 
	int i = 0, opt = 0;
	int addnotfound = 1;
	int pbegin = TRUE, pend = FALSE;
	int indent = FALSE, numIndent = 0;
	int numbered = FALSE;
	int stillGood = TRUE;
	int firstLine = TRUE;


	while ((opt = getopt(argc, argv, "nui:")) != -1)
	{
		switch(opt)
		{
			case 'i':
				indent = TRUE;
				if (optarg)
					numIndent = atoi(optarg);
			break;
			case 'n':
				numbered = TRUE;
			break;
			case 'u':
				numbered = FALSE;
			break;

		}
	}


	in.getline(inputs, BUFSIZ - 1);
	orig = inputs;
	if (inputs)
	{
		cout << "<H3>RECENT PUBLICATIONS</H3>\n";
		cout << "<DL>\n<DD>\n<OL>\n";
        cout.flush();
	}

	// totalWords = orig.wcount();
	if (indent)
		for (i = 0; i < numIndent; i++)
			cout << "<DL>\n<DD>\n";
        	cout.flush();

	if (numbered)
		cout << "<OL>\n";
	else
		cout << "<UL>\n";

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
                cout << "<BR><BR></LI>\n<LI>\n";
                cout << inputs << "\n";
                pend = FALSE;
                if (! stillGood)
                {
                    cout << "</LI><BR><BR>\n";
                }
 
            }
            else
                if (! stillGood)
                {
                    cout << inputs << "\n";
                    cout << "<BR><BR></LI>\n";
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
		cout << "<BR><BR></LI>\n";

	if (indent)
		for (i = 0; i < numIndent; i++)
			cout << "</DD>\n</DL>\n";

	if (numbered)
		cout << "<OL>\n";
	else
		cout << "<UL>\n";
}

