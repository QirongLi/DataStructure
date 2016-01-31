// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

// Please feel free to add any other #includes you need!
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "gwindow.h"
#include "hashmap.h"
#include "map.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "recursionproblems.h"
using namespace std;

int convertStringToInteger(string exp);
bool isBalanced(string exp);
double weightOnKnees(int row, int col, Vector<Vector<double> >& weights);
void drawSierpinskiTriangle(GWindow& gw, int x, int y, int size, int order);
void floodFill(int x, int y, int width, int height, int color);
void floodFillHelper(int x, int y, int width, int height, int color, int oldcolor);
Vector<string> grammarGenerate(istream& input, string symbol, int times);
void grammarGenerateHelper(string symbol, string& v,
                           HashMap<string, Vector<string> > map);

int countKarelPaths(int street, int avenue) {
    // TODO: write this function
    if (street < 1 || avenue < 1) {
        return 0;
    }else if (street == 1 && avenue == 1) {
        return 1;
    }else {
        return countKarelPaths(street - 1, avenue)
                + countKarelPaths(street, avenue - 1);
    }
}

int convertStringToInteger(string exp) {
    if(exp.size() == 0) return 0;
    if(exp[0] == '-') {
       return -convertStringToInteger(exp.substr(1, exp.length()-1));
    }

    if(exp.size() == 1){
        if(isdigit(exp[0])) return exp[0] - '0';
        else {
            cout << exp << " is not a number." << endl;
        }
    }
    int n = exp.length() - 1;
    return convertStringToInteger(exp.substr(exp.length() - 1,1))
            + convertStringToInteger(exp.substr(0, n--) ) * 10 ;
}

bool isBalanced(string exp) {
    if (exp.size() == 0) return true;
    if (exp.size() == 1) return false;

    if (exp[0]=='(' && exp[1]==')'){
        return isBalanced(exp.substr(2,exp.length()-2));
    }else if (exp[0]=='(' && exp[exp.length()-1]==')'){
        return isBalanced(exp.substr(1,exp.length()-2));
    }else if (exp[0]=='{' && exp[1]=='}'){
        return isBalanced(exp.substr(2,exp.length()-2));
    }else if (exp[0]=='{' && exp[exp.length()-1]=='}'){
        return isBalanced(exp.substr(1,exp.length()-2));
    }else if (exp[0]=='[' && exp[1]==']'){
        return isBalanced(exp.substr(2,exp.length()-2));
    }else if (exp[0]=='[' && exp[exp.length()-1]==']'){
        return isBalanced(exp.substr(1,exp.length()-2));
    }else {
        return false;
    }
}

double weightOnKnees(int row, int col, Vector<Vector<double> >& weights) {
    if(row==0){
        return weights[0][0];
    }

    if(col==0){
        return weights[row][col]+(weightOnKnees(row-1,col,weights))/2;
    }else if(col==(weights[row].size()-1)){
        return weights[row][col]+(weightOnKnees(row-1,col-1,weights))/2;
    }
        return weights[row][col] + (weightOnKnees(row-1,col-1,weights))/2
                + (weightOnKnees(row-1,col,weights))/2;
}

void drawSierpinskiTriangle(GWindow& gw, int x, int y, int size, int order) {
    if(order == 1) {
        int delta_y = sqrt(size*size-(size/2)*(size/2));
        gw.drawLine(x, y, x+size, y);
        gw.drawLine(x, y, x+size/2, y+delta_y);
        gw.drawLine(x+size/2, y+delta_y, x+size,y);
    }else{
        int delta_y = sqrt(size*size-(size/2)*(size/2));
        drawSierpinskiTriangle(gw, x, y, size/2, order-1);
        drawSierpinskiTriangle(gw, x+size/2, y, size/2, order-1);
        drawSierpinskiTriangle(gw, x+size/4, y+delta_y/2,size/2, order-1);
    }
}

void floodFill(int x, int y, int width, int height, int color) {
    //check the region boundary
    int oldcolor = getPixelColor(x,y);
    floodFillHelper(x,y,width,height,color,oldcolor);
}

void floodFillHelper(int x, int y, int width, int height, int color, int oldcolor){

    if((x>0&&x<width)&&(y>0&&y<height)&&getPixelColor(x,y)==oldcolor){
    setPixelColor(x,y,color);
    floodFillHelper(x+1,y,width,height,color,oldcolor);
    floodFillHelper(x-1,y,width,height,color,oldcolor);
    floodFillHelper(x,y+1,width,height,color,oldcolor);
    floodFillHelper(x,y-1,width,height,color,oldcolor);
    }
}

Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    // TODO: write this function
    Vector<string> result;

    HashMap<string, Vector<string> > map;
    string line;
    while(getline(input,line)){
        Vector<string> vec0 = stringSplit(line, "::=");
        string key = trim(vec0[0]);
        Vector<string> vec1 = stringSplit(vec0[1],"|");

        Vector<string> values;
        for(string s:vec1){
            values.add(trim(s));
        }
        map.put(key,values);
    }

    for (int i = 0; i < times; i++) {
        string v = "";
        grammarGenerateHelper(symbol,v,map);
        result.add(v);
    }

    return result;
}

void grammarGenerateHelper( string symbol, string& v,
                            HashMap<string, Vector<string> > map){

    Vector<string> vec = map.get(symbol);

    string word = vec[randomInteger(0,vec.size()-1)];
    word = trim(word);
    Vector<string> list = stringSplit(word, " ");
    if(list.size() == 1){
        if (map.containsKey(word)) {
            grammarGenerateHelper(word,v,map);
        }else{
            v = v+ " " + word ;
        }
    }else if(list.size() > 1){
        for(int k=0; k<list.size(); k++){
            if(map.containsKey(list[k])){
                grammarGenerateHelper(list[k],v,map);
            }else{
                v = v + " " + word ;
            }
        }
    }

}
