// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"    //for getLine();
#include "hashmap.h"
#include "queue.h"
#include "vector.h"


using namespace std;

void createMap(HashMap<Queue<string>, Vector<string> >&, ifstream& , int);
void displayWords(HashMap<Queue<string>, Vector<string> >&, int);

int main() {
    // TODO: Finish the program!
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << endl;
    cout << "This program makes random text based on a document. "<< endl;
    cout << "Give me an input file and an 'N' value for groups of words, "<< endl;
    cout << "and I'll create random text for you." << endl;
    cout << " " << endl;

    ifstream input;
    string filename = getLine("Input file name? ");
    cout << " " << endl;
    input.open(filename.c_str());
    int N = getInteger("Value of N?");
    cout << " " << endl;

    HashMap<Queue<string>, Vector<string> > map;
    createMap(map, input, N);

    while(true){
        int wordsNum = getInteger("# of random words to generate (0 to quit)?");
        cout << " " << endl;
        if (wordsNum < N && wordsNum != 0) {
            cout << "Must be at least " << N << " words." << endl;
            cout << " " << endl;
            wordsNum = getInteger("# of random words to generate (0 to quit)?");
            cout << " " << endl;
        }
        if (wordsNum < 1) {
            cout << "Exiting." << endl;
            break;
        }
        displayWords(map,wordsNum);
    }
    return 0;
}

void createMap(HashMap<Queue<string>, Vector<string> > &map, ifstream &input, int N) {
    Queue<string> initKey;
    string word;
    for (int i = 0; i < N-1; i++) {
        input >> word;
        initKey.enqueue(word);
    }

    Queue<string> key;
    key = initKey;
    while(input >> word){
        map[key].add(word);
        key.dequeue();
        key.enqueue(word);
    }

    for (int j = 0; j < N-1; j++) {
        map[key].add(initKey.front());
        key.dequeue();
        key.enqueue(initKey.dequeue());
    }

}

void displayWords(HashMap<Queue<string>, Vector<string> > &map, int wordsNum){
    Vector<string> display_words;
    Queue<string> key;
    Queue<string> start_key = map.keys().get(randomInteger(0, map.keys().size()));
    key = start_key;
    for (int i = 0; i < start_key.size(); i++) {
        string word = start_key.front();
        display_words.add(word);
        start_key.dequeue();
        start_key.enqueue(word);
    }

    while (true) {
        string nextword = map[key].get(randomInteger(0, map[key].size()-1));
        key.dequeue();
        key.enqueue(nextword);
        display_words.add(nextword);
        if(display_words.size() == wordsNum){
            cout << "... ";
            for (int var = 0; var < wordsNum; var++) {
                cout << display_words[var] << " ";
            }
            cout << "..." << endl;
            cout << " " << endl;
            break;
        }
    }

}
