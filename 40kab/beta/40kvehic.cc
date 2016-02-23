#include "40kvehic.h"

// this needs to reflect the vehicle classes stats(see the figure class), but should be setup like the figure class as far as the methods go.

vehicle::vehicle(mstring statList)
{
	mstring token = statList.parse("~");
	if (token())
		baseCost(atoi(token));
	token = statList.parse("~");
	if (token())
		 name(token);
	token = statList.parse("~");
	if (token())
		 baseCost(atoi(token));
	token = statList.parse("~");
	if (token())
		 type(atoi(token));
	if (type() == type() & Walker)
	{
		token = statList.parse("~");
		if (token())
			M(atoi(token));
		token = statList.parse("~");
		if (token())
			M(atoi(token));
		token = statList.parse("~");
		if (token())
			BS(atoi(token));
		token = statList.parse("~");
		if (token())
			S(atoi(token));
		token = statList.parse("~");
		if (token())
			W(atoi(token));
		token = statList.parse("~");
		if (token())
			I(atoi(token));
		token = statList.parse("~");
		if (token())
			A(atoi(token));
		token = statList.parse("~");
		if (token())
			Ld(atoi(token));
		token = statList.parse("~");
	}
	token = statList.parse("~");
	if (token())
		weaponList(token);
	token = statList.parse("~");
	if (token())
		warGearList(token);
}
	
	/*

void vehicle::print()
{
		if (type() == type() &  Walker)
		{
			cout << "======================================================\n";
			cout << "Name: " << name() << "\n";
			cout << "Cost: " << baseCost() << "\n";
			cout << "======================================================\n";
			cout << "| M | "
			cout << "WS | "
			cout << "BS | "
			cout << "S | "
			cout << "I | "
			cout << "A | "
			cout << "LD |\n"
			cout << "------------------------------------------------------\n";
			cout << " " << M() << " | ";
			cout << " " << WS() << " | ";
			cout << " " << BS() << " | ";
			cout << " " << S() << " | ";
			cout << " " << I() << " | ";
			cout << " " << A() << " | ";
			cout << " " << Ld() << "|\n";
			cout << "======================================================\n";
			cout << "Crew: \n"
			for (int i = 0; i < numCrew(); i++)
				cout << _crew[i]->name() << "\n";

			cout << "Ram Value: \n"
			cout << "Strength: " << ramStrength() << "  -" << ramSaveMod() << " Save\n";
			cout << "D" << ramDamageVariable();
			if (ramDamageConst())
				cout << " + " << ramDamageConst() << " Damage\n";
			else
				cout << " Damage\n";
			cout << "Weapons: " << weaponList() << "\n";
			cout << "Type:  
			if (type() == type() & Walker)
				cout << "Walker/";
			if (type() == type() & Skimmer)
				cout << "Skimmer/";
			if (type() == type() & Bike)
				cout << "Bike/";
			if (type() == type() & Tread)
				cout < "Tread/";
			cout << "\n";
		}
		else
		{
			cout << "======================================================\n";
			cout << "Name: " << name() << "\n";
			cout << "Cost: " << baseCost() << "\n";
			cout << "======================================================\n";
			cout << "Crew: \n"
			for (int i = 0; i < numCrew(); i++)
				cout << _crew[i]->name() << "\n";

			cout << "Ram Value: \n"
			cout << "Strength: " << ramStrength() << "  -" << ramSaveMod() << " Save\n";
			cout << "D" << ramDamageVariable();
			if (ramDamageConst())
				cout << " + " << ramDamageConst() << " Damage\n";
			else
				cout << " Damage\n";
			cout << "Weapons: " << weaponList() << "\n";

			cout << "Movement: \n";
			cout << "Slow Speed: " << moveSlow() << "\n"
			cout << "Fast Speed: " << moveFast() << "\n"
			cout << "Combat Speed: " << moveCombat() << "\n"
			cout << "Type:  
			if (type() == type() & Walker)
				cout << "Walker/";
			if (type() == type() & Skimmer)
				cout << "Skimmer/";
			if (type() == type() & Bike)
				cout << "Bike/";
			if (type() == type() & Tread)
				cout < "Tread/";
			cout << "\n";

		}

		cout.flush()

}
*/

