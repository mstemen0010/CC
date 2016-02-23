#ifndef _40K_ARMY_H_
#define _40K_ARMY_H_

#include "40kabio.h"
#include "40kcdx.h"
#include "40kfig.h"
#include "40kvehic.h"
#include "40ksquad.h"
#include "table.h"

#define PRINT_LEADERS			0
#define PRINT_CHARACTERS        1
#define PRINT_SQUADS            2
#define PRINT_SUPPORT			3
#define PRINT_SQUAD_LIST        4
#define PRINT_WARGEAR_LIST      5
#define PRINT_WARGEAR_CARDS     6

#define CHARACTER_RATIO_EXCEEDED	1	
#define SQUAD_RATIO_EXCEEDED		2	
#define SUPPORT_RATIO_EXCEEDED		3	
#define	RATIOS_OK					4

class fkArmy
{
    public:

				fkArmy(int type, int costbase);
				~fkArmy();
	void 		leader(figure *newLeader);
	figure 		leader(int arraytIndex);
	figure 		leader(char name);
	figure		*leader();

	// friend int operator+(fkArmy a, int b);
	// friend int operator-(fkArmy a, int b);

	void 		character(figure newCharacter);
	figure 		character(int arrayIndex);
	figure 		character(char name);
	void 		squads(squad *newSquad);
	squad 		*squads(int arrayIndex);
	char		*squads();
	void 		support(vehicle newSupport);
	vehicle 	support(int arrayIndex);
	vehicle 	support(char name);
	int 		checkRatios();
	char 		*print(int type);
	int			maxCost();
	void		maxCost(int newCost);
	int			totalCost();
	void		totalCost(int newTotalCost);
	fkCodex     *codex();


    private:
	fkCodex		*_codex;
	figure   	*_leader;
	figure  	**_characterList;
	squad     	**_squadList;
	figure   	**_supportList;
	int        _totalCost;
	int        _totalCharacterCost;
	int        _totalSquadCost;
	int        _totalSupportCost;
	int        _leaderFlag;
	int 	   _numSquads;
	int		   _maxCost;
};

inline fkCodex *fkArmy::codex(){ return _codex;}
inline void fkArmy::leader(figure *newLeader){ _leader = newLeader; /*  _leader->baseCost(newLeader->baseCost()); */}
inline figure *fkArmy::leader(){ return _leader; }
inline squad *fkArmy::squads(int arrayIndex){return _squadList[arrayIndex];}
inline void fkArmy::maxCost(int newMax){ _maxCost = newMax;}
inline int fkArmy::maxCost(){ return _maxCost;}
inline void fkArmy::totalCost(int newTotalCost){ _totalCost += newTotalCost;}
inline int fkArmy::totalCost(){ return _totalCost;}

// int operator+(fkArmy a, int b){return a.totalCost() + b;}
// int operator-(fkArmy a, int b){return a.totalCost() - b;}
#endif
		
	
