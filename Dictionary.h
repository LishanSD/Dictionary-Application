// "Dictionary.h" header file

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include "Word.h"

// "Dictionary" class
class Dictionary
{
private:
    // Attribute
    std::vector<Word> wordlist;
    int highScore = 0;

public:
    // Constructor
    Dictionary();

    // Getters
    std::vector<Word> getWordlist();
    int getHighScore();

    // Setters
    void setWordlist(Word word);
    void setHighScore(int newHighScore);

    // Other methods
    bool load(std::string fileName);
    void search(std::string term);
    void menu();

    // Basic tasks
    void findPalindromes();
    void findRhymingWords(std::string word);

    // Intermediate tasks
    void guessTheWord();
    void addWord();
};

#endif