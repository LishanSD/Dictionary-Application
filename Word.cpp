// "Word.cpp" file
// Implemented the "Word" class in this file for better modularity

#include <iostream>
#include <string>
#include "Word.h"

using namespace std;

// Implementation of constructor and methods of "Word" class

// Constructor
Word::Word(string name, string type, string definition) : name(name), type(type), definition(definition) {}

// Getters
string Word::getName()
{
    return name;
}

string Word::getType()
{
    return type;
}

string Word::getDefinition()
{
    return definition;
}