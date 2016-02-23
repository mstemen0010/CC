/*
** File: tableElement.h SCCS 1.2 - 8/4/95
**
** Author:   Matthew Stemen
**
**
**
** Created:  19 June 1995
**
**
**
** Purpose: 
**          
**        
**       
*/

#ifndef TABLE_ELEMENT_H
#define TABLE_ELEMENT_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <fstream.h>
#include "mstring.h"
// #include <stream.h>

#ifndef TRUE
        #define TRUE    1
        #define FALSE   ! TRUE
#endif

class   tableElement 
{        
        public:  
                        tableElement();
                        tableElement(char *val);
			~tableElement();

                        void next(tableElement *newNext);
                        void first(tableElement *newNext);
                        tableElement *first();
                        tableElement *next();
			mstring       value();
			void	      value(mstring newValue);
			bool	      deleted();
			void	      deleted(bool tfval);
                 
        private: 
 
        mstring         _value;
        tableElement    *_next;
        tableElement    *_first;
	bool		_deleted;
};
inline void tableElement::next(tableElement *newNext){ _next = newNext ;}
inline void tableElement::first(tableElement *newFirst){ _first = newFirst;}
inline tableElement *tableElement::next(){ return _next ;}
inline tableElement *tableElement::first(){ return _first;}
inline mstring tableElement::value(){ return _value;}
inline bool tableElement::deleted(){return _deleted;}
inline void tableElement::deleted(bool tfval){_deleted = tfval;}
			void	      deleted(bool tfval);
inline void tableElement::value(mstring newValue){ _value = newValue();}
#endif
