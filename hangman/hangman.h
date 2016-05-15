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
			throw "Error: open file fail"; // выбрасывание эксепшена ошибки открытия файла
		}
	}
	void start()
	{

		string realword, mask, enter_sybol;// реально слово, маска под угадываемое слово, строка введенных букв
		char c;
		while (!_in_file.eof()) //подсчет количества слов в файле 
		{

			getline(_in_file, realword);
			++_sof_str;

		}
		_in_file.close();
		
		while (true) //цикл игр
		{
			bool error_yes = true; // флаг была ли ошибка
			_sof_e_er = 0; // Количество допущенных ошибок
			realword.erase(); //Очистка слова
			mask.erase(); //очистка маски для слов
			enter_sybol.erase();//Очистка введеных букв
			realword = get_random_word(); //получение случайного слова из файла
			for (unsigned int i = 0; i < realword.size(); ++i) //Заполнение строки для отгадываемого слова точками для дальнейшего заполнения отгадавшими буквами 
			{
				mask.insert(i, ".");
			}
			while (true) //Цикл отгадывания слова
			{
				cout << "Guesses: " << "\"" << enter_sybol << "\"" << " word: " << mask << " error: " << _sof_e_er << "/" << _sof_er << endl;
				//cout << "realword: " << realword << endl; //вывод реального слова (для отладки)
				cout << "Guess: ";

				for (bool exit = true; true;) //цикл ввода буквы
				{
					exit = true; //флаг выхода из цикла
					error_yes = true; //флаг допуска ошибки
					while (true)
					{
						cin >> c;
						if (cin.fail() || c<'a' || c>'z') //проверка на корректность ввода
						{
							cin.sync(); 
							cin.clear();
							cin.ignore(cin.rdbuf()->in_avail());
							cerr << "Error: incorrect enter, reenter: ";
						}
						else // если ввод корректен, очищается входной поток (на случай ввода больше одной буквы) и происходит выход из цикла ввода
						{
							cin.ignore(cin.rdbuf()->in_avail());
							break;
						}
					}
					for (int i = 0; i < enter_sybol.size(); ++i) //Цикл проверки не была ли введена введенная буква ранее 
					{
						if (enter_sybol[i] == c) // если буква введена ранее, вывод информации и ввод буквы по новой 
						{
							cout << "You guessed that: \"" << enter_sybol <<"\". Reenter: ";
							exit = false; //выставление флага о том что буква была введена ранее и происходит следующий ввод буквы
							break;
						}
					}
					if(exit) //Если буква не была введена, добавляется в список введены букв и происходит выход из цикла ввода
					{
						enter_sybol += c;
						break;
					}
					
				}
				for (int i = 0; i < realword.size(); ++i) // Цикл проверки присутствия введенной буквы в слове
				{
					if (realword[i] == c) //если буква присутствует в слове, то происходит запись в маску
					{
						mask[i] = c;
						error_yes = false; // выставляется флаг что ошибки нет, буква угадана
					}
					
				}
				if (error_yes) //если ошибка присутствует, инкрустируется счетчик ошибок
				{
					++_sof_e_er;
				}
				if (_sof_er - _sof_e_er == 0) //если количество допущенных ошибок равно количеству возможных - игра проиграна.
				{
					cout << "The answer was \"" << realword <<"\" you blew it.\n";
					cout << "Try again.\n";
					break;


				}
				else if(mask==realword) // если маска и угадываемое слово раны - игра выиграна
				{
					cout << "You win, the word is \"" << realword << "\"\n";
					cout << "Try again.\n";
					break;
				}
				
			}
		}
	}
	

	string get_random_word() //метод получения рандомного слова из файла
	{
		_in_file.open("words", ios::in);
		string result;
		int num_string;
		srand(time(0));
		num_string = rand() % _sof_str; //генерация рандомного числа от нудя до размера количества строк
		for (int i = 0; i < num_string; ++i)
		{
			getline(_in_file, result);
		}
		_in_file.close();
		return result;
	}

protected:
	unsigned int _sof_str=0; //Количество строк в библиотеке слов
	unsigned int _sof_e_er; //Совершенное количество ошибок
	unsigned int _sof_er; //Допустимое количество ошибок
	fstream _in_file;
};
