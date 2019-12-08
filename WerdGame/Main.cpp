#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <random>

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

	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, five_words.size() -1 );
	//get a random, word as the guess result
	const std::string target = five_words[dist(rng)];

	return 0;
}