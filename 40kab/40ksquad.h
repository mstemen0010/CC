#ifndef _40K_SQUAD_H_
#define _40K_SQUAD_H_
#include "40kab.h"


class squad
{
 
    public:
 
// the basics

			squad();
        	squad(char *statList);
        	squad(squad *oldSquad);
        	~squad();
    void    minNum(int newMin);
    int     minNum();
    void    currSquadSize(int newMin);
    int     currSquadSize();
    void    name(char *newName);
    char    *name();
    void    baseCost(int newBaseCost);
    int     baseCost();
    void    totalCost(int newBaseCost);
    int     totalCost();
    void    print();

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
    void            maxHW(int newcurrHW);
    int             maxHW();
    void            currHW(int newcurrHW);
    int             currHW();
    void            maxSW(int newcurrSW);
    int             maxSW();
    void            currSW(int newcurrSW);
    int             currSW();
    void            maxAG(int newcurrAG);
    int             maxAG();
    void            currAG(int newcurrAG);
    int             currAG();
    void            weaponList(char *newWeapon);
    char            *weaponList();
    void            heavyWeaponList(char *newWeapon);
    char            *heavyWeaponList();
    void            specialWeaponList(char *newWeapon);
    char            *specialWeaponList();
    void            grenadeList(char *newWeapon);
    char            *grenadeList();
    void            armourList(char *newArmour);
    char            *armourList();
    void            warGearList(char *newWarGear);
    char            *warGearList();
    void            addList(char *newAddLists);
    char            *addList();
    void            special(char *newSpecial);
    char            *special();
    void            isupport(char *newSpecial);
    char            *isupport();
	// squad leader info
    void            sqdLdrName(char *newName);
    char            *sqdLdrName();
    void            sqdLdrWeapon(char *newWeapon);
    char            *sqdLdrWeapon();
    void            sqdLdrArmour(char *newArmour);
    char            *sqdLdrArmour();
    void            sqdLdrGrenades(char *newGrenades);
    char            *sqdLdrGrenades();
    void            sqdLdrAddList(char *newAddList);
    char            *sqdLdrAddList();
    void            sqdLdrWgList(char *newWgList);
    char            *sqdLdrWgList();
    void            sqdLdrWgCards(int newCards);
    int             sqdLdrWgCards();
    void            sqdLdrCost(int newCost);
    int             sqdLdrCost();

    private:

    int                 _race;
    char                *_type;
    char                *_name;
    int                 _minNum;
	int					_currSquadSize;
    int                 _baseCost;
    int                 _totalCost;
    int                 _maxWg;
    int                 _maxHW;
    int                 _maxSW;
    int                 _maxAG;
    int                 _currHW;
    int                 _currSW;
    int                 _currAG;
    int                 _M;
    int                 _WS;
    int                 _BS;
    int                 _Str;
    int                 _T;
    int                 _W;
    int                 _I;
    int                 _A;
    int                 _Ld;
	int					_sqdLdrCost;
	int					_sqdLdrWgCards;

    char*               _weaponList;
    char*               _specialWeaponList;
    char*               _heavyWeaponList;
	char*				_grenadeList;
    char*               _armourList;
    char*               _warGearList;
	char*				_sqdLdrName;
	char*				_sqdLdrWeapon;
	char*				_sqdLdrArmour;
	char*				_sqdLdrGrenades;
	char*				_sqdLdrAddList;
	char*				_sqdLdrWgList;
    char*               _addList;
    char*               _special;
    char*               _isupport;

};

// inlines
inline 			squad::squad(){;}

inline void    	squad::minNum(int newmin){_minNum = newmin;}
inline int		squad::minNum(){ return _minNum;}
inline void    	squad::currSquadSize(int newcurrSquadSize){_currSquadSize = newcurrSquadSize;}
inline int		squad::currSquadSize(){ return _currSquadSize;}

inline void    squad::maxWg(int newMax){_maxWg = newMax;}
inline int 		squad::maxWg(){ return _maxWg; }

    inline    void    squad::name(char *newName)
    {
        char *tmpNameHold = NULL;
        if ( _name)
            tmpNameHold = _name;
        _name = new char[strlen(newName) + 1];
        if (_name)
            strcpy(_name, newName);
        if (tmpNameHold)
            delete[] tmpNameHold;
    }
    inline    char    *squad::name(){return _name;}

    inline  void   squad::baseCost(int baseCost){_baseCost = baseCost;}
    inline  int     squad::baseCost(){return _baseCost;}

    inline  void   squad::totalCost(int newTotalCost){_totalCost = _totalCost + newTotalCost;}
    inline  int     squad::totalCost(){return _totalCost;}

    inline    void    squad::M(int newMove){_M = newMove;}
    inline    int     squad::M(){return _M;}
    inline    void    squad::WS(int newWS){_WS = newWS;}
    inline    int     squad::WS(){return _WS;}
    inline    void    squad::BS(int newBS){_BS = newBS;}
    inline    int     squad::BS(){return _BS;}
    inline    void    squad::S(int newS){_Str = newS;}
    inline    int     squad::S(){return _Str;}
    inline    void    squad::T(int newT){_T = newT;}
    inline    int     squad::T(){return _T;}
    inline    void    squad::W(int newW){_W = newW;}
    inline    int     squad::W(){return _W;}
    inline    void    squad::I(int newI){_I = newI;}
    inline    int     squad::I(){return _I;}
    inline    void    squad::A(int newA){_A = newA;}
    inline    int     squad::A(){return _A;}
    inline    void    squad::Ld(int newLd){_Ld = newLd;}
    inline    int     squad::Ld(){return _Ld;}


inline    void    squad::isupport(char *newSupport)
{
    char *tmpNameHold = NULL;
    if ( _isupport)
        tmpNameHold = _isupport;
    _isupport = new char[strlen(newSupport) + 1];
    if (_isupport)
        strcpy(_isupport, newSupport);
    if (tmpNameHold)
        delete[] tmpNameHold;
}
inline    void    squad::special(char *newSpecial)
{
    char *tmpNameHold = NULL;
    if ( _special)
        tmpNameHold = _special;
    _special = new char[strlen(newSpecial) + 1];
    if (_special)
        strcpy(_special, newSpecial);
    if (tmpNameHold)
        delete[] tmpNameHold;
}

inline    void    squad::addList(char *newList)
{
    char *tmpNameHold = NULL;
    if ( _addList)
        tmpNameHold = _addList;
    _addList = new char[strlen(newList) + 1];
    if (_addList)
        strcpy(_addList, newList);
    if (tmpNameHold)
        delete[] tmpNameHold;
}
inline    void    squad::warGearList(char *newList)
{
    char *tmpNameHold = NULL;
    if ( _warGearList)
        tmpNameHold =  _warGearList;
    _warGearList = new char[strlen(newList) + 1];
    if (_warGearList)
        strcpy(_warGearList, newList);
    if (tmpNameHold)
        delete[] tmpNameHold;
}
inline    void    squad::armourList(char *newList)
{
    char *tmpNameHold = NULL;
    if ( _armourList)
        tmpNameHold =  _armourList;
    _armourList = new char[strlen(newList) + 1];
    if (_armourList)
        strcpy(_armourList, newList);
    if (tmpNameHold)
        delete[] tmpNameHold;
}

inline char *squad::heavyWeaponList(){ return _heavyWeaponList; }

inline    void    squad::heavyWeaponList(char *newList)
{
    char *tmpNameHold = NULL;
    if ( _heavyWeaponList)
        tmpNameHold =  _heavyWeaponList;
    _heavyWeaponList = new char[strlen(newList) + 1];
    if (_heavyWeaponList)
        strcpy(_heavyWeaponList, newList);
    if (tmpNameHold)
        delete[] tmpNameHold;
}
inline char *squad::specialWeaponList(){ return _specialWeaponList; }
inline    void    squad::specialWeaponList(char *newList)
{
    char *tmpNameHold = NULL;
    if ( _specialWeaponList)
        tmpNameHold =  _specialWeaponList;
    _specialWeaponList = new char[strlen(newList) + 1];
    if (_specialWeaponList)
        strcpy(_specialWeaponList, newList);
    if (tmpNameHold)
        delete[] tmpNameHold;
}

inline    void    squad::grenadeList(char *newList)
{
    char *tmpNameHold = NULL;
    if ( _grenadeList)
        tmpNameHold =  _grenadeList;
    _grenadeList = new char[strlen(newList) + 1];
    if (_grenadeList)
        strcpy(_grenadeList, newList);
    if (tmpNameHold)
        delete[] tmpNameHold;
}
inline char *squad::grenadeList(){ return _grenadeList; }

inline    void    squad::weaponList(char *newList)
{
    char *tmpNameHold = NULL;
    if ( _weaponList)
        tmpNameHold =  _weaponList;
	_weaponList = new char[strlen(newList) + 1];
    if (_weaponList)
        strcpy(_weaponList, newList);
    if (tmpNameHold)
        delete[] tmpNameHold;
}

inline char *squad::sqdLdrName(){ return _sqdLdrName; }

inline    void    squad::sqdLdrName(char *newName)
{
    char *tmpNameHold = NULL;
    if ( _sqdLdrName)
        tmpNameHold =  _sqdLdrName;
    _sqdLdrName = new char[strlen(newName) + 1];
    if (_sqdLdrName)
        strcpy(_sqdLdrName, newName);
    if (tmpNameHold)
        delete[] tmpNameHold;
}

inline char *squad::sqdLdrWeapon(){ return _sqdLdrWeapon; }

inline    void    squad::sqdLdrWeapon(char *newWeapon)
{
    char *tmpNameHold = NULL;
    if ( _sqdLdrWeapon)
        tmpNameHold =  _sqdLdrWeapon;
    _sqdLdrWeapon = new char[strlen(newWeapon) + 1];
    if (_sqdLdrWeapon)
        strcpy(_sqdLdrWeapon, newWeapon);
    if (tmpNameHold)
        delete[] tmpNameHold;
}

inline char *squad::sqdLdrArmour(){ return _sqdLdrArmour; }

inline    void    squad::sqdLdrArmour(char *newArmour)
{
    char *tmpNameHold = NULL;
    if ( _sqdLdrArmour)
        tmpNameHold =  _sqdLdrArmour;
    _sqdLdrArmour = new char[strlen(newArmour) + 1];
    if (_sqdLdrArmour)
        strcpy(_sqdLdrArmour, newArmour);
    if (tmpNameHold)
        delete[] tmpNameHold;
}

inline char *squad::sqdLdrWgList(){ return _sqdLdrWgList; }

inline    void    squad::sqdLdrWgList(char *newWgList)
{
    char *tmpNameHold = NULL;
    if ( _sqdLdrWgList)
        tmpNameHold =  _sqdLdrWgList;
    _sqdLdrWgList = new char[strlen(newWgList) + 1];
    if (_sqdLdrWgList)
        strcpy(_sqdLdrWgList, newWgList);
    if (tmpNameHold)
        delete[] tmpNameHold;
}

inline char *squad::sqdLdrGrenades(){ return _sqdLdrGrenades; }

inline    void    squad::sqdLdrGrenades(char *newGrenades)
{
    char *tmpNameHold = NULL;
    if ( _sqdLdrGrenades)
        tmpNameHold =  _sqdLdrGrenades;
    _sqdLdrGrenades = new char[strlen(newGrenades) + 1];
    if (_sqdLdrGrenades)
        strcpy(_sqdLdrGrenades, newGrenades);
    if (tmpNameHold)
        delete[] tmpNameHold;
}

inline char *squad::sqdLdrAddList(){ return _sqdLdrAddList; }

inline    void    squad::sqdLdrAddList(char *newAddList)
{
    char *tmpNameHold = NULL;
    if ( _sqdLdrAddList)
        tmpNameHold =  _sqdLdrAddList;
    _sqdLdrAddList = new char[strlen(newAddList) + 1];
    if (_sqdLdrAddList)
        strcpy(_sqdLdrAddList, newAddList);
    if (tmpNameHold)
        delete[] tmpNameHold;
}
inline char *squad::weaponList(){ return _weaponList; }
inline char *squad::armourList(){ return _armourList; }
inline char *squad::addList(){ return _addList; }
inline char *squad::isupport(){ return _isupport; }
inline char *squad::warGearList(){ return _warGearList; }
inline char *squad::special(){ return _special; }
inline int squad::maxHW(){ return _maxHW; }
inline void squad::maxHW(int newMax){ _maxHW = newMax; }
inline int squad::maxSW(){ return _maxSW; }
inline void squad::maxSW(int newMax){ _maxSW = newMax; }
inline int squad::maxAG(){ return _maxAG; }
inline void squad::maxAG(int newMax){ _maxAG = newMax; }
inline int squad::currHW(){ return _currHW; }
inline void squad::currHW(int newcurr){ _currHW = newcurr; }
inline int squad::currSW(){ return _currSW; }
inline void squad::currSW(int newcurr){ _currSW = newcurr; }
inline int squad::sqdLdrCost(){ return _sqdLdrCost; }
inline void squad::sqdLdrCost(int newsqdLdrCost){ _sqdLdrCost = _sqdLdrCost + newsqdLdrCost; }
inline int squad::sqdLdrWgCards(){ return _sqdLdrWgCards; }
inline void squad::sqdLdrWgCards(int newsqdLdrWgCards){ _sqdLdrWgCards = newsqdLdrWgCards; }
inline int squad::currAG(){ return _currAG; }
inline void squad::currAG(int newcurr){ _currAG = newcurr; }
#endif

