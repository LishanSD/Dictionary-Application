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

bool checkWord(const string &word)
{
  return all_of(word.begin(), word.end(), [](char c)
                { return isalpha(c) || c == '-'; });
}

bool Dictionary::load(const string &fileName)
{
  ifstream file(fileName);
  if (!file.is_open())
  {
    cout << "Error opening the dictionary file!" << "\n";
    return false;
  }

  string line;
  string type, definition, name;
  while (getline(file, line))
  {
    size_t found = line.find("Type: ");
    if (found != string::npos)
    {
      type = line.substr(found + 6);
      getline(file, line);
      found = line.find("Definition: ");
      if (found != string::npos)
      {
        definition = line.substr(found + 12);
        getline(file, line);
        found = line.find("Word: ");
        if (found != string::npos)
        {
          name = line.substr(found + 6);
          setWordlist(Word(name, type, definition));
        }
        else
        {
          cout << "Error: invalid file format" << "\n";
          return false;
        }
      }
      else
      {
        cout << "Error: invalid file format" << "\n";
        return false;
      }
    }
    else
    {
      cout << "Error: invalid file format" << "\n";
      return false;
    }
  }

  file.close();

  cout << "Dictionary loaded and parsed successfully..." << "\n";
  return true;
}

const Word *Dictionary::search(const string &term) const
{
  const auto &format_term = format_string(term); // Make the input lowercase and replace the spaces in the input with hyphens

  const auto &found = std::lower_bound(getWordlist().begin(), getWordlist().end(), format_term,
                                       [](const Word &a, const std::string &b)
                                       { return a.getName() < b; });

  if (found != getWordlist().end() && found->getName() == format_term)
  {
    return &*found;
  }
  else
  {
    throw std::out_of_range("Word not found!");
  }
}

void Dictionary::findPalindromes() const
{
  cout << "Palindromes," << "\n";

  const auto &end = getWordlist().end();
  for (const auto &word : getWordlist())
  {
    const auto &reversed_word = std::string(word.rbegin(), word.rend());

    // Check whether the word is a palindrome
    if (word == reversed_word)
    {
      cout << "   " << word << "\n";
    }
  }
}

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