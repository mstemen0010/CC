/*
** File: table.cc SCCS 1.2 - 8/4/95
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


#include "table.h"

mstring table::getField(mstring row, int field, mstring delimiter)
{
	int count = 1;
	mstring retStr = "";
	retStr =  row.parse(delimiter());
	// cout << row << ":" << retStr << endl;
	while (count != field)
	{
		retStr = row.parse(delimiter());
		count++;
	}
	row.parse(NULL);
	return (retStr);
}

table::table(int newSize)
{
	size = newSize;
	_potentialNumRows = newSize;
	_currentNumRows = 0;
	_hashed = false;
	_hashField = 0;
	_soundexed = 0;
	mstring value = "";
	tbl = (tableRow**) new tableRow[size];
	_actualNumRows = newSize;
	for (int i = 0; i <= size; i++)
	{
		tbl[i] = (tableRow *)new tableRow();
		tbl[i]->appendCell();
	}
}

table::table(int newSize, int hashed)
{
	size = newSize;
        _potentialNumRows = newSize;
        _currentNumRows = 0;
        _hashed = false;
        _hashField =  hashed;
        _soundexed = 0;
        mstring value = "";
        tbl = (tableRow**) new tableRow[size];
        _actualNumRows = newSize;
        for (int i = 0; i <= size; i++)
        {
		tbl[i] = (tableRow *)new tableRow();
                tbl[i]->appendCell();
        }
}


table::table(mstring filename, int hashField, mstring delimiter)
{
        _potentialNumRows = numLines(filename);
       	_currentNumRows = 0;
        fstream  fs(filename(), ios::in);
	_hashed = true;
	_fieldDelimit = delimiter();
	_hashField = hashField;
	_soundexed = 0;
	_actualNumRows = 0;
        build(fs);
}

table::table(mstring filename, int hashed)
{
	
	mstring name = filename;
        _potentialNumRows = numLines(filename);
       	_currentNumRows = 0;
       	fstream  fs(filename(), ios::in);
	_hashed = hashed;
	_soundexed = 0;
	_hashField = 0;
	_actualNumRows = 0;
        build(fs);
}


table::table(mstring filename, int hashField, mstring delimiter, int soundexed)
{
        _potentialNumRows = numLines(filename);
        _currentNumRows = 0;
        fstream  fs(filename(), ios::in);
        _hashed = true;
        _fieldDelimit = delimiter();
        _hashField = hashField;
	_soundexed = 1;
	_soundexAcc = 100;
	_actualNumRows = 0;
        build(fs);
}


table::~table()
{
	for (int i = 0; i < _potentialNumRows; i++)
		if (tbl[i])
			delete tbl[i];
}

void table::append(mstring newValue)
{
	int Tkey = _currentNumRows;
	if (hashed())
		Tkey = makeHash(newValue);

	tbl[Tkey]->appendCell(newValue());
	_currentNumRows++;
	if (tbl[Tkey]->numCells() >= 1)
		_actualNumRows++;
}
/*
void table::deleteRow(int index)
{
	tableRow **newTbl =  (tableRow**) new tableRow[_potentialNumRows];
	for (int i = 0; i < _potentialNumRows; i++)
	{
		tableRow *newRow = (tableRow *)new tableRow();
		newTbl[i] = newRow; 
	}
	for (int i = 0; i < _potentialNumRows; i++)
		if (i != index)
			newTbl[i] ;
	_potentialNumRows--;
	tbl = (tableRow**) new tableRow[_potentialNumRows];
	for (int i = 0; i < _potentialNumRows; i++)

}
*/

void table::build (fstream& file) 
{
	mstring			inputs;
	char			buffer[BUFSIZ];
	int             success = TRUE;
	mstring		value = "EMPTY";

	tbl = (tableRow**) new tableRow[_potentialNumRows];
	for (int i = 0; i < _potentialNumRows; i++)
	{
		tableRow *newRow = (tableRow *)new tableRow();
		tbl[i] = newRow; 
	}
	file.seekg(0);
	while(file.getline(buffer, BUFSIZ - 1))
	{
			inputs = (char *)buffer;
			int Tkey = _currentNumRows;
			if (hashed())
			{
				if (_hashField)
				{
					mstring newItem = getField(inputs(), _hashField, _fieldDelimit());
					if (_soundexed)
					{
						mstring sndx = newItem.sndxCalc();
						Tkey = makeHash(sndx);
					}
					else
						Tkey = makeHash(newItem);
				}
				else
					if (_soundexed)
					{
						mstring sndx = inputs.sndxCalc();
						Tkey = makeHash(sndx);
					}
					else
						Tkey = makeHash(inputs);
			}
			tbl[Tkey]->appendCell(inputs());													
			if (tbl[Tkey]->numCells() >= 1)
				_actualNumRows++;
			_currentNumRows++;
	}
}

mstring table::search (mstring item)
{
	mstring retStr;
	for (int i = 0; i < _currentNumRows; i++)
	{
		if (! tbl[i]->empty())
			retStr = tbl[i]->find(item);
		if (retStr.len() > 0)
			break;
	}
	return (retStr);
}

int table::getRowCount(int index)
{
	int count = tbl[index]->numCells();
	return count;
}
mstring table::getRow(int index)
{
	mstring retVal = tbl[index]->get();
	return (retVal);
}

mstring table::getAll (mstring  item)
{
        mstring retStr;
        if (hashed())
        {
                long    tKey = makeHash(item);
                retStr = tbl[tKey]->getAll(item);
        }
        else
        {
                for (int i = 0; i < _currentNumRows; i++)
                {
                        retStr += tbl[i]->getAll(item);
                        // if (retStr.len())
                          //       break;
                }
        }
        return(retStr);
}

mstring table::get (mstring  item)
{
	mstring retStr;
	if (hashed())
	{
		long    tKey = makeHash(item);
		if (_hashField)
		{
			mstring newItem = getField(item(), _hashField, _fieldDelimit());
			tKey = makeHash(newItem);
		}
		else
			tKey = makeHash(item);
		retStr = tbl[tKey]->get(item);
	}
	else
	{
		for (int i = 0; i < _currentNumRows; i++)
		{
			retStr = tbl[i]->get(item);
			if (retStr.len())
				break;
		}
	}
	return(retStr);		
}
int table::find (mstring  item)
{
	int found = false;
	if (hashed())
	{
		long    tKey = makeHash(item);
		found = tbl[tKey]->find(item);
	}
	else
	{
		for (int i = 0; i < _currentNumRows; i++)
		{
			found = tbl[i]->find(item);
			if (found)
				break;
		}
	}
	return(found);		
}

int table::findNoCase (mstring item)
{
	int found = false;
	if (hashed())
	{
		long    tKey = makeHash(item);
		if (_hashField)
		{
			mstring newItem = getField(item(), _hashField, _fieldDelimit());
			tKey = makeHash(newItem);
		}
		else
			tKey = makeHash(item);
		found = tbl[tKey]->findNoCase(item);
	}
	else
	{
		for (int i = 0; i < _currentNumRows; i++)
		{
			found = tbl[i]->findNoCase(item);
			if (found)
				break;
		}
	}
	return(found);		
}

mstring table::getNoCase (mstring item)
{
	mstring retStr;
	if (hashed())
	{
		long    tKey = makeHash(item);
		retStr = tbl[tKey]->getNoCase(item);
	}
	else
	{
		for (int i = 0; i < _currentNumRows; i++)
		{
			retStr = tbl[i]->getNoCase(item);
			if (retStr.len())
				break;
		}
	}
	return(retStr);		
}

mstring table::getAllCnNoCase (mstring item)
{
        mstring retStr;
	long tKey = 0;
        if (hashed())
        {
			
		if (_soundexed)
		{
                	tKey = makeHash(item.sndxCalc());
                	// retStr = tbl[tKey]->getAllSd(item.sndxCalc(), _soundexAcc, _hashField,   fieldDelimit());
                	retStr = tbl[tKey]->getAllSd(item(), _soundexAcc, _hashField,   fieldDelimit());
		}
		else
		{
                	tKey = makeHash(item);
                	retStr = tbl[tKey]->getAllCnNoCase(item);
		}
        }
        else
        {
                for (int i = 0; i < _currentNumRows; i++)
                {
			if (_soundexed)
                        	retStr += tbl[i]->getAllSd(item.sndxCalc(), _soundexAcc,  _hashField, fieldDelimit());
			else
			{
                        	retStr += tbl[i]->getAllCnNoCase(item);
			}
                       // if (retStr.len())
                        //        break;
                }
		if (retStr.ccount("\t") == 1)
			retStr -= "\t";
        }
        return(retStr);
}

mstring table::getAllNoCase (mstring item, int part)
{
        mstring retStr;
        long tKey = 0;
        if (hashed())
        {

                if (_soundexed)
                {
                        tKey = makeHash(item.sndxCalc());
                        // retStr = tbl[tKey]->getAllSd(item.sndxCalc(), _soundexAcc, _hashField,   fieldDelimit());
                        retStr += tbl[tKey]->getAllSd(item(), _soundexAcc, _hashField,   fieldDelimit());
                }
                else
                {
                        tKey = makeHash(item);
                        retStr += tbl[tKey]->getAllNoCase(item, _hashField, _fieldDelimit(), part);
                }
        }
        else
        {
                for (int i = 0; i < _currentNumRows; i++)
                {
                        if (_soundexed)
                                retStr += tbl[i]->getAllSd(item.sndxCalc(), _soundexAcc,  _hashField, fieldDelimit());
                        else
                        	retStr += tbl[i]->getAllNoCase(item(), _hashField, _fieldDelimit(), part);
                       // if (retStr.len())
                        //        break;
                }
        }
        return(retStr);
}

mstring table::getCnNoCase (mstring item)
{
        mstring retStr;
        if (hashed())
        {
                long    tKey = makeHash(item);
                retStr = tbl[tKey]->getCnNoCase(item);
        }
        else
        {
                for (int i = 0; i < _currentNumRows; i++)
                {
                        retStr = tbl[i]->getCnNoCase(item);
                        if (retStr.len())
                                break;
                }
        }
        return(retStr);
}

int table::numLines (mstring fileName)
{
	int     lCount = 0;
	char    inputs[BUFSIZ];

	fstream in(fileName(), ios::in);

	while(in.getline(inputs, BUFSIZ - 1))
		lCount++;

	in.close();
	return(lCount);
}

unsigned long table::makeHash (mstring key)
{
	register   unsigned     long    Tkey;
	register   unsigned             Code;
	int     index = 0;
	mstring temp = new mstring(key.upper());
	mstring nKey = temp();

	Tkey = 1;
	// pos adds weight to the position a letter in the word
	int     pos = (int)nKey[index] + 7; // 7 is just a prime number
	int len = strlen(nKey());
	if (len)
		len--;
	for (index = 0; index < len; index++)
	{
		Code = ((unsigned) nKey[index]* (pos += ((int)nKey[index] ))) * 3;
		Tkey += (Code + 11);
	}
	return(Tkey % _potentialNumRows);

}
