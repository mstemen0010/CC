#include <iostream.h>
#include <stdio.h>
#include "mstring.h"

main()

{
	mstring s1, s2;
	char buffer[BUFSIZ];

	while (1)
	{
		cout << "Enter strings to compare (on separate lines): \n";
		cin >> buffer;
		s1 = buffer;
		cin >> buffer;
		s2 = buffer;
		cout << s1 << " sounds like " << s2 << " " << s1.sndLike(s2) << "% \n\n";
	}
}
