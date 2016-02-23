
#ifndef	KADCHR_H
#define	KADCHR_H	// include only once

#include "40kab.h"

class figure
{
 
    public:
 
// the basics

            figure();
            figure(FILE *fp);
            figure(int fd);
            ~figure();
    void    race(int newRace);
    int     race();
    void    type(char *newType);
    char    *type();
    void    name(char *newName)
    char    *name()
    void    baseCost(int newBaseCost);
    int     baseCost();
 
 // stats

    void    M(int newMove);
    int     M();
    void    WS(int newWS);
    int     WS();
    void    BS(int newBS);
    int     BS();
    void    S(int newS);
    int     S();
    void    T(int newT);
    int     T();
    void    W(int newW);
    int     W();
    void    I(int newI);
    int     I();
    void    A(int newA);
    int     A();
    void    Ld(int newLd);
    int     Ld();

// wargear and stuff 

    void            maxWg(int newMaxWg);
    int             maxWg();
    void            weapon(weaponElement *newWeapon);
    weaponElement   weapon(int elementNum);
    void            armour(armourElement *newArmour);
    armourElement   armour(int elementNum);
    void            warGear(warGearElement *newWarGear);
    weaponElement   warGear(int elementNum);
    
    private:
 
    int                 _race;
    char                *_type;
    char                *_name;
    int                 _baseCost;
    int                 _M;
    int                 _WS;
    int                 _S;
    int                 _T;
    int                 _W;
    int                 _I;
    int                 _A;
    int                 _Ld;
    
    weaponElement**     _weaponList;
    armourElement**     _armourList;
    warGearElement**    _warGearList;
 
};

// inlines

	inline	void   figure::race(int newRace)
	{	
		if (! _race)
			_race = newRace;
		else
			errorMsg("Loader error");
	}
    inline	int     figure::race(){return _race;}

    inline	void    figure::type(char *newType)
	{
		char *tmpTypeHold = NULL;
		if ( _type)
			tmpTypeHold = _type;
		_type = new char[strlen(newType) + 1]
		if (_type)
			strcpy(_type, newType);
		if (tmpTypeHold)
			delete[] tmpTypeHold;
	}
    inline	char    *figure::type(){return _type;}

    inline	void    figure::name(char *newName)
	{
		char *tmpNameHold = NULL;
		if ( _name)
			tmpNameHold = _name;
		_name = new char[strlen(newName) + 1]
		if (_name)
			strcpy(_name, newName);
		if (tmpNameHold)
			delete[] tmpNameHold;
	}
    inline	char    *figure::name(){return _name;}

    inline  void   figure::baseCost(int baseCost)
    {
        if (! _baseCost)
            _race = baseCost;
        else
            errorMsg("Loader error");
    }
    inline  int     figure::baseCost(){return _baseCost;}

    inline	void    figure::M(int newMove){_M = newMove;}
    inline	int     figure::M(){return _M;}
    inline	void    figure::WS(int newWS){_WS = newWS;}
    inline	int     figure::WS(){return _WS;
    inline	void    figure::BS(int newBS){_BS = newBS;}
    inline	int     figure::BS(){return _BS;}
    inline	void    figure::S(int newS){_S = newS;}
    inline	int     figure::S(){return _S;}
    inline	void    figure::T(int newT){_T = newT;}
    inline	int     figure::T(){return _T;}
    inline	void    figure::W(int newW){_W = newW;}
    inline	int     figure::W(){return _W;}
    inline	void    figure::I(int newI){_I = newI;}
    inline	int     figure::I(){return _I;}
    inline	void    figure::A(int newA){_R = newA;}
    inline	int     figure::A(){return _A;}
    inline	void    figure::Ld(int newLd){_Ld = newLd;}
    inline	int     figure::Ld(){return _Ld;}
#endif
