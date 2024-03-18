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

// Setters
void Word::setName(string newName)
{
    this->name = newName;
}

void Word::setType(string newType)
{
    this->type = newType;
}

void Word::setDefinition(string newDefinition)
{
    this->definition = newDefinition;
}

void Word::printDefinition()
{
    // Print name
    cout << "Name: " << getName() << "\n";

    // Print type
    cout << "Type: ";
    if (getType() == "v")
    {
        cout << "verb" << "\n";
    }
    else if (getType() == "n")
    {
        cout << "noun" << "\n";
    }
    else if (getType() == "adv")
    {
        cout << "adverb" << "\n";
    }
    else if (getType() == "adj")
    {
        cout << "adjective" << "\n";
    }
    else if (getType() == "prep")
    {
        cout << "preposition" << "\n";
    }
    else if (getType() == "pn")
    {
        cout << "proper noun" << "\n";
    }
    else if (getType() == "n_and_v")
    {
        cout << "noun and a verb" << "\n";
    }
    else if (getType() == "misc")
    {
        cout << "other words" << "\n";
    }

    cout << "Definition: " << getDefinition() << '\n';
}