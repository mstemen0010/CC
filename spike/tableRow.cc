#include "tableRow.h"
#include "tableCell.h"


tableRow::tableRow()
{
	_empty = 1;
	_numCells = 0;
	_cells = (tableCell **)new tableCell();
	_cells[0] = (tableCell *) new tableCell("");
}
tableRow::~tableRow()
{
	
	for (int i = 0; i < _numCells; i++)
		delete _cells[i];
}
void tableRow::appendCell()
{

      if (_numCells > 0)
        {
                tableCell **newRow = (tableCell **)new tableCell[_numCells + 1];
                for (int i = 0; i < _numCells; i++)
                {
                        newRow[i] = (tableCell *)new tableCell("");
                        mstring tVal = _cells[i]->value();
                        int tDel = _cells[i]->deleted();
                        newRow[i] = new tableCell(tVal());
                        newRow[i]->deleted(tDel);
                }

                newRow[i] = (tableCell *) new tableCell("EMPTY");
                delete [] _cells;
                _cells = (tableCell **)new tableCell[_numCells + 1];
                for ( i = 0; i < _numCells + 1; i++)
                {
                        mstring tVal = newRow[i]->value();
                        int tDel = newRow[i]->deleted();
                        _cells[i] = (tableCell *)new tableCell("");
                        _cells[i]->value(tVal);
                        _cells[i]->deleted(tDel);

                }
        }
        else
        {

		_cells[0]->value("EMTPY");
        }

	/*
	if (_numCells > 0)
	{
		tableCell **newRow = (tableCell **)new tableCell[_numCells + 1];
		for (int i = 0; i < _numCells; i++)
		{
			newRow[i] = new tableCell(_cells[i]);
		}
		
		tableCell *newCell = new tableCell();
		newRow[i + 1] = newCell;
		delete _cells;
		_cells = newRow;
	}
	*/
	_empty = false;
	_numCells++;
}
void tableRow::appendCell(mstring val)
{
 	int cellAdded = 0;
       if (_numCells > 0)
        {
		tableCell **newRow = (tableCell **)new tableCell[_numCells + 1];
                for (int i = 0; i < _numCells; i++)
		{	
			newRow[i] = (tableCell *)new tableCell("");
			mstring tVal = _cells[i]->value();
			int tDel = _cells[i]->deleted();
			newRow[i] = new tableCell(tVal());
			newRow[i]->deleted(tDel);
		}

                newRow[i] = (tableCell *) new tableCell(val());
                delete [] _cells;
		_cells = (tableCell **)new tableCell[_numCells + 1];
                for ( i = 0; i < _numCells + 1; i++)
		{
			mstring tVal = newRow[i]->value();
			int tDel = newRow[i]->deleted();
			_cells[i] = (tableCell *)new tableCell("");
			_cells[i]->value(tVal);
			_cells[i]->deleted(tDel);

		}
        }
        else
        {
		
		_cells[0]->value(val);
        }
        _empty = false;
        _numCells++;
}
void tableRow::cellValue(int cellNum, mstring newCellVal)
{
	if (cellNum < _numCells)
		_cells[cellNum]->value(newCellVal);
}
mstring tableRow::cellValue(int cellNum)
{
	if (cellNum < _numCells)
		return _cells[cellNum]->value();
}
int tableRow::find(mstring target)
{
	int found = 0;
	for (int i = 0; i < _numCells; i++)
	{

		mstring tval = _cells[i]->value();
		if (tval == target)
		{
			found = 1;
			break;
		}
	}

	return (found);
}
int tableRow::findNoCase(mstring target)
{
        int found = 0;
        for (int i = 0; i < _numCells; i++)
        {

                mstring tval = _cells[i]->value();
                if (tval.upper() == target.upper())
                {
                        found = 1;
                        break;
                }
        }                                                   

        return (found);
}
mstring tableRow::getAll(mstring target)
{
        mstring retStr;
        for (int i = 0; i < _numCells; i++)
        {

                mstring tval = _cells[i]->value();
                if (tval == target)
                {
                        retStr += tval();
			retStr += "\t";
                }
        }         

        return (retStr);
}

mstring tableRow::get(mstring target)
{
	mstring retStr;
        for (int i = 0; i < _numCells; i++)
        {

                mstring tval = _cells[i]->value();
                if (tval == target)
                {
			retStr = tval();
                        break;
                }
        }                                                   

        return (retStr);
}
mstring tableRow::getNoCase(mstring target)
{
        mstring retStr;
        for (int i = 0; i < _numCells; i++)                 
        {

                mstring tval = _cells[i]->value();
                if (tval.upper() == target.upper())
                {
                        retStr = tval();
                        break;
                }
        }
                                                            
        return (retStr);
}
mstring tableRow::getAllNoCase(mstring target, int targetField, mstring delimiter, int part)
{
        mstring retStr, pStr;
        for (int i = 0; i < _numCells; i++)
        {

                mstring tval = _cells[i]->value();
                tval = tval.upper();
		pStr =  tval.parse(delimiter());
                int count = 1;
                while (count++ != targetField)
                        pStr = tval.parse(delimiter());
                mstring tartemp = pStr.upper();
                count = 1;
		if (part)
		{
			pStr =  tartemp.parse(" "); 
                	while (count++ != part)
                        	pStr = tartemp.parse(" ");
                	tartemp = pStr.upper();
		}
		
		pStr = target.upper();
                if (pStr == tartemp)
                {
                        retStr += tval();
                        retStr += "\t";
                }
        }

        return (retStr);
}

mstring tableRow::getAllNoCase(mstring target)
{
        mstring retStr;
        for (int i = 0; i < _numCells; i++)
        {

                mstring tval = _cells[i]->value();
		tval = tval.upper();
		mstring tartemp = target.upper();
                if (tval.upper() == tartemp.upper())
                {
                        retStr += tval();
                        retStr += "\t";
                }
        }

        return (retStr);
}

mstring tableRow::getCnNoCase(mstring target)
{
        mstring retStr;
        for (int i = 0; i < _numCells; i++)
        {

                mstring tval = _cells[i]->value();
                tval = tval.upper();
                mstring tartemp = target.upper();
                if (strstr(tval, tartemp()))
                {
                        retStr += tval();
                        retStr += "\t";
			break;
                }
        }

        return (retStr);
}

mstring tableRow::getAllCnNoCase(mstring target)
{
        mstring retStr;
        for (int i = 0; i < _numCells; i++)
        {

                mstring ttval = _cells[i]->value();
		mstring tval = ttval();
                tval = tval.upper();
		mstring tartemp = target.upper();
                if (strstr(tval, tartemp()))
                {
                        retStr += tval();
                        retStr += "\t";
                }
        }

        return (retStr);
}


mstring tableRow::getAllSd(mstring target, int allowance, int field, mstring delimiter)
{
        mstring retStr;
	int	soundLike = 0;
        mstring pStr = "";


        for (int i = 0; i < _numCells; i++)
        {

                mstring tval = _cells[i]->value();
        	pStr =  tval.parse(delimiter); //change this later
       		int count = 1;
        	while (count++ != field)
                	pStr = tval.parse(delimiter);
		soundLike = pStr.sndLike(target());
		pStr.parse(NULL);
                if (soundLike == allowance)
                {
                        retStr += tval();
                        retStr += "\t";
                }
        }

        return (retStr);
}

mstring tableRow::get()
{
	mstring retStr; 
	for(int i = 0; i < _numCells; i++)
	{
		retStr += _cells[i]->value();
		retStr += "\t";
	}
	return (retStr);
}


