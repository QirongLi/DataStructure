
#include <cctype>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Boggle.h"
#include "bogglegui.h"
#include "hashmap.h"
#include "random.h"
#include "set.h"
#include "strlib.h"
#include "foreach.h"

HashMap<int, string> convertCubesToMap(Vector<string>& words);
HashMap<int, char> getLabelChar(HashMap<int, string>& map);
Vector<char> stringToCharVec(string word);
void setUpBoard();
int convert2Dto1D(int x, int y);
Vector<int> convert1Dto2D(int result);
bool visitedAround(Vector<int> positon, Set<int>& visitedPositions);
Vector<Vector<int> > getAllPositions(char c);
bool humanWordSearchHelper(string &word, int x, int y, Vector<int> &visitedPositions);
void computerWordSearchHelper(int x, int y, string word, Lexicon &lex, Set<string>& result, Set<int> &visitedPositions);

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Vector<Vector<char> > boardlabels;
Vector<string> humanWords;

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    setUpBoard();

}

void setUpBoard(){
    int row=4;
    int col=4;
    BoggleGUI::initialize(row,col);
    Vector<string> words;
    for (int var = 0; var < row*col; var++) {
        words.add(CUBES[var]);
    }
    HashMap<int,string> labelmap = convertCubesToMap(words);
    HashMap<int,char> labels = getLabelChar(labelmap);
    for(int i=0; i<row; i++){
        Vector<char> vec;
        for(int j=0; j<col; j++){
            BoggleGUI::labelCube(i,j,labels.get(i*row+j));
            vec.add(labels.get(i*row+j));
        }
        boardlabels.add(vec);
    }
}

HashMap<int, string> convertCubesToMap(Vector<string>& words){
    HashMap<int, string> map;
    for(int i=0; i < words.size(); i++){
        map.put(i,words[i]);
    }
    return map;
}

HashMap<int, char> getLabelChar(HashMap<int, string>& map){
    HashMap<int, char> charmap;
    for(int i=0; i<map.size(); i++){
        Vector<char> sc = stringToCharVec(map.get(i));
        char label = sc[randomInteger(0,sc.size()-1)];
        charmap.put(i,label);
    }
    return charmap;
}

Vector<char> stringToCharVec(string word){
    std::string s = word;
    std::vector<char> sc(s.begin(), s.end());
    Vector<char> vec;
    for(int i=0; i<(int)sc.size(); i++){
        vec.add(sc[i]);
    }
    return vec;
}

//Vector<Vector<int> > getAllPositions(char c){
//    Vector<Vector<int> > startpositions;
//    for(int i=0; i<boardlabels.size(); i++){
//        for(int j=0; j<boardlabels.get(0).size();j++){
//            if(boardlabels.get(i).get(j)==c){
//                Vector<int> vec;
//                vec.add(i);
//                vec.add(j);
//                startpositions.add(vec);
//            }
//        }
//    }
//    return startpositions;
//}

char Boggle::getLetter(int row, int col) {
    return boardlabels.get(row).get(col);
}

bool Boggle::checkWord(string word) {
    return false;   // remove this
}

bool Boggle::humanWordSearch(string word) {

//    Lexicon lex("dictionary.txt");
//    if(!lex.contains(word)) return false;

    string upWord = toUpperCase(word);
    bool result = false;

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(boardlabels.get(i).get(j)==upWord[0]){
                Vector<int> visitedPositions;
                int p = convert2Dto1D(i,j);
                visitedPositions.add(p);
                upWord = upWord.substr(1,upWord.size()-1);
                result = humanWordSearchHelper(upWord, i, j, visitedPositions);
                if(result){
                    cout << visitedPositions.toString() << endl;
                    humanWords.add(word);
                    return result;
                }
            }
        }
    }

    return result;

}

bool alreadyUsed(Vector<int>& visited, int k){
    for(int i=0; i<visited.size(); i++){
        if(visited.get(i)==k)
            return true;
    }
    return false;
}

bool humanWordSearchHelper(string &word, int x, int y, Vector<int>& visitedPositions){

    if(word.size()==0){
        for(int index=0; index<visitedPositions.size(); index++){
            Vector<int> v = convert1Dto2D(visitedPositions.get(index));
            BoggleGUI::setHighlighted(v.get(0), v.get(1), true);
            BoggleGUI::setAnimationDelay(100);
            //BoggleGUI::clearHighlighting();
        }
        return true;
    }

//    if(visitedPositions.contains(p)) return false;
//    for(int k=0; k<visitedPositions.size(); k++){
//        if(visitedPositions.get(k)==p) return false;
//    }

    for(int i=x-1; i<x+2; i++){
        for(int j=y-1; j<y+2; j++){
            if(i>=0&&i<4&&j>=0&&j<4&&!(i==x&&j==y)){
                BoggleGUI::setHighlighted(i, j, true);
                BoggleGUI::setAnimationDelay(500);
                BoggleGUI::clearHighlighting();

                if(boardlabels.get(i).get(j) == word[0]&&!alreadyUsed(visitedPositions, convert2Dto1D(i,j))){
                    int p=convert2Dto1D(i,j);
                    visitedPositions.add(p);
                    string s = word.substr(0,1);
                    word = word.substr(1,word.size()-1);
                    if(humanWordSearchHelper(word, i, j, visitedPositions))
                        return true;
                    word.insert(0,s);
                    visitedPositions.remove(visitedPositions.size()-1);
                }
            }
        }
    }

    return false;
}

int Boggle::humanScore() {
    // TODO: implement
    return 0;   // remove this
}

Set<string> Boggle::computerWordSearch() {
    Set<string> result;

    Lexicon lex("dictionary.txt");
    for(int i=0; i<boardlabels.size(); i++){
        for(int j=0; j<boardlabels.get(0).size(); j++){
            Set<int> visitedPoints;
            string word = "";
            computerWordSearchHelper(i, j, word, lex, result, visitedPoints);
        }
    }
    cout << result.toString() << endl;
    return result;        // remove this
}

void computerWordSearchHelper(int x, int y, string word, Lexicon &lex, Set<string>& result, Set<int>& visitedPositions){

    if(x<0||x>=4||y<0||y>=4) return;

    int p = convert2Dto1D(x,y);
    if(visitedPositions.contains(p)) return;

    word += boardlabels.get(x).get(y);
    if(!lex.containsPrefix(word)) return;
    if(word.length()>=4&&lex.contains(word))
        result.add(word);

    for(int i=x-1; i<=x+1; i++){
        for(int j=y-1; j<=y+1; j++){
            if(!(i==x&&j==y)){
                if(i>=0&&i<4&&j>=0&&j<4){
                    visitedPositions.add(p);
                    computerWordSearchHelper(i, j, word, lex, result, visitedPositions);
                    visitedPositions.remove(p);
                }
            }
        }
    }
}

int convert2Dto1D(int x, int y){
    int slope = 4;
    return x*slope+y;
}

Vector<int> convert1Dto2D(int result){
    int x = result/4;
    int y = result%4;
    Vector<int> vec;
    vec.add(x);
    vec.add(y);
    return vec;
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}
