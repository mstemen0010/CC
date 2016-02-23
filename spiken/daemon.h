/*
** File: daemon.h SCCS 1.2 - 8/4/95
**
** Author:   Matthew Stemen
**
**
** 
** Created:  19 June 1995
**  
**
**
** Purpose: Monitors and reports any and all remote logins to the 
**          host it is run from.  This activity is reported either 
**          using Sound, Images(icons), and Tabular reports or any
**          combination thereof.
*/


#include <fstream.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>


#include<sys/types.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include<sys/file.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/unistd.h>
#include "mstring.h"





#ifndef DAEMON_H
#define DAEMON_H

#ifndef TRUE
	#define 	TRUE	1
	#define		FALSE	! TRUE
#endif

class daemon 
{
	public:
		     	    	daemon();
				virtual		~daemon();
		     	void	start(const int ignsigcld = 1);
	protected:
		virtual void 	run(void) = 0 ; // pure
				msting  usrName();
				void	usrName(mstring newName );
				mstring	usrHome();
				void	usrHome(mstring newHome);
				mstring daemonName();
				void	daemonName(mstring newdeamonName);
				mstring msg();
				void	msg(mstring newMsg);

				signed	timerVal();
				void	timerVal(const signed newTime);
				


		virtual void 	logMsg();
		virtual int 	mailUser(mstring message);
		virtual int 	makeRounds(void) = 0 ; // pure
	    virtual	fstream *	logFile() = 0; // pure
		virtual	void	logFile(fstream *newLog) = 0; // pure
		virtual	mstring logFileName() = 0; // pure
		virtual	void	logFileName(mstring newLogName) = 0; // pure

				unsigned	_timerVal;
				mstring _usrName;
				mstring _usrHome;
				fstream	*_logFile;
				mstring _logFileName;
				mstring _msg;
				mstring _daemonName;



	private:
				SIG_PF	sig_child();

};
#endif

/* inline methods */

inline  mstring   daemon::daemonName(){ return _daemonName;}
inline  void	daemon::daemonName(mstring newdaemonName )
{ 
	_daemonName =  newdaemonName;
}
inline  mstring    daemon::msg(){ return _msg;}
inline  void	daemon::msg(mstring newMsg )
{ 
	_msg = newMsg;
}
inline	mstring	daemon::usrName(){return _usrName;}

inline	void	daemon::usrName(mstring newName)
{	
	_usrName = newName;
}
inline	mstring	daemon::usrHome(){return _usrHome;}
inline	void	daemon::usrHome(mstring newHome)
{	
	_usrHome = newHome;
}
inline	signed	daemon::timerVal(){ return _timerVal;}
inline	void	daemon::timerVal(const signed newTime){ _timerVal = newTime;}
