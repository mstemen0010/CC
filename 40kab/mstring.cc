#include <errno.h>
#include <stdio.h>
#include "mstring.h"

void error(char * msg);
int wordCount(const char *s);
int wordCount(char *s);


mstring::mstring()
{
	p = new srep;
	p->s = new char[1];
	strcpy(p->s, "");
	len(strlen(p->s));
	wcount(0);
	p->pcount = 0;
}
mstring::mstring(mstring* x)
{
	if (x)
	{
		x->p->n++;
		p = x->p;
		p->pcount = 0;
	}
	else
		p = NULL;
}
mstring::mstring(const mstring& x)
{
	if (x())
	{
		x.p->n++;
		p = x.p;
		p->pcount = 0;
	}
	else
		p = NULL;
}
mstring::mstring(char s)
{
	char *temp = &s;
	p = new srep;
	p->s = new char[ strlen(temp) + 1];
	strcpy(p->s, temp);
	p->pcount = 0;
	len(strlen(p->s));
	wcount(wordCount(p->s));
}


mstring::mstring(const char* s)
{
	p = new srep;
	p->s = new char[ strlen(s) + 1];
	strcpy(p->s, s);
	p->pcount = 0;
	len(strlen(p->s));
	wcount(wordCount(s));
}
mstring::mstring(char* s)
{
	p = new srep;
	p->s = new char[ strlen(s) + 1];
	strcpy(p->s, s);
	p->pcount = 0;
	len(strlen(p->s));
	wcount(wordCount(s));
}
mstring::~mstring()
{
	if (--p->n == 0)
	{
		delete [] p->s;
		delete p;
	}
}

mstring& mstring::operator=(const char* s)
{
	if (p->n > 1) // disconnect self
	{
		p->n--;
		p = new srep;
	}
	else	     // free old mstring

		delete [] p->s;

	p->s = new char [ strlen(s) + 1];
	strcpy(p->s, s);
	len(strlen(p->s));
	/*
	mstring tempStr = p->s;
	p->_numWords = tempStr.ccount(" ");
	p->_numWords++;
	*/
	p->pcount = 0;
	wcount(wordCount(p->s));
	return *this;
}

mstring& mstring::operator=(const mstring& x)
{
	x.p->n++; // protect against "st = st"
	if (--p->n == 0)
	{
		delete [] p->s;
		delete p;
	}
	p = x.p;
	len(strlen(p->s));
	wcount(wordCount(p->s));
	return *this;
}

mstring&  mstring::operator+=(const mstring &x)
{
	x.p->n++;
	mstring hold = p->s;
	delete [] p->s;
	p->s = new char[ hold.len() + x.len() + 1];
	strcpy(p->s, hold());
	strcat(p->s, x.p->s);
	len(strlen(p->s));
	wcount(wordCount(p->s));

	return *this;
}

mstring&  mstring::operator+=(const char *x)
{
	mstring hold = p->s;
	delete [] p->s;
	p->s = new char[ hold.len() + strlen(x) + 1];
	strcpy(p->s, hold());
	strcat(p->s, x);
	len(strlen(p->s));
	wcount(wordCount(p->s));

	return *this;
}

mstring&  mstring::operator-=(const mstring &x)
{
	mstring workStr = p->s;
	mstring targetStr = x.p->s;
	mstring disCard, retStr;
	int lenOfWorkStr = strlen(workStr.p->s);
	int numMatchesFound = 0;

	int sizeOfTarget = strlen(targetStr.p->s);
	int targetIndex = 0;
	for (int index = 0; index < lenOfWorkStr; index++)
	{

		if (workStr.p->s[index] == targetStr.p->s[targetIndex])
		{
			numMatchesFound++;
			targetIndex++;
			mstring value = workStr[index];
			disCard += value;
		}
		else
		{
			if (numMatchesFound < sizeOfTarget && numMatchesFound > 0) // we did not find the one we wanted
			{
				targetIndex = 0;
				retStr += disCard;
				mstring value = workStr[index];
				retStr += value;
				disCard = "";
			}
			else
			{
				mstring value = workStr[index];
				retStr += value;
			}

		}
	}
	delete [] p->s;
    p->s = new char[ strlen(retStr.p->s) + 1];
    strcpy(p->s, retStr.p->s);
	len(strlen(p->s));
	wcount(wordCount(p->s));
	return *this;
}

void mstring::swap(const char* t,  const char* r, int howMany)
{
    mstring workStr = p->s;
    mstring targetStr = t;
    mstring disCard, retStr;
    int lenOfWorkStr = strlen(workStr.p->s);
    int numMatchesFound = 0;
         
    int sizeOfTarget = strlen(targetStr.p->s);
    int targetIndex = 0;   
    for (int index = 0; index < lenOfWorkStr; index++)
    {
    
        if (workStr.p->s[index] == targetStr.p->s[targetIndex])
        {
            numMatchesFound++;
            targetIndex++; 
            mstring value = workStr[index];
            disCard += value;
        }
        else
        {
            if (numMatchesFound < sizeOfTarget && numMatchesFound > 0) // we did not find the one we wanted
            {
                targetIndex = 0;
                retStr += disCard;
                mstring value = workStr[index];
                retStr += value;
                disCard = "";
				numMatchesFound = 0;
            }
			else if (numMatchesFound == sizeOfTarget) // we found the whole thing	
			{
				retStr += r;
                mstring value = workStr[index];
                retStr += value;
				if (howMany == OPERATE_ALL) // the default here is OPERATE_FIRST
					numMatchesFound = 0;
					
			}
            else
            {   
                mstring value = workStr[index];
                retStr += value;
            }
 
    	}	
    }
    delete [] p->s;
    p->s = new char[ strlen(retStr.p->s) + 1];
    strcpy(p->s, retStr.p->s);
    len(strlen(p->s));
    wcount(wordCount(p->s));
}

mstring&  mstring::operator-=(const char* x)
{
	mstring workStr = p->s;
	mstring targetStr = x;
    mstring disCard, retStr;
    int lenOfWorkStr = strlen(workStr.p->s);
    int numMatchesFound = 0;

    int sizeOfTarget = strlen(targetStr.p->s);
    int targetIndex = 0;
    for (int index = 0; index < lenOfWorkStr; index++)
    {

	if (workStr.p->s[index] == targetStr.p->s[targetIndex])
	{
	    numMatchesFound++;
	    targetIndex++;
	    mstring value = workStr[index];
	    disCard += value;
	}
	else
	{
	    if (numMatchesFound < sizeOfTarget && numMatchesFound > 0) // we did not find the one we wanted
	    {
		targetIndex = 0;
		retStr += disCard;
		mstring value = workStr[index];
		retStr += value;
		disCard = "";
	    }
	    else
	    {
		mstring value = workStr[index];
		retStr += value;
	    }

	}
    }
    delete [] p->s;
    p->s = new char[ strlen(retStr.p->s) + 1];
    strcpy(p->s, retStr.p->s);
	len(strlen(p->s));
	wcount(wordCount(p->s));
    return *this;
}
char mstring::operator[](int i)
{
	// int index;
	// mstring copy = p->s;
	if (i<0 || strlen(p->s)<i) error("index out of bounds");
	if (p->n >1) // clone to maintain value semantics
	{
		srep* np = new srep;
		np->s = new char[strlen(p->s) + 1];
		strcpy(np->s, p->s);
		np->pcount = 0;
		np->_lenStr = strlen(np->s);
		wcount(wordCount(np->s));
		p->n--;
		p = np;

	}
	return p->s[i];
}


const char* mstring::operator[] (int i) const
{
	if (i<0 || strlen(p->s)<i)
		error("index out of bounds");
	return (char *)p->s[i];
}
mstring* mstring::sub(const int s)
{
    mstring tmp = new mstring(p->s);

    mstring *sub = new mstring(strchr(tmp.p->s, s));
	return sub;
}

mstring* mstring::sub(const char *s)
{
    mstring tmp = p->s;
	char *value = strstr(tmp.p->s, s);
	mstring *sub;
	if (value)
		sub = new mstring(value);
	else
		sub = NULL;

	return sub;
}


mstring* mstring::sub(const mstring x)
{
    mstring tmp = p->s;
	char *value = strstr(tmp.p->s, x());
	mstring *sub;
	if (value)
		sub = new mstring(value);
	else
		sub = NULL;

	return sub;
}

mstring* mstring::parse(const char* s)
{
	int  tcount = 0;


	if (s)
	{
		mstring tmp = p->s;
		mstring *retVal;
		char *token;
		// first let us see how many tokens there are, if any
		if(strstr(tmp(), s))
			token = strtok(tmp(), s);
		else
		{
			token = NULL;
			p->pcount = 0;
		}
		while (tcount != p->pcount)
		{
			token = strtok(NULL, s);
			tcount++;
		}
		if (token)
		{
			p->pcount++;
			retVal = new mstring(token);
			return(retVal);
		}
		else
		{
			retVal = new mstring("");
			p->pcount = 0;
			return(retVal);
		}
	}
	else
		p->pcount = 0;

}
mstring& mstring::clipn(int posToDrop)
{
	mstring retStr = "";
	int currPos = 0;
	char *copy = new char[strlen(p->s) + 1];
	strcpy(copy, p->s);

	while(*copy != '\0')
	{
		if ( currPos++ != posToDrop)
			retStr += *copy++;
		else
			copy++;
	}
	if (retStr.len() > 0)
	{
		delete [] p->s;
		p->s = new char[ strlen(retStr.p->s) + 1];
		strcpy(p->s, retStr.p->s);
		len(strlen(p->s));
		wcount(wordCount(p->s));
	}
	return *this;
}


mstring& mstring::cutn(int wordToDrop, char *delimiter)
{
    mstring retVal;
    char *token;
    int pos = 1;
    char *copy = new char[strlen(p->s) + 1];
    strcpy(copy, p->s);
    token = strtok(copy, delimiter);
    while (token)
    {
	if (pos != wordToDrop)
	{
		retVal += token;
		pos++;
		token = strtok(NULL, delimiter);
	}
	else
		break;
	retVal += token;
    }
    if (retVal.len() > 0)
    {
	delete [] p->s;
	p->s = new char[ strlen(retVal.p->s) + 1];
	strcpy(p->s, retVal.p->s);
	len(strlen(p->s));
	wcount(wordCount(p->s));
    }
    return *this;
}

int mstring::cPos(char s)
{
	int pos = 0;
	int index = 0;
	char 	*copy = new char[strlen(p->s) + 1];
	strcpy(copy, p->s);
	int lenCopy = strlen(copy);
	while (*copy != '\0')
	{
		if (copy[0] == s)
			break;
		copy++;
		pos++;
	}
	return pos;
}

mstring * mstring::wPos(int wordToGet, char *delimiter)
{
	mstring *retVal;
	char *token;
	int pos = 1;
		char *copy = new char[strlen(p->s) + 1];
		strcpy(copy, p->s);
		token = strtok(copy, delimiter);
		while (token)
		{
			if (pos == wordToGet)
				break;
			pos++;
			token = strtok(NULL, delimiter);
		}
	retVal = new mstring(token);
	return(retVal);
}

int mstring::wPos(char *s)
{
	int pos = 0;
	if (s)
	{
		char *copy = new char[strlen(s) + 1];
		strcpy(copy, s);
		char *token = strtok(copy, " ");
		while (token)
		{
			if (strcmp(token, s) == 0)
				break;
			pos++;
			token = strtok(NULL, " ");
		}
	}
	return(pos);
}

int mstring::ccount(char *s)
{
	int	count = 0;
	int 	index = 0;
	char 	*copy = new char[strlen(p->s) + 1];
	strcpy(copy, p->s);
	int lenCopy = strlen(copy);

	while (*copy != '\0')
	{
		if (copy[0] == *s)
			count++;
		copy++;
		index++;
	}
	for (int i = 0; i < lenCopy; i++)
		copy--;


	delete [] copy;
	return count;

	/* old stuff
	int 		count = 0;
	mstring temp = p->s;
	int currentParseNum = p->pcount;
	if (strstr(p->s, s))
	{
		if (! count )
			count = 1;
		temp.parse(NULL);
		while(temp.parse(s))
			count++;
		count--;
	}
	p->count = currentParseNum;
	return count;
	*/
}
int wordCount(const char *s)
{
	int count = 0;
	if (s)
	{
		char *copy = new char[strlen(s) + 1];
		strcpy(copy, s);
		char *token = strtok(copy, " ");
		while (token)
		{
			count++;
			token = strtok(NULL, " ");
		}
	}
	return(count);
}

int wordCount(char *s)
{

	int count = 0;
	if (s)
	{
		char *copy = new char[strlen(s) + 1];
		strcpy(copy, s);
		char *token = strtok(copy, " ");
		while (token)
		{
			count++;
			token = strtok(NULL, " ");
		}
	}
	return(count);
}


mstring mstring::deXSpaces()
{
	mstring retStr = "";
	mstring workStr = p->s;
	mstring blank = " ";
	int lenCopy = workStr.len();
	int index = 0;
	int spaceCount;


	while (index <= lenCopy)
	{
		// first we get rid of leading and trailing spaces
		if (index == 0 || index == lenCopy)
		{
			if (!(workStr[index] == blank[0]))
				retStr += workStr[index];
		}
		else
		{
			// then we get rid of mutiple space blocks
			if (isspace(workStr[index]))
			{
				spaceCount++;
				if (spaceCount <= 1)
					retStr += workStr[index];
			}
			else
			{
				spaceCount = 0;
				retStr += workStr[index];
			}
		}
		index++;
	}
	retStr.len(strlen(retStr.p->s));
	return retStr;
}

mstring mstring::deSpace()
{
	mstring retStr;
	char *copy = new char[strlen(p->s) + 1];
	strcpy(copy, p->s);
	int lenCopy = strlen(copy);

	while (*copy != '\0')
	{
		if(! isspace(*copy))
			retStr += *copy;
		copy++;
	}
	for (int i = 0; i < lenCopy; i++)
		copy--;
	delete [] copy;
	retStr.len(strlen(retStr.p->s));
	return retStr;
}

int mstring::isBlank()
{
	int retVal = TRUE;
	char *copy = new char[strlen(p->s) + 1];
	strcpy(copy, p->s);
	while (*copy != '\0')
	{
		if (! isspace(*copy++))
		{
			retVal = FALSE;
			break;
		}
	}
	return (retVal);
}

mstring mstring::upper()
{
	mstring retStr;
	char *copy = new char[strlen(p->s) + 1];
	strcpy(copy, p->s);
	int lenCopy = strlen(copy);

	while (*copy != '\0')
		retStr += toupper(*copy++);
	for (int i = 0; i < lenCopy; i++)
		copy--;

	// mstring *retStrPtr = new mstring(retStr());
	delete [] copy;
	return retStr;
}

mstring mstring::lower()
{
	mstring retStr;
	char *copy = new char[strlen(p->s) + 1];
	strcpy(copy, p->s);
	int lenCopy = strlen(copy);

	while (*copy != '\0')
		retStr += tolower(*copy++);
	for (int i = 0; i < lenCopy; i++)
		copy--;

	// mstring *retStrPtr = new mstring(retStr());
	return retStr;
}

void error(char * msg)
{
	perror(msg);
}
