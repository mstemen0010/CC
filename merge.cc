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

#define MAYBE -1

#define NEXT_TO_LAST -1
#define LAST FALSE

mstring currMergeTag, nextMergeTag, mergeLine;

void getNextTag(fstream *mergeFileStream);

void main(int argc, char *argv[])
{
	int 	fd;
	char in[BUFSIZ] = "";
	char answer;
	char *answerPtr = NULL;
	mstring origNews, origTemplate;
	mstring copy; 
	int addnotfound = 1;
	int pbegin = TRUE, pend = FALSE;
	int stillGood = TRUE; 
	int firstLine = TRUE;
	int indent = FALSE;
	extern char *optarg;
	int opt, i, index = 0;
	int numIndent = 0;
	mstring inLine, mergeFileName;
	mstring outLine;
	int newsBody = FALSE;
	int mergeTagFound = FALSE;
	int nextMergeTagFound = FALSE;


	
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

		// fstream inFile(fileno(stdin));
		fstream inFile("news_template.html", ios::in);
		fstream mergeFile(mergeFileName, ios::in); 
			
		getNextTag(&mergeFile);
		
		// cout << "::::" << currMergeTag << ":::::\n";
		// cout << "::::" << mergeLine << ":::::\n";
		// cout << "::::" << nextMergeTag << ":::::\n";
		// cout << "Got here !!!\n\n";
	
		while(inFile.getline(in, BUFSIZ - 1))
		{
			inLine = in;
				
			if (inLine.sub(currMergeTag)) // found current tag
			{
				outLine = inLine;
				outLine.swap(currMergeTag, mergeLine, 1) ;
			}
			else if (inLine.sub(nextMergeTag)) // found new tag 
			{
				getNextTag(&mergeFile);
				outLine = in;
				outLine.swap(currMergeTag, mergeLine, 1) ;
			}
			else
			{
				outLine = inLine;
			}
				
			cout << outLine << "\n";
			cout.flush();
		}
}


void getNextTag(fstream *mergeFileStream)
{

	int nextTagFound = FALSE;
	int multiMergeLines = FALSE;
	int firstMultiLine = TRUE;
	int mergeTagFound = FALSE;
	char input[BUFSIZ];
	mstring tempLine;




	while(! nextTagFound && mergeFileStream->getline(input, BUFSIZ - 1))
    {
		if (input)
			tempLine = input;
		else
			break;

		if (nextMergeTag.len() && mergeTagFound == FALSE) 
		{
			currMergeTag = nextMergeTag();
			mergeTagFound = TRUE;
			mergeLine = tempLine();
		}
        else if (! tempLine.isBlank() && mergeTagFound == FALSE )
        {   
        	currMergeTag = tempLine(); 
            mergeTagFound = TRUE;
        }
        else if (! tempLine.isBlank() &&  mergeTagFound == TRUE)
        {
        	if (! multiMergeLines )
            {
            	mergeLine = tempLine();
                multiMergeLines = TRUE;
            }
            else
            {
            	if (firstMultiLine)
                {
                	mergeLine += "\n";
                    firstMultiLine = FALSE;
                	mergeLine += tempLine();
                }
                else
                {
                	mergeLine += tempLine();
                    mergeLine += "\n";
                }
			}
		}
        else if (tempLine.isBlank() )
		{
        	mergeTagFound = MAYBE;
            mergeLine += "\n";
		}
        else if (! tempLine.isBlank() && mergeTagFound == MAYBE)
        {
			if (tempLine.ccount("{") && tempLine.ccount("}"))
			{
        		nextMergeTag = tempLine();
				nextTagFound = TRUE;
				break;
			}
			else
				mergeTagFound = TRUE;
        }
	}
}

