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
	p = new srep;
	p->s = new char[2];
	p->s[0] = s;
	p->s[1] = NULL;

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

mstring mstring::operator+ (const int y)
{
	
	char buffer[5];
	mstring retStr;
	mstring workStr = p->s;

	int xval = workStr[0] + y;
	// cout << "Value is : " << workStr[0] << "     Integer value is : " << xval << "\n";
	sprintf(buffer, "%c", xval);	
	// cout << "String Value is : " << buffer << "\n";
	retStr = buffer;

    return retStr;
	
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

int mstring::sndLike(const mstring &x)
{
    int num;
    int wordLen;
    int i, similarities;
    float  value, lenValue, ssave, lsave;

 
	mstring copy = p->s;
	int lenC1 = copy.len(); // ourselves
	int lenC2 = x.len();    // what we are being compared to

	if (lenC1 > lenC2) // we are longer than what we are being compared to
	{
		similarities = lenC1;
		wordLen = lenC1;
	}
	else // we are shorter than what we are being compared to
	{
		similarities = lenC2;
		wordLen = lenC2;
	}
	
	mstring codeC1 = copy.sndxCalc();
	mstring codeC2 = x.sndxCalc();
 
    lenC1 = codeC1.len(); 
    lenC2 = codeC2.len();
 
 
    if (lenC1 > lenC2)  {
        similarities = lenC1;
        wordLen = lenC1;
    }
    else {
        similarities = lenC2;
        wordLen = lenC2;
    }
 
    for (i = 0; i < wordLen; i++) 
	{
        if ( lenC1 > lenC2) 
		{
            if (i < lenC2) 
			{
                if (codeC1[i] != codeC2[i])
                    similarities--;
            }
            else
                similarities--;
        }
        else 
		{
            if (i < lenC1) {
                if (codeC1[i] != codeC2[i])
                    similarities--;
            }
            else
                similarities--;
        }
    }
    ssave = lenC1;
    lsave = lenC2;
 

    if (lenC1 > lenC2 && lenC2 > 0) // no solutions half the size of the orginal string 
        lenValue = (abs(lenC1/lenC2));
    else
        if (lenC1 > 0)
            lenValue = (abs(lenC2/lenC1));
 
    if (lenValue >= 2 )
        wordLen = 0;
 
    if (wordLen > 0){
        ssave = similarities;
        lsave = wordLen;
        value = ssave / lsave;
        num = value * 100;
    }
    else
        num = 0;
 
    return (num);
} 

mstring *mstring::sndxCalc() const
{
   /* Calculate a "soundex" hash code given a string */

	int	 discard, i;
	int      place = 1;
	mstring  hCode;
	mstring  code;
	mstring  workStr = p->s;
	workStr = workStr.upper();

	int length = workStr.len();
 
 
    // strcpy(hCode, "");

    // ch = toupper(s[0]);

    switch (workStr[0]) {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
            code  = "1";
            break;
 
 
        case 'F':
        case 'H':
            code  = "9";
            break;
 
        case 'C':
        case 'K':
        case 'G':
        case 'J':
        case 'Q':
            code  = "8";
            break;
        case 'S':
        case 'X':
        case 'Z':
            code  = "2";
            break;
 
		case 'B':
        case 'V':
        case 'P':
        case 'D':
        case 'T':
        case 'W':

            code  = "3";
            break;

        case 'L':
		case 'R':
            code  = "4";
            break;
 
        case 'M':
        case 'N':
            code  = "5";
            break;
 
        case 'Y':
        case 'U':
            code  = "6";
            break;
 
        case '0':
            code  = "7";
            break;
        default:
            break;
    } /* end switch */
 
    hCode = code;
    for (i = 1; i < length; i++) {
        discard = FALSE;
		code = "";
		if (workStr[i] != workStr[i - 1])
		{
	        switch (workStr[i]) {
	            case 'A':
	            case 'E':
	            case 'I':
	            case 'O':
	            case 'U':
	            case 'W':
	            case 'Y':
	                discard = TRUE;
	                break;
				/* 
	            case 'H': // special case check for sch in germanic names
	                if (i >= 2 ) 
					{
	                    if (workStr[i - 1] == 'C') 
						{
	                        if (workStr[i - 2] == 'S') 
	                            discard = TRUE;
						}
	                }
	                break;
				*/
	 
	            case 'B':
	            case 'F':
	            case 'P':
	            case 'V':
	                code = "1";
	                break;
	 
	            case 'C':
	            case 'G':
	            case 'J':
	            case 'K':
	            case 'Q':
	            case 'S':
	            case 'X':
				case 'Z':
	                code = "2";
	                break;
				/* 
				case 'Z': // special case check for sz and cz in czech names
					if (i >= 1)
					{
						if ((workStr[i - 1] == 'C') || (workStr[i - 1] == 'S'))
							discard = TRUE;
					}
					else
						code = "2";
					break;
				*/
	
	 
	            case 'D':
	            case 'T':
	                code = "3";
	                break;
	 
	            case 'L':
	                code = "4";
	                break;
	 
	            case 'M':
	            case 'N':
	                code = "5";
	                break;
	 
	            case 'R':
	                code = "6";
	                break;
	 
	            case '0':
	                code = "7";
	                break;
	            default:
	                discard = TRUE;
	                break;
	        } /* end switch */
 
    		if (! discard) 
				hCode += code;
		}
        code = "";
    } /* end for */

	mstring retStr = hCode[0];
	for (i = 1; i < hCode.len(); i++)
	{
		
		if (hCode[i] != hCode[i - 1])
			retStr += hCode[i];
	}
  	mstring *returnCode = new mstring(retStr());
	return returnCode;

} /* end sndxCalc */





void mstring::swap(const char* t,  const char* r, int howMany)
{
    mstring workStr = p->s;
    mstring targetStr = t;
	mstring replaceStr = r;
    mstring disCard = "", retStr = "", value = "";
    int lenOfWorkStr = workStr.len();
	int lenOfReplace = replaceStr.len();
    int sizeOfTarget = targetStr.len();
    int numMatchesFound = 0;
	int allMatched = TRUE;
	int swapComplete = FALSE;
	int index = 0;
         
    int targetIndex = 0;   
    for (index = 0; index < lenOfWorkStr; index++)
    {
    
        if (workStr.p->s[index] == targetStr.p->s[targetIndex])
        {
            numMatchesFound++;
			// cout << "Match found: " << workStr.p->s[index] << "==" << targetStr.p->s[targetIndex] << ". Number of matched elements: " << numMatchesFound << ".\n";
			if (targetIndex < (sizeOfTarget - 1))
            	targetIndex++; 
            value = workStr.p->s[index];
            disCard += value();
        }
        else
        {
            if (numMatchesFound < sizeOfTarget && numMatchesFound > 0 && ! swapComplete) // we did not find the one we wanted
            {
                targetIndex = 0;
                retStr += disCard;
                value = workStr.p->s[index];
                retStr += value();
                disCard = "";
				numMatchesFound = 0;
				// cout << "MString:Match NOT found: output -- " << retStr << "::\n";
            }
			else if (numMatchesFound == sizeOfTarget && ! swapComplete) // we found the whole thing	
			{
				// cout << "SWAPING \n " << "disCard is: " << disCard << ":\n";
				// cout << "TRIGGER IS: " << workStr.p->s[index] << ":\n";
				allMatched = FALSE;
				retStr += replaceStr();
                value = workStr.p->s[index];
                retStr += value();
				// cout << "SWAPPED \n " << "retStr is now: " << retStr << ":\n";
				// cout << "MString:Match found: output -- " << retStr << "::\n";
				if (howMany == OPERATE_ALL) // the default here is OPERATE_FIRST
				{
					numMatchesFound = 0;
				}
				else
					swapComplete = TRUE;
					
			}
            else
            {   
                value = workStr.p->s[index];
               	retStr += value();
				// cout << "KEEPING: " << retStr << ":\n";

            }
 
    	}	
    }
	if (allMatched)
		retStr = replaceStr();
    delete [] p->s;
    p->s = new char[ retStr.len() + 1];
    strcpy(p->s, retStr.p->s);
    len(strlen(p->s));
	// cout << "FINAL retStr is: " << retStr << ":\n";
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

mstring mstring::range(int begin, int end)
{
	mstring retVal;
	char *token;
	int pos = 1;
	char *copy = new char[strlen(p->s) + 1];
	strcpy(copy, p->s);
	token = strtok(copy, " ");
	while (token)
	{
		if (pos >= begin && pos =< end)
		{
			retVal += token;
			retVal += " ";
		}
	}
	return retVal;
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


	while (index <= lenCopy)
	{
		// first we get rid of leading and trailing spaces
		if (index == 0 || index == lenCopy)
		{
			if (!(workStr[index] == blank[0]))
				retStr += workStr[index];
		}
		else
			retStr += workStr[index];
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
