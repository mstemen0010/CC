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

int main(int argc, char *argv[])
{
	fstream in(fileno(stdin));

	char inputs[BUFSIZ] = "";
	mstring orig;
	int opt, i;
	extern char *optarg;
	int numIndent = 0; 
	int numLevels = 0; 
	int center = FALSE;
	mstring cell_type_begin = "<TD>";
	mstring cell_type_end = "</TD>";
	mstring table_width = "";
	int numBuffer = 0;

	while ((opt = getopt(argc, argv, "ci:l:w:hb:")) != -1)
    {
        switch(opt)
        {
			case 'b':
				if (optarg)
					numBuffer = atoi(optarg);
			break;
            case 'i':
                if (optarg)
                    numIndent = atoi(optarg);
            break;
            case 'l':
                if (optarg)
                    numLevels = atoi(optarg);
            break;
			case 'c':
				center = TRUE;	
			break;
			case 'w':
				if (optarg)
				{
					table_width = "WIDTH=";
					table_width += optarg;	
				}
			break;
			case 'h':
				cell_type_begin = "<TH>";
				cell_type_end = "</TH>";
        }

    }



	in.getline(inputs, BUFSIZ - 1);
	orig = inputs;
	if (inputs) 
	{
		if (center)
			cout << "<CENTER>\n";
			cout << "<TABLE BORDER=8 " << table_width <<  " > <!--Begin Raised table level 1-->\n <TR>\n" << cell_type_begin << "\n";
		if (numBuffer)
			for (i = 1; i < numBuffer; i++)
				cout << "<BR>\n";

		for (i = 1; i < numLevels; i++) 
		{
			cout << "<TABLE BORDER=8 " << table_width <<  " > <!--Begin Raised table level 1-->\n <TR>\n" << cell_type_begin << "\n";
		}


		if (numIndent)
		{
			cout << "<DL><DD> <!-Begin Indent Level 1-->\n";
			for (i = 1; i < numIndent; i++)
				cout << "<DL><DD> <!--Continue Indent Level " << i + 1 << "-->\n";
		}
		cout << orig << "\n";
		while ( in.getline(inputs, BUFSIZ - 1))
		{
			orig = inputs;
			cout << orig << "\n";
		}
		cout.flush();
		if (numIndent)
		{
			for (i = 1; i <= numIndent; i++)
				cout << "</DD></DL> <!--End Indent Level " << abs(i - numIndent) + 1 << "-->\n";
		}
		cout.flush();
		for (i = 1; i < numLevels; i++) 
		{
			cout << cell_type_end << "\n</TR>\n" << "</TABLE> <!--End of Raised table level " << abs(i - numLevels) + 1 << "-->\n";
		}

		if (numBuffer)
			for (i = 1; i < numBuffer; i++)
				cout << "<BR>\n";
		cout << cell_type_end << "\n</TR>\n" << "</TABLE> <!--End Raised table level 1-->\n";
		if (center)
			cout << "</CENTER>\n";
	}
}

