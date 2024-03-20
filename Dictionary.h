// "Dictionary.h" header file

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include "Word.h"

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
};

#endif