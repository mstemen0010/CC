#ifndef _40K_AB_CDX_H_
#define _40K_AB_CDX_H_

#include "40ksquad.h"
#include "40kabfig.h"
#include "40kvehic.h"
#include "table.h"
#include "mstring.h"
#include <iostream.h>


class fkCodex
{
	public:
			fkCodex(mstring fileList);
			~fkCodex();

		figure  *leaders(mstring& name);
		mstring leaders();
		figure  *character(char *name);
		mstring characters();
		squad  	*squads(char *name);
		mstring squads();
		vehicle *support(char *name);
		mstring support();
		mstring wgList();
		void	wgList(fstream &file);
		mstring wgList(int element);
		mstring wgList(mstring name, int dummy);
		int	wgList(mstring& header);
		mstring listStr();
		void	listStr(mstring& newElement);




	private:

		int	_numWarGearLists;
		mstring _listStr;
		table	**_wgLists;
		table	*_leaders;
		table	*_characters;
		table	*_squads;
		table	*_support;
};
inline	mstring fkCodex::listStr(){return _listStr;}
#endif

