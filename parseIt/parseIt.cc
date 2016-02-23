#include <fstream.h>
#include <stdio.h>
#include "utils/mstring.h"
#include "utils/table.h"

int main()
{
	mstring buffer;
	mstring value, name;
	mstring line, cleanLine;
	int  totalItems = 0;
	char input[BUFSIZ];
	int  firstLine = TRUE;
	fstream in("tf.dat", ios::in);
	fstream out("tf.xls", ios::out);
	table  tempTable("tf.template", 0);
	int total_lines = tempTable.numRows() - 1;
	int currentItemCount = -1;
	mstring currentItem;
	int pairsStarted = FALSE;
	int startedPair = FALSE;
	currentItem = tempTable.getRow(0);
	int needTab = FALSE;
	int kick = FALSE;
	while (in.getline(input, BUFSIZ-1))
	{
		if (currentItemCount > total_lines)
			currentItemCount = 0;
		if (input)
		{
			line = "";
			line = input;
			value = input;
			line = line.rmNonPrint(" ");
			cleanLine = line();
			mstring lastChar = line.charAtIndex(line.len() - 1);
			mstring firstChar = line.charAtIndex(0);
			if (firstChar == ">" || line.isBlank())
				kick = TRUE;
			else
				kick = FALSE;
			if (lastChar == "=")
				line += " =";
			else
				line += "=";
			line.delimiter("=");
			if (line.wcount() == 2)
			{
				if (! kick ) 
				{
					line.delimiter(" ");
					if (! line.wPos("Content-Type:"))
					{
	                        		if (needTab)
	                        		{
	                                		out << "\t";
	                                		needTab = FALSE;
	                        		}
	
						line.delimiter("=");
						name = line.parse("=");
						value = line.parse("=");
						mstring cleanVal = value.rmNonPrint(" ");
						value = cleanVal();
						if (tempTable.find(name()))
						{
							currentItemCount++;
							if (currentItemCount > total_lines)
								currentItemCount = 0;
							currentItem = tempTable.getRow(currentItemCount);
							pairsStarted = TRUE;
							startedPair = TRUE;
						}
					}
				}
			}
			else if (pairsStarted && !kick)
			{
				out <<  " " <<  cleanLine() << " ";
				out.flush();
			}
			if (pairsStarted && !kick)
			{
				while(currentItem != name)
				{
					if (needTab)
					{
						out <<  "\tNONE\t";
						needTab = FALSE;
					}
					else
						out <<  "NONE\t";
					currentItemCount++;
					if (currentItemCount > total_lines)
						currentItemCount = 0;
					currentItem = tempTable.getRow(currentItemCount);
					// startedPair = FALSE;
					out.flush();
				}
                                if ((! value.isBlank()|| startedPair ) && !kick)
                                {
					if (value.isBlank())
					{
                                		out <<  "NONE";
					}
					else
					{
                                		out << value();
					}
                                        needTab = TRUE;
                                }
                                else if (!kick)
                                {
                                	out <<  "NONE\t";
                                       	startedPair = FALSE;
                                }

			}
			out.flush();
			if (currentItemCount >= total_lines)
			{
				out << endl;
				currentItemCount = -1;
				startedPair = FALSE;
				pairsStarted = FALSE;
				// buffer = "";
				totalItems++;
				needTab = FALSE;
			}
		}
	}
}

