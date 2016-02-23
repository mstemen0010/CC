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
	int 	fd;
	char inputs;
	char answer;
	char *answerPtr = NULL;
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
	int offSet = 0, linePos = 1, lineNum = 1, xaCount = 0;
	int xaFound = FALSE;
	int interActive = FALSE;
	mstring newLine, outFile, inFileName;

	char c;

	
	while ((opt = getopt(argc, argv, "i:o:")) != -1)
	{
		switch(opt)
		{
			case 'o':
				interActive = TRUE;
				if (optarg)
					outFile = optarg; 
			break;
			case 'i':
				interActive = TRUE;
				if (optarg)
					inFileName = optarg; 
			break;
		}
	}
	fstream out(outFile, ios::out);

	fstream inFile(inFileName, ios::in);
	fstream in(fileno(stdin));


	if (interActive)
		inFile.get(inputs);
	else
		in.get(inputs);

	orig = inputs;

	while (in.get(inputs))
	{
		if (stillGood == NEXT_TO_LAST)
			stillGood = LAST;
		index = 0;
		linePos = 1;
		newLine = "";
		while(orig[0] != NULL)
		{
			if (! isascii(orig[0]))
			{
				xaCount++;
				if (interActive)
					cout << "------------------------------------------------------------\n";
				cout << "Found extended ascii character\"" << orig[0] << "\"(" << (int)orig[0] << "). " << "On line:" << lineNum << " line position:" << linePos << " offset: " << offSet << "\n"; 
				cout << "Current line: \"" << orig << "\"\n";
				if (interActive)
				{
					cout << "------------------------------------------------------------\n";
					cout << "Old value (" << orig[0] << ") new value ?: " ;
					cout.flush();
					cin >> answer;
					answerPtr = &answer;
					newLine += answerPtr;
					xaFound = TRUE;
					fflush(stdin);
					fflush(stdout);

				}
				else
					cout << "============================================================\n";
			}
			else
			{
				if (interActive)
					newLine += orig[0];
			}
			cout.flush();
			index++;
			linePos++;
			offSet++;
		}
		if (interActive)
		{
			newLine += "\n";
			out << newLine;
			if (xaFound)
			{
				cout << "------------------------------------------------------------\n";
				cout << "New line: "  << newLine;
				cout << "============================================================\n";
				xaFound = FALSE;
			}
			else
				cout << newLine;
		}


		if (interActive)
			inFile.get(inputs);
		else
			in.get(inputs);

		offSet++;
		orig = inputs;
		if (interActive)
		{
			if (! inFile.good() && stillGood)
				stillGood = NEXT_TO_LAST;
		}
		else
		{
			if (! in.good() && stillGood)
				stillGood = NEXT_TO_LAST;

		}

		lineNum++;
	}
	cout << "Found " << xaCount << " extended ascii characters \n";
}


