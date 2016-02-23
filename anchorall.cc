#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <strings.h>
#include "mstring.h"

#ifndef TRUE
	#define TRUE 1
	#define FALSE ! TRUE
#endif

void main(int argc, char *argv[])
{

	char *fname = "/tmp/anchorallTmp";
	char inputs[BUFSIZ];
	char currMatch[BUFSIZ];
	fstream in(fileno(stdin));
	fstream temp(fname, ios::out);
	int writeTemp = 1;
	int items = 0;
	int noList = 1;
	int tblBuilt = 0;
	int status = 0;
	char *envval = "STARTCHAR";
	char *acounterPtr = "";
	char acounter[BUFSIZ];
	int	counter = 0;
	int origCounter = 0;
	int multicount = 1;

    if (getenv(envval))
	{
		acounterPtr = (char *)getenv(envval);
		counter = toascii(*acounterPtr);
		origCounter = counter;
	}
	else
	{
		counter = 65; /* acsii "A" */
		origCounter = counter;
	}


	in.getline(inputs, BUFSIZ - 1);
	while (noList)
	{
		if ( ! (strlen(inputs) > 1))
			writeTemp = 0;
		if (writeTemp)
		{
			temp << inputs << "\n";
			items++;
			temp.flush();
			in.getline(inputs, BUFSIZ - 1);
		}
		else
		{
			temp.close();
			noList = 0;
		}	
	}
	// print out the top list
	fstream list(fname, ios::in);
	list.getline(inputs, BUFSIZ - 1);
	while (list.good())
	{
		sprintf(acounter, "%c", counter);
		cout << "<A HREF = \"#"; 
		for (int i = 1; i <= multicount; i++)
			cout << acounter;
		cout << "\">" << inputs << "</A><BR>\n";
		counter++;
		if (counter >= 91)
		{	
			counter = origCounter;
			multicount++;
		}
		list.getline(inputs, BUFSIZ - 1);
	}
	list.clear();
	list.seekg(0);
	int noMatch = 1;
	counter = origCounter;
	multicount = 1;

	in.getline(inputs, BUFSIZ - 1);
	while (in.good())
	{
		sprintf(acounter, "%c", counter);
		if (noMatch)
		{
			list.getline(currMatch, BUFSIZ - 1);
			noMatch = 0;
		}		
		if (strstr(inputs, currMatch) && list.good())
		{
			cout << "<A NAME = \"" ;
			for (int i = 1; i <= multicount; i++)
				cout << acounter;
			cout << "\">" << inputs << "</A>\n";
			noMatch = 1;
			counter++;
			if (counter >= 91)
			{	
				counter = origCounter;
				multicount++;
			}
		}
		else
			cout << inputs << "\n";
		in.getline(inputs, BUFSIZ - 1);
	}
	cout << inputs << "\n";
	unlink(fname);

}

