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

void usage(mstring tag);

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

        
        if (argc > 1)
        {
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
        else
                usage("");
}

void usage(mstring tag)
{
        cout << "\n\nUsage: htmlMerge -m raw file\n\n";
        cout << "Description:\n";
        cout << "------------\n";
        cout << "htmlMerge is a filter that allows you to merge raw data into an HTML template.\n";
        cout << "This is done by having a \"template\" HTML file that contains special tags of the\n";
        cout << "form: {tagname}, where \"tagname\" is a unique name composed of an upper and or lower
alpha\n";
        cout << "numeric string surrounded by \"{}\"--such as : \"<TITLE> {Title1} </TITLE>\"Note: this
\"tag\" is embedded\n ";
        cout << "within HTML Tags. The merge tag may appear embedded within a line, or on a line by
itself\n";
        cout <<"The merge tag will be have a match in the \"raw file\" which appears in the same form,
however\n";
        cout << "the merge tag must appear on a line by itself followed by a blank line. \n";
        cout << " This raw file should look something like the following: \n\n";
        cout << "{Title}\n\n";
        cout << "This is the Title we want\n\n";
        cout << "{Another_tag_not_mentioned_above}\n\n";
        cout << "Some more text we which to merge in the template\n";
        cout << "More text to merge\n";
        cout << "More text to merge\n";
        cout << "More text to merge\n\n";
        cout << "Note: that that the text to be merged follows the blank line that follows the merge
tag\n";
        cout << "that is releated to said text. Also the lines to be merged, should appear in the raw
file \n";
        cout << "exactly, in repsect to line returns, as you which them to appear in the template\n\n";
        cout << "Given the above example, the title line after the merge should look like :\n\n";
        cout << "<TITLE> This is the Title we want </TITLE>\n\n";
        cout << "since this is a filter, all input is read from stdin, and all output is written to
stdout\n\n";
        cout << "Example:\n";
        cout << "---------\n";
        cout << "We have a \"raw file\" called \"update.txt\" and a template called
\"job_post_template.html\" \n\n" ;
        cout << "If we which to create a new job posting called \"new_job1.html\" then we would
type:\n\n";
        cout << "\"cat job_post_template.html | htmlMerge -m update.txt > new_job1.html\"\n\n";
        cout << "Restrictions:\n";
        cout << "------\n";
        cout << "Within the \"template\" file any merge tag should not appear on the same line more than
once\n";
        cout << "If a merge tag is found in one file and not the other, then it will be igorned, not
replaced.\n";
        cout << "For each merge tag found in the \"raw file\" every one like it found in the
\"template\" file\n";
        cout << "will be replaced with the merge text associated with that tag.\n\n";

        exit(1);


}

