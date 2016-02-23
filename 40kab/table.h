/*
** File: table.h SCCS 1.2 - 8/4/95
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

#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <fstream.h>
#include "mstring.h"
// #include <stream.h>

#ifndef TRUE
	#define	TRUE	1
	#define FALSE	! TRUE
#endif


struct	tableElement 
{	
	mstring					value;
	struct  tableElement	*next;
	struct	tableElement	*first;
};

class table
{
	public:
			table();
			table(int newSize);
			table(mstring & filename);
			table(mstring * filename);
			~table();

			int	find(mstring & key);
			mstring get(mstring & key);
			mstring get(int index);
			mstring get();
			mstring get(int elementNum, mstring &delimiter);
			int		add(mstring &item);
			int		numElements();

	private:
			unsigned 	long	makeHash(mstring & value);
			int		chain(tableElement * item, mstring &  value);
			int   	numLines(mstring &fileName);
			int		build(fstream& file);
			// numLines();


			int		arraySize;
			int		_numItems;
			int		_numLines;
			int		modValue;
			int		size;

			struct tableElement**	tbl;

};

inline table::table(){;}
inline int table::numElements(){ return _numItems;}

#endif

