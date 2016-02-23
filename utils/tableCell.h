/*
** File: tableCell.h SCCS 1.2 - 8/4/95
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

#ifndef TABLE_CELL_H
#define TABLE_CELL_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <fstream.h>
#include "mstring.h"
// #include <stream.h>

#ifndef true
        #define true    1
        #define false   ! true
#endif

class   tableCell 
{        
        public:  
                        tableCell();
                        tableCell(char *val);
			tableCell(tableCell *x);
			~tableCell();

			mstring       value();
			void	      value(const mstring val);
			int	      deleted();
			void	      deleted(const int tfval);
                 
        private: 
 
        mstring         _value;
	int		_deleted;
};
inline int tableCell::deleted(){return _deleted;}
inline void tableCell::deleted(const int tfval){_deleted = tfval;}
inline void tableCell::value(const mstring val){_value = val();}
inline mstring tableCell::value(){ return _value();}
#endif
