// "Word.h" header file
// Implemented the "Word" class in a seperate file, "Word.cpp" for better modularity

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
};

#endif