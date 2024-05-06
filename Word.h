// "Word.h" header file

#ifndef WORD_H
#define WORD_H

#include <string>

// "Word" class
class Word
{
private:
    // Attributes
    std::string name;
    std::string type;
    std::string definition;

public:
    // Constructor
    Word(std::string name, std::string type, std::string definition);

    // Getters
    std::string getName();
    std::string getType();
    std::string getDefinition();

    // Setters
    void setName(std::string newName);
    void setType(std::string newType);
    void setDefinition(std::string newDefinition);

    // Method to print the word's name, type and definition
    void printDefinition();
};

#endif