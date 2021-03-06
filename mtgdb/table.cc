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
table::table(int newSize)
{
    _numItems = 0;
    size = newSize;
    _numLines = newSize;
	delimited = FALSE;
    tbl = (tableElement**)malloc(size * sizeof(tableElement));
    for (int i = 0; i <= size; i++)
    {
        tbl[i] = new tableElement;
        tbl[i]->value = (char *)"EMPTY";
    }
}
table::table(mstring filename)
{
    fstream  fs(filename(), ios::in);
    _numItems = 0;
    _numLines = numLines(filename);
	delimited = FALSE;
    size = _numLines;
    build(fs);
}

table::table(mstring* filename)
{
    mstring name = filename;
    fstream  fs(name(), ios::in);
    _numItems = 0;
    _numLines = numLines(name);
	delimited = FALSE;
    size = _numLines;
    build(fs);
}u

table::table(int newSize, mstring fDelimiter, int kField)
{
	_numItems = 0;
	size = newSize;
	_numLines = newSize;
	fieldDelimiter(fDelimiter);
	keyField(kField);
	delimited = TRUE;
	tbl = (tableElement**)malloc(size * sizeof(tableElement)); 
	for (int i = 0; i <= size; i++)
	{
		tbl[i] = new tableElement;
		tbl[i]->value = (char *)"EMPTY";
	}
}
table::table(mstring filename, mstring fDelimiter, int kField)
{
	fstream  fs(filename(), ios::in); 
	_numItems = 0;
	_numLines = numLines(filename); 
	fieldDelimiter(fDelimiter);
	keyField(kField);
	delimited = TRUE;
	size = _numLines;
	build(fs);      
}

table::table(mstring* filename, mstring fDelimiter, int kField)
{
	mstring name = filename;
    fstream  fs(name(), ios::in);
    _numItems = 0;
    _numLines = numLines(name);
	fieldDelimiter(fDelimiter);
	keyField(kField);
	delimited = TRUE;
    size = _numLines;
    build(fs);
}

table::~table()
{
	for (int i = 0; i < _numItems; i++)
	{       
		tableElement *nx;
		for (tableElement* n = tbl[i]; n;n=nx)
		{
			if (n)
			{
				if (n->next)
					nx=n->next;
				delete n;
			}
		}
	}
	delete tbl;
}

int table::build (fstream& file) 
{
	mstring			inputs;
	char			buffer[BUFSIZ];
	int             success = TRUE;

	tbl = (tableElement**)malloc(size * sizeof(tableElement));
	for (int i = 0; i <= size; i++)
	{
		tbl[i] = new tableElement;
		tbl[i]->value = "EMPTY";
	}
	file.seekg(0);
	while(file.getline(buffer, BUFSIZ - 1))
	{
			inputs = (char *)buffer;
			success = add(inputs);
	}
	return(success);

}
table::add ( mstring item)
{
	unsigned        long    Tkey;
			int     status = FALSE;
			int	Occupied;

	Tkey = 0;
	Tkey = makeHash(item);
	mstring tvalue = tbl[Tkey]->value;
	Occupied = strcmp(tvalue(), "EMPTY");
	if (Occupied) // see if the element is being used
	{
		// yes it is, chain it
		status = chain(&*tbl[Tkey], item);
	}
	else
	{
		// no it is not, add it
		tbl[Tkey]->value = item();
		tbl[Tkey]->next = tbl[Tkey];
		tbl[Tkey]->first = tbl[Tkey];
		status = TRUE;

	}
	_numItems++;
	return(status);


}

int table::find ( mstring  item)
{
	long    tHash = makeHash(item);
	int             found = FALSE;

	// char *tName;

	if (tbl[tHash]->first) // see if this element is occupied
	{
		mstring tName = tbl[tHash]->value();
		if (strcmp(item(), tName()) == 0)
			found = TRUE;
		else // it was not in the first pos, so now we walk the chain
		{
			// see if there is a chain, if there isn't, the first person should
			// be the begining element
			if (tbl[tHash] != tbl[tHash]->first)
			{
				// walk the chain
				struct tableElement *currentElement = tbl[tHash]->first;
				while (! found)
				{
					mstring tName = currentElement->value();
					if (strcmp(item, tName()) == 0)
						found = TRUE;
					else
					{
						currentElement = currentElement->next;
						if (! currentElement || (currentElement == currentElement->next))
							break;
					}
				} // end while
			}
		} // end else walk chain
	}
	return(found);
} // end table::find

mstring  table::get( mstring  name, int field)
{
	long    tHash = makeHash(name);
	int     found = FALSE;
	mstring tName, tValue, retBuf;

	tValue = tbl[tHash]->value();

	if (strcmp(tValue(), "EMPTY") != 0) // see if this element is occupied
	{
		if (delimited)
		{
			for (int i = 1; i <= keyField(); i++)
				tName = tValue.parse(fieldDelimiter());
		}
		else
			tName = name;

		// tValue.parse("~");
		// tName = tValue.parse("~");
		retBuf = tbl[tHash]->value();
		// see if the first element is the one we want, if it is return it
		if (strcmp(name(), tName()) != 0 )
		{
			// no, now we walk the chain to see if there are more elements
			if (tbl[tHash] != tbl[tHash]->first)
			{
				// walk the chain
				struct tableElement *currentElement = tbl[tHash]->first;
				while (! found)
				{
					tValue = currentElement->value();
					if(strlen(tValue()) > 0)
					{
						retBuf = tValue;
						tValue.parse(NULL);
						for (int i = 1; i <= field; i++)
							tName = tValue.parse(delimiter());
							
					}
					if (strcmp(name(), tName()) == 0)
		    		{
						found = TRUE;
					}
					else
					{
						currentElement = currentElement->next;
						if (! currentElement || (currentElement == currentElement->next))
							break;
					}
				} // end while
			}
		}
	}
	return(retBuf);
} // end table::get


mstring table::get(int index)
{
    int         noEndFound = FALSE;
	mstring     retStr;
    mstring 	tValue; 

    tValue = tbl[index]->value();
	retStr = "";

    if (strcmp(tValue(), "EMPTY") != 0) // see if this element is occupied
    {
		noEndFound = TRUE;
		retStr = tValue;
		retStr += "@";
		// see if there is a chain, if there isn't, the first person should
		// be the begining element
		if (tbl[index] != tbl[index]->first)
		{
			struct tableElement *currentElement = tbl[index]->first;
			while ( noEndFound)
			{
				// walk the chain
				tValue = currentElement->value();
				if (strlen(tValue()) > 1) // check to see if "value" is populated
				{
					// hold the current value of retStr
					retStr += tValue;
					retStr += "@";
					currentElement = currentElement->next;
					// see the current element is the end of the chain
					if (! currentElement || (currentElement == currentElement->next))
						noEndFound = FALSE;
				}

			}
		}
	}
    return(retStr);
} // end table::get(int index)

mstring table::get()
{
	int             noEndFound = FALSE;
	mstring			tValue, tName, retBuf;

	for (int index = 0; index <= _numItems; index++)
	{
		// tbl[index]->value.clear();
		tValue = tbl[index]->value();
		if (strcmp(tValue(), "EMPTY") != 0) // see if this element is occupied
		{
			noEndFound = TRUE;
            tName = tValue;
            retBuf += tName;
            retBuf += "@";
			// see if there is a chain, if there isn't, the first person should
			// be the begining element
			if (tbl[index] != tbl[index]->first)
			{
				struct tableElement *currentElement = tbl[index]->first;
				while ( noEndFound)
				{
					// walk the chain
					tName = currentElement->value();
            		retBuf += tName;
            		retBuf += "@";
					currentElement = currentElement->next;
					// see the current element is the end of the chain
					if (! currentElement || (currentElement == currentElement->next))
						noEndFound = FALSE;

				}
			}
		}
	}
	return(retBuf);
} // end table::getall

mstring table::get(int elementNum, mstring delimiter)
{
	int     noEndFound = FALSE;
	mstring	tValue, tName, retBuf;

	for (int index = 0; index <= _numItems; index++)
	{
		tValue = tbl[index]->value();
		if (strcmp(tValue(), "EMPTY") != 0) // see if this element is occupied
		{
			noEndFound = TRUE;
			if (strlen(delimiter()) > 0)
				tName = tValue.parse(delimiter());
			else
				tName = tValue;

			for (int i = 0; i < (elementNum - 1); i++)
			{
				if (delimiter())
					tName = tValue.parse(delimiter());
				else
					break;
			}
			if (strlen(retBuf()) > 1)
			{
				retBuf += tName;
				retBuf += "@";
			}
			else
	    {
				retBuf = tName;
				retBuf += "@";
	    }
			// see if there is a chain, if there isn't, the first person should
			// be the begining element
			if (tbl[index] != tbl[index]->first)
			{
				struct tableElement *currentElement = tbl[index]->first;
				while ( noEndFound)
				{
					// walk the chain


					tValue = currentElement->value();
					if(strlen(tValue()) > 0)
					{
				if (strlen(delimiter()) > 0)
					tName = tValue.parse(delimiter());
				else
					tName = tValue;

				for (int i = 0; i < (elementNum - 1); i++)
				{
					if (delimiter())
					tName = tValue.parse(delimiter());
					else
					break;
				}
						if (strlen(retBuf()) > 1)
						{
							retBuf += tName;
							retBuf += "@";
						}
						else
			{
							retBuf = tName;
							retBuf += "@";
			}
					}
					currentElement = currentElement->next;
					// see the current element is the end of the chain
					if (! currentElement || (currentElement == currentElement->next))
						noEndFound = FALSE;

				}
			}
		}
	}
	return(retBuf);
} // end table::getall

table::chain ( tableElement* item,  mstring value)
{
	int     status = FALSE;
	tableElement* newElement = new tableElement;

	if(newElement)
	{
		newElement->value = value();
		newElement->next = item->first;
		item->first = newElement;
		status = TRUE;
	}
	return(status);
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
	mstring    token, nKey;
	mstring buffer =  key;
	if (delimited)
	{
		for (int i = 1; i <= keyField(); i ++;)
			token = buffer.parse(fieldDelimiter());
		nKey = token;
	}
	else
		nKey = key;

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
	return(Tkey % _numLines);

}


	
	

