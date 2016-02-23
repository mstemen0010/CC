#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "mstring.h"

#define MAX_ENTRIES 10000

/* char *sender = "Anonymous"; */
/* char *subject= "[No Subject]"; */
/* char *content = ""; */
/* char *outLine = ""; */
char *month = "";
char *year = "";
mstring comment;
mstring fileName = "/opt/users/cssurvey/survey_";
int  numEntries = 0;
time_t	currTime;
char timeStamp[BUFSIZ];
char rawTimeStamp[BUFSIZ];


typedef struct {
    char *name;
    char *val;
} entry;

entry entries[MAX_ENTRIES];

char *makeword(char *line, char stop);
char *fmakeword(FILE *f, char stop, int *len);
char x2c(char *what);
void unescape_url(char *url);
void plustospace(char *str);


void writeIt()
{
    FILE *fp;
    char command[256];
    int  x = 0;
    mstring location = "Unknown";
    char *loc = getenv("REMOTE_HOST"); 
    if (loc)
	location = loc;


    currTime = time(NULL);
    
    strcpy(rawTimeStamp, (char *)ctime(&currTime));
    strncpy (timeStamp, rawTimeStamp, (strlen(rawTimeStamp) - 1));
    mstring rTime = timeStamp;
    mstring fTime = rTime.parse(" "); //Day of week
    fTime += " ";
    fTime += rTime.parse(" "); // Month
    fTime += " ";
    fTime += rTime.parse(" "); // Date(day)
    rTime.parse(" "); // Time of day (do not want)
    fTime += " ";
    fTime += rTime.parse(" "); // Year
     


    fp = fopen(fileName(), "a");
    if (fp != NULL)
    {	
	fprintf(fp, "%s \t", fTime());
	fprintf(fp, "%s \t", location());
    	for(x=1 ;x < numEntries - 1 ;x++) 
	{
		int blank = FALSE;
		mstring tempStr;
		tempStr = entries[x].val;
		if(tempStr.isBlank()) 
			blank = TRUE;

		if (strcasecmp(entries[x].name, "cName") == 0 )
		{
			tempStr = entries[x].val;
			if(tempStr.isBlank()) 
				blank = TRUE;
		}
		else if (strcasecmp(entries[x].name, "Surveyer") == 0 )
		{
			tempStr = entries[x].val;
			if(tempStr.isBlank()) 
				blank = TRUE;
		}
		else if (strcasecmp(entries[x].name, "Techname") == 0 )
		{
			tempStr = entries[x].val;
			if(tempStr.isBlank()) 
				blank = TRUE;
		}
		else if (strcasecmp(entries[x].name, "Location") == 0 )
		{
			tempStr = entries[x].val;
			if(tempStr.isBlank()) 
				blank = TRUE;
		}
		else if (strcasecmp(entries[x].name, "Date") == 0 )
		{
			tempStr = entries[x].val;
			if(tempStr.isBlank()) 
				blank = TRUE;
		}
		else if (strcasecmp(entries[x].name, "Ticket") == 0 )
		{
			tempStr = entries[x].val;
			if(tempStr.isBlank()) 
				blank = TRUE;
		}
		else if (strcasecmp(entries[x].name, "Title") == 0 )
		{
			tempStr = entries[x].val;
			if(tempStr.isBlank()) 
				blank = TRUE;
		}
		if (blank)
			fprintf(fp, "NONE \t");
		else
		{
			fprintf(fp, "%s \t", entries[x].val);
		}
	}
	fprintf(fp, "%s \t", comment());
	
	fprintf(fp, "\n");
	fflush(fp);
    }
    else
	fprintf(fp, "<H1>Unable to open survey</H1>");
	
    fclose(fp);

}

main(int argc, char *argv[]) {
    register int x,m=0, i = 0;
    int cl;
    char *commentCopy;
    int commentLen = 0;

#ifdef OLD
    cl = atoi(argv[1]);
#else
    cl = atoi(getenv("CONTENT_LENGTH"));
#endif

    printf("Content-type: text/html%c%c",10,10);

    for(x=0;cl && (!feof(stdin));x++) 
	{
		numEntries++;
        m=x;
        entries[x].val = fmakeword(stdin,'&',&cl);
        plustospace(entries[x].val);
        unescape_url(entries[x].val);
        entries[x].name = makeword(entries[x].val,'=');
		if (strcasecmp(entries[x].name, "Month") == 0 && (strlen(entries[x].val) > 0))
			month = entries[x].val;
		if (strcasecmp(entries[x].name, "Year") == 0 && (strlen(entries[x].val) > 0))
			year = entries[x].val;
		if (strcasecmp(entries[x].name, "customer") == 0 && (strlen(entries[x].val) > 0))
		{
			fileName += entries[x].val;
			fileName += ".xls";
		}
		{
			comment = entries[x].val;
			comment = comment.deCntrl(" ");
			// commentCopy = entries[x].val;
			// strcpy(comment, commentCopy);
			// commentLen = strlen(comment);
			// strcpy(comment, "");
			// while (*commentCopy != '\0')
			// {
		// 		if (! iscntrl(*commentCopy))
		// 			strcat(comment, *commentCopy);
		// 		commentCopy++;
		// 	}
		// 	for ( i = 0; i < commentLen; i++)
		// 		commentCopy--;
		// 	entries[x].val = comment;
		}
			

    }
    printf ("<h1><IMG SRC=/images/teklogo.gif> Your survey was submitted</h1> <br> ");

    writeIt(); 

}
