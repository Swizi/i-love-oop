#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <Windows.h>

using namespace std;

const string END_COMMAND = "...";
const string RUSSIAN_LOWERCASE_ALPHABET = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const string DICT_SEPARATOR = "RUS-ENG DICT";

class Args
{
public:
	string dict_path;
};

vector<string> split(const string& s, char delim)
{
	vector<string> elems;
	istringstream iss(s);
	string item;
	while (getline(iss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

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

Args parse_args(int argc, char* argv[])
{
	Args args = Args();

	args.dict_path = argc == 2 ? argv[1] : "";

	return args;
}

bool is_russian_letter(char letter)
{
	bool is_russian = false;
	int i = 0;
	while (i != RUSSIAN_LOWERCASE_ALPHABET.size() && !is_russian)
	{
		if (RUSSIAN_LOWERCASE_ALPHABET[i] == letter)
		{
			is_russian = true;
		}
		i++;
	}

	return is_russian;
}

bool is_word_russian(const string word)
{
	bool is_russian = false;
	int i = 0;
	while (i != word.size() && !is_russian)
	{
		is_russian_letter(word[i]);
		i++;
	}

	return is_russian;
}

void print_translations(map<string, vector<string>>& dict, map<string, vector<string>>& mirror_dict, const string word, ostream& out, bool& has_changed)
{
	map<string, vector<string>>::iterator it;
	it = dict.find(word);

	if (it != dict.end())
	{
		vector<string> translations = it->second;

		for (int i = 0; i < translations.size(); i++)
		{
			cout << translations[i];
			if (i != translations.size() - 1)
			{
				out << " ";
			}
		}

		out << endl;
	}
	else
	{
		out << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
		string translation_word = "";
		getline(cin, translation_word);
		if (translation_word != "")
		{
			has_changed = true;
			translation_word = lowercase_string(translation_word);
			vector<string> translations = { translation_word };
			pair<string, vector<string>> translation = { word, translations };
			dict.insert(translation);

			if (mirror_dict.count(translation_word) != 0)
			{
				mirror_dict[translation_word].push_back(word);
			}
			else {
				mirror_dict.insert({ translation_word, { word } });
			}
			out << "Слово \"" << word << "\" сохранено в словаре как \"" << translation_word << "\"." << endl;
		}
		else
		{
			out << "Слово \"" << word << "\" проигнорировано" << endl;
		}
	}
}

map<string, vector<string>> get_dict(ifstream& dict_file_stream, string separator)
{
	string line = "";
	map<string, vector<string>> dict = {};

	while (getline(dict_file_stream, line) && line != separator)
	{
		vector<string> translation = split(line, ' ');
		string word = translation[0];
		string translation_word = translation[1];
		if (dict.count(word) == 0)
		{
			dict.insert({ word, {translation_word} });
		}
		else {
			dict[word].push_back(translation_word);
		}
	}

	return dict;
}

void print_dict(string dict_file_name, map<string, vector<string>>& eng_to_rus_dict, map<string, vector<string>>&  rus_to_eng_dict)
{
	if (dict_file_name == "") {
		cout << "Введите имя файла для словаря" << endl;
		getline(cin, dict_file_name);
	}

	if (dict_file_name != "")
	{
		ofstream dict_file(dict_file_name);

		for (const auto& [word, translations] : eng_to_rus_dict)
		{
			dict_file << word;
			dict_file << " ";
			for (int translationIndex = 0; translationIndex < translations.size(); translationIndex++)
			{
				dict_file << translations[translationIndex];
				if (translationIndex != translations.size() - 1)
				{
					dict_file << " ";
				}
			}

			dict_file << endl;
		}

		dict_file << DICT_SEPARATOR << endl;

		for (const auto& [word, translations] : rus_to_eng_dict)
		{
			dict_file << word;
			dict_file << " ";
			for (int translationIndex = 0; translationIndex < translations.size(); translationIndex++)
			{
				dict_file << translations[translationIndex];
				if (translationIndex != translations.size() - 1)
				{
					dict_file << " ";
				}
			}

			dict_file << endl;
		}

		dict_file.close();
	}
	cout << "Изменения сохранены. ";
}

void save_dicts(map<string, vector<string>>& eng_to_rus_dict, map<string, vector<string>>& rus_to_eng_dict, string dict_path)
{
	string agreement = "";
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом" << endl;
	getline(cin, agreement);

	if (lowercase_string(agreement) == "y")
	{
		print_dict(dict_path, eng_to_rus_dict, rus_to_eng_dict);
	}
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Args args = parse_args(argc, argv);
	string line = "";

	map<string, vector<string>> eng_to_rus_dict = {};
	map<string, vector<string>> rus_to_eng_dict = {};
	if (args.dict_path != "")
	{
		ifstream dict_file_stream(args.dict_path);
		
		eng_to_rus_dict = get_dict(dict_file_stream, DICT_SEPARATOR);

		rus_to_eng_dict = get_dict(dict_file_stream, "");
	}
	bool has_dict_changed = false;

	while (getline(cin, line) && line != END_COMMAND)
	{
		string word = lowercase_string(line);
		if (is_word_russian(word)) {
			print_translations(rus_to_eng_dict, eng_to_rus_dict, word, cout, has_dict_changed);
		}
		else
		{
			print_translations(eng_to_rus_dict, rus_to_eng_dict, word, cout, has_dict_changed);
		}
	}

	if (has_dict_changed) {
		save_dicts(eng_to_rus_dict, rus_to_eng_dict, args.dict_path);
	}

	cout << "До свидания." << endl;
	return 0;
}

