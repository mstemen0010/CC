
#ifndef	VEHICLE_H
#define	VEHICLE_H	// include only once

#include "40kab.h"

enum vehicleTypes
{
	Walker = 2,
	Skimmer = 4,
	Tread = 8,
	Bike = 16,
};

class vehicle
{
 
    public:
 
// the basics

	    vehicle(mstring statList);
	    ~vehicle();
    void    type(int newType);
    int 	type();
    void    name(mstring newName);
    mstring name();
    void    baseCost(int newBaseCost);
    int     baseCost();
	void 	ramStrength(int newVal);
	int     ramStrength();
	void 	ramDamageVariable(int newVal);
	int     ramDamageVariable();
	void 	ramDamageConst(int newVal);
	int     ramDamageConst();
	void 	ramSaveMod(int newVal);
	int     ramSaveMod();
	void 	moveSlow(int newVal);
	int		moveSlow();
	void 	moveFast(int newVal);
	int		moveFast();
	void 	moveCombat(int newVal);
	int		moveCombat();

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

    void            weaponList(mstring newWeapon);
    mstring weapon();
    void            warGearList(mstring newWarGear);
    mstring warGear();
	
	void maxCrew(int newNum);
	int maxCrew();
	void numCrew(int newNum);
	int numCrew();
	void crew(figure newMember);
	

    private:

    int                 _race;
    long		        _type;
    mstring             _name;
	int					_M;
	int					_WS;
	int					_BS;
	int					_Str;
	int					_W;
	int					_I;
	int					_A;
	int					_Ld;
	int					_numCrew;
	int					_maxCrew;
    int                 _baseCost;
    int                 _moveSlow;
    int                 _moveCombat;
    int					_moveFast;
	int					_ramStrength;
	int					_ramDamageVariable;
	int					_ramDamageConst;
	int					_ramSaveMod;

    mstring     		_weaponList;
    mstring    			_warGearList;
	figure**			_crew;
};

// inlines

	inline	void    vehicle::type(int newType)
	{
		_type = _type | newType; // capture multiple types
	}
    inline	int vehicle::type(){return _type;}

    inline	void    vehicle::name(mstring newName)
	{
		_name = newName;
	}
	inline void vehicle::numCrew(int newNum){ _numCrew = newNum;}
	inline int vehicle::numCrew() { return _numCrew;}
	inline void vehicle::maxCrew(int newNum){ _maxCrew = newNum;}
	inline int vehicle::maxCrew() { return _maxCrew;}
	
    inline	mstring vehicle::name(){return _name;}
    inline  void   vehicle::baseCost(int baseCost){_baseCost = baseCost;}
    inline  int     vehicle::baseCost(){return _baseCost;}

    inline	void    vehicle::M(int newMove){_M = newMove;}
    inline	int     vehicle::M(){return _M;}
    inline	void    vehicle::WS(int newWS){_WS = newWS;}
    inline	int     vehicle::WS(){return _WS;}
    inline	void    vehicle::BS(int newBS){_BS = newBS;}
    inline	int     vehicle::BS(){return _BS;}
    inline	void    vehicle::S(int newS){_Str = newS;}
    inline	int     vehicle::S(){return _Str;}
    inline	void    vehicle::W(int newW){_W = newW;}
    inline	int     vehicle::W(){return _W;}
    inline	void    vehicle::I(int newI){_I = newI;}
    inline	int     vehicle::I(){return _I;}
    inline	void    vehicle::A(int newA){_A = newA;}
    inline	int     vehicle::A(){return _A;}
    inline	void    vehicle::Ld(int newLd){_Ld = newLd;}
    inline	int     vehicle::Ld(){return _Ld;}
	inline void 	vehicle::ramStrength(int newVal){_ramStrength = newVal;}
	inline int      vehicle::ramStrength() { return _ramStrength;}
	inline void 	vehicle::ramDamageVariable(int newVal){_ramDamageVariable = newVal;}
	inline int      vehicle::ramDamageVariable() { return _ramDamageVariable;}
	inline void 	vehicle::ramDamageConst(int newVal){_ramDamageConst = newVal;}
	inline int      vehicle::ramDamageConst() { return _ramDamageConst;}
	inline void 	vehicle::ramSaveMod(int newVal){_ramSaveMod = newVal;}
	inline int      vehicle::ramSaveMod() { return _ramSaveMod;}


	inline 	void 	vehicle::moveSlow(int newVal){_moveSlow = newVal;}
	inline 	int		vehicle::moveSlow(){return _moveSlow;}
	inline 	void 	vehicle::moveFast(int newVal){_moveFast = newVal;}
	inline 	int		vehicle::moveFast(){return _moveFast;}
	inline 	void 	vehicle::moveCombat(int newVal){_moveCombat = newVal;}
	inline 	int		vehicle::moveCombat(){return _moveCombat;}

inline	void    vehicle::warGearList(mstring newList)
{
	_warGearList = newList;
}

inline	void    vehicle::weaponList(mstring newList)
{
	_weaponList = newList;
}

inline void  vehicle::crew(figure newMember)
{
	_crew[_numCrew++] = new figure(newMember);
}

#endif

