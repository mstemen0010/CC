#include <errno.h>
#include <stdio.h>
#include "mstring.h"
// #define DEBUG


void error(char * msg);
int wordCount(const char *s, const char *d);
int wordCount(char *s, char *d);


mstring::mstring()
{
	p = new srep;
	p->s = new char[2];
	strcpy(p->s, "");
	len(strlen(p->s));
	wcount(0);
	p->pcount = 0;
	p->_index = 0;
	p->d = new char[3];
	strcpy(p->d, " ");
}
mstring::mstring(const mstring* x)
{
	if (x)
	{
		x->p->n++;
		p = x->p;
		p->pcount = 0;
		p->_index = 0;
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
		p->_index = 0;
	}
	else
		p = NULL;
}
mstring::mstring(const char s)
{
	p = new srep;
	p->s = new char[2];
	p->s[0] = s;
	p->s[1] = NULL;
	p->_index = 0;
	p->d = new char[2];
	strcpy(p->d, " ");

	p->pcount = 0;
	len(strlen(p->s));
	wcount(wordCount(p->s, p->d));
}


mstring::mstring(const char* s)
{
	p = new srep;
	p->s = new char[ strlen(s) + 1];
	strcpy(p->s, s);
	p->pcount = 0;
	p->_index = 0;
	len(strlen(p->s));
	p->d = new char[2];
	strcpy(p->d, " ");
	wcount(wordCount(s, p->d));
}
/*
mstring::mstring(char* s)
{
	char *t = s;
	p = new srep;
	p->s = new char[ strlen(t) + 1];
	strcpy(p->s, t);
	p->pcount = 0;
	p->_index = 0;
	len(strlen(p->s));
	p->d = new char[2];
	strcpy(p->d, " ");
	wcount(wordCount(t, p->d));
}
*/
mstring::~mstring()
{
	if (p)
	{
		if (--p->n == 0)
		{
			if (p->s)
				delete [] p->s;
			if (p->d)
				delete [] p->d;
			if (p)
				delete p;
		}
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

		delete[] p->s;

	p->s = new char [ strlen(s) + 1];
	p->d = new char[2];
	strcpy(p->d, " ");
	strcpy(p->s, s);
	len(strlen(p->s));
	p->pcount = 0;
	wcount(wordCount(p->s, p->d));
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
		delete [] p->d;
		delete p;
	}
	
	p = x.p;
	return *this;
}

mstring& mstring::operator+=(const int x)
{
    char s[BUFSIZ];
    sprintf(s, "%c", x);
    // sprintf(s, "%d", x);
	mstring hold = p->s;
	delete [] p->s;
	p->s = new char[ hold.len() + strlen(s) + 1];
	strcpy(p->s, hold());
	strcat(p->s, s);
	len(strlen(p->s));
	wcount(wordCount(p->s, p->d));

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
	wcount(wordCount(p->s, p->d));

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
	wcount(wordCount(p->s, p->d));

	return *this;
}
void mstring::delimiter(char *d)
{
	delete [] p->d;
	p->d = new char [ strlen(d) + 1];
	strcpy(p->d, d);
	wcount(wordCount(p->s, p->d));
}

char *mstring::delimiter() 
{ 
	return p->d; 
}


	
int mstring::index()
{
	return p->_index;
}
char *mstring::charAtIndex()
{
	return (char *)p->s[p->_index];
}
mstring *mstring::charAtIndex(int index)
{
	mstring retVal = p->s[index];
    	mstring *retStr = new mstring(retVal);
    	return retStr;
}
mstring *mstring::wordAtIndex(int index)
{
	int	start = 0, end = 0;
	int	startIsLetter = FALSE;
	int	startIsSpace = FALSE;
	
	mstring workStr = p->s;
    int lenCopy = workStr.len();
  	mstring tempStr;

	if (index > (lenCopy - 1))
		index = (lenCopy - 1);
	if ( index < 0)
		index = 0;

	int	currentPos = index;

	startIsSpace = isspace(workStr[currentPos]);
	if (startIsSpace && currentPos == 0) // special case
	{
		// read up until we find a letter
		while (currentPos < lenCopy)
		{
			if (!isspace(workStr[currentPos]))
				currentPos++;
			else
				break;
		}
		tempStr += currentPos;
		while (!isspace(workStr[currentPos]))
		{
			mstring value = workStr[currentPos];
			tempStr += value;
		}
				
	}
	
	if (startIsSpace)
	{
		// read back until we find a letter
		while (currentPos != 0)
		{
			if (isspace(workStr[currentPos]))		
				currentPos--;
			else
				break;
		}
		end = currentPos;
		//  now read back till we find a space or the begining
		while (currentPos != 0)
		{
			if (!isspace(workStr[currentPos]))		
				currentPos--;
			else
				break;
		}
		if (currentPos != 0)
			start = currentPos++;
		// now we get our word
		for (int i = start; i <= end; i++)
		{
			mstring value = workStr[i];
			tempStr += value;
		}
	}
	else 
	{
		// Find the end of the word
		while (currentPos < lenCopy)
		{
			if(!isspace(workStr[currentPos]))
				currentPos++;
			else
				break;
		}
		end = currentPos--;
		// Find the start of the word
		while (currentPos != 0)
		{
			if(!isspace(workStr[currentPos]))
				currentPos--;
			else
				break;
		}
		if (currentPos != 0)
			start = currentPos++;
		// now we get our word
		for (int i = start; i <= end; i++)
		{
			mstring value = workStr[i];
			tempStr += value;
		}
	}

    mstring *retStr = new mstring(tempStr);
    return retStr;
}

int mstring::find(const mstring &x, int start)
{
    mstring workStr = p->s;
    mstring targetStr = x.p->s;
    mstring disCard;
	int	retIndex = NULL;
    int lenOfWorkStr = workStr.len();
    int numMatchesFound = 0;
	if (start < 0)
		start = 0;
	if (start > (workStr.len() - 1))
		start = workStr.len() - 1;

    int sizeOfTarget = targetStr.len();
    int targetIndex = 0;
    for (int index = start; index < lenOfWorkStr; index++)
    {
        if (workStr.p->s[index] == targetStr.p->s[targetIndex])
		{
			numMatchesFound++;
			targetIndex++;
			retIndex = index;
		}
		else
		{
			numMatchesFound = 0;
			targetIndex = 0;
		}
		if (numMatchesFound == sizeOfTarget)
			break;
	}
	return retIndex;
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
	wcount(wordCount(p->s, p->d));
	return *this;
}

int mstring::sndLike( char *x)
{
    	int num;
    	int wordLen;
    	int i, similarities;
    	float  value, lenValue, ssave, lsave;
	mstring codeC1, codeC2;

 
	mstring copy1 = p->s;
	mstring copy2 = x;
	int lenC1 = copy1.len(); // ourselves
	int lenC2 = copy2.len();    // what we are being compared to

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
	
	codeC1 = copy1.sndxCalc();

	codeC2 = copy2.sndxCalc();
 
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
        num = (int) value * 100;
    }
    else
        num = 0;
 
    return (num);
} 

mstring *mstring::sndxCalc() // const
{
   /* Calculate a "soundex" hash code given a string */

	int	 discard, i;
	int      place = 1;
	mstring  hCode;
	mstring  code;
	mstring  tempStr = p->s;
	mstring  workStr = tempStr.upper();
  	mstring *retPtr;
	mstring token = "EMPTY";

 
 

   	 while (token.len())
    	{
    		token = workStr.parse(" ");
		int length = token.len();

	    switch (token[0]) {
	        case 'A':
	        case 'E':
	        case 'I':
			code = "A";
		break;
	        case 'B':
			code = "B";
		break;
	        case 'C':
	        case 'K':
			code = "C";
		break;
	        case 'D':
			code = "D";
		break;
	        case 'F':
			code = "F";
		break;
	        case 'G':
	        case 'J':
			code = "G";
		break;
	        case 'H':
			code = "H";
		break;
	        case 'L':
			code = "L";
		break;
	        case 'M':
			code = "M";
		break;
	        case 'N':
			code = "N";
		break;
	        case 'O':
			code = "O";
		break;
	        case 'P':
			code = "P";
		break;
	        case 'Q':
			code = "Q";
		break;
	        case 'R':
			code = "R";
		break;
	        case 'S':
	        case 'Z':
			code = "S";
		break;
	        case 'T':
			code = "T";
		break;
	        case 'U':
			code = "U";
		break;
	        case 'V':
			code = "V";
		break;
	        case 'W':
			code = "W";
		break;
	        case 'X':
			code = "X";
		break;
	        case 'Y':
			code = "Y";
		break;
	 
	        default:
	            code  = "0";
	            break;
	    } /* end switch */
	 
	    hCode += code();
	    for (i = 1; i < length; i++) {
	        discard = FALSE;
			code = "";
			if (token[i] != token[i - 1])
			{
		        switch (token[i]) {
		            case 'A':
		            case 'E':
		            case 'I':
		            case 'O':
		            case 'U':
		            case 'W':
		            case 'Y':
		                discard = TRUE;
		                break;
		            case 'H': // special case check for sch in germanic names
		                if (i >= 2 ) 
						{
		                    if (token[i - 1] == 'C') 
							{
		                        if (token[i - 2] == 'S') 
		                            discard = TRUE;
							}
		                }
		                break;
		 
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
							if ((token[i - 1] == 'C') || (token[i - 1] == 'S'))
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
		                code = "0";
		                break;
		        } /* end switch */
	 
	    		if (! discard) 
					hCode += code();
			}
	        code = "";
	    } /* end for */
	}
	
	
	mstring retStr = hCode[0];

	for (i = 1; i < hCode.len(); i++)
	{
		
		if (hCode[i] != hCode[i - 1])
			retStr += hCode[i];
	}

  	retPtr = new mstring(retStr);
	return retPtr;

} /* end sndxCalc */


int mstring::cSwap(const char t,  const char r)
{

	mstring copy =  p->s;
	mstring retStr;
	int slen = copy.len();
	int count = 0;
	for (int i = 0; i < slen; i++)
	{
		if (copy[i] != t)
		{
			retStr += copy[i]; 
		}
		else
		{
			retStr += r;
			count++;
		}
	}
    	if (retStr.len() > 0)
    	{
       	 delete [] p->s;
       	 p->s = new char[ retStr.len() + 1];
       	 strcpy(p->s, retStr());
       	 len(strlen(p->s));
       	 wcount(wordCount(p->s, p->d));
    	}
	return (count);
}
int mstring::swap(const char* t,  const char* r)
{

    mstring retVal;
    mstring token;
    mstring targetStr = t;
    mstring replaceStr = r;
    int numSwapped = 0;
    mstring copy = p->s;
    // cout << "mstring(cutn(int wordToDrop, char *delimiter)): copy is ---> " << copy<< endl;
    token = copy.parse(copy.delimiter());
    for (int i = 0; i < copy.wcount(); i++)
    {
        if (token != targetStr)
        {

                // cout << "i:" << i << " mstring(cutn(int wordToDrop, char *delimiter)): token is ---> " << t oken<< endl;
                retVal += token();
                retVal += " ";
                // cout << "i:" << i << " mstring(cutn(int wordToDrop, char *delimiter)): keeping retVal is -- -> " << retVal<< endl;
                token = copy.parse(copy.delimiter());
        }
        else
        {
                retVal += replaceStr();
                retVal += " ";
                token = copy.parse(copy.delimiter());
                // cout << "i:" << i << " mstring(cutn(int wordToDrop, char *delimiter)): cutting retVal is -- -> " << retVal<< endl;
	 	numSwapped++;
        }
    }
    // cout << "mstring(cutn(int wordToDrop, char *delimiter)): retVal is ---> " << retVal<< endl;
    if (retVal.len() > 0)
    {
        delete [] p->s;
        p->s = new char[ retVal.len() + 1];
        strcpy(p->s, retVal());
        len(strlen(p->s));
        wcount(wordCount(p->s, p->d));
    }

    return (numSwapped);

/********** Old Swap *****************

void mstring::swap(const char* t,  const char* r, int howMany)
{

    // cout << " Getting a new memory block" << "\n";
    mstring workStr = p->s;
    // cout << " Got a new memory block" << "\n";
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
    
        if (workStr.p->s[index] == targetStr.p->s[targetIndex] && numMatchesFound < sizeOfTarget && ! swapComplete)
        {
            numMatchesFound++;
			#ifdef DEBUG
			// cout << "(" << index << ")" << "Match found: " << workStr.p->s[index] << "==" << targetStr.p->s[targetIndex] << ". Number of matched elements: " << numMatchesFound << " Replace: " << workStr <<  "  Target: " << targetStr << "\n";
			#endif
			if (targetIndex < (sizeOfTarget - 1))
            	targetIndex++; 
            value = workStr.p->s[index];
            disCard += value();
	 allMatched = TRUE;
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
				#ifdef DEBUG
				 // cout << "(" << index << ")" << "MString:Match NOT found: output -- " << retStr << "::\n";
				 // cout << "(" << index << ")" << "SWAPING \n " << "disCard is: " << disCard << ":\n";
				 // cout << "(" << index << ")" << "TRIGGER IS: " << workStr.p->s[index] << ":\n";
				#endif
            }
			else if (numMatchesFound == sizeOfTarget && ! swapComplete) // we found the whole thing	
			{
				allMatched = FALSE;
				retStr += replaceStr();
                value = workStr.p->s[index];
                retStr += value();
				#ifdef DEBUG
				// cout << "(" << index << ")" << "SWAPPED \n " << "retStr is now: " << retStr << ":\n";
				// cout << "(" << index << ")" << "MString:Match found: output -- " << retStr << "::\n";
				#endif
				if (howMany != OPERATE_ALL) // the default here is OPERATE_FIRST
				{
					swapComplete = TRUE;
				}
				numMatchesFound = 0;
				targetIndex = 0;
					
			}
            else
            {   
                value = workStr.p->s[index];
               	retStr += value();
				#ifdef DEBUG
				 // cout << "(" << index << ")" << "KEEPING: " << retStr << ":\n";
				#endif

            }
 
    	}	
    }
    delete [] p->s;
    p->s = new char[ retStr.len() + 1];
    strcpy(p->s, retStr());
    len(strlen(p->s));
	#ifdef DEBUG
		// cout << "FINAL retStr is: " << retStr << ":\n";
	#endif
    wcount(wordCount(p->s, p->d));
	**************** End of old Swap *************/
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
	wcount(wordCount(p->s, p->d));
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
		np->d = new char[strlen(p->d) + 1];
		strcpy(np->d, p->d);
		np->pcount = 0;
		np->_lenStr = strlen(np->s);
		wcount(wordCount(np->s, p->d));
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
	mstring workStr = p->s;
	mstring retVal;
	mstring *val;


	if (s)
	{
		char *token;
		// first let us see how many tokens there are, if any
		if(strstr(workStr(), s))
			token = strtok(workStr(), s);
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
			retVal=token;
		}
		else
		{
			retVal="";
			p->pcount = 0;
		}
	}
	else
		p->pcount = 0;

	
	val = new mstring(retVal);
	return val;

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
		wcount(wordCount(p->s, p->d));
	}
	return *this;
}


mstring& mstring::cutn(int wordToDrop, char *delimiter)
{
    mstring retVal;
    mstring token;
    int pos = 0;
    mstring copy = p->s;
    // cout << "mstring(cutn(int wordToDrop, char *delimiter)): copy is ---> " << copy<< endl;
    if (copy.cPos(' '))
    {
    	// token = copy.parse(delimiter); 
    	// cout << " mstring(cutn(int wordToDrop, char *delimiter)): token is ---> " << token<< endl;
    }
    for (int i = 0; i < copy.wcount(); i++)
    {
	if (pos != wordToDrop)
	{
		// cout << "Position to drop: " << wordToDrop << " Current postion: " << pos << endl;

    		token = copy.parse(delimiter); 
    		// cout << "i:" << i << " mstring(cutn(int wordToDrop, char *delimiter)): token is ---> " << token<< endl;
		retVal += token();
		retVal += " ";
		pos++;
    		// cout << "i:" << i << " mstring(cutn(int wordToDrop, char *delimiter)): keeping retVal is ---> " << retVal<< endl;
	}
	else
	{
		// cout << "Position to drop: " << wordToDrop << " Current postion: " << pos << endl;
		if (token.ccount("\n"))
		{
			// cout << "Adding \n" << endl;
			retVal += "\n";
		}
    		token = copy.parse(delimiter); 
    		// cout << "i:" << i << " mstring(cutn(int wordToDrop, char *delimiter)): cutting retVal is ---> " << retVal<< endl;
		pos++;
	}
    }
    // cout << "mstring(cutn(int wordToDrop, char *delimiter)): retVal is ---> " << retVal<< endl;
    if (retVal.len() > 0)
    {
	delete [] p->s;
	p->s = new char[ retVal.len() + 1];
	strcpy(p->s, retVal());
	len(strlen(p->s));
	wcount(wordCount(p->s, p->d));
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
	int pos = 0;
		char *copy = new char[strlen(p->s) + 1];
		strcpy(copy, p->s);
		token = strtok(copy, delimiter);
		while (token)
		{
			if (pos == wordToGet)
			{
				break;
			}
			pos++;
			token = strtok(NULL, delimiter);
		}
	retVal = new mstring(token);
	return(retVal);
}

int mstring::wPos(char *s)
{
    	int pos = 1;
	int	match = FALSE;
	mstring target = s;
	mstring copy = p->s;
	mstring del = p->d;
	// target = target.deSpace();
	// copy = copy.deSpace();
	#ifdef DEBUG
		cout << "mstring(wPos(char *s)): looking for ---> \"" << target() << "\"<BR>" << endl;
		cout << "mstring(wPos(char *s)): copy is --->\"" << copy() << "\"<BR>" << endl;
 	#endif
	mstring token;
        token = copy.parse(del); 
        for (int i = 0; i < copy.wcount(); i++)
        {
	    
 	    #ifdef DEBUG
	    	cout << "mstring(wPos(char *s)): Token is ---> " << token << "<BR>" << endl;
 	    #endif
            // if (strstr(target(), token()))
	    if (strcmp(token(),target()) == 0)
	    {
		match = TRUE;
               	break;
	    }
	    token = copy.parse(del);
            pos++;
        }
	if (! match)
		pos = 0;
 	#ifdef DEBUG
		cout << "mstring(wPos(char *s)): match is ---> " << match << "<BR>" << endl;
		cout << "mstring(wPos(char *s)): pos is ---> " << pos << "<BR>" << endl;
 	#endif
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
		temp.parse("0");
		while(temp.parse(s))
			count++;
		count--;
	}
	p->count = currentParseNum;
	return count;
	*/
}
int wordCount(const char *s, const char *d)
{
	int count = 0;
	if (s)
	{
		char *copy = new char[strlen(s) + 1];
		strcpy(copy, s);
		char *token = strtok(copy, d);
		while (token)
		{
			count++;
			token = strtok(NULL, d);
		}
		delete [] copy;
	}
	return(count);
}

int wordCount(char *s, char *d)
{

	int count = 0;
	if (s)
	{
		char *copy = new char[strlen(s) + 1];
		strcpy(copy, s);
		char *token = strtok(copy, d);
		while (token)
		{
			count++;
			token = strtok(NULL, d);
		}
		delete [] copy;
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

mstring *mstring::upper()
{
	mstring *ret;
	mstring retVal;
	retVal.delimiter(p->d);
	mstring copy = p->s;
	int i = 0;
	while (copy[i] != '\0')
		retVal += toupper(copy[i++]);

	// mstring *retStrPtr = new mstring(retStr);
	mstring *retPtr = new mstring(retVal());
	return (retPtr);
}

mstring *mstring::lower()
{
	char temp[BUFSIZ];
	mstring retStr;
	char *copy = new char[strlen(p->s) + 1];
	strcpy(copy, p->s);
	strcpy(temp, "");
	int lenCopy = strlen(copy);
	retStr.delimiter(p->d);

	while (*copy != '\0')
	{
		sprintf(temp, "%c", tolower(*copy++));
		retStr += temp;
	}

	for (int i = 0; i < lenCopy; i++)
		copy--;

	// mstring *retStrPtr = new mstring(retStr());
	delete [] copy;
	mstring *retPtr = new mstring(retStr());
	return (retPtr);
}

mstring mstring::rmNonPrint()
{
        mstring ret;
        mstring copy = p->s;
        mstring retVal;
	retVal.delimiter(p->d);
        int i = 0;
        while (copy[i] != '\0')
	{
		if (isascii(copy[i]))
                	retVal += copy[i];
		i++;
	}
        // mstring *retStrPtr = new mstring(retStr);
        ret = retVal();
	ret.delimiter(retVal.delimiter());
        return (ret);
}

mstring * mstring::rmNonPrint(char *sub)
{
        mstring *ret;
        mstring copy = p->s;
        mstring retVal;
        retVal.delimiter(p->d);
        int i = 0;
        while (copy[i] != '\0')
        {
                if (isascii(copy[i]))
                        retVal += copy[i];
		else
                        retVal += sub;
                i++;
        }
        // mstring *retStrPtr = new mstring(retStr);
        mstring *retPtr = new mstring(retVal());
        retPtr->delimiter(retVal.delimiter());
        return (retPtr);
}

void mstring::to64() 
{
	int c[3], ct = 0, tc = 0;
    	mstring workStr = p->s;
	mstring tempChar;
	mstring retStr;
   	mstring basis_64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char *tempstr = new char[workStr.len()*2];

	int numTimes = workStr.len() / 3;
	for (int index = 0; index < numTimes ; index++)
	{
		//c[0] = (int)workStr[index * 3];
		//c[1] = (int)workStr[(index * 3) + 1];
		//c[2] = (int)workStr[(index * 3) + 2];

		tempstr[tc++]=basis_64[((int)workStr[index*3])>>2];
		tempstr[tc++]=basis_64[
			(( ((int)workStr[index * 3]) & 0x3)<< 4) | 
			(( ((int)workStr[(index * 3) + 1])& 0xF0) >> 4)];

		tempstr[tc++]= basis_64[
			(( (int)workStr[(index * 3) + 1] & 0xF) << 2) | 
			(( (int)workStr[(index * 3) + 2] & 0xC0) >>6)];
		tempstr[tc++]= basis_64[(int)workStr[(index * 3) + 2] & 0x3F];

		//tempChar = basis_64[c[0]>>2];
		//tempChar += basis_64[((c[0] & 0x3)<< 4) | ((c[1] & 0xF0)>> 4)];
		//tempChar += basis_64[((c[1] & 0xF) << 2) | ((c[2] & 0xC0) >>6)];
		//tempChar += basis_64[c[2] & 0x3F];
		ct++;
		if (ct > 21)
		{
			tempstr[tc++]='\n';
			//retStr += "\n";
			ct = 0;
		}
		//retStr += tempChar;
	}
	if (workStr.len() % 3)
	{
		tempstr[tc++]=basis_64[(int)workStr[ numTimes* 3]>>2];
   		//tempChar = basis_64[c[0]>>2];
    		//tempChar += basis_64[((c[0] & 0x3)<< 4) | ((c[1] & 0xF0) >> 4)];
		tempstr[tc++]=basis_64[
		    (( (int)workStr[numTimes*3] & 0x3)<< 4) | 
		    (( (int)workStr[(numTimes*3) +1] & 0xF0) >> 4)];
		//retStr += tempChar;
		if (3 - (workStr.len() % 3) == 2)
		{
			//tempChar = '=';
			//tempChar += '=';
			retStr += tempChar;
			tempstr[tc++]='=';
			tempstr[tc++]='=';
		}
    		else 
		{
        		//tempChar = basis_64[((c[1] & 0xF) << 2) | ((c[2] & 0xC0) >>6)];
		    tempstr[tc++] = basis_64[
		        (( (int)workStr[(numTimes*3)+1] & 0xF) << 2) | 
		        (( (int)workStr[(numTimes*3)+2] & 0xC0) >>6)];
		    tempstr[tc++]= '=';
			//retStr += tempChar;
		}
	}
        tempstr[tc++]='\0';
	retStr=tempstr;

    	delete [] p->s;
    	p->s = new char[ retStr.len() + 1];
    	strcpy(p->s, retStr());
    	len(strlen(p->s));
        #ifdef DEBUG
                // cout << "FINAL retStr is: " << retStr << ":\n";
        #endif
    	wcount(wordCount(p->s, p->d));
}
mstring mstring::deCntrl(char *replace)
{
        mstring retStr;
        char *copy = new char[strlen(p->s) + 1];
        strcpy(copy, p->s);
        int lenCopy = strlen(copy);

        while (*copy != '\0')
        {
                if(! iscntrl(*copy))
                        retStr += *copy;
                else
                        retStr += replace;
                copy++;
        }
        for (int i = 0; i < lenCopy; i++)
                copy--;
        delete [] copy;
        retStr.len(strlen(retStr.p->s));
        return retStr;
}
void error(char * msg)
{
        mstring errMsg = "mtring error: ";
        errMsg += msg;
        perror(errMsg());
}

