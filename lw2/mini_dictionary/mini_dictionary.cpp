#include <Windows.h>;
#include "dict.h";

using namespace std;

class Args
{
public:
	string dict_path;
	boolean was_error;
};

Args parse_args(int argc, char* argv[])
{
	Args args = Args();

	args.was_error = argc > 1;
	args.dict_path = argc == 2 ? argv[1] : "";

	return args;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Args args = parse_args(argc, argv);
	if (args.was_error)
	{
		cout << "Неверное количество аргументов" << endl;
		return 1;
	}

	string line = "";

	map<string, vector<string>> dict = {};
	if (args.dict_path != "")
	{
		ifstream dict_file_stream(args.dict_path);

		dict = get_dict(dict_file_stream);
	}

	bool has_dict_changed = false;
	while (getline(cin, line) && line != END_COMMAND)
	{
		string word = get_lowercased_string(line);
		if (has_translation(dict, word))
		{
			vector<string> translation = dict[word];
			print_translation(translation, cout);
		}
		else
		{
			cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
			string translation_word = "";
			getline(cin, translation_word);
			translation_word = get_lowercased_string(translation_word);

			if (translation_word != "")
			{
				vector<string> translation = { word, translation_word };
				has_dict_changed = true;
				append_translation(dict, translation);

				cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation_word << "\"." << endl;
			}
			else
			{
				cout << "Слово \"" << word << "\" проигнорировано" << endl;
			}
		}
	}

	if (has_dict_changed)
	{
		string agreement = "";
		cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом" << std::endl;
		getline(cin, agreement);

		if (get_lowercased_string(agreement) == "y")
		{
			save_dict(dict, args.dict_path, cin);
		}
	}

	cout << "До свидания." << endl;
	return 0;
}

