#include <stdio.h>
#include <stdlib.h>
#include <fstream.h>
#include <memory.h>
#include <sys/types.h>
#include <time.h>
#include "mstring.h"

char *makeword(char *line, char stop);
char *fmakeword(FILE *f, char stop, int *len);
char x2c(char *what);
void unescape_url(char *url);
void plustospace(char *str);
mstring timeStampFile = "/opt/users/cgi/bin/pageItTimeStamp";

void pageIt(char *emailNameTo, char *emailNameFrom, char *message)
{

        time_t  currTime = time(NULL);
	time_t  fileTime = 0;
        char timeStamp[BUFSIZ] = "";
        fstream fname(timeStampFile, ios::in|ios::out);
	char inputs[BUFSIZ] = "";
        int stampFound = 0;
        mstring workStr;
	if (fname.good())
	{
		// fname.getline(inputs, BUFSIZ -1 );
		fname >> inputs;
		// cout << "Got here<BR>" << endl;
		if (inputs)
			fileTime = atol(inputs);
			
	}
	// cout << "Current time: " << currTime << "<BR>";
	// cout << "File time: " << fileTime << "<BR>";
	if ((abs(currTime - fileTime)) > 60 ) // 1 minute
	{
		
		cout << "sending Page...<BR>" << endl;
		fname.seekg(0);
		fname << currTime << endl;
	        fname.close();

		FILE *ptr;
       		mstring cmd = "/usr/lib/sendmail";
	        cmd += " ";
	        cmd += emailNameTo;
	        mstring mailMessage = "Subject: ";
	        mailMessage += "Message from: " ;
	        mailMessage += emailNameFrom;
	        mailMessage += "\n";
	        mailMessage += "From: ";
	        mailMessage += emailNameFrom;
	        mailMessage += "\n";
	        mailMessage += "To: \"";
	        mailMessage += emailNameTo;
	        mailMessage += "\"\n";
	        mailMessage += "Content-Type: text/plain; charset=us-ascii\n";
	        mailMessage += "Content-Transfer-Encoding: 7bit\n\n";
	        mailMessage += "\n";
	        mailMessage += message;
	 
	        if ((ptr = popen(cmd(), "w")) != NULL)
	        {
	                fprintf(ptr, "%s", mailMessage());
	                // cout << message() << "|" << cmd << endl;
	                pclose(ptr);
    			cout << "<H2>Page was sent</H2>" << endl;
	        }
	        else
	        	printf("Unable to open pipe to %s, cmd");
	}
	else
    		cout << "<H2>Page was already sent</H2>" << endl;
}


main(int argc, char *argv[])
{
  char *orders = getenv("QUERY_STRING");
  char *emailNameToRaw;
  char *emailNameFromRaw;
  char *messageRaw;

  printf("Content-type: text/html%c%c", 10, 10);
  if (!orders) {
    cout << "<h2>Something went wrong with the server, please try again later.</h2>" << endl;
    exit(1);
  }

  makeword(orders, '='); 
    emailNameToRaw = makeword(orders, '&');      
    unescape_url(emailNameToRaw);
    plustospace(emailNameToRaw);
  makeword(orders, '='); 
    emailNameFromRaw = makeword(orders, '&'); 
    unescape_url(emailNameFromRaw);
    plustospace(emailNameFromRaw);
  makeword(orders, '='); 
    messageRaw = makeword(orders, '&'); 
    unescape_url(messageRaw);
    plustospace(messageRaw);

    pageIt(emailNameToRaw, emailNameFromRaw, messageRaw);
}


