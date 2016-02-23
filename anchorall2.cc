#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <strings.h>
#include "mstring.h"
#include "table.h"

void main(int argc, char *argv[])
{

	char *fname = "/tmp/anchorallTmp";
	char inputs[BUFSIZ];
	char buffer[BUFSIZ];
	fstream in(fileno(stdin));
	fstream temp(fname, ios::out);
	int writeTemp = 1;
	int noList = 1, items = 0;
	char *envval = "STARTCHAR";
	char *acounterPtr = "";
	char acounter[BUFSIZ];
	int	counter = 0;
	int origCounter = 0;

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
	while(in.getline(inputs, BUFSIZ -1 ))
		items++;

	in.clear();
	in.seekg(0);
	table list(items);

	in.getline(inputs, BUFSIZ - 1);
	while (noList)
	{
		if ( ! (strlen(inputs) > 1))
			writeTemp = 0;
		if (writeTemp)
		{
			cout << "got here !!\n";
			sprintf(acounter, "%c", counter);
			// print out the top list
			cout << "<A HREF = \"#" << acounter << "\">" << inputs << "</A><BR>\n";
			cout.flush();
			// write the table
			sprintf(buffer, "%c~%s", counter, inputs);
			list.add(buffer);
			in.getline(inputs, BUFSIZ - 1);
			counter++;
		}
		else
		{
			temp.close();
			noList = 0;
		}	
	}
	int noMatch = 1;
	counter = origCounter;

	in.getline(inputs, BUFSIZ - 1);
	while (in.good())
	{
		if (list.find(inputs))
		{
			mstring temp = list.get(inputs);
			mstring pos = temp.parse("~");
			mstring name = temp.parse("~");
			cout << "<A NAME = \"" << pos << "\">" << name << "</A>\n";
		}
		else
			cout << inputs << "\n";
		in.getline(inputs, BUFSIZ - 1);
	}
	cout << inputs << "\n";

}

