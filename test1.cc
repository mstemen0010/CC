#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream.h>

char *blah = "stuff; more stuff, still more stuff";

fun()
{
	cout << blah++ << endl;
}

main ()
{
	
	char *h = "Hello";
	int len = strlen(blah);
	int count = 0;
	while (*blah != '\0')
	{
		fun();
		if (count == 5)
			*blah = h;
		count++;
	}
	for (int i = 0; i < len; i++)
		blah--;

	cout << blah << endl;
}
