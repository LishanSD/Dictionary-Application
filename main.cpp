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
        cout << "Welcome! do you want to open a file other than \"dictionary_file.txt\"? (y/n): ";
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
            fileName = "dictionary_file.txt"; // Specify the file path if it's not in the same directory
            cout << "Opening the file \"dictionary_file.txt\"..." << "\n\n";
            break;
        }
        else
        {
            cout << "Please enter only \'y\' or \'n\'!" << "\n\n";
        }
    }

    // Execute the dictionary
    Dictionary dictionary;
    bool loaded = dictionary.load(fileName);

    if (loaded == true)
    {
        dictionary.menu();
    }

    return 0;
}