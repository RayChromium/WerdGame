#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <cctype>



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

std::vector<int> fill_buckets(const std::string& word)
{
	//Each letter in the alphabet matches an entry, which is the amount in the word
	std::vector<int> bucket(26, 0);
	for (const auto& c : word)
	{
		bucket[c - 'a']++;
	}
	return bucket;
}

//Break the scoring proccess to 2 steps:
//1. Fill the buckets to see how many letters matched
//2. Check if they're in the right position
int score_match(const std::string& word1, const std::string& word2)
{
	const auto bucket1 = fill_buckets(word1);
	const auto bucket2 = fill_buckets(word2);
	//take the minimum of the corresponding entry in the bucket as the matching score
	int score = 0;
	for (int i = 0; i < 26; ++i)
	{
		score += std::min(bucket1[i], bucket2[i]);
	}
	
	//Now, check the positions:
	for (int i = 0; i < 5; ++i)
	{
		if (word1[i] == word2[i])
		{
			score++;
		}
	}
	return score;
}

//return a intersection of words based on 2 input containers
std::vector<std::string> get_intersection(const std::vector<std::string>& vec1, const std::vector<std::string>& vec2)
{
	std::vector<std::string> intersection;
	for (const auto& w : vec1)
	{
		if (vector_contain_word(vec2 , w))
		{
			intersection.push_back(w);
		}
	}
	return intersection;
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

	std::vector<std::string> freq_words;
	{
		std::ifstream freq_words_file("20k.txt");
		for (std::string line; std::getline(freq_words_file, line);)
		{
			if (line.empty())
			{
				continue;
			}
			freq_words.push_back(line);
		}
	}

	//Choose only the first 2000 most common words to reduce the difficulty
	//That is, to use the `resize()` function in std::vector
	freq_words.resize(2000);

	//get the intersection:
	auto filtered_words = get_intersection(five_words, freq_words);

	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, filtered_words.size() -1 );
	//get a random, word as the guess result
	const std::string target = filtered_words[dist(rng)];

	while (true)
	{
		std::cout << "Guess a five letter word: " << std::endl;
		std::string guess;
		std::getline(std::cin, guess);

		for (auto& c : guess)
		{
			c = std::tolower(c);
		}

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
		
		const int score = score_match(guess, target);
		if (score == 10)
		{
			std::cout << "You did it.WOW." << std::endl;
			break;
		}
		else
		{
			std::cout << "Nah that ain't it. I'll give you " << score << " points"<<std::endl;
			continue;
		}

	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
	return 0;
}