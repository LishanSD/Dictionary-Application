// "Dictionary.cpp" file

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <sstream>
#include <cctype>
#include "Dictionary.h"

using namespace std;

// Implementation of other supportive functions which do not belong to a class

// Function to make all the characters of a word lowercase and replace all the spaces in the word by hyphens
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

// Function to count the number of words in a string
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

// Function to generate a random number
int randomNumber(int lower_bound, int upper_bound)
{
    mt19937 generator(static_cast<unsigned int>(time(0)));                // Seed the random number generator with the current time
    uniform_int_distribution<int> distribution(lower_bound, upper_bound); // Define the distribution
    int randNum = distribution(generator);                                // Generate a random number between lower bound and upper bound
    return randNum;
}

// Function to check whether there are only a-z characters and the hyphen in a string
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

// Implementation of constructor and methods of "Dictionary" class

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

// Method for the game "Guess the fourth word"
void Dictionary::guessTheWord()
{
    int score = 0;
    int n = 0;

    cout << "------ Welcome to \"Guess the fourth word\"...! ------" << "\n\n";
    cout << "Current high score: " << getHighScore() << "\n\n";

    while (true)
    {
        int randNum = randomNumber(0, getWordlist().size() - 1); // Generate a random number between 0 and the length of the wordlist
        Word randWord = getWordlist()[randNum];                  // Choose a random word from the dictionary

        if (countWords(randWord.getDefinition()) >= 4)
        {
            stringstream stream(randWord.getDefinition()); // Create a stringstream from the definition of the word
            vector<string> words;
            string word;
            string guess;

            // Split the input string into words
            while (stream >> word)
            {
                words.push_back(word);
            }

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

            if (guess == correct_word)
            {
                cout << "Congratulations! your guess is correct!" << "\n\n";
                score += 10;

                if (score > getHighScore())
                {
                    n++;
                    setHighScore(score);
                    if (n == 1)
                    {
                        cout << "Congratulations! you have beaten the highest score!" << "\n\n";
                    }
                }
            }
            else
            {
                cout << "Your guess is incorrect!" << "\n";
                cout << "The correct answer is, \"" << correct_word << "\"" << "\n";
                cout << "Your score: " << score << "\n";
                break;
            }
        }
    }
}

// Method to add a new word to the dictionary
void Dictionary::addWord()
{
    string name, type, definition, fileName;

    // Input name
    cout << "Enter the word: ";
    getline(cin, name);
    cout << "\n";

    name = format_string(name); // Make the name lowercase and replace the spaces in the name with hyphens

    // Check whether the name only contains a-z characters and the hyphen
    if (checkWord(name) == false)
    {
        cout << "Invalid word!" << "\n";
        return;
    }

    // Check whether the word already exists in the dictionary
    for (auto &wordObj : getWordlist())
    {
        // Word exists
        if (wordObj.getName() == name)
        {
            cout << "error: word exists, elevated privileges required to edit existing words" << "\n";
            return;
        }
    }

    // Input type
    cout << "Enter the type: ";
    getline(cin, type);
    cout << "\n";

    // Check whether the type is valid
    if (type == "v" or type == "verb")
    {
        type = "v";
    }
    else if (type == "n" or type == "noun")
    {
        type = "n";
    }
    else if (type == "adv" or type == "adverb")
    {
        type = "adv";
    }
    else if (type == "adj" or type == "adjective")
    {
        type = "adj";
    }
    else if (type == "prep" or type == "preposition")
    {
        type = "prep";
    }
    else if (type == "pn" or type == "proper noun")
    {
        type = "pn";
    }
    else if (type == "n_and_v" or type == "noun and a verb")
    {
        type = "n_and_v";
    }
    else if (type == "misc" or type == "other words")
    {
        type = "misc";
    }
    else
    {
        cout << "Invalid type!" << "\n";
        return;
    }

    // Input definition
    cout << "Enter the definition: ";
    getline(cin, definition);
    cout << "\n";

    // Input file name
    cout << "Enter a name for the file to store the updated dictionary (with the extension \".txt\"): ";
    getline(cin, fileName);
    cout << "\n";

    // Create a new Word instance
    Word newWord(name, type, definition);

    // Add the new word into the dictionary
    setWordlist(newWord);

    // Save the updated dictionary to a new file
    ofstream outputFile(fileName); // Create an ofstream object and open the file

    // Check whether the file is opened successfully
    if (outputFile.is_open())
    {
        // Write data to the file
        for (auto &wordObj : getWordlist())
        {
            outputFile << "Type: " << wordObj.getType() << "\n";
            outputFile << "Definition: " << wordObj.getDefinition() << "\n";
            outputFile << "Word: " << wordObj.getName() << "\n";
            outputFile << "\n";
        }

        outputFile.close();
        cout << "File \"" << fileName << "\" has been created and saved the updated dictionary successfully...\n";
    }
    else
    {
        cout << "Error opening the file \"" << fileName << "\" for writing!\n";
    }
}

// Method to execute the menu
void Dictionary::menu()
{
    while (true)
    {
        string n;
        string word;

        // Menu
        cout << "------------------------------------------------------------------------------------------------" << "\n";
        cout << "Dictionary..." << "\n";
        cout << "   Enter '1' to search a word" << "\n";
        cout << "   Enter '2' to list all the palindromes in the dictionary" << "\n";
        cout << "   Enter '3' to find rhyming words to a word" << "\n";
        cout << "   Enter '4' to play the game \"Guess the fourth word\"" << "\n";
        cout << "   Enter '5' to add a new word to the dictionary" << "\n";
        cout << "   Enter '6' to exit" << "\n\n";

        cout << "Enter a number to continue: ";
        cin >> n;
        cin.ignore();
        cout << "\n";

        // Execution of tasks
        if (n == "1")
        { // Search for a word if '1' is entered
            cout << "Enter a word to search: ";
            getline(cin, word);
            cout << "\n";

            try
            {
                search(word); // Search for the entered word in the dictionary
            }
            catch (const std::out_of_range &exception)
            {
                cerr << exception.what() << "\n"; // Handle the exception
            }
        }
        else if (n == "2")
        { // List down palindromes if '2' is entered
            findPalindromes();
        }
        else if (n == "3")
        { // Find rhyming words if '3' is entered
            cout << "Enter a word to find rhyming words: ";
            getline(cin, word);
            cout << "\n";
            findRhymingWords(word); // Find rhyming words to the entered word
        }
        else if (n == "4")
        { // Execute the game "Guess the fourth word" if '4' is entered
            guessTheWord();
        }
        else if (n == "5")
        { // Add a word to the dictionary if '5' is entered
            addWord();
        }
        else if (n == "6")
        { // Exit the loop if '6' is entered
            break;
        }
        else
        { // Output "Invalid number!" if anything else is inputted
            cout << "Invalid number!" << "\n";
        }

        cout << "\n";
    }
}