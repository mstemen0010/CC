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

#define 	HASHED_AS_STRING	0
#define		HASHED_AS_NUMBER	1
#define		NOT_HASHED			2 

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
			table(int newSize, mstring fDelimiter, int kField);
			table(mstring  filename, mstring fDelimiter, int kField);
			table(fstream  fs, mstring fDelimiter, int kField, int hashType);
			table(fstream  *fs, mstring fDelimiter, int kField, int hashType);

			table(mstring * filename, mstring fDelimiter, int kField);
			table(mstring * filename, mstring fDelimiter, int kField, int hashType);
			table(mstring filename, mstring fDelimiter, int kField, int hashType);

			table(int newSize);
			table(mstring  filename);
			table(mstring filename, int hashType);
			table(fstream fs, int hashType);
			table(fstream *fs, int hashType);
			table(mstring * filename);
			table(mstring * filename, int hashType);
			~table();


			void	keyField(int newKeyField){ _keyField = newKeyField; }
			int		keyField(){ return _keyField; }
			void 	fieldDelimiter(mstring newDelimiter) { _fieldDelimiter = newDelimiter;}
			mstring fieldDelimiter() { return _fieldDelimiter; }
			
			int	find(mstring  key);
			mstring get(mstring  key, int field);
			mstring get(int index);
			mstring get();
			mstring get(int elementNum, mstring delimiter);
			int		add(mstring item);
			int		numElements();

	private:
			unsigned 	long	makeHash(mstring  value);
			int		chain(tableElement * item, mstring   value);
			int   	numLines(mstring fileName);
			int   	numLines(fstream fs);
			int   	numLines(fstream *fs);
			int		build(fstream & file);
			int		build(fstream * file);
			// numLines();


			int		arraySize;
			int		_numItems;
			int		_numLines;
			int		modValue;
			int		size;
			mstring _fieldDelimiter;
			int		_keyField;
			int		delimited;
			int 	_hashType;

			struct tableElement**	tbl;

};

inline table::table(){;}
inline int table::numElements(){ return _numItems;}

#endif

