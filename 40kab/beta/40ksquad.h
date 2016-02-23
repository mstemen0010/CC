#ifndef _40K_SQUAD_H_
#define _40K_SQUAD_H_
#include "40kab.h"


class squad
{
 
    public:
 
// the basics

			squad();
        	squad(mstring  statList);
        	squad(squad *oldSquad);
        	~squad();
    void    minNum(int newMin);
    int     minNum();
    void    currSquadSize(int newMin);
    int     currSquadSize();
    void    name(mstring newName);
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

    void            maxWg(int newList);
    int             maxWg();
    void            maxHW(int newList);
    int             maxHW();
    void            currHW(int newList);
    int             currHW();
    void            maxSW(int newList);
    int             maxSW();
    void            currSW(int newList);
    int             currSW();
    void            maxAG(int newList);
    int             maxAG();
    void            currAG(int newList);
    int             currAG();
    void            weaponList(mstring newList);
    mstring weaponList();
    void            heavyWeaponList(mstring newList);
    mstring heavyWeaponList();
    void            specialWeaponList(mstring newList);
    mstring specialWeaponList();
    void            grenadeList(mstring newList);
    mstring grenadeList();
    void            armourList(mstring newList);
    mstring armourList();
    void            warGearList(mstring newList);
    mstring warGearList();
    void            addList(mstring newList);
    mstring addList();
    void            special(mstring newList);
    mstring special();
    void            isupport(mstring newList);
    mstring isupport();
	// squad leader info
    void            sqdLdrName(mstring newList);
    mstring sqdLdrName();
    void            sqdLdrWeapon(mstring newList);
    mstring sqdLdrWeapon();
    void            sqdLdrArmour(mstring newList);
    mstring sqdLdrArmour();
    void            sqdLdrGrenades(mstring newList);
    mstring sqdLdrGrenades();
    void            sqdLdrAddList(mstring newList);
    mstring sqdLdrAddList();
    void            sqdLdrWgList(mstring newList);
    mstring sqdLdrWgList();
    void            sqdLdrWgCards(int newList);
    int             sqdLdrWgCards();
    void            sqdLdrCost(int newList);
    int             sqdLdrCost();

    private:

    int                 _race;
    mstring _type;
    mstring _name;
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

    mstring               _weaponList;
    mstring               _specialWeaponList;
    mstring               _heavyWeaponList;
	mstring				_grenadeList;
    mstring               _armourList;
    mstring               _warGearList;
	mstring				_sqdLdrName;
	mstring				_sqdLdrWeapon;
	mstring				_sqdLdrArmour;
	mstring				_sqdLdrGrenades;
	mstring				_sqdLdrAddList;
	mstring				_sqdLdrWgList;
    mstring               _addList;
    mstring               _special;
    mstring               _isupport;

};

// inlines
inline 			squad::squad(){;}

inline void    	squad::minNum(int newList){_minNum = newList;}
inline int		squad::minNum(){ return _minNum;}
inline void    	squad::currSquadSize(int newList){_currSquadSize = newList;}
inline int		squad::currSquadSize(){ return _currSquadSize;}

inline void    squad::maxWg(int newList){_maxWg = newList;}
inline int 		squad::maxWg(){ return _maxWg; }

    inline    void    squad::name(mstring newList)
    {
		_name = newList;
    }
    inline    char    *squad::name(){return _name;}

    inline  void   squad::baseCost(int baseCost){_baseCost = baseCost;}
    inline  int     squad::baseCost(){return _baseCost;}

    inline  void   squad::totalCost(int newList){_totalCost = _totalCost + newList;}
    inline  int     squad::totalCost(){return _totalCost;}

    inline    void    squad::M(int newList){_M = newList;}
    inline    int     squad::M(){return _M;}
    inline    void    squad::WS(int newList){_WS = newList;}
    inline    int     squad::WS(){return _WS;}
    inline    void    squad::BS(int newList){_BS = newList;}
    inline    int     squad::BS(){return _BS;}
    inline    void    squad::S(int newList){_Str = newList;}
    inline    int     squad::S(){return _Str;}
    inline    void    squad::T(int newList){_T = newList;}
    inline    int     squad::T(){return _T;}
    inline    void    squad::W(int newList){_W = newList;}
    inline    int     squad::W(){return _W;}
    inline    void    squad::I(int newList){_I = newList;}
    inline    int     squad::I(){return _I;}
    inline    void    squad::A(int newList){_A = newList;}
    inline    int     squad::A(){return _A;}
    inline    void    squad::Ld(int newList){_Ld = newList;}
    inline    int     squad::Ld(){return _Ld;}


inline    void    squad::isupport(mstring newList)
{
	_isupport = newList;
}
inline    void    squad::special(mstring newList)
{
	_special = newList;
}

inline    void    squad::addList(mstring newList)
{
	_addList = newList;
}
inline    void    squad::warGearList(mstring newList)
{
	_warGearList = newList;
}
inline    void    squad::armourList(mstring newList)
{
    _armourList = newList;
}

inline mstring squad::heavyWeaponList(){ return _heavyWeaponList; }

inline    void    squad::heavyWeaponList(mstring newList)
{
    _heavyWeaponList = newList;
}
inline mstring squad::specialWeaponList(){ return _specialWeaponList; }
inline    void    squad::specialWeaponList(mstring newList)
{
	_specialWeaponList = newList;
}

inline    void    squad::grenadeList(mstring newList)
{
    _grenadeList = newList; 
}
inline mstring squad::grenadeList(){ return _grenadeList; }

inline    void    squad::weaponList(mstring newList)
{
	_weaponList = newList; 
}

inline mstring squad::sqdLdrName(){ return _sqdLdrName; }

inline    void    squad::sqdLdrName(mstring newList)
{
    _sqdLdrName = newList;
}

inline mstring squad::sqdLdrWeapon(){ return _sqdLdrWeapon; }

inline    void    squad::sqdLdrWeapon(mstring newList)
{
    _sqdLdrWeapon = newList;
}

inline mstring squad::sqdLdrArmour(){ return _sqdLdrArmour; }

inline    void    squad::sqdLdrArmour(mstring newList)
{
    _sqdLdrArmour = newList;
}

inline mstring squad::sqdLdrWgList(){ return _sqdLdrWgList; }

inline    void    squad::sqdLdrWgList(mstring newList)
{
    _sqdLdrWgList = newList;
}

inline mstring squad::sqdLdrGrenades(){ return _sqdLdrGrenades; }

inline    void    squad::sqdLdrGrenades(mstring newList)
{
    _sqdLdrGrenades = newList;
}

inline mstring squad::sqdLdrAddList(){ return _sqdLdrAddList; }

inline    void    squad::sqdLdrAddList(mstring newList)
{
    _sqdLdrAddList = newList;
}
inline mstring squad::weaponList(){ return _weaponList; }
inline mstring squad::armourList(){ return _armourList; }
inline mstring squad::addList(){ return _addList; }
inline mstring squad::isupport(){ return _isupport; }
inline mstring squad::warGearList(){ return _warGearList; }
inline mstring squad::special(){ return _special; }
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

