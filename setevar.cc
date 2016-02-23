#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include "mstring.h"

main(int argc, char *argv[])
{
	if (argc > 1)
	{
		for (int i = 1; i <= argc; i++)
		{
			if (argv[i])
			{
				mstring argument = argv[i];
				putenv(argument);
			}
		}
	}
}
