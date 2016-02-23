h24484
s 00013/00010/00104
d D 1.2 97/07/15 12:21:21 mstemen 2 1
c 
e
s 00114/00000/00000
d D 1.1 97/02/14 11:21:10 mstemen 1 0
c date and time created 97/02/14 11:21:10 by mstemen
e
u
U
f e 0
t
T
I 1
#ifndef _MSTRING_H
#define _MSTRING_H
#include <iostream.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#ifndef TRUE
	#define TRUE 1
	#define FALSE !TRUE
#endif

#define ERROR_INDEX_OUT_OF_BOUNDS "index out of range"
#define OPERATE_FIRST 0
#define OPERATE_ALL   1

class mstring {

	public:
		mstring();
		mstring(const char* );
D 2
		mstring(char *);
		mstring(char);
E 2
I 2
		// mstring(char *);
		mstring(const char);
E 2
		mstring(const mstring& );
D 2
		mstring(mstring*);
E 2
I 2
		mstring(const mstring*);
E 2
		mstring& operator=(const char *);
		mstring& operator=(const mstring &);
D 2
		mstring& operator=(const int);
E 2
I 2
		// mstring& operator=(const int);
E 2
	
		// user defined type conversion

		operator char *() { return p->s;}
		operator const char*() { return p->s;}
		operator const char() { return *p->s;}
		operator const int() { return atoi(p->s); }
		operator int() { return atoi(p->s); }

		~mstring();
		const char* operator[] (int i ) const;
		char operator [] (int i);

		friend int operator==(const mstring &x, char *s)
			{return strcmp(x.p->s, s) == 0; }
		friend int operator==(const mstring &x, const char *s)
			{return strcmp(x.p->s, s) == 0; }
		friend int operator==(const mstring &x, const mstring &y)
			{return strcmp(x.p->s, y.p->s) == 0; }
		friend int operator!=(const mstring &x, const char *s)
			{return strcmp(x.p->s, s) != 0; }
		friend int operator!=(const mstring &x, const mstring &y)
			{return strcmp(x.p->s, y.p->s) != 0; }
		friend ostream&  operator<<(ostream& s, const mstring& x)
			{ return s << x.p->s;}

		mstring& operator+=(const mstring &x);
		mstring& operator+=(const char *x);
		mstring& operator+=(const int x);
		mstring& operator-=(const mstring &x);
		mstring& operator-=(const char *x);
		mstring operator+ (const int y);
D 2
		int sndLike(const mstring &x);
E 2
I 2
		int sndLike(char * x);
E 2

		mstring& mstring::cutn(int wordToDrop, char *delimiter);
		mstring& mstring::clipn(int posToDrop);

		char* operator()() const { return p->s;}

D 2
		mstring* parse(const char *s);
E 2
I 2
		mstring*  parse(const char *s);
E 2
		mstring* sub(const int s);
		mstring* sub(const char *s);
		mstring* sub(const mstring x);
		void clear(){ p->pcount=0;} 
		void delimiter(char *d);
		char *delimiter();
		int ccount(char *s);
		int len() const { return p->_lenStr;}
		int wcount(){ return p->_numWords;}
		int cPos(char s);
		int wPos(char *s);
		int index();
		char* charAtIndex();
		char* charAtIndex(int index);
		int mstring::find(const mstring &x, int index);
		// mstring wordAtIndex();
		mstring *wordAtIndex(int index);
		mstring *wPos(int wordToGet, char *delimiter);
D 2
		mstring upper();
		mstring lower();
E 2
I 2
		mstring *upper();
		mstring *lower();
E 2
		mstring deSpace();
		mstring deXSpaces();
D 2
		void swap(const char* t,  const char* r, int howMany);
E 2
I 2
		// void swap(const char* t,  const char* r, int howMany);
		int swap(const char* t,  const char* r);
		int cSwap(const char t,  const char r);
E 2
		int isBlank();
I 2
		void to64();
		mstring* sndxCalc(); // const; 
E 2
	private:

		struct 	srep 
			{
				char*	s;
				char*	d;
				int		n;
				int		pcount; // counter for the parser
				int		_lenStr;
				int    _numWords;
				int		_index;
				srep() {n = 1;}
			};

			srep 	*p;
		void len(int newLen){ p->_lenStr = newLen;}
		void wcount(int newWCount){p->_numWords = newWCount;}
D 2
		mstring* sndxCalc() const; 
E 2
};


#endif
E 1
