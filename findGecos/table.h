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
#include "tableCell.h"
#include "tableRow.h"
// #include <stream.h>

#ifndef TRUE
	#define	TRUE	1
	#define FALSE	! TRUE
#endif


class table
{
	public:
			table();
			table(int newSize);
			table(int newSize, int hashed);
			// table(mstring & filename, int hashed);
			table(mstring * filename, int hashed);
			table(mstring  filename, int hashed);
			table(mstring  filename, int hashField, mstring delimiter);
			table(mstring  filename, int hashField, mstring delimiter, int soundexed);
			
			~table();

			void		append(mstring newValue);
			int		find(mstring target);
			int		findNoCase(mstring target);
			mstring		getRow(int index);
			int		getRowCount(int index);
			mstring		get(mstring target);
			mstring		getAll(mstring target);
			mstring		getAllNoCase(mstring target, int part);
			mstring		getNoCase(mstring target);
			mstring		getCnNoCase(mstring target);
			mstring		getAllCnNoCase(mstring target);
			mstring		search(mstring target);
			int		numRows();
			int		hashed();
			void		deleteRow(int index);
			void		fieldDelimit(mstring newDelim);
			mstring 	fieldDelimit();
			int		soundexAcc();
			void		soundexAcc(int newAcc);
			int		hashField();
			void		hashField(int newField);

	private:
			mstring 	getField(mstring row, int field, mstring delimiter);
			unsigned 	long	makeHash(mstring  value);
			int   		numLines(mstring fileName);
			void		build(fstream& file);
			void		hashed(int value);
			void		soundexed(int value);
			int 		soundexed();
			// numLines();


			int		arraySize;
			int		_potentialNumRows;
			int		_currentNumRows;
			int		_actualNumRows;
			int		modValue;
			int		size;
			int		_hashed;
			int		_hashField;
			int		_soundexed;
			int		_soundexAcc;
			mstring		_fieldDelimit;

			tableRow**	tbl;

};

inline table::table(){;}
inline int table::numRows(){ return _currentNumRows;}
inline void table::hashed(int value) {_hashed = value;}
inline int table::hashed() {return _hashed;}
inline void table::soundexed(int value) {_soundexed = value;}
inline int table::soundexed() {return _soundexed;}
inline void table::fieldDelimit(mstring newDelim){_fieldDelimit = newDelim();}
inline mstring table::fieldDelimit(){return _fieldDelimit();}
inline int table::soundexAcc(){return _soundexAcc;}
inline void table::soundexAcc(int newAcc){_soundexAcc = newAcc;}
inline int table::hashField(){return _hashField;}
inline void table::hashField(int newField){_hashField = newField;}

#endif

