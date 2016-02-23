#include <fstream.h>
#include <stdio.h>
#include "utils/mstring.h"

#define BS  BUFSIZ * 4

int main()
{
	char input[BS];
	int  itemCount = 0;

	fstream in("tf.xls", ios::in);
	while (in.getline(input, BS-1))
	{
		itemCount++;
		mstring line;
		if (input)
		{
			line = input;
			line.delimiter("\t");
			int tabCount = line.wcount();
			cout << itemCount << ":" << tabCount << endl;
		}
	}
}

