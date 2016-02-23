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

	

	while (in.getline(inputs, BUFSIZ - 1))
	{
		mstring cityName = inputs;
		mstring code;
		int count = 0;

		for (int i = 0; i < cityName.len(); i++)
		{
			if (isalpha(cityName[i]) )
			{
				code += cityName[i];
				count++;
			}
			if (count > 3)
				break;
		}
		code = code.lower();
		mstring outLine;
		outLine = "<A HREF=\"";
		outLine += code;
		outLine += ".html\">";
		outLine += cityName;
		outLine += "</A><BR>";
		cout << outLine << "\n";
		
	}

}

