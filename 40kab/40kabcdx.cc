#include "40kabcdx.h"


fkCodex::fkCodex( mstring fileList)
{
	int i = 0;
	_numWarGearLists = 0;
	_listStr = "";
	fileList.parse(NULL);
	mstring fileName = fileList.parse(",");
	_leaders = new table(fileName);
	fileName = fileList.parse(",");
	_characters = new table(fileName);
	fileName = fileList.parse(",");
	_squads = new table(fileName);
	fileName = fileList.parse(",");
	_support = new table(fileName);
	fileName = fileList.parse(",");
	{
		fstream  wglfile(fileName(), ios::in);
		wgList(wglfile);
		wglfile.close();
	}
}
fkCodex::~fkCodex()
{
	delete _leaders;
	delete _characters;
	delete _squads;
	delete _support;
}

void fkCodex::listStr(mstring& newElement)
{

	_listStr += newElement;
	_listStr += "~";
	_numWarGearLists++;
}

figure *fkCodex::leaders(mstring& name)
{
	figure *newFigure = new figure(_leaders->get(name()));
	return(newFigure);
}
figure *fkCodex::character(char *name)
{
	figure *newFigure = new figure(_characters->get(name));
	return(newFigure);
}
squad *fkCodex::squads(char *name)
{
	squad *newSquad = new squad(_squads->get(name));
	return(newSquad);
}
vehicle *fkCodex::support(char *name)
{
	vehicle *newVehicle = new vehicle(_support->get(name));
	return(newVehicle);
}
mstring fkCodex::leaders()
{
	mstring temp,retString, buffer, name, cost;
	int	items = 0, count = 0;



	int numLeaders = _leaders->numElements();

	for (int i = 0; i < numLeaders; i++)
	{
		items = 0;
		count = 0;
		// find out how leaders are in this element
		buffer = _leaders->get(i);
		buffer.parse(NULL);
		items = buffer.ccount("@");

		if (buffer.len() > 1)
		{
			while (count < items )
			{
				temp = buffer.parse("@");
				temp.parse("~");
				name = temp.parse("~");
				cost = temp.parse("~");
				if (strlen(retString()) > 1)
					retString += name;
				else
					retString = name;
				retString += "-( ";
				retString += cost;
				retString += " )";
				retString += ",";
				count++;
			}
		}
	}
	return(retString);
}

int fkCodex::wgList(mstring& header)
{
    mstring nameList= listStr();
    int  count = 0;
    mstring uheader = header.upper(), utoken;


    mstring token = nameList.parse("~");
    while(token.len())
    {
	utoken = token.upper();
	if (strcmp(utoken(), uheader()) == 0)
	{
		break;
	}
		token = nameList.parse("~");
		count++;
	}
    return(count);
}

mstring fkCodex::wgList(mstring name, int dummy)
{
	mstring retunVal, value, cost, type, buffer;
	char *temp;
	for(int i = 0; i < _numWarGearLists; i++)
	{
		buffer = name.deXSpaces();
		temp = _wgLists[i]->get(buffer);	
		value = temp;
		if (value.sub(buffer))
		{
			buffer = value;
			if (buffer.len())
			{
				cost = buffer.parse("~");
				type = buffer.parse("~");
				retunVal = type;
				retunVal += "- ( ";
				retunVal += cost;
				retunVal += " )";	
				break;
			}
		}
	}
	return retunVal;
}

mstring fkCodex::wgList(int element)
{
    mstring buffer, value, valStr, cost, vBuffer;
	char *totalStr;
    mstring nameList;
    int  numNames = 0, parse = TRUE;


    buffer = _wgLists[element]->get(2,"");
    while (parse)
    {
	valStr = buffer.parse("@");
	cost = valStr.parse("~");
	value = valStr.parse("~");
	if (valStr.len())
	{
		nameList += value;
		nameList += "- ( ";
		nameList += cost;
		nameList += " )";
		nameList += ",";
	}
	else
		parse = FALSE;
    }
    return(nameList);
}

mstring fkCodex::squads()
{
    mstring temp,retString, buffer, name, cost;
    int items = 0, count = 0;

 
 
    int numSquads = _squads->numElements();
 
    for (int i = 0; i < numSquads; i++)
    {
        items = 0;
        count = 0;
        // find out how Squads are in this element
        buffer = _squads->get(i);
    	// buffer = _squads->get(2, "~");
        buffer.parse(NULL);
        items = buffer.ccount("@");
 
        if (buffer.len() > 1)
        {
            while (count < items )
            {
                temp = buffer.parse("@");
                temp.parse("~");
                name = temp.parse("~");
                cost = temp.parse("~");
                if (strlen(retString()) > 1)
                    retString += name;
                else
                    retString = name;
                retString += "-( ";
                retString += cost;
                retString += " )";
                retString += ",";
                count++;
            }
        }  
    }
    return(retString);
}
void fkCodex::wgList(fstream &file)
{
	char	 inputs[BUFSIZ + 1];
	int		index = 0;
	int		headerFound = FALSE;
	int		elementsFound = 0;
	char    elementList[BUFSIZ];
	streampos headerPos = 0, lastPos = 0;
	mstring token, orig;
	int 	elementCount = 0;
	int		headerCount = 0;
	int		readIt = TRUE;

	file.seekg(0);
    while( file.getline(inputs, BUFSIZ))
	{
		orig = inputs;
		if (orig.ccount("]"))
			elementCount++;
	}

	_wgLists = (table**) new table[sizeof(table) * elementCount];
	// find out how many lists there are
	file.seekg(0);
	file.clear();
	while( readIt )
	{
		if (!( file.getline(inputs, BUFSIZ)) )
		{
			if (headerCount == elementCount)
			{
				headerCount++;
				headerFound = FALSE;
				file.clear();
			}
			else
				break;
		}

		orig = inputs;
		if (orig.ccount("]") && ! headerFound)
		{
			headerPos = file.tellg();
			token = orig.parse("]");
			listStr(token);
			headerFound = TRUE;
			elementsFound = 0;
			headerCount++;
		}
		else if (!orig.ccount("]") && headerFound)
		{
			elementsFound++;
		}
		else
		{

			_wgLists[index] = new table(elementsFound);
			file.seekg(headerPos);
			for(int i = 0; i < elementsFound; i++)
			{
			file.getline(inputs, BUFSIZ);
				orig = inputs;
				_wgLists[index]->add(orig);

			}
			headerFound = 0;
			elementsFound = 0;
			index++;
		}
	}
}







