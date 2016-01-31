
#include <cctype>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "lexicon.h"
#include "Boggle.h"
#include "bogglegui.h"
#include "hashmap.h"
#include "random.h"
#include "set.h"
#include "Vector.h"
#include "simpio.h"

void playOneGame(Lexicon& dictionary) {
    // TODO: implement
    Boggle boggle = Boggle(dictionary, "");

    Set<string> humanWords;

    while (true) {
        string humanWord = getLine("Please enter a human word (Enter to exit human turn): ");
        if(humanWord=="") break;
        if(boggle.humanWordSearch(humanWord)){
            humanWords.add(humanWord);
            cout << "This is a valid word!" << endl;
        } else
            cout << "This is not a valid word!" << endl;

    }

    cout << humanWords.toString() << endl;
    //Set<string> results = boggle.computerWordSearch();
}


