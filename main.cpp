// The "main" function

#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main()
{
    string preference;
    string fileName;

    // Confirm the file name
    while (true)
    {
        cout << "Welcome! do you want to open a file other than \"dictionary_2024S0.txt\"? (y/n): ";
        getline(cin, preference);
        cout << "\n";

        if (preference == "y")
        {
            cout << "Please enter the name of the file you want to open (with the extension \".txt\"), please specify the file path if it's not in the same directory: ";
            getline(cin, fileName);
            cout << "\n";
            cout << "Opening the file \"" << fileName << "\"..." << "\n\n";
            break;
        }
        else if (preference == "n")
        {
            fileName = "dictionary_2024S0.txt"; // Specify the file path if it's not in the same directory
            cout << "Opening the file \"dictionary_2024S0.txt\"..." << "\n\n";
            break;
        }
    }

    Dictionary dictionary;
    bool loaded = dictionary.load(fileName);

    dictionary.menu();

    return 0;
}