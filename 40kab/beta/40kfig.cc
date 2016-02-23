#include "40kfig.h"

figure::figure(figure *oldFig)
{
		maxNum(oldFig->maxNum());
		name(oldFig->name());
		baseCost(oldFig->baseCost());
		M(oldFig->M());
		BS(oldFig->BS());
		WS(oldFig->WS());
		S(oldFig->S());
		T(oldFig->T());
		W(oldFig->W());
		I(oldFig->I());
		A(oldFig->A());
		Ld(oldFig->Ld());
		weaponList(oldFig->weaponList());
		armourList(oldFig->armourList());
		maxWg(oldFig->maxWg());
		warGearList(oldFig->warGearList());
		addList(oldFig->addList());
		stratRate(oldFig->stratRate());
		special(oldFig->special());
		isupport(oldFig->isupport());
}
figure::figure(mstring statList)
{
	mstring token = statList.parse("~");
	if (token())
		maxNum(atoi(token));
	else
		maxNum(0);
	token = statList.parse("~");
	if (token())
		 name(token);
	else
		name("");
	token = statList.parse("~");
	if (token())
		 baseCost(atoi(token));
	else
		 baseCost(0);
	token = statList.parse("~");
	if (token())
		M(atoi(token));
	else
		M(0);
	token = statList.parse("~");
	if (token())
		WS(atoi(token));
	else
		WS(0);
	token = statList.parse("~");
	if (token())
		BS(atoi(token));
	else
		BS(0);
	token = statList.parse("~");
	if (token())
		S(atoi(token));
	else
		S(0);
	token = statList.parse("~");
	if (token())
		T(atoi(token));
	else
		T(0);
	token = statList.parse("~");
	if (token())
		W(atoi(token));
	else
		W(0);
	token = statList.parse("~");
	if (token())
		I(atoi(token));
	else
		T(0);
	token = statList.parse("~");
	if (token())
		A(atoi(token));
	else
		A(0);
	token = statList.parse("~");
	if (token())
		Ld(atoi(token));
	else
		Ld(0);
	token = statList.parse("~");
	if (token())
		weaponList(token);
	else
		weaponList("");
	token = statList.parse("~");
	if (token())
		armourList(token);
	else
		armourList("");
	token = statList.parse("~");
	if (token())
		maxWg(atoi(token));
	else
		maxWg(0);
	token = statList.parse("~");
	if (token())
		warGearList(token);
	else
		warGearList("");
	token = statList.parse("~");
	if (token())
		addList(token);
	else
		addList("");
	token = statList.parse("~");
	if (token())
		stratRate(atoi(token));
	else
		stratRate(0);
	token = statList.parse("~");
	if (token())
		special(token);
	else
		special("");
	token = statList.parse("~");
	if (token())
		isupport(token);
	else
		isupport("");

}
void figure::print()
{
		cout << "======================================================\n";
		cout << maxNum() << "\n";
		cout << "Name: " << name() << "\n";
		cout << "Cost: " << baseCost() << "\n";
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
		cout << "Armour: " << armourList() << "\n";
		cout << "War gear cards allowed: " << maxWg() << "\n";
		cout << "War gear: " << warGearList() << "\n";
		cout << "Lists: " << addList() << "\n";
		cout << "Strategy Rating: " << stratRate() << "\n";
		cout << "======================================================\n";
		cout << "Special: " << special() << "\n\n";
		cout << "Support: " << isupport() << "\n";
		cout << "======================================================\n";
		cout.flush();
}
