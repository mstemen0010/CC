#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "mstring.h"

#define MAX_ENTRIES 10000

struct surveyitem
{
	mstring		catagory;
	mstring 	name;
	float		rate_1;
	float		rate_2;
	float		rate_3;
	float		rate_4;
	float		rate_5;
	float		total;
	float		perrate_1;	
	float		perrate_2;	
	float		perrate_3;	
	float		perrate_4;	
	float		perrate_5;	
};

char *month = "";
char *year = "";
mstring comment;
mstring inFile = "/opt/users/cssurvey/";
mstring custName;
int  numEntries = 0;
char timeStamp[BUFSIZ];
char rawTimeStamp[BUFSIZ];
 
 
typedef struct {
    char *name;
    char *val;
} entry;

entry entries[MAX_ENTRIES];
	
void addValue(mstring value, surveyitem *item);
void printRow(surveyitem item, fstream &outs);
void printRow(surveyitem item);
char *makeword(char *line, char stop);
char *fmakeword(FILE *f, char stop, int *len);
char x2c(char *what);
void unescape_url(char *url);
void plustospace(char *str);



main (int argc, char *argv[])
{
	register int x,m=0;
	int 		statingCurrentMonth = FALSE;
        int cl;
	char 		buffer[BUFSIZ * 4];
	mstring 	date, line, tempLine;
	mstring 	searchMonth;
	mstring 	searchYear;
	mstring 	surItemNames = "Politeness, Knowledge Level, Communicating Skill, Helpfulness, Accuracy, Quality of Resolution, Reasonable Timeframe, Met Expectations, Convenient Hours, Initial Contact Resolution, Call taker, Overall Rating"; 
	surveyitem	surveyItem[12];
	surveyitem	surveyItemYTD[12];
	int		opt;
	extern	char	*optarg;
	extern  int	errno;
	mstring		comment;
	float 		rate_1_YTD;
	float 		rate_2_YTD;
	float 		rate_3_YTD;
	float 		rate_4_YTD;
	float 		rate_5_YTD;
	float		YTD;

	// cout.flush();
	cout << "content-type: text/html\n\n";
	date.delimiter(" ");
	#ifdef OLD
                cl = atoi(argv[1]);
        #else
                cl = atoi(getenv("CONTENT_LENGTH"));
        #endif
 
 
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
			inFile += "survey_";
			custName = entries[x].val;
                        inFile += custName();
			inFile += ".xls";
		}
        }


	fstream 	in(inFile, ios::in);
	// cout << "Got Here!!!" << endl;

	// setup the survey items
	searchMonth = month;
	searchMonth = searchMonth.deSpace();
	searchYear = year;
	searchYear = searchYear.deSpace();
	// check to see if we are look at data from the current month
	time_t	currTime = time(NULL);	
	char rawTimeStamp[BUFSIZ];
	char timeStamp[BUFSIZ];
	strcpy(rawTimeStamp, (char *)ctime(&currTime));
    	strncpy (timeStamp, rawTimeStamp, (strlen(rawTimeStamp) - 1));
	mstring currentTime = timeStamp;
	if (currentTime.wPos(searchMonth()) && currentTime.wPos(searchYear()))
		statingCurrentMonth = TRUE;
	
	surItemNames.delimiter(",");
	int numWords = surItemNames.wcount();
	int	totalSurveys = 0;
	int 	totalSurveysYTD = 0;
	for (int i = 0; i < numWords; i++)
		surveyItem[i].name = surItemNames.parse(",");

	FILE *inptr;
        mstring fileName = "/opt/docs/services/IS/helpdesk/survey_stats/";
	fileName += custName();
	fileName += "_";
        fileName += month;
        fileName += year;
        fileName += ".html";
	struct stat statbuff;
 
	if (stat(fileName, &statbuff) || statingCurrentMonth) // check to see if the file exists
	{
		int dateCvt = FALSE;
		int sMonth = 0;
		int cMonth = 0;
		fstream outs(fileName, ios::out);
		while(in.getline(buffer, (BUFSIZ * 4 - 1))) 
		{
			if (! dateCvt )
			{
				dateCvt = TRUE;
				if (strstr("Jan", searchMonth()))
					sMonth = 1;
				else if (strstr("Feb", searchMonth()))
					sMonth = 2;
				else if (strstr("Mar", searchMonth()))
					sMonth = 3;
				else if (strstr("Apr", searchMonth()))
					sMonth = 4;
				else if (strstr("May", searchMonth()))
					sMonth = 5;
				else if (strstr("Jun", searchMonth()))
					sMonth = 6;
				else if (strstr("Jul", searchMonth()))
					sMonth = 7;
				else if (strstr("Aug", searchMonth()))
					sMonth = 8;
				else if (strstr("Sep", searchMonth()))
					sMonth = 9;
				else if (strstr("Oct", searchMonth()))
					sMonth = 10;
				else if (strstr("Nov", searchMonth()))
					sMonth = 11;
				else if (strstr("Dec", searchMonth()))
					sMonth = 12;
			}
			line = buffer;
			mstring tempLine = line();
			date = tempLine.parse("\t");
			mstring dateCpy = date();
			dateCpy.parse(" ");
			mstring currMonth = dateCpy.parse(" ");
			if (strstr("Jan", currMonth()))
                                cMonth = 1;
                        else if (strstr("Feb", currMonth()))
                                cMonth = 2;
                        else if (strstr("Mar", currMonth()))
                                cMonth = 3;
                        else if (strstr("Apr", currMonth()))
                                cMonth = 4;
                        else if (strstr("May", currMonth()))
                                cMonth = 5;
                        else if (strstr("Jun", currMonth()))
                                cMonth = 6;
                        else if (strstr("Jul", currMonth()))
                                cMonth = 7;
                        else if (strstr("Aug", currMonth()))
                                cMonth = 8;
                        else if (strstr("Sep", currMonth()))
                                cMonth = 9;
                        else if (strstr("Oct", currMonth()))
                                cMonth = 10;
                        else if (strstr("Nov", currMonth()))
                                cMonth = 11;
                        else if (strstr("Dec", currMonth()))
                                cMonth = 12;


			// cout << "SearchMonth: " << date.wPos(searchMonth()) << "<BR>" << endl;
			// cout << "SearchYear: " << date.wPos(searchYear())<< "<BR>"  << endl;
			if (date.wPos(searchMonth()) && date.wPos(searchYear()))
			{
				totalSurveys++;	
				line.parse("\t"); // Date
				line.parse("\t"); // IP Adress
				line.parse("\t"); // First Name
				line.parse("\t"); // Last Name
				line.parse("\t"); // ESC technicians name
				line.parse("\t"); // Location
				line.parse("\t"); // Ticket #
				addValue(line.parse("\t"), &surveyItem[0]); // stat 1
				addValue(line.parse("\t"), &surveyItem[1]); // stat 2
				addValue(line.parse("\t"), &surveyItem[2]); // stat 3
				addValue(line.parse("\t"), &surveyItem[3]); // stat 4
				addValue(line.parse("\t"), &surveyItem[4]); // stat 5
				addValue(line.parse("\t"), &surveyItem[5]); // stat 6
				addValue(line.parse("\t"), &surveyItem[6]); // stat 7
				addValue(line.parse("\t"), &surveyItem[7]); // stat 8
				addValue(line.parse("\t"), &surveyItem[8]); // stat 9
				addValue(line.parse("\t"), &surveyItem[9]); // stat 10
				addValue(line.parse("\t"), &surveyItem[10]); // stat 11
				addValue(line.parse("\t"), &surveyItem[11]); // stat 12
	
				mstring token = line.parse("\t"); // comment 
		
				// outs.flush();
			}
			line.parse(NULL);
			if (date.wPos(searchYear()) && (cMonth <= sMonth))
			{
				totalSurveysYTD++;	
				// cout << "currMonth: " << currMonth <<  "searchMonth: " << searchMonth << endl;
				// cout << "Date: " << date << "cMonth: " << cMonth << " <= " << "sMonth: " << sMonth << endl;
				// cout << "Search year: " << searchYear() << " is at pos: " << date.wPos(searchYear());
				line.parse("\t"); // Date
				line.parse("\t"); // IP Adress
				line.parse("\t"); // First Name
				line.parse("\t"); // Last Name
				line.parse("\t"); // ESC technicians name
				line.parse("\t"); // Location
				line.parse("\t"); // Ticket #
				addValue(line.parse("\t"), &surveyItemYTD[0]); 
				addValue(line.parse("\t"), &surveyItemYTD[1]); 
				addValue(line.parse("\t"), &surveyItemYTD[2]); 
				addValue(line.parse("\t"), &surveyItemYTD[3]); 
				addValue(line.parse("\t"), &surveyItemYTD[4]); 
				addValue(line.parse("\t"), &surveyItemYTD[5]); 
				addValue(line.parse("\t"), &surveyItemYTD[6]); 
				addValue(line.parse("\t"), &surveyItemYTD[7]); 
				addValue(line.parse("\t"), &surveyItemYTD[8]); 
				addValue(line.parse("\t"), &surveyItemYTD[9]); 
				addValue(line.parse("\t"), &surveyItemYTD[10]); 
				addValue(line.parse("\t"), &surveyItemYTD[11]); 
	
				mstring token = line.parse("\t"); // comment 
		
				// outs.flush();
			}
		}
		// cout << "totalSurveys: " << totalSurveys << endl;
		if (totalSurveys)
		{
			int i;
			for (i = 0; i < 12; i++)
			{
				YTD = YTD + surveyItemYTD[i].total;
				surveyItem[i].perrate_1 = (surveyItem[i].rate_1/surveyItem[i].total) * 100;
				surveyItem[i].perrate_2 = (surveyItem[i].rate_2/surveyItem[i].total) * 100;
				surveyItem[i].perrate_3 = (surveyItem[i].rate_3/surveyItem[i].total) * 100;
				surveyItem[i].perrate_4 = (surveyItem[i].rate_4/surveyItem[i].total) * 100;
				surveyItem[i].perrate_5 = (surveyItem[i].rate_5/surveyItem[i].total) * 100;

				surveyItemYTD[i].perrate_1 = (surveyItemYTD[i].perrate_1/YTD) * 100;
				surveyItemYTD[i].perrate_2 = (surveyItemYTD[i].perrate_2/YTD) * 100;
				surveyItemYTD[i].perrate_3 = (surveyItemYTD[i].perrate_3/YTD) * 100;
				surveyItemYTD[i].perrate_4 = (surveyItemYTD[i].perrate_4/YTD) * 100;
				surveyItemYTD[i].perrate_5 = (surveyItemYTD[i].perrate_5/YTD) * 100;
				rate_1_YTD = rate_1_YTD + surveyItemYTD[i].rate_1;
				rate_2_YTD = rate_2_YTD + surveyItemYTD[i].rate_2;
				rate_3_YTD = rate_3_YTD + surveyItemYTD[i].rate_3;
				rate_4_YTD = rate_4_YTD + surveyItemYTD[i].rate_4;
				rate_5_YTD = rate_5_YTD + surveyItemYTD[i].rate_5;
			}
			
			// cout << "YTD total: " << YTD << "<BR>" << endl;
			// cout << "YTD rate total: " << YTD << "<BR>" << endl;
			// cout << "YTD rate 1: " << rate_1_YTD << "<BR>\n";
			// cout << "YTD rate 2: " << rate_2_YTD << "<BR>\n";
			// cout << "YTD rate 3: " << rate_3_YTD << "<BR>\n";
			// cout << "YTD rate 4: " << rate_4_YTD << "<BR>\n";
			// cout << "YTD rate 5: " << rate_5_YTD << "<BR>\n";
			rate_1_YTD = rate_1_YTD/YTD * 100;
			rate_2_YTD = rate_2_YTD/YTD * 100;
			rate_3_YTD = rate_3_YTD/YTD * 100;
			rate_4_YTD = rate_4_YTD/YTD * 100;
			rate_5_YTD = rate_5_YTD/YTD * 100;
			
			cout << "<HTML>	\n <HEAD>\n <TITLE>\n" << "Help Desk Survey Statistics for " << custName() << ": " << month << " " << year << "</TITLE>\n </HEAD>\n";
			outs << "<HTML>	\n <HEAD>\n <TITLE>\n" << "Help Desk Survey Statistics for " << custName() << ": " << month << " " << year << "</TITLE>\n </HEAD>\n";

			cout << "<BODY BGCOLOR=\"#FFFFFF\"> \n <CENTER>\n";
			outs << "<BODY BGCOLOR=\"#FFFFFF\"> \n <CENTER>\n";

			cout << "<BR><H2><IMG SRC=/images/teklogo.gif> Help Desk Survey Statistics for " << custName() << ": " << month << " " << year << "</H2>\n";
			outs << "<BR><H2><IMG SRC=/images/teklogo.gif> Help Desk Survey Statistics for " << custName() << ": " << month << " " << year << "</H2>\n";
			cout << "<TABLE BORDER=\"1\" WIDTH=\"90%\">\n <TR> <TH BGCOLOR=\"#000099\"><FONT COLOR=\"#FFFFFF\">QUESTIONS:</FONT></TH> <TH BGCOLOR=\"#FFFFFF\">Rating 5 </TH><TH BGCOLOR=\"#FFFFFF\">Rating 4</TH> <TH BGCOLOR=\"#FFFFFF\">Rating 3</TH> <TH BGCOLOR=\"#FFFFFF\">Rating 2</TH> <TH BGCOLOR=\"#FFFFFF\">Rating 1</TH></TR> \n <TR><TH COLSPAN=6 BGCOLOR=\"#3366FF\">Specialist</TH></TR>\n";
			outs << "<TABLE BORDER=\"1\" WIDTH=\"90%\">\n <TR> <TH BGCOLOR=\"#000099\"><FONT COLOR=\"#FFFFFF\">QUESTIONS:</FONT></TH> <TH BGCOLOR=\"#FFFFFF\">Rating 5 </TH><TH BGCOLOR=\"#FFFFFF\">Rating 4</TH> <TH BGCOLOR=\"#FFFFFF\">Rating 3</TH> <TH BGCOLOR=\"#FFFFFF\">Rating 2</TH> <TH BGCOLOR=\"#FFFFFF\">Rating 1</TH></TR> \n <TR><TH COLSPAN=6 BGCOLOR=\"#3366FF\">Specialist</TH></TR>\n";

			for (i= 0; i< 8; i++) 
			{
				printRow(surveyItem[i]);
				printRow(surveyItem[i], outs);
			}
			cout << "<TR><TH COLSPAN=6 BGCOLOR=\"#3366FF\">Help Desk</TH></TR>\n";
			outs << "<TR><TH COLSPAN=6 BGCOLOR=\"#3366FF\">Help Desk</TH></TR>\n";

			for (i= 8; i< 12; i++) 
			{
				printRow(surveyItem[i]);
				printRow(surveyItem[i], outs);
			}
			cout << "<TR><TH COLSPAN=6 BGCOLOR=\"#3366FF\"><FONT COLOR=\"#FFFFFF\">";
			outs << "<TR><TH COLSPAN=6 BGCOLOR=\"#3366FF\"><FONT COLOR=\"#FFFFFF\">";

			cout << setiosflags(ios::fixed);
			outs << setiosflags(ios::fixed);

			cout << setprecision(0);
			outs << setprecision(0);

			cout << "<TR> <TD BGCOLOR=\"#000099\"><FONT COLOR=\"#FFFFFF\">";
			outs << "<TR> <TD BGCOLOR=\"#000099\"><FONT COLOR=\"#FFFFFF\">";

			cout <<  "YTD";
			outs <<  "YTD";

			cout <<  "</FONT></TD> <TH BGCOLOR=\"#FFFFFF\">";
			outs <<  "</FONT></TD> <TH BGCOLOR=\"#FFFFFF\">";

			cout <<  rate_5_YTD;
			outs <<  rate_5_YTD;

			cout <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
			outs <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";

			cout <<  rate_4_YTD;
			outs <<  rate_4_YTD;

			cout <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
			outs <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";

			cout <<  rate_3_YTD;
			outs <<  rate_3_YTD;

			cout <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
			outs <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";

			cout <<  rate_2_YTD;
			outs <<  rate_2_YTD;

			cout <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
			outs <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";

			cout <<  rate_1_YTD;
			outs <<  rate_1_YTD;

			cout <<  "%</TH></TR>\n";
			outs <<  "%</TH></TR>\n";

			cout << "<TR><TH COLSPAN=3 BGCOLOR=\"#3366FF\"><FONT COLOR=\"#FFFFFF\">Total Surveys Received for " << searchMonth() << ": " << totalSurveys << "</TH>";
			outs << "<TR><TH COLSPAN=3 BGCOLOR=\"#3366FF\"><FONT COLOR=\"#FFFFFF\">Total Surveys Received for " << searchMonth() << ": " << totalSurveys << "</TH>";
			cout << "<TH COLSPAN=3 BGCOLOR=\"#3366FF\"><FONT COLOR=\"#FFFFFF\">Total Surveys Received for " << searchYear() << ": "<< totalSurveysYTD << "</TH></TR>";
			outs << "<TH COLSPAN=3 BGCOLOR=\"#3366FF\"><FONT COLOR=\"#FFFFFF\">Total Surveys Received for " << searchYear() << ": "<< totalSurveysYTD << "</TH></TR>";

			// <TD BGCOLOR=\"#FFFFFF\">&nbsp</TD><TD BGCOLOR=\"#FFFFFF\">&nbsp</TD><TD BGCOLOR=\"#FFFFFF\">&nbsp</TD><TD BGCOLOR=\"#FFFFFF\">&nbsp</TD><TH BGCOLOR=\"#FFFFFF\">";


			cout << "</FONT></TH><TR>\n";
			outs << "</FONT></TH><TR>\n";

			cout << "</TABLE>\n</BODY>\n</HTML>\n";
			outs << "</TABLE>\n</BODY>\n</HTML>\n";
	
			outs.flush();
			outs.close();
			in.close();
		} // end of if totalSurveys
		else
		{
			cout << "<HTML>	\n <HEAD>\n <TITLE>\n</TITLE>\n </HEAD>\n <BODY BGCOLOR=\"#FFFFFF\">";
			cout << "<BR><BR><BR><CENTER><H2><IMG SRC=/images/teklogo.gif> Sorry, There is no survey data for: " << month << " " << year << "</H2></CENTER>\n";	
			cout << "</BODY>\n</HTML>\n";
			unlink(fileName());
		}

	} // end of check to see if file exists
	else
	{
		fstream 	nin(fileName, ios::in);
        	// printf("Content-type: text/html%c%c",10,10);
		while(nin.getline(buffer, (BUFSIZ * 4 - 1))) 
		{
			cout << buffer << "\n";
			cout.flush();
       		}
	}
}
void printRow(surveyitem item)
{
        cout << setiosflags(ios::fixed);
        cout << setprecision(0);
        cout << "<TR> <TD BGCOLOR=\"#000099\"><FONT COLOR=\"#FFFFFF\">";
        cout <<  item.name;
        cout <<  "</FONT></TD> <TH BGCOLOR=\"#FFFFFF\">";
        cout <<  item.perrate_5;
        cout <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
        cout <<  item.perrate_4;
        cout <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
        cout <<  item.perrate_3;
        cout <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
        cout <<  item.perrate_2;
        cout <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
        cout <<  item.perrate_1;
        cout <<  "%</TH></TR>\n";
}

void printRow(surveyitem item, fstream &outs)
{
	outs << setiosflags(ios::fixed);
	outs << setprecision(0);
	outs << "<TR> <TD BGCOLOR=\"#000099\"><FONT COLOR=\"#FFFFFF\">";
	outs <<  item.name;
	outs <<  "</FONT></TD> <TH BGCOLOR=\"#FFFFFF\">";
	outs <<  item.perrate_5;
	outs <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
	outs <<  item.perrate_4;
	outs <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
	outs <<  item.perrate_3;
	outs <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
	outs <<  item.perrate_2;
	outs <<  "%</TH><TH BGCOLOR=\"#FFFFFF\">";
	outs <<  item.perrate_1;
	outs <<  "%</TH></TR>\n";
}
void addValue(mstring value, surveyitem *item)
{
	float tempValue = 0.0;
	int ivalue = atoi(value()); 
	// cout << item->name << ivalue << "\n"; 
	item->total += 1;
	switch (ivalue)
	{
		case 1:
			item->rate_1 += 1;
			tempValue = (item->rate_1/item->total) * 100;
			// cout << tempValue << "\n";
			// item->perrate_1 = tempValue;
		break;
		case 2:
			item->rate_2 += 1;
			tempValue = (item->rate_2/item->total) * 100;
			// cout << tempValue << "\n";
			// item->perrate_2 = tempValue;
		break;
		case 3:
			item->rate_3 += 1;
			tempValue = (item->rate_3/item->total) * 100;
			// cout << tempValue << "\n";
			// item->perrate_3 = tempValue;
		break;
		case 4:
			item->rate_4 += 1;
			tempValue = (item->rate_4/item->total) * 100;
			// cout << tempValue << "\n";
			// item->perrate_4 = tempValue;
		break;
		case 5:
			item->rate_5 += 1;
			tempValue = (item->rate_5/item->total) * 100;
			// cout << tempValue << "\n";
			// item->perrate_5 = tempValue;
		break;
	}
}
