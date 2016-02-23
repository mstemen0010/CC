

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
	if (type() == TYPE_WALKER)
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
	
