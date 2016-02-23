#include "40kcxbld.h"
void main()
{
	int go = 1;
	int	choicei = 0;
	char filename[BUFSIZ] = "";
	char cdxtype[3];

	while(! choicei)
	{
		choicei = getChoiceInt("Choose Codex to Build:", "Eldar,Imperial Guard,Orks,Space Wolfs,Tyranid,Ultra Marine", 6);
		switch(choicei)
		{
			case 1:
				strcpy(cdxtype, "el");
				break;
			case 2:
				strcpy(cdxtype, "ig");
				break;
			case 3:
				strcpy(cdxtype, "or");
				break;
			case 4:
				strcpy(cdxtype, "sw");
				break;
			case 5:
				strcpy(cdxtype, "ty");
				break;
			case 6:
				strcpy(cdxtype, "um");
				break;
		}
	} 
	while (go)
	{
		choicei = getChoiceInt("Codex builder Main Menu", "Add Leader,Add Character,Add Squad,Add Support,Add Wargear List,Add Wargear Cards,Quit", 7);
		
		int goOn = TRUE;
		switch(choicei)
		{
			case 1:
				sprintf(filename, "%scdxldr.dat", cdxtype);
				while (goOn)
					goOn = addFig(filename);
			break;
			case 2:
				sprintf(filename, "%scdxchr.dat", cdxtype);
				while (goOn)
					goOn = addFig(filename);
			break;
			case 3:
				sprintf(filename, "%scdxsqd.dat", cdxtype);
				while (goOn)
					goOn = addSqd(filename);
			break;
			case 4:
				sprintf(filename, "%scdxspt.dat", cdxtype);
				// addSpt(filename);
			break;
			case 5:
				sprintf(filename, "%swglist.dat", cdxtype);
				addList(filename);
			break;
			case 6:
				sprintf(filename, "%swgcard.dat", cdxtype);
				// addCard(filename);
			break;
			case 7:
				go = 0;
			break;
		}
	}
}
					
int addSqd(char *filename)
{
    FILE    *fp;
    char     answer[BUFSIZ];
    char    lineOut[BUFSIZ] = "";
    int     retval = TRUE;
    char questStr[] = "Min number in squad (q to quit),Name,Base cost,M,WS,BS,S,T,W,I,A,Ld,Weapons,Additional grenades,Armour,Max # of Heavy Weapons,Max # of Special Weapons,Max # of extra grenade types,Wargear Cards (number),Wargear,Additional Lists,Special,Support,Additional Lists for the squad Leader";
   
    char *token;
   
    fp = fopen(filename, "a+t");
    token = strtok(questStr, ",");
    while (token)
    {
        printf("%35s : ", token);
        gets(answer);
        if (strcmp(answer, "q") != 0)
        {
            if (strlen(answer) > 0)
                sprintf(lineOut, "%s%s~", lineOut, answer);
            else
                sprintf(lineOut, "%sNone~", lineOut, answer);
        }
        else
        {
            retval = FALSE;
            break;
        }
        token = strtok(NULL, ",");
    }
    if (retval)
        fprintf(fp,  "%s\n", lineOut);
    fclose(fp);
 
    return retval;
}

int addFig(char *filename)
{
	FILE 	*fp;
	char 	 answer[BUFSIZ];
	char 	lineOut[BUFSIZ] = "";
	int		retval = TRUE;
	char questStr[] = "Max number Allowed (q to quit),Name,Base cost,M,WS,BS,S,T,W,I,A,Ld,Weapons,Armour,Wargear Cards (number),Wargear,Additional Lists,Strategy Rating,Special,Support";
				
	char *token;
	
	fp = fopen(filename, "a+t");
	token = strtok(questStr, ",");
	while (token)
	{
        printf("%s :              ", token);
		gets(answer);
		if (strcmp(answer, "q") != 0)
		{
			if (strlen(answer) > 0)
				sprintf(lineOut, "%s%s~", lineOut, answer);
			else
				sprintf(lineOut, "%sNone~", lineOut, answer);
		}
		else
		{
			retval = FALSE;
			break;
		}
		token = strtok(NULL, ",");
	}
	if (retval)
		fprintf(fp,  "%s\n", lineOut);
	fclose(fp);

	return retval;
}
	
int addSpt(char *filename)
{
	return 1;
}

int addCard(char *filename)
{
	return 1;
}

int addList(char *filename)
{
    char     answer[BUFSIZ];
    char     itemName[BUFSIZ];
    char     itemCost[BUFSIZ];
    char    lineOut[BUFSIZ] = "";
    char    inputs[BUFSIZ] = "";
    int     retval = TRUE;
	int		choice;
	int		header = TRUE;
	int		item = TRUE;
    char questStr[] = "Max number Allowed (q to quit),Name,Base cost,M,WS,BS,S,T,W,I,A,Ld,Weapons,Armour,Wargear Cards (number),Wargear,Additional Lists,Strategy Rating,Special,Support";
         
    char *token;
    
	
	while (header)
	{
		choice = getChoiceInt("Add List Menu", "Add Header,Edit Header,Quit", 3);
		if (choice == 1)
		{
				fstream file(filename, ios::app);
				printf("Enter new header name : ");
        		gets(answer);
				file << answer << "]\n";
				while (item)
				{
					printf("Item name(q to quit) : ");
        			gets(itemName);
					if (strcmp(itemName, "q") == 0)
						break;
					printf("Item cost(q to quit) : ");
        			gets(itemCost);
					if (strcmp(itemName, "q") == 0)
						break;
					file << itemCost << "~" << itemName << "~\n";
				}
				file.flush();
				file.close();
		}
		if (choice == 2)
		{
			int headerFound = FALSE;
			printf("Enter header name to edit : ");
        	gets(answer);
			strcat(answer, "]");
			fstream ifile(filename, ios::in);
			fstream tfile("40ktmp.tmp", ios::out);
			while ( ifile.getline(inputs, BUFSIZ))
			{
				if (strcmp(answer, inputs) == 0)
				{
					tfile << inputs << "\n";
					tfile.flush();
					headerFound = TRUE;
					break;
				}
				else
				{
					tfile << inputs << "\n";
					tfile.flush();
				}
			}
			if (headerFound)
			{
				while (item)
            	{
              		printf("Item name(q to quit) : ");
                	gets(itemName);
                	if (strcmp(itemName, "q"))
					{
                 		printf("Item cost(q to quit) : ");
                		gets(itemCost);
					}
					else
						break;
                	if (strcmp(itemCost, "q"))
					{
            			tfile << itemCost << "~" << itemName << "~\n";
						tfile.flush();
					}
					else
						break;
				}
       		}
			else
			{
				printf("Unable to find header: \"%s\" ", answer);
				ifile.close();
				tfile.close();
			}
			if (headerFound)
			{
				
				while(ifile.getline(inputs, BUFSIZ))
				{
					tfile << inputs << "\n";
					tfile.flush();
				}
				tfile.close();
				ifile.close();
				fstream ofile(filename, ios::out);
				fstream nifile("40ktmp.tmp", ios::in);
				while(nifile.getline(inputs, BUFSIZ))
				{
					ofile << inputs << "\n";
					ofile.flush();
				}
				nifile.close();
				ofile.close();
			}	
		}
		if (choice == 3)
			header = FALSE;
	}
	return retval;
}

int newLine(FILE *file, char *item, char *def)
{
	if (strlen(item) > 0)
		fprintf(file, "%s~", item);
	else
		fprintf(file, "%s~", def);
	return 1;
}
