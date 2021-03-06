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
			throw "Error: open file fail"; // ������������ ��������� ������ �������� �����
		}
	}
	void start()
	{

		
		char c;
		while (!_in_file.eof()) //������� ���������� ���� � ����� 
		{

			getline(_in_file, realword);
			++_sof_str;

		}
		_in_file.close();
		
		for (bool flg = true; flg;) //���� ���
		{
			bool error_yes = true; // ���� ���� �� ������
			_sof_e_er = 0; // ���������� ���������� ������
			realword.erase(); //������� �����
			mask.erase(); //������� ����� ��� ����
			enter_sybol.erase();//������� �������� ����

			set_word(get_random_word()); //���������/��������� ���������� ����� �� �����
			for (unsigned int i = 0; i < realword.size(); ++i) //���������� ������ ��� ������������� ����� ������� ��� ����������� ���������� ����������� ������� 
			{
				mask.insert(i, ".");
			}
			while (true) //���� ����������� �����
			{
				cout << "Guesses: " << "\"" << enter_sybol << "\"" << " word: " << mask << " error: " << _sof_e_er << "/" << _sof_er << endl;
				//cout << "realword: " << realword << endl; //����� ��������� ����� (��� �������)
				cout << "Guess: ";

				for (bool exit = true; true;) //���� ����� �����
				{
					exit = true; //���� ������ �� �����
					error_yes = true; //���� ������� ������
					while (true)
					{
						cin >> c;
						if (cin.fail() || c<'a' || c>'z') //�������� �� ������������ �����
						{
							cin.sync(); 
							cin.clear();
							cin.ignore(cin.rdbuf()->in_avail());
							cerr << "Error: incorrect enter, reenter: ";
						}
						else // ���� ���� ���������, ��������� ������� ����� (�� ������ ����� ������ ����� �����) � ���������� ����� �� ����� �����
						{
							cin.ignore(cin.rdbuf()->in_avail());
							break;
						}
					}
					for (int i = 0; i < enter_sybol.size(); ++i) //���� �������� �� ���� �� ������� ��������� ����� ����� 
					{
						if (enter_sybol[i] == c) // ���� ����� ������� �����, ����� ���������� � ���� ����� �� ����� 
						{
							cout << "You guessed that: \"" << enter_sybol <<"\". Reenter: ";
							exit = false; //����������� ����� � ��� ��� ����� ���� ������� ����� � ���������� ��������� ���� �����
							break;
						}
					}
					if(exit) //���� ����� �� ���� �������, ����������� � ������ ������� ���� � ���������� ����� �� ����� �����
					{
						enter_sybol += c;
						break;
					}
					
				}
				for (int i = 0; i < realword.size(); ++i) // ���� �������� ����������� ��������� ����� � �����
				{
					if (realword[i] == c) //���� ����� ������������ � �����, �� ���������� ������ � �����
					{
						mask[i] = c;
						error_yes = false; // ������������ ���� ��� ������ ���, ����� �������
					}
					
				}
				if (error_yes) //���� ������ ������������, �������������� ������� ������
				{
					++_sof_e_er;
				}
				if (_sof_er - _sof_e_er == 0) //���� ���������� ���������� ������ ����� ���������� ��������� - ���� ���������.
				{
					char fl;
					cout << "The answer was \"" << realword <<"\" you blew it.\n";
					cout << "Enter \"y\" for try again.\n";
					cin >> fl;
					cin.sync();
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					if(fl=='y')
					{

						break;

					}
					else
					{
						flg = false;
						break;
					}


				}
				else if(mask==realword) // ���� ����� � ����������� ����� ���� - ���� ��������
				{
					char fl;
					cout << "You win, the word is \"" << realword << "\"\n";
					cout << "Enter \"y\" for try again.\n";
					cin >> fl;
					cin.sync();
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					if (fl == 'y')
					{

						break;

					}
					else
					{
						flg = false;
						break;
					}

				}
				
			}
		}
	}
	void set_word(string const &st)
	{
		realword = st;
	}

	string get_random_word() //����� ��������� ���������� ����� �� �����
	{
		_in_file.open("words", ios::in);
		if(!_in_file)
		{
			throw "Error: open file fail"; // ������������ ��������� ������ �������� �����
		}
		string result;
		int num_string;
		srand(time(0));
		num_string = rand() % _sof_str; //��������� ���������� ����� �� ���� �� ������� ���������� �����
		for (int i = 0; i < num_string; ++i)
		{
			getline(_in_file, result);
		}
		_in_file.close();
		return result;
	}

protected:
	string realword, mask, enter_sybol;// ������� �����, ����� ��� ����������� �����, ������ ��������� ����
	unsigned int _sof_str=0; //���������� ����� � ���������� ����
	unsigned int _sof_e_er; //����������� ���������� ������
	unsigned int _sof_er; //���������� ���������� ������
	fstream _in_file;
};
