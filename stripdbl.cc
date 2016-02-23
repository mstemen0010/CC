#include <stdio.h>
#include <iostream.h>
#include <fstream.h>

#define TRUE 1
#define FALSE !TRUE

void main()
{
	int goodRead = TRUE;
	int singleBlank = TRUE;
	char buffer[BUFSIZ];


	fstream in(fileno(stdin));

	while (goodRead)
	{

		in.getline(buffer, sizeof(buffer) - 1);
		if (strlen(buffer) <= 0)
		{
			if ( singleBlank)
			{
				cout << buffer << "\n";
				singleBlank = FALSE;
			}
		}
		else
		{
			cout << buffer << "\n";
			singleBlank = TRUE;
		}
		if (! in.good())
			goodRead = FALSE;

	}
}
	
