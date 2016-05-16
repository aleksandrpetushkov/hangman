#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string>
#include "hangman.h"
#include "gtest/gtest.h"

using namespace std;


TEST()
{
	ASSERT_ANY_THROW(Hangman hg("kk"));
	
}





int main(int argc, char* argv[])
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
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	cin.get();
	
	return 0;
}