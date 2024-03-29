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

    while (stream >> word)
    {
        wordCount++;
    }

    return wordCount;
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