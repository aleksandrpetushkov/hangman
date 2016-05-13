#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string>
#include "hangman.h"

using namespace std;


int main()
{
	try
	{
		Hangman hm("words");
		hm.start();
	}
	catch(char *st)
	{
		cerr << st;
	}


	cout << "Pres any key";
	cin.get();
	
	return 0;
}