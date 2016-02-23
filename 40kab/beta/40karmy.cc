#include "40karmy.h"

fkArmy::fkArmy(int type, int costBase)
{
	_numSquads = 0;
	_leaderFlag = FALSE;
	_totalCost = 0;
	_totalCharacterCost = 0;
	_totalSquadCost = 0;
	_totalSupportCost = 0;
	fkCodex *tempCodex;

	maxCost(costBase);
	_squadList = (squad**) new squad[sizeof(squad)];

	switch(type)
	{
		case Eldar:
			tempCodex = new fkCodex("elcdxldr.dat,elcdxchr.dat,elcdxsqd.dat,elcdxspt.dat");
			_codex = tempCodex;
			delete tempCodex;
		break;
		case SpaceWolf:
			tempCodex = new fkCodex("smcdxldr.dat,smcdxchr.dat,smcdxsqd.dat,smcdxspt.dat");
			_codex = tempCodex;
			delete tempCodex;
		break;
		case Tyranid:
			tempCodex = new fkCodex("tycdxldr.dat,tycdxchr.dat,tycdxsqd.dat,tycdxspt.dat");
			_codex = tempCodex;
			delete tempCodex;
		break;
		case UltraMarine:
			tempCodex = new fkCodex("umcdxldr.dat,umcdxchr.dat,umcdxsqd.dat,umcdxspt.dat,umwglist.dat");
			_codex = tempCodex;
		break;
	}
}

char *fkArmy::squads()
{
	char retStr[BUFSIZ] = "";
	char *sptr = NULL;

	for (int i = 1; i <= _numSquads; i++)
	{
		sptr = _squadList[i - 1]->name();
		if (sptr)
		{
			strcat(retStr, sptr);
			strcat(retStr, ",");
		}

	}
	return retStr;
}


char *fkArmy::print(int type)
{
	mstring names; 
	int	 nameCount = 0;
	char *choice;
	int	 choicei = 0;

	switch (type)
	{
		case PRINT_LEADERS:
			names = codex()->leaders();
			nameCount = names.ccount(",");
			choice = getChoiceName("Choose a Leader", names, nameCount, totalCost(), maxCost());
		break;

		case PRINT_CHARACTERS:
		break;

		case PRINT_SQUADS:
			names = codex()->squads();
			nameCount = names.ccount(",");
			choice = getChoiceName("Choose a Squad", names, nameCount, totalCost(), maxCost());
		break;

        case PRINT_SQUAD_LIST:

        break;

		case PRINT_WARGEAR_LIST:
				
		break;


		case PRINT_SUPPORT:
		break;
	}
	return(choice);
}
void fkArmy::squads(squad *newsquad)
{
	int 	i = 0;
	squad 	**holdingList = NULL;
	if(newsquad)
	{
		_numSquads++;
		squad **tmpSquadList = (squad**) new squad[sizeof(squad) * _numSquads];
		if (_squadList)
			holdingList = _squadList;
			
		if (_numSquads > 1)
		{
			for (i = 1; i < _numSquads; i++)
			{
				tmpSquadList[i - 1] = _squadList[i - 1];
			}
			tmpSquadList[i - 1] = new squad(newsquad);
			_squadList = tmpSquadList;
			delete tmpSquadList;
		}
		else
		{
			tmpSquadList[i] = new squad(newsquad);
			_squadList = tmpSquadList;
			delete tmpSquadList;
		}
		if (holdingList)
			delete [] holdingList;
	}
}
			
