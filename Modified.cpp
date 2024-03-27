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