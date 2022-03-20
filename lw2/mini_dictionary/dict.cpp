#include "dict.h";

// Dictionary

std::map<std::string, std::vector<std::string>> get_dict(std::ifstream& dict_file_stream)
{
	std::string line = "";
	std::map<std::string, std::vector<std::string>> dict = {};

	while (getline(dict_file_stream, line))
	{
		std::vector<std::string> translation = split(line, ' ');
		append_translation(dict, translation);
	}

	return dict;
}

void print_dict(std::string dict_file_name, std::map<std::string, std::vector<std::string>>& dict)
{
	if (dict_file_name != "")
	{
		std::ofstream dict_file(dict_file_name);

		for (const auto& [word, translations] : dict)
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

			dict_file << std::endl;
		}

		dict_file.close();
	}

	std::cout << "Изменения сохранены. ";
}

void save_dict(std::map<std::string, std::vector<std::string>>& dict, std::string dict_path, std::istream& in)
{
	if (dict_path == "")
	{
		std::cout << "Введите имя файла для словаря" << std::endl;
		std::getline(in, dict_path);
	}

	print_dict(dict_path, dict);
}

// Translation

bool has_translation(std::map<std::string, std::vector<std::string>>& dict, const std::string word)
{
	std::map<std::string, std::vector<std::string>>::iterator it;
	it = dict.find(word);

	return it != dict.end();
}

void append_translation(std::map<std::string, std::vector<std::string>>& dict, std::vector<std::string> translation)
{
	std::string word = translation[0];
	std::string translation_word = translation[1];

	if (!has_translation(dict, word))
	{
		dict.insert({ word, {translation_word} });
	}
	else
	{
		dict[word].push_back(translation_word);
	}

	if (!has_translation(dict, translation_word))
	{
		dict.insert({ translation_word, {word} });
	}
	else
	{
		dict[translation_word].push_back(word);
	}
}

void print_translation(std::vector<std::string> translation, std::ostream& out)
{
	for (int i = 0; i < translation.size(); i++)
	{
		out << translation[i];
		if (i != translation.size() - 1)
		{
			out << ", ";
		}
	}

	out << std::endl;
}