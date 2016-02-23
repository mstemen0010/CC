h03535
s 00018/00000/01425
d D 1.4 97/07/18 09:41:48 mstemen 4 3
c 
e
s 00484/00274/00941
d D 1.3 97/07/15 12:21:03 mstemen 3 2
c fixed various things
e
s 00275/00066/00940
d D 1.2 97/03/19 10:20:32 mstemen 2 1
c 
e
s 01006/00000/00000
d D 1.1 97/01/31 13:01:56 mstemen 1 0
c date and time created 97/01/31 13:01:56 by mstemen
e
u
U
f e 0
t
T
I 1
#include <errno.h>
#include <stdio.h>
#include "mstring.h"
I 3
// #define DEBUG
E 3

I 3

E 3
void error(char * msg);
D 2
int wordCount(const char *s);
int wordCount(char *s);
E 2
I 2
int wordCount(const char *s, const char *d);
int wordCount(char *s, char *d);
E 2


mstring::mstring()
{
	p = new srep;
D 3
	p->s = new char[1];
E 3
I 3
	p->s = new char[2];
E 3
	strcpy(p->s, "");
	len(strlen(p->s));
	wcount(0);
	p->pcount = 0;
I 2
	p->_index = 0;
D 3
	p->d = new char[1];
E 3
I 3
	p->d = new char[3];
E 3
	strcpy(p->d, " ");
E 2
}
D 3
mstring::mstring(mstring* x)
E 3
I 3
mstring::mstring(const mstring* x)
E 3
{
	if (x)
	{
		x->p->n++;
		p = x->p;
		p->pcount = 0;
I 2
		p->_index = 0;
E 2
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
I 2
		p->_index = 0;
E 2
	}
	else
		p = NULL;
}
D 3
mstring::mstring(char s)
E 3
I 3
mstring::mstring(const char s)
E 3
{
	p = new srep;
	p->s = new char[2];
	p->s[0] = s;
	p->s[1] = NULL;
I 2
	p->_index = 0;
D 3
	p->d = new char[1];
E 3
I 3
	p->d = new char[2];
E 3
	strcpy(p->d, " ");
E 2

	p->pcount = 0;
	len(strlen(p->s));
D 2
	wcount(wordCount(p->s));
E 2
I 2
	wcount(wordCount(p->s, p->d));
E 2
}


mstring::mstring(const char* s)
{
	p = new srep;
	p->s = new char[ strlen(s) + 1];
	strcpy(p->s, s);
	p->pcount = 0;
I 2
	p->_index = 0;
E 2
	len(strlen(p->s));
D 2
	wcount(wordCount(s));
E 2
I 2
D 3
	p->d = new char[1];
E 3
I 3
	p->d = new char[2];
E 3
	strcpy(p->d, " ");
	wcount(wordCount(s, p->d));
E 2
}
I 3
/*
E 3
mstring::mstring(char* s)
{
I 3
	char *t = s;
E 3
	p = new srep;
D 3
	p->s = new char[ strlen(s) + 1];
	strcpy(p->s, s);
E 3
I 3
	p->s = new char[ strlen(t) + 1];
	strcpy(p->s, t);
E 3
	p->pcount = 0;
I 2
	p->_index = 0;
E 2
	len(strlen(p->s));
D 2
	wcount(wordCount(s));
E 2
I 2
D 3
	p->d = new char[1];
E 3
I 3
	p->d = new char[2];
E 3
	strcpy(p->d, " ");
D 3
	wcount(wordCount(s, p->d));
E 3
I 3
	wcount(wordCount(t, p->d));
E 3
E 2
}
I 3
*/
E 3
mstring::~mstring()
{
D 3
	if (--p->n == 0)
E 3
I 3
	if (p)
E 3
	{
D 3
		delete [] p->s;
I 2
		delete [] p->d;
E 2
		delete p;
E 3
I 3
		if (--p->n == 0)
		{
			if (p->s)
				delete [] p->s;
			if (p->d)
				delete [] p->d;
			if (p)
				delete p;
		}
E 3
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

D 3
		delete [] p->s;
E 3
I 3
		delete[] p->s;
E 3

	p->s = new char [ strlen(s) + 1];
I 4
	p->d = new char[2];
	strcpy(p->d, " ");
E 4
	strcpy(p->s, s);
	len(strlen(p->s));
D 3
	/*
	mstring tempStr = p->s;
	p->_numWords = tempStr.ccount(" ");
	p->_numWords++;
	*/
E 3
	p->pcount = 0;
D 2
	wcount(wordCount(p->s));
E 2
I 2
	wcount(wordCount(p->s, p->d));
E 2
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

I 2
D 3
mstring& mstring::operator=(const int x)
{
	char s[BUFSIZ];
E 3
	
D 3
	sprintf(s, "%d", x);
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
	p->pcount = 0;
	wcount(wordCount(p->s, p->d));
	return *this;

}
	
E 3
E 2
mstring& mstring::operator=(const mstring& x)
{
	x.p->n++; // protect against "st = st"
	if (--p->n == 0)
	{
		delete [] p->s;
I 3
		delete [] p->d;
E 3
		delete p;
	}
I 3
	
E 3
	p = x.p;
D 3
	len(strlen(p->s));
D 2
	wcount(wordCount(p->s));
E 2
I 2
	wcount(wordCount(p->s, p->d));
E 3
E 2
	return *this;
}

I 2
mstring& mstring::operator+=(const int x)
{
    char s[BUFSIZ];
D 3
    sprintf(s, "%d", x);
E 3
I 3
    sprintf(s, "%c", x);
    // sprintf(s, "%d", x);
E 3
	mstring hold = p->s;
	delete [] p->s;
	p->s = new char[ hold.len() + strlen(s) + 1];
	strcpy(p->s, hold());
	strcat(p->s, s);
	len(strlen(p->s));
	wcount(wordCount(p->s, p->d));

	return *this;
}

E 2
mstring&  mstring::operator+=(const mstring &x)
{
	x.p->n++;
	mstring hold = p->s;
	delete [] p->s;
	p->s = new char[ hold.len() + x.len() + 1];
	strcpy(p->s, hold());
	strcat(p->s, x.p->s);
	len(strlen(p->s));
D 2
	wcount(wordCount(p->s));
E 2
I 2
	wcount(wordCount(p->s, p->d));
E 2

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
D 2
	wcount(wordCount(p->s));
E 2
I 2
	wcount(wordCount(p->s, p->d));
E 2

	return *this;
}
I 2
void mstring::delimiter(char *d)
{
	delete [] p->d;
	p->d = new char [ strlen(d) + 1];
	strcpy(p->d, d);
	wcount(wordCount(p->s, p->d));
}
E 2

I 2
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
char *mstring::charAtIndex(int index)
{
	return (char *)p->s[p->_index];
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


E 2
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
D 2
	wcount(wordCount(p->s));
E 2
I 2
	wcount(wordCount(p->s, p->d));
E 2
	return *this;
}

D 3
int mstring::sndLike(const mstring &x)
E 3
I 3
int mstring::sndLike( char *x)
E 3
{
D 3
    int num;
    int wordLen;
    int i, similarities;
    float  value, lenValue, ssave, lsave;
E 3
I 3
    	int num;
    	int wordLen;
    	int i, similarities;
    	float  value, lenValue, ssave, lsave;
	mstring codeC1, codeC2;
E 3

 
D 3
	mstring copy = p->s;
	int lenC1 = copy.len(); // ourselves
	int lenC2 = x.len();    // what we are being compared to
E 3
I 3
	mstring copy1 = p->s;
	mstring copy2 = x;
	int lenC1 = copy1.len(); // ourselves
	int lenC2 = copy2.len();    // what we are being compared to
E 3

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
	
D 3
	mstring codeC1 = copy.sndxCalc();
	mstring codeC2 = x.sndxCalc();
E 3
I 3
	codeC1 = copy1.sndxCalc();

	codeC2 = copy2.sndxCalc();
E 3
 
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
D 3
        num = value * 100;
E 3
I 3
        num = (int) value * 100;
E 3
    }
    else
        num = 0;
 
    return (num);
} 

D 3
mstring *mstring::sndxCalc() const
E 3
I 3
mstring *mstring::sndxCalc() // const
E 3
{
   /* Calculate a "soundex" hash code given a string */

	int	 discard, i;
	int      place = 1;
	mstring  hCode;
	mstring  code;
D 3
	mstring  workStr = p->s;
	workStr = workStr.upper();
E 3
I 3
	mstring  tempStr = p->s;
	mstring  workStr = tempStr.upper();
  	mstring *retPtr;
	mstring token = "EMPTY";
E 3

D 3
	int length = workStr.len();
E 3
 
 
D 3
    // strcpy(hCode, "");
E 3

D 3
    // ch = toupper(s[0]);
E 3
I 3
   	 while (token.len())
    	{
    		token = workStr.parse(" ");
		int length = token.len();
E 3

D 3
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
E 3
I 3
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
E 3
						{
D 3
	                        if (workStr[i - 2] == 'S') 
	                            discard = TRUE;
E 3
I 3
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
E 3
						}
D 3
	                }
	                break;
				*/
E 3
I 3
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
E 3
	 
D 3
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
E 3
I 3
	    		if (! discard) 
					hCode += code();
			}
	        code = "";
	    } /* end for */
	}
E 3
	
D 3
	 
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

E 3
I 3
	
E 3
	mstring retStr = hCode[0];
I 3

E 3
	for (i = 1; i < hCode.len(); i++)
	{
		
		if (hCode[i] != hCode[i - 1])
			retStr += hCode[i];
	}
D 3
  	mstring *returnCode = new mstring(retStr());
	return returnCode;
E 3

I 3
  	retPtr = new mstring(retStr);
	return retPtr;

E 3
} /* end sndxCalc */


I 3
int mstring::cSwap(const char t,  const char r)
{
E 3

I 3
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
E 3

I 3
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
E 3

I 3
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

E 3
void mstring::swap(const char* t,  const char* r, int howMany)
{
I 3

    // cout << " Getting a new memory block" << "\n";
E 3
    mstring workStr = p->s;
I 3
    // cout << " Got a new memory block" << "\n";
E 3
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
    
D 3
        if (workStr.p->s[index] == targetStr.p->s[targetIndex])
E 3
I 3
        if (workStr.p->s[index] == targetStr.p->s[targetIndex] && numMatchesFound < sizeOfTarget && ! swapComplete)
E 3
        {
            numMatchesFound++;
D 3
			// cout << "Match found: " << workStr.p->s[index] << "==" << targetStr.p->s[targetIndex] << ". Number of matched elements: " << numMatchesFound << ".\n";
E 3
I 3
			#ifdef DEBUG
			// cout << "(" << index << ")" << "Match found: " << workStr.p->s[index] << "==" << targetStr.p->s[targetIndex] << ". Number of matched elements: " << numMatchesFound << " Replace: " << workStr <<  "  Target: " << targetStr << "\n";
			#endif
E 3
			if (targetIndex < (sizeOfTarget - 1))
            	targetIndex++; 
            value = workStr.p->s[index];
            disCard += value();
I 3
	 allMatched = TRUE;
E 3
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
D 3
				// cout << "MString:Match NOT found: output -- " << retStr << "::\n";
E 3
I 3
				#ifdef DEBUG
				 // cout << "(" << index << ")" << "MString:Match NOT found: output -- " << retStr << "::\n";
				 // cout << "(" << index << ")" << "SWAPING \n " << "disCard is: " << disCard << ":\n";
				 // cout << "(" << index << ")" << "TRIGGER IS: " << workStr.p->s[index] << ":\n";
				#endif
E 3
            }
			else if (numMatchesFound == sizeOfTarget && ! swapComplete) // we found the whole thing	
			{
D 3
				// cout << "SWAPING \n " << "disCard is: " << disCard << ":\n";
				// cout << "TRIGGER IS: " << workStr.p->s[index] << ":\n";
E 3
				allMatched = FALSE;
				retStr += replaceStr();
                value = workStr.p->s[index];
                retStr += value();
D 3
				// cout << "SWAPPED \n " << "retStr is now: " << retStr << ":\n";
				// cout << "MString:Match found: output -- " << retStr << "::\n";
				if (howMany == OPERATE_ALL) // the default here is OPERATE_FIRST
E 3
I 3
				#ifdef DEBUG
				// cout << "(" << index << ")" << "SWAPPED \n " << "retStr is now: " << retStr << ":\n";
				// cout << "(" << index << ")" << "MString:Match found: output -- " << retStr << "::\n";
				#endif
				if (howMany != OPERATE_ALL) // the default here is OPERATE_FIRST
E 3
				{
D 3
					numMatchesFound = 0;
				}
				else
E 3
					swapComplete = TRUE;
I 3
				}
				numMatchesFound = 0;
				targetIndex = 0;
E 3
					
			}
            else
            {   
                value = workStr.p->s[index];
               	retStr += value();
D 3
				// cout << "KEEPING: " << retStr << ":\n";
E 3
I 3
				#ifdef DEBUG
				 // cout << "(" << index << ")" << "KEEPING: " << retStr << ":\n";
				#endif
E 3

            }
 
    	}	
    }
D 3
	if (allMatched)
		retStr = replaceStr();
E 3
    delete [] p->s;
    p->s = new char[ retStr.len() + 1];
D 3
    strcpy(p->s, retStr.p->s);
E 3
I 3
    strcpy(p->s, retStr());
E 3
    len(strlen(p->s));
D 3
	// cout << "FINAL retStr is: " << retStr << ":\n";
E 3
I 3
	#ifdef DEBUG
		// cout << "FINAL retStr is: " << retStr << ":\n";
	#endif
E 3
D 2
    wcount(wordCount(p->s));
E 2
I 2
    wcount(wordCount(p->s, p->d));
I 3
	**************** End of old Swap *************/
E 3
E 2
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
D 2
	wcount(wordCount(p->s));
E 2
I 2
	wcount(wordCount(p->s, p->d));
E 2
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
I 3
		np->d = new char[strlen(p->d) + 1];
		strcpy(np->d, p->d);
E 3
		np->pcount = 0;
		np->_lenStr = strlen(np->s);
D 2
		wcount(wordCount(np->s));
E 2
I 2
		wcount(wordCount(np->s, p->d));
E 2
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
I 3
	mstring workStr = p->s;
	mstring retVal;
	mstring *val;
E 3


	if (s)
	{
D 3
		mstring tmp = p->s;
		mstring *retVal;
E 3
		char *token;
		// first let us see how many tokens there are, if any
D 3
		if(strstr(tmp(), s))
			token = strtok(tmp(), s);
E 3
I 3
		if(strstr(workStr(), s))
			token = strtok(workStr(), s);
E 3
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
D 3
			retVal = new mstring(token);
			return(retVal);
E 3
I 3
			retVal=token;
E 3
		}
		else
		{
D 3
			retVal = new mstring("");
E 3
I 3
			retVal="";
E 3
			p->pcount = 0;
D 3
			return(retVal);
E 3
		}
	}
	else
		p->pcount = 0;

I 3
	
	val = new mstring(retVal);
	return val;

E 3
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
D 2
		wcount(wordCount(p->s));
E 2
I 2
		wcount(wordCount(p->s, p->d));
E 2
	}
	return *this;
}


mstring& mstring::cutn(int wordToDrop, char *delimiter)
{
    mstring retVal;
D 3
    char *token;
    int pos = 1;
    char *copy = new char[strlen(p->s) + 1];
    strcpy(copy, p->s);
    token = strtok(copy, delimiter);
    while (token)
E 3
I 3
    mstring token;
    int pos = 0;
    mstring copy = p->s;
    // cout << "mstring(cutn(int wordToDrop, char *delimiter)): copy is ---> " << copy<< endl;
    if (copy.cPos(' '))
E 3
    {
I 3
    	// token = copy.parse(delimiter); 
    	// cout << " mstring(cutn(int wordToDrop, char *delimiter)): token is ---> " << token<< endl;
    }
    for (int i = 0; i < copy.wcount(); i++)
    {
E 3
	if (pos != wordToDrop)
	{
D 3
		retVal += token;
E 3
I 3
		// cout << "Position to drop: " << wordToDrop << " Current postion: " << pos << endl;

    		token = copy.parse(delimiter); 
    		// cout << "i:" << i << " mstring(cutn(int wordToDrop, char *delimiter)): token is ---> " << token<< endl;
		retVal += token();
		retVal += " ";
E 3
		pos++;
D 3
		token = strtok(NULL, delimiter);
E 3
I 3
    		// cout << "i:" << i << " mstring(cutn(int wordToDrop, char *delimiter)): keeping retVal is ---> " << retVal<< endl;
E 3
	}
	else
D 3
		break;
	retVal += token;
E 3
I 3
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
E 3
    }
I 3
    // cout << "mstring(cutn(int wordToDrop, char *delimiter)): retVal is ---> " << retVal<< endl;
E 3
    if (retVal.len() > 0)
    {
	delete [] p->s;
D 3
	p->s = new char[ strlen(retVal.p->s) + 1];
	strcpy(p->s, retVal.p->s);
E 3
I 3
	p->s = new char[ retVal.len() + 1];
	strcpy(p->s, retVal());
E 3
	len(strlen(p->s));
D 2
	wcount(wordCount(p->s));
E 2
I 2
	wcount(wordCount(p->s, p->d));
E 2
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

D 2
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

E 2
mstring * mstring::wPos(int wordToGet, char *delimiter)
{
	mstring *retVal;
	char *token;
D 3
	int pos = 1;
E 3
I 3
	int pos = 0;
E 3
D 2
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
E 2
I 2
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
E 2
	retVal = new mstring(token);
	return(retVal);
}

int mstring::wPos(char *s)
{
D 2
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
E 2
I 2
    	int pos = 1;
	int	match = FALSE;
D 3
    if (s)
    {
        char *copy = new char[strlen(p->s) + 1];
        strcpy(copy, p->s);
        char *token = strtok(copy, " ");
        while (token)
E 3
I 3
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
E 3
        {
D 3
            if (strcmp(token, s) == 0)
E 3
I 3
	    
 	    #ifdef DEBUG
	    	cout << "mstring(wPos(char *s)): Token is ---> " << token << "<BR>" << endl;
 	    #endif
            // if (strstr(target(), token()))
	    if (strcmp(token(),target()) == 0)
E 3
	    {
D 3
				match = TRUE;
                break;
E 3
I 3
		match = TRUE;
               	break;
E 3
	    }
D 3
	   
E 3
I 3
	    token = copy.parse(del);
E 3
            pos++;
D 3
            token = strtok(NULL, " ");
E 3
        }
	if (! match)
		pos = 0;
D 3
    }
	// cout << pos << "\n";
E 3
I 3
 	#ifdef DEBUG
		cout << "mstring(wPos(char *s)): match is ---> " << match << "<BR>" << endl;
		cout << "mstring(wPos(char *s)): pos is ---> " << pos << "<BR>" << endl;
 	#endif
E 3
    return(pos);
E 2
}

I 2

E 2
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
D 3
		temp.parse(NULL);
E 3
I 3
		temp.parse("0");
E 3
		while(temp.parse(s))
			count++;
		count--;
	}
	p->count = currentParseNum;
	return count;
	*/
}
D 2
int wordCount(const char *s)
E 2
I 2
int wordCount(const char *s, const char *d)
E 2
{
	int count = 0;
	if (s)
	{
		char *copy = new char[strlen(s) + 1];
		strcpy(copy, s);
D 2
		char *token = strtok(copy, " ");
E 2
I 2
		char *token = strtok(copy, d);
E 2
		while (token)
		{
			count++;
D 2
			token = strtok(NULL, " ");
E 2
I 2
			token = strtok(NULL, d);
E 2
		}
I 3
		delete [] copy;
E 3
	}
	return(count);
}

D 2
int wordCount(char *s)
E 2
I 2
int wordCount(char *s, char *d)
E 2
{

	int count = 0;
	if (s)
	{
		char *copy = new char[strlen(s) + 1];
		strcpy(copy, s);
D 2
		char *token = strtok(copy, " ");
E 2
I 2
		char *token = strtok(copy, d);
E 2
		while (token)
		{
			count++;
D 2
			token = strtok(NULL, " ");
E 2
I 2
			token = strtok(NULL, d);
E 2
		}
I 3
		delete [] copy;
E 3
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

D 3
mstring mstring::upper()
E 3
I 3
mstring *mstring::upper()
E 3
{
D 3
	mstring retStr;
	char *copy = new char[strlen(p->s) + 1];
	strcpy(copy, p->s);
	int lenCopy = strlen(copy);
E 3
I 3
	mstring *ret;
	mstring retVal;
	mstring copy = p->s;
	int i = 0;
	while (copy[i] != '\0')
		retVal += toupper(copy[i++]);
E 3

D 3
	while (*copy != '\0')
		retStr += toupper(*copy++);
	for (int i = 0; i < lenCopy; i++)
		copy--;

	// mstring *retStrPtr = new mstring(retStr());
	delete [] copy;
	return retStr;
E 3
I 3
	// mstring *retStrPtr = new mstring(retStr);
	mstring *retPtr = new mstring(retVal());
	return (retPtr);
E 3
}

D 3
mstring mstring::lower()
E 3
I 3
mstring *mstring::lower()
E 3
{
I 2
	char temp[BUFSIZ];
E 2
	mstring retStr;
	char *copy = new char[strlen(p->s) + 1];
	strcpy(copy, p->s);
I 2
	strcpy(temp, "");
E 2
	int lenCopy = strlen(copy);

	while (*copy != '\0')
D 2
		retStr += tolower(*copy++);
E 2
I 2
	{
		sprintf(temp, "%c", tolower(*copy++));
		retStr += temp;
	}

E 2
	for (int i = 0; i < lenCopy; i++)
		copy--;

	// mstring *retStrPtr = new mstring(retStr());
I 2
	delete [] copy;
E 2
D 3
	return retStr;
E 3
I 3
	mstring *retPtr = new mstring(retStr());
	return (retPtr);
E 3
}

I 4
mstring * mstring::rmNonPrint()
{
        mstring *ret;
        mstring retVal;
        mstring copy = p->s;
        int i = 0;
        while (copy[i] != '\0')
	{
		if (isascii(copy[i]))
                	retVal += copy[i];
		i++;
	}
        // mstring *retStrPtr = new mstring(retStr);
        mstring *retPtr = new mstring(retVal());
        return (retPtr);
}
E 4
I 3

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
E 3
void error(char * msg)
{
	perror(msg);
}
E 1
