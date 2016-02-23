#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <fstream.h>
#include "mstring.h"

#ifndef TRUE
    #define TRUE    1
    #define FALSE   ! TRUE
#endif

struct  pageLine
{
	mstring	 value;
};

class subPage
{
	public:
		subPage(int numLines);
		~subPage();

		// access methods
		void addLine(mstring line);
		mstring lineAt(int index);
		// to do:::: int lineAt(mstring key);
		// to do:::: deleteLine(int index);
		// to do:::: deleteLine(mstring key);
		int	numLines();
		
	private:
				int			_numLines;
		struct	pageLine** 	_content;
				int			_index;
}
inline	void subPage::addLine(mstring line){ _content[_index]->value =
line; _index++; _numLines++;}
inline 	mstring	subPage::lineAt(int index) {return _content[index]->value;}
inline int numLines(){return _numLines;}
		
