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
	int addnotfound = 1;
	int pbegin = TRUE, pend = FALSE;
	int words = 0, totalWords = 0;
	int colonsFound = 0, colonCount = 0;
	int stillGood = TRUE;
	int indent = FALSE;
	int numIndent = 1;
	int opt;
	int i = 0;

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
	totalWords = orig.wcount();
	if (indent)
		for (i = 0; i < numIndent; i++)
			cout << "<DL>\n<DD>\n";
	while (stillGood)
	{
		if (stillGood == NEXT_TO_LAST)
			stillGood = LAST;
		words = 0;
		colonCount = orig.ccount(":");
		if (colonCount >= 1)
			colonCount = 1;
		colonsFound = 0;
		while (words < totalWords)
		{
			if (! orig.isBlank()) // is it a blank line ??
			{
				if (orig.wcount() >= 1)
				{
					if ( colonsFound < colonCount)
					{
						// cout << "Got Here !!\nBOOM!!\n";
						// cout.flush(); 
						// if (orig[orig.len()] != ':')
						// if (temp.wcount() > 0)
						if (orig.cPos(':') != orig.len() - 1)
						{
							copy = orig.parse(":");
							words += copy.wcount();
							cout << "<B>" << copy << ":</B> ";
							int wordCount = copy.wcount();
							for(i = 0; i < wordCount; i++)
							{
							//	copy = orig.parse(" ");
								mstring *temp = orig.parse(" ");
								if (temp)
									copy = temp;
							}
						} // end of check to seen if last char of string is ":"
						else
						{
							copy = orig;
							cout << copy << "<BR>\n";
							break;
						}
						words++;
						colonsFound++;
					} // end of colonsFound < colonCout
					else
					{
						// copy = orig.parse(" ");
						mstring *temp = orig.parse(" ");
						if (temp)
							copy = temp;
						words++;
					}
				} // end of check to see in the number of words in the orig string is >= to 1
				else
					copy = orig;

				if (copy.ccount("@"))
					cout << "<A HREF=\"mailto:" << copy <<"\">" << copy << "</A>";
				else if (copy.sub("http://"))
					cout << "<A HREF=\"" << copy <<"\">" << copy << "</A>";
				else
					cout << copy << " ";
				if (words == totalWords)
					cout << "<BR>\n";

			}  // end of check to see if we read a blank line 
			else
		    	cout << "\n";
		} // end of while words < totalWords
		if (orig.isBlank())
			cout << "<BR>\n";
			
		cout.flush();
		in.getline(inputs, BUFSIZ - 1);
		orig = inputs;
		totalWords = orig.wcount();
		if (! in.good() && stillGood)
			stillGood = NEXT_TO_LAST;
	} // end of while stillGood
	if (indent)
		for (i = 0; i < numIndent; i++)
			cout << "</DD>\n</DL>\n";
}

