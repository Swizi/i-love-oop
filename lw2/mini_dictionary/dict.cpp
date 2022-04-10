#include "dict.h"

// Dictionary

std::map<std::string, std::vector<std::string>> GetDict(std::istream& dictFileStream)
{
	std::string line;
	std::map<std::string, std::vector<std::string>> dict = {};

	while (getline(dictFileStream, line))
	{
		std::vector<std::string> translation = split(line, ' ');
		AppendTranslation(dict, translation);
	}

	return dict;
}

void PrintDict(const std::string& dictFileName, const std::map<std::string, std::vector<std::string>>& dict)
{
		std::ofstream dictFile(dictFileName);

		for (const auto& [word, translations] : dict)
		{
			dictFile << word;
			dictFile << " ";
			for (int translationIndex = 0; translationIndex < translations.size(); translationIndex++)
			{
				dictFile << translations[translationIndex];
				if (translationIndex != translations.size() - 1)
				{
					dictFile << " ";
				}
			}

			dictFile << std::endl;
		}

		dictFile.close();

	std::cout << "Изменения сохранены. ";
}

void SaveDict(const std::map<std::string, std::vector<std::string>>& dict, std::string& dictPath, std::istream& in)
{
	PrintDict(dictPath, dict);
}

// Translation

bool HasTranslation(std::map<std::string, std::vector<std::string>>& dict, const std::string word)
{
	auto it = dict.find(word);

	return it != dict.end();
}

void AppendTranslation(std::map<std::string, std::vector<std::string>> & dict, const std::vector<std::string>& translation)
{
	std::string word = translation[0];
	std::string translationWord = translation[1];

	if (!HasTranslation(dict, word))
	{
		dict.insert({ word, {translationWord} });
	}
	else
	{
		dict[word].push_back(translationWord);
	}

	if (!HasTranslation(dict, translationWord))
	{
		dict.insert({ translationWord, {word} });
	}
	else
	{
		dict[translationWord].push_back(word);
	}
}

void PrintTranslation(const std::vector<std::string>& translation, std::ostream& out)
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