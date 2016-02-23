/*
** File: %M% SCCS %I% - %G% 
**
** Author:   Matthew Stemen
**
**
**
** Created:  07 March 1996
**
**
**
** Purpose: Class designed to aid with editing HTML code and creating HTML
**          code by offering a series of tool built into the class
**          
**          
*/
#ifndef HTML_EDIT_H   
#define HTML_EDIT_H   

#include "table.h"
#include "mstring.h"

#define 	TREAT_AS_LIST	0
#define		TREAT_AS_ONE	1
#define		ALL_OCCURRENCES 	0
#define		FIRST_OCCURRENCE	1



class htmlE // Hyper Text Markup Language Editor 
{

	public:
				htmlE(); // assumes reading from stdin(cin) and writing to stdout(cout)
				htmlE(mstring inFileName);  // assume writing to stdout(cout)
				htmlE(mstring inFileName, mstring outFileName); 
				~htmlE();

		void	paraAdd(int numToDo, int lineBreakCountPerLine);
		void 	listAdd(int lineBreakCountPerLine, int numbered);
		void	mailToAdd(int numOfOccurrencesToReplace);
		void	stripHtml();
		void 	stripDlbSpace();
		// void	publistAdd(mstring Title, int numbered);
		void    indent(int numberOfIndents);

	private:

		table	*_rawText;
		table	*_htmlText;
		fstream *inS;
		fstream *outS;
};

			
#endif
