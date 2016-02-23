#include "40kab.h"
#include "40karmy.h"

fkArmy  *army;
figure *newFigure;

main()
{
	char answer[BUFSIZ];
	int cost;

	int     choice = 0;
	// char *cdxChoicec;
	int     goOn = TRUE;

	int mainChoice = getChoiceInt("Choose one:", "Build new army list,Edit old army list", 2, 0, 0);

	cout << "Enter the total points you have to spend: ";
	cout.flush();
	gets(answer);
	cost = atoi(answer);

	switch(mainChoice)
	{
		case 1:
			choice  = getChoiceInt("Select a Codex", "Eldar,Space Wolf,Tyranid,Ultra Marine", 4, 0, cost);
			switch(choice)
			{
				case Eldar:
					army = new fkArmy(Eldar, cost);
				break;

				case SpaceWolf:
					army = new fkArmy(SpaceWolf, cost);
				break;

				case Tyranid:
					army = new fkArmy(Tyranid, cost);
				break;

				case UltraMarine:
					army = new fkArmy(UltraMarine, cost);                   
				break;
			}

		break;
	}
	while (goOn)
	{
		choice = getChoiceInt("Main Menu", "Leader,Character,Squad,Support,Review,Quit", 6, (int)army->totalCost(), (int)army->maxCost());
		switch(choice)
		{
			case 1: // Leader
				leaderMenu();
			break;
			case 2: // Character
			break;
			case 3: // Squad
				squadMenu();
			break;
			case 4: // Support
			break;
			case 5: // Review
			break;
			case 6: // Quit
				goOn = FALSE;
			break;
		}
	}
return 1;
}

void squadMenu()
{
	int     go = TRUE;
	char    *choicec;
	int     choicei;
	char    answer[BUFSIZ];
	char    blank[BUFSIZ];
    char        *ch = NULL;

	while (go)
	{
		choicei = getChoiceInt("Squad Menu", "Add squad,List squad,Edit squad,Quit", 4, army->totalCost(), army->maxCost());

		switch(choicei)
		{
			case 1: // add squad
				choicec = army->print(PRINT_SQUADS);
		if (choicec)
		{
		    mstring answer = choicec;
		    mstring name = answer.parse("-");
		    mstring cost = answer.sub('(');
		    cost = cost.sub(' ');
		    cost = cost.parse(" ");
		    int costi = atoi(cost());
		    army->totalCost(costi);
					squad *newSquad = new squad(army->codex()->squads(name()));
					army->squads(newSquad);
		 }





			break;

			case 2: // List Squad
				choicec = army->print(PRINT_SQUAD_LIST);
				if (choicec)
		{
					int i = atoi(choicec) - 1;
					army->squads(i)->print();
					cout << "Press Return to Continue";
					cout.flush();
					gets(blank);
				}
				break;

			case 3: // Edit Leader
		editFigureMenu(army->leader(), "Leader");
			break;

			case 4: // Quit
				go = FALSE;
			break;
		}

	}
}
void leaderMenu()
{
	static  leaderPicked = FALSE;
	int     go = TRUE;
	char    *choicec;
	int     choicei;
	char    blank[BUFSIZ];
    char        *ch = NULL;

	while (go)
	{
		if (! leaderPicked)
		{
			choicei = getChoiceInt("Leader Menu", "Choose Leader,Quit", 2, army->totalCost(), army->maxCost());
			if (choicei == 1)
			{
				choicec = army->print(PRINT_LEADERS);
				if (choicec)
				{
					mstring answer = choicec;
					mstring name = answer.parse("-");
					mstring cost = answer.sub('('); 
					cost = cost.sub(' '); 
					cost = cost.parse(" "); 
					int costi = atoi(cost()); 
					army->totalCost(costi);
					newFigure = new figure(army->codex()->leaders(name()));
					army->leader(newFigure);
					leaderPicked = TRUE;
		 }


			 }
			 if (choicei == 2)
			 {
				go = FALSE;
				break;
			 }
		}
		else
		{
			choicei = getChoiceInt("Leader Menu", "Change Leader,List Leader,Edit Leader,Quit", 4, army->totalCost(), army->maxCost());

			int oldCost, costi, newCost;
			switch(choicei)
			{
				case 1: // Change Leader
				 	oldCost = army->totalCost();
					costi = army->leader()->baseCost();
					newCost = oldCost - costi;
					army->totalCost(newCost);
					leaderPicked = FALSE;
				break;

				case 2: // List Leader
					army->leader()->print();
					cout << "Press Return to Continue";
					cout.flush();
					gets(blank);
				break;

				case 3: // Edit Leader
					editFigureMenu(army->leader(), "Leader");
				break;

				case 4: // Quit
					go = FALSE;
				break;
			}
		}

	}
}





void editFigureMenu(figure *figureToEdit, char *type)
{
	int     go = TRUE;
	char    title[BUFSIZ];
	char    blank[BUFSIZ];
	int     choicei;

	sprintf(title, "Edit %s Menu", type);
	while (go)
	{
		choicei = getChoiceInt(title, "Add Wargear,Drop Wargear,List Wargear,Quit", 4, army->totalCost(), army->maxCost());
		switch (choicei)
		{
			case 1: // Add
				addToFigure(figureToEdit);
			break;

			case 2: // Drop
				dropFromFigure(figureToEdit);
			break;

			case 3: // List
				figureToEdit->print();
				cout << "Press Return to Continue";
					cout.flush();
				gets(blank);
			break;

			case 4: // Quit
				go = FALSE;
			break;
		}
	}
}

void dropFromFigure(figure *figureToEdit)
{
    mstring choicec;
    mstring listType;
    int  choicei = 0;
    int numChoices = 0;
	int costi, oldCost, newCost;
    char title[] = "Drop From Figure Menu";
 
    mstring codexLists = army->codex()->listStr();
    mstring warGearLists = figureToEdit->addList();
    mstring choiceList;  
    mstring token;
    mstring uList, uToken;
    mstring newList;
	mstring buffer;
	mstring cost, answer, name;
 
    int    parse = TRUE;
 
	
	buffer = figureToEdit->warGearList();
	if (buffer != "None")
	{
	choiceList += "Remove a wargear card,";
		numChoices++;
	}
	buffer = figureToEdit->armourList();
	if (buffer != "None")
	{
		choiceList += "Remove Armour,";
		numChoices++;
	}
	buffer = figureToEdit->weaponList();
	if (buffer != "None")
	{
		choiceList += "Remove Weapons,";
		numChoices++;
	}
	choiceList += "Quit";
	numChoices++;

	choicec = getChoiceName("Choose a wargear list type to Drop from", choiceList, numChoices, army->totalCost(), army->maxCost());

	if (choicec == "Remove a wargear card")
	{
		
	}

	if (choicec == "Remove Armour")
	{
		choiceList = figureToEdit->armourList();
		buffer = army->codex()->wgList(token, 1); 
		cost = buffer.parse("~");
		costi = atoi(cost);
		oldCost = army->totalCost();
		newCost = oldCost - costi;
		army->totalCost(newCost); 
	} 

	if (choicec == "Remove Weapons")
	{
		choiceList = figureToEdit->weaponList();
	numChoices = 0;
	buffer = "";
	while (parse)
	{
	    token = choiceList.parse(",");
	    if (token.len())
	    {
		buffer += army->codex()->wgList(token, 1);
		buffer += ",";
		numChoices++;
	    }
	    else
		parse = FALSE;
	}
		buffer += "Quit,";
	numChoices++;
	choicec = getChoiceName("Choose item to drop", buffer, numChoices, army->totalCost(), army->maxCost());

		if (choicei != numChoices)
		{
			answer = choicec;
			name = answer.parse("-");
			cost = answer.sub('(');
			cost = cost.sub(' ');
			cost = cost.parse(" ");
			costi = atoi(cost());
			oldCost = figureToEdit->baseCost();
			newCost = oldCost - costi;
			figureToEdit->baseCost(newCost);
			oldCost = army->totalCost();
			newCost = oldCost - costi;
			army->totalCost(newCost);
			mstring temp = figureToEdit->weaponList();
			temp += ",";
			mstring target = name;
			target += ", ";
			temp -= target;
			choiceList = temp;
			choiceList.deXSpaces();
			if (choiceList[0] == ',')
				choiceList -= ",";
			int length = choiceList.len() - 1;
			if (choiceList[length] == ',')  // last character
			{
				int pos = length;
				choiceList.clipn(pos);
			}
			choiceList.deXSpaces();
			newList = choiceList;
			figureToEdit->weaponList(newList);
		}
	}
}




void addToFigure(class figure *figureToEdit)
{
	mstring choicec;
	mstring listType;
	int      choicei = 0;
	int     numLists = 1;
	char title[] = "Add to Figure Menu";

	mstring codexLists = army->codex()->listStr();
	mstring warGearLists = figureToEdit->addList();
	mstring choiceList;
	mstring token;
	mstring uList, uToken;
	mstring newList;

	int    parse = TRUE;

	if (figureToEdit->maxWg() > 0   )
		choiceList += "Add a wargear card,";

	uList = codexLists.upper();
	while(parse)
	{
		token = warGearLists.parse(",");
		mstring temp = token.deXSpaces();
		token = temp;

		if (token.len())
		{
			uToken = token.upper();
			if (strstr(uList(), uToken()))
			{
				choiceList += token;
				choiceList += ",";
				numLists++;
			}

		}
		else
			parse = FALSE;

	}
	choiceList += "Quit";
	numLists++;
	if (strlen(choiceList) > 0)
	{
		choicec = getChoiceName("Choose a wargear list type", choiceList, numLists, army->totalCost(), army->maxCost());
		listType = choicec;
		listType = listType.lower();
		mstring headerChoice = choicec;
		if (headerChoice != "Quit")
		{
			int index = army->codex()->wgList(headerChoice.deXSpaces());
			warGearLists = army->codex()->wgList(index);
			warGearLists += "Quit";
			numLists = warGearLists.ccount(",") + 1;
			mstring title = listType;
			title += " list";
			choicec = getChoiceName(title, warGearLists, numLists, army->totalCost(), army->maxCost());
			if (choicec != "Quit")
			{
				mstring answer = choicec;
				mstring name = answer.parse("-");
				mstring cost = answer.sub('('); 
				cost = cost.sub(' '); 
				cost = cost.parse(" "); 
				int costi = atoi(cost()); 
				int oldCost = army->totalCost();
				int newCost = oldCost + costi;
				army->totalCost(newCost);
				oldCost = figureToEdit->baseCost();
				newCost = oldCost + costi;
				figureToEdit->baseCost(newCost);
				if (listType.sub("weapon"))
				{
					newList = figureToEdit->weaponList();
					newList += ", ";
					newList += name;
					figureToEdit->weaponList(newList);
				}
				if (listType.sub("grenade"))
				{
					newList = figureToEdit->weaponList();
					newList += ", ";
					newList += name;
					figureToEdit->weaponList(newList);
				}
				if (listType.sub("armour"))
				{
					newList = name;
					figureToEdit->armourList(newList);
				}
			}
		}

	}
}

char *upperStr(char *string)
{

	char tmpString[BUFSIZ] = "";
	char *tmpStringPtr = NULL;
	char *retString;

	strcpy(tmpString, string);
	tmpStringPtr = tmpString;
	while (*tmpStringPtr != '\0')
	{       
		*tmpStringPtr = toupper(*tmpStringPtr);
		tmpStringPtr++; 
	}
	retString = tmpString;
	return retString;

}
