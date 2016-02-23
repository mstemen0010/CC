#include "40kabio.h"

int getChoiceInt(char *title, char *arglist, int numChoices, int totCost, int currCost)
{
    int answer = 0;
    char argbuf[BUFSIZ] = "";
    char a;
    char *aptr = NULL;   

	fflush(stdout);
    while (answer > numChoices || answer == 0 )
    {
        answer = 0;
        strcpy(argbuf, arglist);
        cout << "===========================================================\n";
        cout << title << "\n";
        cout << "===========================================================\n\n";
        char *token = strtok(argbuf, ",");
        int i = 1;
        while(token)
        {
            cout << i << ")" << " " << token << "\n";
            token = strtok(NULL, ",");
            i++;
            cout.flush();
        }      
        cout << "\n===========================================================\n";
        cout <<  "Army Cost: "  << totCost << "            Max Cost: " << currCost << "\n";
        cout << "===========================================================\n";
        cout << "Choice: ";
        cout.flush();
        cin >> a;
        aptr = &a;
        answer = atoi(aptr);
        fflush(stdin); 
        fflush(stdout);
    }
    return(answer);
}

char *getChoiceName(char *title, char *arglist, int numChoices, int totCost, int currCost)
{
    char answer[BUFSIZ];
    char *argbuf = new char[strlen(arglist) + 1];
    char a;
    char *aptr = NULL;
	int	 index = 0;
	int  answeri = 0;

	char **tempBuffer = (char **)new char[numChoices * sizeof(char *)];

	fflush(stdout);
    while (answeri > numChoices || answeri == 0 )
    {
	answeri = 0;
	strcpy(argbuf, arglist);
	cout << "===========================================================\n";
	cout << title << "\n";
	cout << "===========================================================\n\n";
	char *token = strtok(argbuf, ",");
	int i = 1;
	while(token)
	{
	    cout << i << ")" << " " << token << "\n";
			tempBuffer[i - 1]  = new char[strlen(token) + 1];
			if (tempBuffer[i - 1])
				strcpy(tempBuffer[i - 1], token);
			else
				return NULL;
	    i++;
	    cout.flush();
	    token = strtok(NULL, ",");
	}
	cout << "\n===========================================================\n";
	cout <<  "Army Cost: "  << totCost << "            Max Cost: " << currCost << "\n";
	cout << "===========================================================\n";
	cout << "Choice: ";
	cout.flush();
	cin >> a;
	aptr = &a;
		index = atoi(aptr) - 1;
		answeri = atoi(aptr);
		strcpy(answer,tempBuffer[index]);
	fflush(stdin);
	fflush(stdout);
    }
	for (int j = 0; j < numChoices; j++)
		delete[] tempBuffer[j];
	delete tempBuffer;
    return(answer);
}
