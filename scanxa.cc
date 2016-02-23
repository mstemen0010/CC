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
	char inputs[BUFSIZ] = "";
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
	mstring newLine, outFileName, inFileName;
	fstream *intemp, *outtemp;


	
	while ((opt = getopt(argc, argv, "i:o:")) != -1)
	{
		switch(opt)
		{
			case 'o':
				interActive = TRUE;
				if (optarg)
					outFileName = optarg; 
			break;
			case 'i':
				interActive = TRUE;
				if (optarg)
					inFileName = optarg; 
			break;
		}
	}
	if (! outFileName.isBlank())
		outtemp = new fstream(outFileName, ios::out);
	else
		outtemp = new fstream(fileno(stdout));
	

	if (! inFileName.isBlank())
		intemp = new fstream(inFileName, ios::in);
	else
		intemp = new fstream(fileno(stdin));

	fstream in(intemp, ios::in);
	fstream out(outtemp);

	in->getline(inputs, BUFSIZ - 1);

	orig = inputs;

	while (stillGood)
	{
		if (stillGood == NEXT_TO_LAST)
			stillGood = LAST;
		index = 0;
		linePos = 1;
		newLine = "";
		while(orig[index] != NULL)
		{
			if (! isascii(orig[index]))
			{
				xaCount++;
				if (interActive)
					cout << "------------------------------------------------------------\n";
				cout << "Found extended ascii character\"" << orig[index] << "\"(" << (int)orig[index] << "). " << "On line:" << lineNum << " line position:" << linePos << " offset: " << offSet << "\n"; 
				cout << "Current line: \"" << orig << "\"\n";
				if (interActive)
				{
					cout << "------------------------------------------------------------\n";
					cout << "Old value (" << orig[index] << ") new value ?: " ;
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
					newLine += orig[index];
			}
			cout.flush();
			index++;
			linePos++;
			offSet++;
		}
		if (interActive)
		{
			newLine += "\n";
			cout << "New line is: " << newLine << endl;
			out << newLine();
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


		in->getline(inputs, BUFSIZ - 1);

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


