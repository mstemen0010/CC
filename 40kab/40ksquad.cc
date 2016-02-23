#include "40ksquad.h"
squad::squad(squad *oldSquad)
{
		
		minNum(oldSquad->minNum());
		name(oldSquad->name());
		sqdLdrName(oldSquad->sqdLdrName());
		currSquadSize(oldSquad->currSquadSize());
		baseCost(oldSquad->baseCost());
		totalCost(oldSquad->totalCost());
		M(oldSquad->M());
		BS(oldSquad->BS());
		WS(oldSquad->WS());
		S(oldSquad->S());
		T(oldSquad->T());
		W(oldSquad->W());
		I(oldSquad->I());
		A(oldSquad->A());
		Ld(oldSquad->Ld());
		maxWg(oldSquad->maxWg());
		maxHW(oldSquad->maxHW());
		maxSW(oldSquad->maxSW());
		maxAG(oldSquad->maxAG());
		currHW(oldSquad->currHW());
		currSW(oldSquad->currSW());
		currAG(oldSquad->currAG());
		weaponList(oldSquad->weaponList());
		sqdLdrWeapon(oldSquad->sqdLdrWeapon());
		sqdLdrArmour(oldSquad->sqdLdrArmour());
		sqdLdrGrenades(oldSquad->sqdLdrGrenades());
		sqdLdrWgList(oldSquad->sqdLdrWgList());
		sqdLdrAddList(oldSquad->sqdLdrAddList());
		sqdLdrWgCards(oldSquad->sqdLdrWgCards());
		sqdLdrWgCards(oldSquad->sqdLdrWgCards());
		heavyWeaponList(oldSquad->heavyWeaponList());
		specialWeaponList(oldSquad->specialWeaponList());
		grenadeList(oldSquad->grenadeList());
		weaponList(oldSquad->weaponList());
		armourList(oldSquad->armourList());
		warGearList(oldSquad->warGearList());
		addList(oldSquad->addList());
		special(oldSquad->special());
		isupport(oldSquad->isupport());
}
squad::squad(char *statList)
{
	_currHW = 0;
	_currSW = 0;
	_currAG = 0;
	_totalCost = 0;
	sqdLdrName("");
	sqdLdrCost(0);
	sqdLdrArmour("");
	sqdLdrWeapon("");
	sqdLdrGrenades("");
	sqdLdrWgCards(0);
	sqdLdrWgList("");
	heavyWeaponList("");
	specialWeaponList("");
	weaponList("");
	char *token = strtok(statList, "~");
	if (token)
		minNum(atoi(token));
	else 
		minNum(0);
	currSquadSize(minNum());
	token = strtok(NULL, "~");
	if (token)
		 name(token);
	else 
		name("");
	token = strtok(NULL, "~");
	if (token)
		 baseCost(atoi(token));
	else
		 baseCost(0);
	totalCost(baseCost());
	token = strtok(NULL, "~");
	if (token)
		M(atoi(token));
	else
		M(0);
	token = strtok(NULL, "~");
	if (token)
		WS(atoi(token));
	else
		WS(0);
	token = strtok(NULL, "~");
	if (token)
		BS(atoi(token));
	else
		BS(0);
	token = strtok(NULL, "~");
	if (token)
		S(atoi(token));
	else
		S(0);
	token = strtok(NULL, "~");
	if (token)
		T(atoi(token));
	else
		T(0);
	token = strtok(NULL, "~");
	if (token)
		W(atoi(token));
	else
		W(0);
	token = strtok(NULL, "~");
	if (token)
		I(atoi(token));
	else
		T(0);
	token = strtok(NULL, "~");
	if (token)
		A(atoi(token));
	else
		A(0);
	token = strtok(NULL, "~");
	if (token)
		Ld(atoi(token));
	else
		Ld(0);
	token = strtok(NULL, "~");
	if (token)
		weaponList(token);
	else
		weaponList("");
	token = strtok(NULL, "~");
	if (token)
		grenadeList(token);
	else
		grenadeList("");
	token = strtok(NULL, "~");
	if (token)
		armourList(token);
	else
		armourList("");
	token = strtok(NULL, "~");
	if (token)
		maxHW(atoi(token));
	else
		maxHW(0);
	token = strtok(NULL, "~");
	if (token)
		maxSW(atoi(token));
	else
		maxSW(0);
	token = strtok(NULL, "~");
	if (token)
		maxAG(atoi(token));
	else
		maxAG(0);
	token = strtok(NULL, "~");
	if (token)
		maxWg(atoi(token));
	else
		maxWg(0);
	token = strtok(NULL, "~");
	if (token)
		warGearList(token);
	else
		warGearList("");
	token = strtok(NULL, "~");
	if (token)
		addList(token);
	else
		addList("");
	token = strtok(NULL, "~");
	if (token)
		special(token);
	else
		special("");
	token = strtok(NULL, "~");
	if (token)
		isupport(token);
	else
		isupport("");
	token = strtok(NULL, "~");
	if (token)
		sqdLdrAddList(token);
	else
		sqdLdrAddList("");

}
void squad::print()
{
		cout << "======================================================\n";
		cout << "Squad size: " << currSquadSize() << "\n";
		cout << "Type: " << name() << "          Leader: " << sqdLdrName() << "\n";
		cout << "Squad cost: " << totalCost() << "\n";
		cout << "======================================================\n";
		cout << "M:  " << M() << "\n";
		cout << "WS: " << WS() << "\n";
		cout << "BS: " << BS() << "\n";
		cout << "S:  " << S() << "\n";
		cout << "T:  " << T() << "\n";
		cout << "W:  " << W() << "\n";
		cout << "I:  " << I() << "\n";
		cout << "A:  " << A() << "\n";
		cout << "Ld: " << Ld() << "\n";
		cout << "======================================================\n";
		cout << "Weapons: " << weaponList() << "\n";
		cout << "Heavy Weapons"  << "(" << maxHW() << ")" << ": " << heavyWeaponList() << " (" << currHW() << ") Choices left\n";
		cout << "Special Weapons"  << "(" << maxSW() << ")" << ": " << specialWeaponList() << " (" << currSW() << ") Choices left\n";
		cout << "Additional Grenades"  << "(" << maxAG() << ")" << ": " << grenadeList() << " (" << currAG() << ") Choices left\n";
		cout << "Armour: " << armourList() << "\n";
		cout << "War gear cards allowed: " << maxWg() << "\n";
		cout << "War gear: " << warGearList() << "\n";
		cout << "Lists: " << addList() << "\n";
		cout << "======================================================\n";
		cout << "Special: " << special() << "\n\n";
		cout << "Support: " << isupport() << "\n";
		cout << "======================================================\n";
		cout << "Squad Leader Weapons: "<< sqdLdrWeapon() << "\n";
		cout << "Squad Leader Armour: "<< sqdLdrArmour() << "\n";
		cout << "Squad Leader Grenades: "<< sqdLdrGrenades() << "\n";
		cout << "Squad Leader Wargear: "<< sqdLdrWgList() << "(" << sqdLdrWgCards() << ") Cards Left\n";
		cout << "======================================================\n";
		cout << "======================================================\n";
		cout.flush();
}
