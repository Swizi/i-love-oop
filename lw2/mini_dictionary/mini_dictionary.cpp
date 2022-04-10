#include <Windows.h>
#include "dict.h"

using namespace std;

class Args
{
public:
	string dictPath;
	boolean wasError;
};

Args parse_args(int argc, char* argv[])
{
	Args args = Args();

	args.wasError = argc > 1;
	args.dictPath = argc == 2 ? argv[1] : "";

	return args;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Args args = parse_args(argc, argv);
	if (args.wasError)
	{
		cout << "Неверное количество аргументов" << endl;
		return 1;
	}

	string line = "";

	map<string, vector<string>> dict = {};
	if (args.dictPath != "")
	{
		ifstream dictFileStream(args.dictPath);

		dict = GetDict(dictFileStream);
	}

	bool hasDictChanged = false;
	while (getline(cin, line) && line != END_COMMAND)
	{
		string word = GetLowercasedString(line);
		if (HasTranslation(dict, word))
		{
			vector<string> translation = dict[word];
			PrintTranslation(translation, cout);
		}
		else
		{
			cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
			string translationWord = "";
			getline(cin, translationWord);
			translationWord = GetLowercasedString(translationWord);

			if (translationWord != "")
			{
				vector<string> translation = { word, translationWord };
				hasDictChanged = true;
				AppendTranslation(dict, translation);

				cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translationWord << "\"." << endl;
			}
			else
			{
				cout << "Слово \"" << word << "\" проигнорировано" << endl;
			}
		}
	}

	if (hasDictChanged)
	{
		string agreement = "";
		cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом" << std::endl;
		getline(cin, agreement);

		if (GetLowercasedString(agreement) == "y")
		{
			if (dictPath == "")
			{
				std::cout << "Введите имя файла для словаря" << std::endl;
				std::getline(in, dictPath);
			}
			SaveDict(dict, args.dictPath, cin);
		}
	}

	cout << "До свидания." << endl;
	return 0;
}

