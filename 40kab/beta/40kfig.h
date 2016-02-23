#ifndef	FKABFIGH
#define	FKABFIGH	// include only once

#include "40kab.h"

class figure
{
 
    public:
 
// the basics

		figure(mstring statList);
	    	figure(figure *oldFig);
	    	~figure();
	void    maxNum(int newMax);
	int     maxNum();
    void    type(char *newType);
    char    *type();
    void    name(char *newName);
    char    *name();
    void    baseCost(int newBaseCost);
    int     baseCost();
	void	print();

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
    void            weaponList(mstring newWeapon);
    char   			*weaponList();
    void            armourList(mstring newArmour);
    char 			*armourList();
    void            warGearList(mstring newWarGear);
    char		    *warGearList();
    void            addList(mstring newAddLists);
    char		    *addList();
    void            special(mstring newSpecial);
    char		    *special();
    void            isupport(mstring newSpecial);
    char		    *isupport();
	void			stratRate(int newStratRate);
	int			    stratRate();

    private:

    int                 _race;
    char                *_type;
    mstring             _name;
    int			_maxNum;
    int                 _baseCost;
    int			_maxWg;
    int                 _M;
    int                 _WS;
    int			_BS;
    int                 _Str;
    int                 _T;
    int                 _W;
    int                 _I;
    int                 _A;
    int                 _Ld;
	int					_stratRate;

    mstring    			_weaponList;
    mstring 			_armourList;
    mstring			_warGearList;
    mstring			_addList;
    mstring			_special;
    mstring			_isupport;

};

// inlines

inline void    figure::maxNum(int newMax){_maxNum = newMax;}
inline void    figure::maxWg(int newMax){_maxWg = newMax;}
inline	void    figure::type(char *newType)
	{
		char *tmpTypeHold = NULL;
		if ( _type)
			tmpTypeHold = _type;
		_type = new char[strlen(newType) + 1];
		if (_type)
			strcpy(_type, newType);
		if (tmpTypeHold)
			delete[] tmpTypeHold;
	}
    inline	char    *figure::type(){return _type;}

    inline	void    figure::name(char *newName)
	{
		_name = newName;
	}
    inline	char    *figure::name(){return _name;}

    inline  void   figure::baseCost(int newbaseCost){_baseCost = newbaseCost;}
    inline  int     figure::baseCost(){return _baseCost;}

    inline	void    figure::M(int newMove){_M = newMove;}
    inline	int     figure::M(){return _M;}
    inline	void    figure::WS(int newWS){_WS = newWS;}
    inline	int     figure::WS(){return _WS;}
    inline	void    figure::BS(int newBS){_BS = newBS;}
    inline	int     figure::BS(){return _BS;}
    inline	void    figure::S(int newS){_Str = newS;}
    inline	int     figure::S(){return _Str;}
    inline	void    figure::T(int newT){_T = newT;}
    inline	int     figure::T(){return _T;}
    inline	void    figure::W(int newW){_W = newW;}
    inline	int     figure::W(){return _W;}
    inline	void    figure::I(int newI){_I = newI;}
    inline	int     figure::I(){return _I;}
    inline	void    figure::A(int newA){_A = newA;}
    inline	int     figure::A(){return _A;}
    inline	void    figure::Ld(int newLd){_Ld = newLd;}
    inline	int     figure::Ld(){return _Ld;}
    inline	void    figure::stratRate(int newstratRate){_stratRate = newstratRate;}
    inline	int     figure::stratRate(){return _stratRate;}


inline	void    figure::isupport(mstring newSupport)
{
	_isupport = newSupport;
}
inline	void    figure::special(mstring newSpecial)
{
	_special = newSpecial;
}

inline	void    figure::addList(mstring newList)
{
	_addList = newList;
}
inline	void    figure::warGearList(mstring newList)
{
	_warGearList = newList;
}
inline	void    figure::armourList(mstring newList)
{
	_armourList = newList;
}

inline	void    figure::weaponList(mstring newList)
{
	_weaponList = newList;
}
inline char *figure::weaponList(){ return _weaponList(); }
inline char *figure::armourList(){ return _armourList(); }
inline char *figure::addList(){ return _addList(); }
inline char *figure::isupport(){ return _isupport(); }
inline char *figure::warGearList(){ return _warGearList(); }
inline char *figure::special(){ return _special(); }
inline int figure::maxNum(){ return _maxNum; }
inline int figure::maxWg(){ return _maxWg; }
#endif

