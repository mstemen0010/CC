#include <unistd.h>
#include <fstream.h>
#include "mstring.h"
#include "table.h"

#define MATCHEDFILE "matchedFile.txt"
#define POSMATCHFILE "posmatchFile.txt"
#define DISCARDFILE "dicardFile.txt"

void usage(mstring errMsg);

int main(int argc, char *argv[])
{
	mstring sourceFile;
	mstring compareFile = "/opt/users/mstemen/rel/CC/findGecos/passwd";
	mstring sdelim = "|";
	mstring cdelim = ":";
	if (argc == 2)
	{
		if (argv[1] != NULL)
			if (strlen(argv[1]))
				sourceFile = argv[1];
		else
			usage("Invalid argument");
			
		mstring lName, fName;
		fstream matchedFile(MATCHEDFILE, ios::out);
		fstream posMatchFile(POSMATCHFILE, ios::out);
		fstream discardFile(DISCARDFILE, ios::out);

		cout << "Reading in " << compareFile() << " into Table 1 " << endl;
		table compareTable(compareFile(), 5, cdelim());
		cout << "Done" << endl;

		cout << "Reading in " << compareFile() << " into Table 2 (soundex)" << endl;
		table compareTableSd(compareFile(), 5, cdelim(), 1);
		cout << "Done" << endl;

		cout << "Reading in " << compareFile() << " into Table 3 (no-hash)" << endl;
		table compareTableNh(compareFile(), 0);
		cout << "Done" << endl;
		

		cout << "Reading in " << sourceFile() << " into Table 4 (source)" << endl;
		table sourceTable(sourceFile(), 0);
		cout << "Done" << endl;

		int numsElements = sourceTable.numRows();
		// cout << "Search for: ";
		cout.flush();
		int i = 0;
		for (i = 0; i < numsElements; i++)
		{
			/****** find the last and first name pairs ************/

			int lNameFound = 0, fNameFound = 0;
			mstring value =  sourceTable.getRow(i);
			mstring matchStr;
			mstring tempStr;
			value.parse("|");
			mstring nVal =  value.parse("|");
			nVal.cSwap(',', ' ');
			nVal.cSwap('.', ' ');
			for (int j = 0; j < 3; j++)
			{
				mstring token = nVal.parse(" ");
				if (token.len() > 1)
				{
					if (! lNameFound)
					{
						lName = token();
						lNameFound = 1;
					}
					else if (! fNameFound)
					{
						fName = token();
						fNameFound = 1;
					}
						
				} // end if
			} // end for
			mstring name1 = fName();
			name1 += " ";
			name1 += lName();

			mstring name2 = lName();
			name2 += " ";
			name2 += fName();
			mstring name3 = name1();
			name3 -= "'";
			mstring name4 = name2();
			name4 -= "'"; 

			/****************************************************/

			/*********** Make the matches ************************/	
			int 	found = 0;
			int	pass = 1;
			int	soundex = 0;
			int     certainty = 0;
			mstring matchFound;

			while (!found && pass <= 7)
			{
				switch(pass)
				{
					case 1:
						matchFound = compareTable.getAllCnNoCase(name1);
						soundex = 0;
						if (! matchFound.isBlank())
							found = matchFound.len();
						break;
					case 2:
						matchFound = compareTable.getAllCnNoCase(name2);
						soundex = 0;
						if (! matchFound.isBlank())
							found = matchFound.len();
						break;
					case 3:
						matchFound = compareTable.getAllCnNoCase(name3);
						soundex = 0;
						if (! matchFound.isBlank())
							found = matchFound.len();
						break;
					case 4:
						matchFound = compareTable.getAllCnNoCase(name4);
						soundex = 0;
						if (! matchFound.isBlank())
							found = matchFound.len();
						break;
					case 5:
						compareTableSd.soundexAcc(100);
						matchFound = compareTableSd.getAllCnNoCase(name1);
						soundex = 1;
						if (! matchFound.isBlank())
							found = matchFound.len();
						break;
					case 6:
						compareTableSd.soundexAcc(100);
						matchFound = compareTableSd.getAllCnNoCase(name2);
						soundex = 1;
						if (! matchFound.isBlank())
							found = matchFound.len();
						break;
					case 7:	
						name1.parse(" ");
						mstring ld = name1.parse(" ");
						compareTableSd.soundexAcc(75);
						soundex = 2;
						matchFound = compareTableNh.getAllCnNoCase(ld);
						if (! matchFound.isBlank())
							found = matchFound.len();
						break;
				} // end switch
				pass++;
			} // end while
			mstring matchList = "\t";
			if (found)
			{
				mstring token;
				mstring usrName;
				mstring fullName;
				if (matchFound.ccount("\t"))
				{
					token = matchFound.parse("\t");
					while(token.len())
					{
						if (soundex == 1)
						{
							usrName = token.parse(":");
							token.parse(":");
							token.parse(":");
							token.parse(":");
							fullName = token.parse(":");
							matchList += "(";
							matchList += fullName;
							matchList += ":";
							matchList += usrName;
							matchList += ")";
							matchList += "  ";
						}
						else if (soundex == 2)
						{
							usrName = token.parse(":");
							token.parse(":");
							token.parse(":");
							token.parse(":");
							fullName = token.parse(":");
							matchList += "[";
							matchList += fullName;
							matchList += ":";
							matchList += usrName;
							matchList += "]";
							matchList += "  ";
						}
						else
						{
							usrName = token.parse(":");
							token.parse(":");
							token.parse(":");
							token.parse(":");
							fullName = token.parse(":");
							matchList += fullName;
							matchList += ":";
							matchList += usrName;
							matchList += "  ";
					
						}
						token = matchFound.parse("\t");
					}
				}
			
				else
				{
					usrName = matchFound.parse(":");
					matchFound.parse(":");
					matchFound.parse(":");
					matchFound.parse(":");
					fullName = matchFound.parse(":");
					matchList += fullName;
					matchList += ":";
					matchList += usrName;
					matchList += "  ";
				}
			
				cout << value << matchList << endl;
			}
		} // end for
	} // end if argc
	else
		usage("Incorrect number of args");
} // end main
void usage(mstring errMsg)
{
	if (errMsg.len() )
		cerr << errMsg() << endl << endl << endl;
	cerr << "Usage: " << endl;
}
