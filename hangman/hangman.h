#include <string>
#include <fstream>
#include <time.h>
#include <iostream>
using namespace std;

class Hangman
{
public:
	Hangman(const string fw) //fw - file words
	{
		_in_file.open(fw, ios::in);
		_sof_er = 7;
		if (!_in_file)
		{
			throw "Error: open file fail";
		}
	}
	void start()
	{

		string realword, mask, enter_sybol;
		char c;
		while (!_in_file.eof())
		{

			getline(_in_file, realword);
			++_sof_str;

		}
		_in_file.close();
		_in_file.open("words", ios::in);
		
		while (true)
		{
			_sof_e_er = 0;
			realword.erase();
			mask.erase();
			enter_sybol.erase();
			realword = get_random_word();
			for (unsigned int i = 0; i < realword.size(); ++i) //Заполнение строки для отгадываемого слова точками для дальнейшего заполнения отгадавшими буквами
			{
				mask.insert(i, ".");
			}
			while (true)
			{
				cout << "Guesses: " << enter_sybol << "word: " << mask << " error: " << _sof_e_er << "/" << _sof_er << endl;
				cout << "Guess: ";
				for (bool exit = true; true;)
				{
					while (true)
					{
						cin >> c;
						if (cin.fail() || c<'a' || c>'z')
						{
							cin.sync();
							cin.clear();
							cin.ignore(cin.rdbuf()->in_avail());
							cerr << "Error: incorrect enter, reenter: ";
						}
						else
						{
							break;
						}
					}
					for (int i = 0; i < realword.size(); ++i)
					{
						if (enter_sybol[i] == c)
						{
							cout << "You guessed that: " << enter_sybol << endl;
							exit = false;
							break;
						}
					}
					if(exit)
					{
						enter_sybol += c;
						break;
					}
				}
				for (int i = 0; i < realword.size(); ++i)
				{
					if (realword[i] == c)
					{
						mask[i] = c;
					}
					else
					{
						++_sof_e_er;
					}
					
				}
				//cout << "Guess: word: " << mask << "Errors: " << _sof_e_er << "/" << _sof_er << endl;
				if (_sof_er - _sof_e_er == 0)
				{
					cout << "The answer was\"" << realword <<"\" you blew it";
				}
				else if(mask==realword)
				{
					cout << "You win, the word is \"" << realword << "\"\n";
				}
				
			}
		}
	}
	

	string get_random_word()
	{
		string result;
		int num_string;
		srand(time(0));
		num_string = rand() % _sof_str;

		//_in_file.open("words", ios::in);
		//fstream ss("words", ios::in);
		if(!_in_file)
		{
			cout << "kkkkkk";
		}
		for (int i = 0; i < num_string; ++i)
		{
			getline(_in_file, result);
		}
		return result;
	}
	int get_sof_er()
	{
		return _sof_er;
	}

protected:
	unsigned int _sof_str=0; //Количество строк в библиотеке слов
	unsigned int _sof_e_er; //Совершенное количество ошибок
	unsigned int _sof_er; //Допустимое количество ошибок
	fstream _in_file;
};
