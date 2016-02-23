/*
** File: tableRow.h SCCS 1.2 - 8/4/95
**
** Author:   Matthew Stemen
**
**
**
** Created:  19 June 1995
**
**
**
** Purpose:
**
**
**
*/

#ifndef TABLE_ROW_H
#define TABLE_ROW_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <fstream.h>
#include "tableCell.h"
// #include <stream.h>

#ifndef TRUE
        #define TRUE    1
        #define FALSE   ! TRUE
#endif

class   tableRow
{
	public:

		tableRow();
		~tableRow();

		int find(mstring target);
		int findNoCase(mstring target);
		mstring get();
		mstring getAll(mstring target);
		mstring get(mstring target);
		mstring getNoCase(mstring target);
		mstring getCnNoCase(mstring target);
		mstring getAllNoCase(mstring target);
		mstring getAllNoCase(mstring target, int field, mstring delimiter, int part);
		mstring getAllCnNoCase(mstring target);
		mstring getAllSd(mstring target, int allowance, int field, mstring delimiter);
		void appendCell();
		void appendCell(mstring value);
		void deleteCell(int cellNum);
		void cellValue(int cellNum, mstring newCellVal);
		mstring cellValue(int cellNum);
		int	numCells();
		int empty();
		void empty(int newVal);


	private:

		tableCell **_cells;
		int	   _numCells;
		int	   _empty;
};
inline int tableRow::empty(){ return _empty; }
inline void tableRow::empty(int newVal){ _empty = newVal; }
inline int  tableRow::numCells() { return _numCells; }

#endif
