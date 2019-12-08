#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <random>

bool vector_contain_word(const std::vector<std::string>& vec, const std::string& word)
{
	for (const auto& w : vec)
	{
		if (w == word)
		{
			return true;
		}
	}
	return false;
}

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

	while (true)
	{
		std::cout << "Guess a five letter word: " << std::endl;
		std::string guess;
		std::getline(std::cin, guess);

		//First check: see if the input is 5 letters long
		if (guess.size() != 5)
		{
			std::cout << "I said FIVE letter word, asshole. " << std::endl;
			continue;
		}
		if (!vector_contain_word(five_words, guess))
		{
			std::cout << "? That's not even a god damnded word, stupid asshole." << std::endl;
			continue;
		}

	}

	return 0;
}