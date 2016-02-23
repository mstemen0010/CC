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
		mstring(char *);
		mstring(char);
		mstring(const mstring& );
		mstring(mstring*);
		mstring& operator=(const char *);
		mstring& operator=(const mstring &);
		mstring& operator=(const int);
	
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
		int sndLike(const mstring &x);

		mstring& mstring::cutn(int wordToDrop, char *delimiter);
		mstring& mstring::clipn(int posToDrop);

		char* operator()() const { return p->s;}

		mstring* parse(const char *s);
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
		mstring upper();
		mstring lower();
		mstring deSpace();
		mstring deXSpaces();
		void swap(const char* t,  const char* r, int howMany);
		int isBlank();
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
		mstring* sndxCalc() const; 
};


#endif
