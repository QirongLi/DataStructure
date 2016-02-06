/**
 * File: word-ladder.cpp
 * ---------------------
 * Implements a program to find word ladders connecting pairs of words.
 */

#include <iostream>
using namespace std;

#include "console.h"
#include "lexicon.h"
#include "strlib.h"
#include "simpio.h"
#include "queue.h"
#include "foreach.h"

static string getWord(Lexicon& english, string prompt);
static string nextWord(string lastWord, Lexicon& english, Lexicon& alreadyUsed);
static Vector<string> generateLadder(Lexicon& english, string start, string end);
static void printLadder(Vector<string> v);
static void playWordLadder();

static string getWord(Lexicon& english, string prompt) {
    while (true) {
        string response = trim(toLowerCase(getLine(prompt)));
        if (response.empty() || english.contains(response)) return response;
        cout << "Your response needs to be an English word, so please try again." << endl;
    }
}

//Find next word which is one letter different than the previous one.
static string nextWord(string lastWord, Lexicon& english, Lexicon& alreadyUsed){
    string nextword;
    for(int i=0; i<lastWord.length(); i++){
        nextword = lastWord;
        for(char j='a'; j<'z'; j++){
            nextword = nextword.replace(i,1,1,j);
            if(english.contains(nextword)){
                if(!alreadyUsed.contains(nextword)){
                    return nextword;
                }
            }
        }
    }
    return "";
}

static Vector<string> generateLadder(Lexicon& english, string start, string end) {
    Queue<Vector<string> > ladderQueue;
    Lexicon alreadyUsed; //recording words have been used;

    Vector<string> first;
    first.add(start);
    ladderQueue.enqueue(first);

    string next;

    while(true){

        if(ladderQueue.size()==0){
            Vector<string> v;
            return v;
        }else{
            Vector<string> ladder = ladderQueue.dequeue();

            while(true){
                next = nextWord(ladder[ladder.size()-1], english, alreadyUsed);
                if(next == end){
                    ladder.add(next);
                    return ladder;
                }else if(next != ""){
                    Vector<string> newVector;
                    newVector = ladder;
                    newVector.add(next);
                    alreadyUsed.add(next);
                    ladderQueue.enqueue(newVector);
                }else if(next == ""){
                    break;
                    alreadyUsed.add(next);
                }
            }
        }
    }
}

static void printLadder(Vector<string> v){
    if(v.size()==0){
        cout << "No ladder was found!" << endl;
    }else{
        cout << "Ladder found!" << endl;
        cout << v.size() << " steps between " << v[0] << " " << v[v.size()-1] << "." << endl;
        for(int i=0; i<v.size()-1; i++){
            cout << v[i] << "-";
        }
        cout << v[v.size()-1] << endl;
    }
}

static const string kEnglishLanguageDatafile = "EnglishWords.dat";
static void playWordLadder() {
    Lexicon english(kEnglishLanguageDatafile);
    while (true) {
        string start = getWord(english, "Please enter the source word [return to quit]: ");
        if (start.empty()) break;
        string end = getWord(english, "Please enter the destination word [return to quit]: ");
        if (end.empty()) break;
        Vector<string> v = generateLadder(english, start, end);
        printLadder(v);
    }
}

int main() {
    cout << "Welcome to the CS106 word ladder application!" << endl << endl;
    playWordLadder();
    cout << "Thanks for playing!" << endl;
    return 0;
}
