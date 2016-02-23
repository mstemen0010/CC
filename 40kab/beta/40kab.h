#ifndef _40K_AB_H_
#define _40K_AB_H_ // include only once
// #define BUFSIZ 1024

#include <ctype.h>
#include <iostream.h>
#include "table.h"
#include "mstring.h"
#include "40kabio.h"
#include "40kfig.h"
#include "40ksquad.h"

// #include "40kcdx.h"
	
class figure;

enum raceList
{
	Blank,
	Eldar,
	SpaceWolf,
	Tyranid,
	UltraMarine,
	BloodAngel,
	DarkAngel,
	ImperialGuard,
	Chaos,
	Squat,
};

enum armourTypes
{
	Natural,
	Flak,
	Mesh,
	Carapace,
	OrkEavy,
	EldarAspect,
	EldarRune,
	EldarHolo,
	Power,
	Terminator,
	SquatExoArmour,
};

enum troopType
{
	Leader,
	Character,
	Squad,
	Vehicle,
};

enum weaponClass
{
	Basic,
	Hth,
	Pistol,
	Heavy,
	Support,
	Grenade,
};

struct  codex
{
	table	*leaders;
	table	*characters;
	table	*squads;
	table	*support;
};

struct	warGearElement
{
	char	*name;
	char	*description;
	int		armourType;
	int		weaponClass;
    int     cost;
    int     shortRange;  
    int     longRange;
    int     toHitShort;
    int     toHitLong;
    int     strength;
    int     damage; 
    int     saveMod;
    int     armourPenetrationVar;   
    int     armourPenetrationFix;   
    char    *special;
    int     _restriction;
	char*	armourDesc;
	int		save;
	int 	numD6;
	struct	warGearElement *next;
	struct	warGearElement *first;
};
					
struct weaponElement
{
	char 	*name;
	int		cost;
	int		weaponClass;
	int		shortRange;
	int		longRange;
	int		toHitShort;
	int		toHitLong;
	int		strength;
	int		damage;
	int		saveMod;
	int		armourPenetrationVar;	
	int		armourPenetrationFix;	
	char	*special;
	int		_restriction;
	struct	weaponElement *next;
	struct	weaponElement *first;
};
	
struct armourElement
{
	int		armourType;
	int		cost;
	char*   name;
	char*	armourDesc;
	int		save;
	int 	numD6;
	struct	armourElement *next;
	struct	armourElement *first;

};

int getChoice(char *title, char *arglist, int numChoices); 
void leaderMenu();
void squadMenu();
void editFigureMenu(class figure *figureToEdit, char *type);
void addToFigure(class figure *figureToEdit);
void dropFromFigure(class figure *figureToEdit);
char *upperStr(char *string);

#endif

