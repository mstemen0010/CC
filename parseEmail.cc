#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <strings.h>
#include "mstring.h"

#define ASCII_TOP 'a' // ascii "a"
#define ASCII_BOT 'z' // ascii "z"

int main(int argc, char *argv[])
{
	fstream in("adbook", ios::in);
	fstream *outFile;

	char inputs[BUFSIZ] = "";
	mstring field1;
	mstring field2;
	mstring field3;
	mstring temp, tempLetter;
	mstring workStr;
	mstring firstLetter;
	mstring oldLetter;
	mstring nextLetter;
	mstring outFileName;
	mstring navStr;
	mstring alphaDb;
	int 	alphaDbIndex = 1;
	char *outLine;
	int i = 0, j = 0;

	
	while (in.getline(inputs, BUFSIZ - 1))
	{
		workStr = inputs;
		field1 = workStr.parse("\t");  // usr name
		field2 = workStr.parse("\t");  // full name
		firstLetter = field2[0];		
		if (firstLetter != oldLetter && isalpha(firstLetter[0]))
		{
			alphaDb += firstLetter;
			oldLetter = firstLetter;
		}
	}
	alphaDb = alphaDb.lower();
	// cout << alphaDb << "\n";

	in.clear();
	in.seekp(0);

	while (in.getline(inputs, BUFSIZ - 1))
	{
		workStr = inputs;
		field1 = workStr.parse("\t");  // usr name
		temp = workStr.parse("\t");  // full name
		field2 = temp[0];
		for (i = 1; i < temp.len(); i++)
		{
			tempLetter = temp[i];
			if ( ! tempLetter.isBlank())
			{
				if (j == 0)
					field2 += tempLetter.upper();
				else 
					field2 += tempLetter.lower();
				j++;
			}
			else
			{
				field2 += tempLetter();
				j = 0;
			}	
		}

		// field2 = workStr.parse("\t");  // full name
		field3 = workStr.parse("\t");  // email addr
		firstLetter = field2[0];		
		firstLetter = firstLetter.lower();
		if (isalpha(firstLetter[0]))
		{
	
			if (firstLetter == nextLetter ) 
			{
				workStr = "</ul>\n\n<br><br><br>\n<hr>\n";
				workStr += navStr;
				workStr += "</body></html>";
				outFile->write(workStr, workStr.len());
			}
			if (firstLetter != oldLetter)
			{
				nextLetter = firstLetter + 1;
				// while (nextLetter[0] != alphaDb[alphaDbIndex] && alphaDbIndex < alphaDb.len())
				while ( (! alphaDb.ccount(nextLetter)) && alphaDbIndex < alphaDb.len())
				
				{	
					// cout << "No match found for : " << nextLetter << "\n";
					nextLetter = nextLetter + 1;
					// cout << "Going to : " << nextLetter << "\n";
					alphaDbIndex++;
				}
	
				outFileName = firstLetter();
				outFileName += ".html";
				outFile = new fstream(outFileName, ios::out);
				workStr = "<html>\n<head>\n<title> AEROTEK E-mail Directory: ";
				workStr += firstLetter.upper();
				workStr += "\n";
				workStr += "</title>\n</head>\n<body>\n<h1>Aerotek E-mail Directory</h1>\n<hr>\n\n\n";
				if (firstLetter[0] == 'a')
				{
					navStr = "<a href = \"email.html\"><img src=\"prev.gif\"></a>\n";
					navStr += "<a href = \"";
					navStr += nextLetter;
					navStr += ".html\"><img src=\"next.gif\"></a>\n";
					 
				}
				else if (firstLetter[0] > 'a' && (int)firstLetter[0] < 'z')
				{
					navStr = "<a href = \"";
					navStr += oldLetter;
					navStr += ".html\"><img src=\"prev.gif\"></a>\n";
					navStr += "<a href = \"";
					navStr += nextLetter;
					navStr += ".html\"><img src=\"next.gif\"></a>\n";
				}
				else if (firstLetter[0] > 'a' && firstLetter[0] == 'z')
				{
					navStr = "<a href = \"";
					navStr += oldLetter;
					navStr += ".html\"><img src=\"prev.gif\"></a>\n";
					navStr += "<a href = \"email.html\"><img src=\"next.gif\"></a>\n";
				}
				workStr += "<h1>";
				workStr += firstLetter.upper();
				workStr += "</h1>\n";
				workStr += navStr;
				workStr += "<ul>\n";
				
				outFile->write(workStr, workStr.len());
				
			}
			workStr = "<li><a href=\"mailto:";
			workStr += field1; 
			workStr += "@aerotek.com";
			workStr += "\">";
			workStr += field2;
			workStr += "</a>\n";
			outFile->write(workStr, workStr.len());
			outFile->flush();
			oldLetter = firstLetter;
		}
		
	}
	if (firstLetter.ccount("z"))
	{
		// cout << firstLetter << "\n";
		workStr = "</ul>\n\n<br><br><br>\n<hr>\n";
		workStr += navStr;
		workStr += "</body></html>";
		outFile->write(workStr, workStr.len());
	}

	return 1;
}

