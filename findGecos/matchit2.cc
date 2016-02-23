#include <unistd.h>
#include <fstream.h>
#include "mstring.h"
#include "table.h"

#define MATCHEDFILE "matchedFile.txt"
#define POSMATCHFILE "posmatchFile.txt"
#define DISCARDFILE "discardFile2.txt"

void usage(mstring errMsg);

int main(int argc, char *argv[])
{
	mstring sourceFile;
	mstring compareFile = "passwd";
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

//		cout << "Reading in " << compareFile() << " into Table 1 (no-hash)" << endl;
		table compareTableNh(compareFile(), 0);
//		cout << "Done" << endl;
		

//		cout << "Reading in " << sourceFile() << " into Table 2 (source)" << endl;
		table sourceTable(sourceFile(), 0);
//		cout << "Done" << endl;

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
					case 7:	
						name1.parse(" ");
						mstring ld = name1.parse(" ");
						soundex = 2;
						compareTableNh.fieldDelimit(":");
						compareTableNh.hashField(5);
						matchFound = compareTableNh.getAllCnNoCase(ld());
						if (! matchFound.isBlank())
							found = matchFound.len();
						break;
				} // end switch
				pass++;
			} // end while
			mstring matchList;

                        if (found)
                        {
                                mstring token;
                                mstring usrName;
                                mstring fullName;
                                if (matchFound.ccount("\t"))
                                {
                                        token = matchFound.parse("\t");
                                        int count = 0;
                                        while(token.len())
                                        {
                                                char buff[BUFSIZ] = "";
                                                count++;
                                                sprintf(buff, "\t%d", count);
                                                if (soundex == 1)
                                                {
                                                        matchList += buff; 
                                                        usrName = token.parse(":");
                                                        token.parse(":");
                                                        token.parse(":");
                                                        token.parse(":");
                                                        fullName = token.parse(":");
                                                        matchList += "(";
                                                        matchList += fullName;
                                                        matchList += ":";
                                                        matchList += usrName.lower();
                                                        matchList += ")";
                                                        matchList += "\t";
                                                }
                                                else if (soundex == 2)
                                                {
                                                        matchList += buff; 
                                                        usrName = token.parse(":");
                                                        token.parse(":");
                                                        token.parse(":");
                                                        token.parse(":");
                                                        fullName = token.parse(":");
                                                        matchList += "(";
                                                        matchList += fullName;
                                                        matchList += ":";
                                                        matchList += usrName.lower();
                                                        matchList += ")";
                                                        matchList += "\t";
                                                }
                                                else
                                                {
                                                        matchList += buff;
                                                        usrName = token.parse(":");
                                                        token.parse(":");
                                                        token.parse(":");
                                                        token.parse(":");
                                                        fullName = token.parse(":");
                                                        matchList += "(";
                                                        matchList += fullName;
                                                        matchList += ":";
                                                        matchList += usrName.lower();
                                                        matchList += ")";
                                                        matchList += "\t";

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
                                        // matchList += fullName;
                                        // matchList += ":";
                                        matchList += usrName.lower();
                                        // matchList += "  ";
                                }
                       		if (matchList.ccount("(") )
                                        cout << value << "/" << matchList << endl;
                                else
                                        cout << value << matchList << endl;
                        }



/*
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
			*/
			else 
				discardFile << value << endl;
		} // end for
		discardFile.close();
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
