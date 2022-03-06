#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <Windows.h>

using namespace std;

const string END_COMMAND = "...";

class Args
{
public:
	string dict_path;
};

string lowercase_string(string input_string)
{
	string lowercased_string = input_string;
	transform(input_string.begin(), input_string.end(), lowercased_string.begin(),
		[](unsigned char ch)
		{
			return tolower(ch);
		}
	);

	return lowercased_string;
}

Args parse_args(int argc, char* argv, ostream& out)
{
	Args args = Args();

	args.dict_path = argv[0];

	return args;
}

int main(int argc, char* argv)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Args args = parse_args(argc, argv, cout);
	string line = "";

	map<string, vector<string>> eng_to_rus_dict = {};
	map<string, string> rus_to_eng_dict = {};
	map<string, vector<string>>::iterator eng_to_rus_it;
	bool has_changed = false;

	while (getline(cin, line) && line != END_COMMAND)
	{
		string word = lowercase_string(line);
		eng_to_rus_it = eng_to_rus_dict.find(word);

		if (eng_to_rus_it != eng_to_rus_dict.end())
		{
			vector<string> translations = eng_to_rus_it->second;

			for_each(translations.begin(), translations.end(),
				[](string translation_word)
				{
					cout << translation_word << endl;
				}
			);
		}
		else
		{
			cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
			string translation_word = "";
			getline(cin, translation_word);
			if (translation_word != "")
			{
				has_changed = true;
				translation_word = lowercase_string(translation_word);
				vector<string> translations = { translation_word };
				pair<string, vector<string>> translation = { word, translations };
				eng_to_rus_dict.insert(translation);
				cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation_word << "\"." << endl;
			}
			else
			{
				cout << "Слово \"" << word << "\" проигнорировано" << endl;
			}
		}
	}

	if (has_changed) {
		string agreement = "";
		cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом" << endl;
		cin >> agreement;
		if (lowercase_string(agreement) == "y")
		{
			cout << "Изменения сохранены.";
		}
		cout << "До свидания" << endl;
	}
	return 0;
}

