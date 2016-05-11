#include <string>
#include <fstream>
#include <time.h>
#include <iostream>
using namespace std;

class Hangman
{
public:
	Hangman(const string fw, const int sof_er=7) //fw - file words
	{
		_in_file.open(fw, ios::in);
		_sof_er = sof_er;
		if (!_in_file)
		{
			throw "Error open file";
		}
	}
	void start()
	{

		string realstr, mask, enter_sybol;
		
		char c;
		while (!_in_file.eof())
		{
			getline(_in_file, realstr);
			++_sof_str;

		}
		while (true)
		{
			realstr = get_random_string();
			for (int i = 0; i < realstr.size(); ++i) //Заполнение строки для отгадываемого слова точками для дальнейшего заполнения отгадавшими буквами
			{
				mask.insert(i, ".");
			}
			while (true)
			{
				cout << "guess: ";
				for (bool exit = true; true;)
				{
					while (true)
					{
						cin >> c;
						if (cin.fail || c<'a' || c>'z')
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
					for (int i = 0; i < realstr.size(); ++i)
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
				for (int i = 0; i < realstr.size(); ++i)
				{
					if (realstr[i] == c)
					{
						mask[i] = c;
					}
					else
					{
						++_sof_e_er;
					}
					
				}
				cout << "Guess: word: " << mask << "Errors: " << _sof_e_er << "/" << _sof_er << endl;
				if (_sof_er - _sof_e_er == 0)
				{
					cout << "The answer was\"" << realstr <<"\" you blew it";
				}
				else if(mask==realstr)
				{
					c
				}
				
			}
		}
	}
	

	string get_random_string()
	{
		string result;
		int num_string;
		srand(time(0));
		num_string = rand() % _sof_str;

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
