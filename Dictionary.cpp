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

// Method to load the dictionary
bool Dictionary::load(string fileName)
{
    // Open the the dictionary file
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

// Method to search for a word in the dictionary and output it's information
void Dictionary::search(string term)
{
    string format_term = format_string(term); // Make the input lowercase and replace the spaces in the input with hyphens

    // Searching
    for (auto &wordObj : getWordlist())
    {
        // Word found
        if (wordObj.getName() == format_term)
        {
            wordObj.printDefinition();
            return;
        }
    }

    // Throw an exception if the word not found
    throw out_of_range("Word not found!");
}

// Method to list down all the palindromes in the dictionary
void Dictionary::findPalindromes()
{
    cout << "Palindromes," << "\n";

    for (auto &wordObj : getWordlist())
    {
        string word = wordObj.getName();
        string reversed_word;
        reverse_copy(word.begin(), word.end(), back_inserter(reversed_word));

        // Check whether the word is a palindrome
        if (word == reversed_word)
        {
            cout << "   " << word << "\n";
        }
    }
}

// Method to list down all the rhyming words to a given word
void Dictionary::findRhymingWords(string word)
{
    int count = 0;

    if (word.length() >= 3)
    {
        string str_1 = word.substr(word.length() - 3); // Separate the last 3 letters of the given word
        cout << "Rhyming words to \"" << word << "\"," << "\n";

        for (auto &wordObj : getWordlist())
        {
            string curr_word = wordObj.getName();

            if (curr_word.length() >= 3)
            {
                string str_2 = curr_word.substr(curr_word.length() - 3); // Separate the last 3 letters of the current word

                // Check whether the word rhymes with the given word
                if (str_1 == str_2)
                {
                    count++;
                    cout << "   " << curr_word << "\n";
                }
            }
        }

        if (count == 0)
        {
            cout << "   ......" << "\n\n";
            cout << "Sorry, no rhyming words to \"" << word << "\"," << "\n";
        }
        else
        {
            cout << "\n";
            cout << count << " rhyming words found!" << "\n";
        }
    }
    else
    {
        cout << "The word should contain 3 or more letters!" << "\n";
    }
}

void Dictionary::guessTheWord()
{
    int score = 0;
    int n = 0;

    while (true)
    {
        int randNum = randomNumber(0, getWordlist().size() - 1);

        if (countWords(randWord.getDefinition()) >= 4)
        {
            stringstream stream(randWord.getDefinition());
            vector<string> words;
            string word;
            string guess;

            while (stream >> word)
            {
                words.push_back(word);
            }

            string correct_word = words[3];
            words[3] = string(words[3].size(), '_');
            string correct_word = words[3];
            words[3] = string(words[3].size(), '_'); // Replace the 4th word with underscores

            // Reset the stringstream and concatenate the modified words back into a string
            stream.str("");
            stream.clear();

            for (const auto &word : words)
            {
                stream << word << " ";
            }

            string defWithBlank = stream.str().substr(0, stream.str().size() - 1); // Remove the trailing space

            // Implementation of the game
            cout << "----------------------------------------------------" << "\n";
            cout << "Guess the missing word of the definition," << "\n\n";
            cout << "   Word: " << randWord.getName() << "\n";
            cout << "   Definition: " << defWithBlank << "\n\n";
            cout << "Your guess: ";
            getline(cin, guess);
            cout << "\n";
        }
    }
}
