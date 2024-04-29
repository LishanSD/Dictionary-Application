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

void Dictionary::findRhymingWords(string word) const
{
  if (word.length() < 3)
  {
    cout << "The word should contain 3 or more letters!" << "\n";
    return;
  }

  const auto &str_1 = word.substr(word.length() - 3);
  const auto &end = getWordlist().end();
  const auto &found = std::lower_bound(getWordlist().begin(), end,
                                       str_1,
                                       [](const Word &a, const std::string &b)
                                       { return a.getName().substr(a.getName().length() - 3) < b; });

  size_t count = std::distance(found, end);

  if (count == 0)
  {
    cout << "   ......" << "\n\n";
    cout << "Sorry, no rhyming words to \"" << word << "\"," << "\n";
  }
  else
  {
    cout << "\n";
    cout << count << " rhyming words found!" << "\n";

    for (auto it = found; it != end; ++it)
    {
      cout << "   " << it->getName() << "\n";
    }
  }
}

void Dictionary::guessTheWord()
{
  int score = 0;
  int n = 0;

  cout << "------ Welcome to \"Guess the fourth word\"...! ------" << "\n\n";
  cout << "Current high score: " << getHighScore() << "\n\n";

  auto end = getWordlist().end();
  for (auto it = getWordlist().begin(); it != end; ++it)
  {
    if (countWords(it->getDefinition()) >= 4)
    {
      stringstream stream(it->getDefinition());
      vector<string> words(istream_iterator<string>(stream), {});

      string correct_word = words[3];
      words[3] = string(words[3].size(), '_');

      string defWithBlank;
      copy(words.begin(), words.end(), ostream_iterator<string>(defWithBlank, " "));

      cout << "----------------------------------------------------" << "\n";
      cout << "Guess the missing word of the definition," << "\n\n";
      cout << "   Word: " << it->getName() << "\n";
      cout << "   Definition: " << defWithBlank << "\n\n";
      cout << "Your guess: ";
      string guess;
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