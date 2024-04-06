#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <sstream>
#include <cctype>
#include "Dictionary.h"
#include "Dictionary.h"

using namespace std;

string format_string(string word)
{
    string format_word;

    // Make all the characters lowercase
    for (int i = 0; i < word.length(); i++)
    {
        format_word += tolower(word[i]);
    }

    // Replace the spaces in the word by hyphens
    size_t start = 0;

    while ((format_word.find(" ", start)) != string::npos)
    {
        size_t x = format_word.find(" ", start);
        format_word.replace(x, 1, "-");
        start += x;
    }

    return format_word;
}

int countWords(string str)
{
    stringstream stream(str); // Create a stringstream from the input string
    string word;
    int wordCount = 0;

    // Loop through each word in the stringstream
    while (stream >> word)
    {
        wordCount++;
    }

    return wordCount;
}

int randomNumber(int lower_bound, int upper_bound)
{
    mt19937 generator(static_cast<unsigned int>(time(0)));                // Seed the random number generator with the current time
    uniform_int_distribution<int> distribution(lower_bound, upper_bound); // Define the distribution
    int randNum = distribution(generator);                                // Generate a random number between lower bound and upper bound
    return randNum;
}

bool checkWord(string word)
{
    for (char c : word)
    {
        if ((!isalpha(c)) and (c != '-'))
        {
            return false; // Return false if invalid character is found
        }
    }

    return true; // Return true if all the characters are letters a-z and hyphens
}
// Constructor
Dictionary::Dictionary() {}

// Getters
vector<Word> Dictionary::getWordlist()
{
    return this->wordlist;
}

int Dictionary::getHighScore()
{
    return this->highScore;
}

// Setters
void Dictionary::setWordlist(Word word)
{
    this->wordlist.push_back(word);
}

void Dictionary::setHighScore(int newHighScore)
{
    this->highScore = newHighScore;
}

bool Dictionary::load(string fileName)
{
    ifstream file(fileName);

    // Load the information for each word and add them into the dictionary
    if (file.is_open())
    {
        string type;
        string definition;
        string name;
        string blank_line;

        while (getline(file, type))
        {
            type = type.erase(0, 6); // Remove the text "Type: " and load

            getline(file, definition);
            definition = definition.erase(0, 12); // Remove the text "Definition: " and load

            getline(file, name);
            name = name.erase(0, 6); // Remove the text "Word: " and load

            getline(file, blank_line);

            // Add the information of word to a Word object
            Word word(name, type, definition);

            // Add each word into the dictionary
            setWordlist(word);
        }

        file.close();
        cout << "Dictionary loaded and parsed successfully..." << "\n";
        return true;
    }
    else
    {
        cout << "Error opening the dictionary file!" << "\n";
        return false;
    }
}