#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <strings.h>
#include "mstring.h"

void main(int argc, char *argv[])
{
	fstream in(fileno(stdin));

	char inputs[BUFSIZ] = "";
	mstring orig;
	mstring copy; 
	int addnotfound = 1;
	int numFound = 0;
	int loopIt = 1;
	int wordCount = 0, origWordCount = 0;


	while (loopIt)
	{
		wordCount = 1;
		in.getline(inputs, BUFSIZ - 1);
		orig = inputs;
		origWordCount = orig.wcount();
		if (origWordCount > 1)	
			copy = orig.parse(" ");
		if (orig.ccount("@"))
		{
			while(wordCount <= origWordCount)
			{
				if(copy.ccount("@"))
				{
					if (copy.ccount("\n") )
					{
						cout << "<A HREF=\"mailto:" << copy() << "\">" << copy() <<"</A>\n";
						cout.flush();
					}
					else
						cout << "<A HREF=\"mailto:" << copy() << "\">" << copy() <<"</A>";
					numFound++;
				}
				else
				{
					if (copy.ccount("\n") )
					{
						cout << copy() << " \n";
						cout.flush();
					}
					else
						cout << copy() << " ";

				}
				if (wordCount < origWordCount)
					copy = orig.parse(" ");
				if (copy.len())
					wordCount++;
			}
			cout << "\n";
			cout.flush();
		}
		else
		{
			cout << inputs << "\n";
			cout.flush();
		}
		orig = inputs;
		loopIt = in.good();
	}
	cout.flush();
	/* 
		cout << "\n\nThis is a filter program to change all occurances of \"name@adress\", mail addresses, with the HTML code hyperlink to use \"sendmail\" in the form:\n\n";
		cout << "<A HREF=\"mailto:name@address\"> name@address  </A>\n\n";
		*/ 

}

