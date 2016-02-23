#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream.h>
#include <fstream.h>
#include <strings.h>
#include "mstring.h"

#ifndef TRUE
	#define TRUE 1
	#define FALSE !TRUE
#endif

#define MAYBE -1

#define NEXT_TO_LAST -1
#define LAST FALSE

mstring currMergeTag, nextMergeTag, mergeLine;

void getNextTag(fstream *mergeFileStream);

void main(int argc, char *argv[])
{
	char in[BUFSIZ] = "";
	extern char *optarg;
	int opt, i, index = -1;
	mstring inLine, mergeFileName;
	mstring outLine;
	mstring tempFileName = "/tmp/mergeTable.tmp";

	int tagCount = 0;
	mstring tag, mergeLine;

	int lineCount = 0;

	
	while ((opt = getopt(argc, argv, "m:")) != -1)
	{
		switch(opt)
		{
			case 'm':
				if (optarg)
					mergeFileName = optarg;
			break;
		}
	}

	fstream inFile(fileno(stdin));
	// fstream inFile("news_template.html", ios::in);
	fstream mergeFile(mergeFileName, ios::in); 
	fstream tempFile(tempFileName(), ios::out);
			
	// find out how many tags are in the raw file
	while (mergeFile.getline(in, BUFSIZ - 1))
	{
		inLine = in;
		if (inLine.wcount() == 1) // could be a tag
		{
			if ((inLine.ccount("{") == 1) && (inLine.ccount("}") == 1)) // more than likely a tag
			{
				tagCount++;
			}
		}
	}

	// ok now build a table for the tags and there repective lines
	mergeFile.clear();
	mergeFile.seekg(0);
		
	mstring rawTable[tagCount];
	while (mergeFile.getline(in, BUFSIZ - 1))
	{
		inLine = in;
		if ((inLine.wcount() == 1) && inLine.ccount("{") && inLine.ccount("}")) // tag
		{
			index++;
			rawTable[index] = inLine;
			rawTable[index] += "|~|";
		}
		else if (! inLine.isBlank())
		{
			rawTable[index] += inLine;
			rawTable[index] += "\n";
		}
		else if (inLine.isBlank())
		{
			rawTable[index] += "\n";
		}
	}
	// for (index = 0; index < tagCount; index++)
		// cout << rawTable[index] << "\n";

	// now build the template file into a table in memory
	while (inFile.getline(in, BUFSIZ-1))
	{
		tempFile << in << "\n";
		lineCount++;
	}
	tempFile.close();
	fstream newFile(tempFileName(), ios::in);
	newFile.clear();
	newFile.seekg(0);

	mstring templateTable[lineCount];
	index = 0;
	while (newFile.getline(in, BUFSIZ-1))
	{
		inLine = in;
		templateTable[index++] = inLine;
	}
	
	
	
	// now we read the template table for tags and swap out the tag for the merged text

	// go through the file looking for the known tags
	for (index = 0; index < tagCount; index++)
	{
		tag = rawTable[index].parse("|~|");
		mergeLine = rawTable[index].parse("|~|");
		for (int j = 0; j < lineCount; j++)
		{
			if (templateTable[j].sub(tag) != NULL)
			{
				templateTable[j].swap(tag, mergeLine, OPERATE_FIRST);
			}
		}
	}
	// now print out the new merged file
	for (index = 0; index < lineCount; index++)
		cout << templateTable[index] << "\n";
	
	unlink(tempFileName()); // remove the temp file
}

