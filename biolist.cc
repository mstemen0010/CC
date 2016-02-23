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

void main()
{
	fstream in(fileno(stdin));

	char inputs[BUFSIZ] = "";
	mstring orig;
	mstring copy; 
	int addnotfound = 1;
	int pbegin = TRUE, pend = FALSE;
	int words = 0, totalWords = 0;
	int colonsFound = 0;
	int stillGood = TRUE;


	in.getline(inputs, BUFSIZ - 1);
	orig = inputs;
	totalWords = orig.wcount();
	while (stillGood)
	{
		if (stillGood == NEXT_TO_LAST)
			stillGood = LAST;
		words = 0;
		colonsFound = 0;
		while (words < totalWords)
		{
			if (! orig.isBlank())
			{
				if (orig.wcount() > 1)
				{
					if( colonsFound < orig.ccount(":"))
					{
						copy = orig.parse(":");
						words+= copy.wcount();
						cout << "<B>" << copy << ":</B> ";
						int wordCount = copy.wcount();
						for(int i = 0; i < wordCount; i++)
							copy = orig.parse(" ");
						words++;
						colonsFound++;
					}
					else
					{
						copy = orig.parse(" ");
						words++;
					}
				}
				else
					copy = orig;
				if (! copy.isBlank())
				{
					if (copy.ccount("@"))
						cout << "<A HREF=\"mailto:" << copy <<"\">" << copy << "</A>";
					else if (copy.ccount("http://"))
						cout << "<A HREF=\"" << copy <<"\">" << copy << "</A>";
					else
						cout << copy << " ";
				}
			}
		}
		if (! orig.isBlank())
			cout << "<BR>\n";
		cout.flush();
		in.getline(inputs, BUFSIZ - 1);
		orig = inputs;
		totalWords = orig.wcount();
		if (! in.good() && stillGood)
			stillGood = NEXT_TO_LAST;
	}
}

