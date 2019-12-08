#include <vector>
#include <fstream>
#include <string>
#include <iostream>

int main()
{
	std::vector<std::string> five_words;

	//put the file stream in a single scope
	{
		std::ifstream five_word_file("sgb-words.txt");

		//load the words in the file to the vector
		for (std::string line; std::getline(five_word_file, line);)
		{
			if (line.empty())
			{
				continue;
			}
			five_words.push_back(line);
		}
	}

	return 0;
}