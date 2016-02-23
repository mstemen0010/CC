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

int main()
{
	fstream in(fileno(stdin));

	char inputs[BUFSIZ] = "";
	char alpha[BUFSIZ];
	mstring alphaStr;
	int  alphaIndex = 65;
	int  passNumber = 65;


	while (in.getline(inputs, BUFSIZ - 1))
	{
		if (inputs)
		{
			mstring line = inputs;
			sprintf(alpha, "%c", alphaIndex);
			if (alphaIndex > 90)
			{
				alphaIndex = 65;
				sprintf(alpha, "%c", passNumber);
				if (passNumber > 90)
				{
					alphaStr = "";
					alphaStr = alpha;
					passNumber = 65;
				}
				else
				{
					passNumber++;
					alphaStr = alpha;
				}
				sprintf(alpha, "%c", alphaIndex);
				cout << alphaStr();
				cout << alpha << " ";
				cout << line() << endl;
				alphaIndex++;
			}
			else
			{
			
				if (! alphaStr.isBlank())
				{
					cout << alphaStr();
					cout << alpha << " ";
					cout << line() << endl;

				}
				else
				{
					cout << alpha << " ";
					cout << line() << endl;
				}
				alphaIndex++;
			}
			
		}

	}
}

