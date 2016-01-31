/**
 * File: life.cpp
 * --------------
 * Implements the Game of Life.
 */

#include <iostream>  // for cout
using namespace std;

#include "console.h" // required of all files that contain the main function
#include "simpio.h"  // for getLine
#include "random.h"  // for setRandomSeed(seed)
#include "gevents.h" // for mouse event
#include "gwindow.h" // for pause
#include "stack.h"   // for stack
#include "queue.h"   // for queue

#include "life-constants.h"  // for kMaxAge
#include "life-graphics.h"   // for class LifeDisplay

static Grid<int> randomGrid(LifeDisplay& display);
static int checkNeighbor(Grid<int>& board, int row, int column);
static Grid<int> nextGeneration(Grid<int>& board, LifeDisplay& display);
static void runSimulation(Grid<int>& board,LifeDisplay& display,string speed);
static Grid<int> generatedByFile(LifeDisplay& display, string filename);
static Grid<int> displayGrid(LifeDisplay& display);
static Grid<int> readFile(string filename);

static void waitForEnter(string message) {
    cout << message;
    (void) getLine();
}

static void welcome() {
	cout << "Welcome to the game of Life, a simulation of the lifecycle of a bacteria colony." << endl;
	cout << "Cells live and die by the following rules:" << endl << endl;
	cout << "\tA cell with 1 or fewer neighbors dies of loneliness" << endl;
	cout << "\tLocations with 2 neighbors remain stable" << endl;
	cout << "\tLocations with 3 neighbors will spontaneously create life" << endl;
	cout << "\tLocations with 4 or more neighbors die of overcrowding" << endl << endl;
	cout << "In the animation, new cells are dark and fade to gray as they age." << endl << endl;
    waitForEnter("Hit [enter] to continue....   ");
}

static string selectChoice(){
    cout << "You choose how fast to run the simulation." << endl << endl;
    cout << "\t1 = As fast as this chip can go!" << endl;
    cout << "\t2 = Not too fast, this is a school zone." << endl;
    cout << "\t3 = Nice and slow so I can watch everything that happens." << endl;
    cout << "\t4 = Require enter key be pressed before advancing to next generation." << endl << endl;
    cout << "In the animation, new cells are dark and fade to gray as they age." << endl << endl;
    string i = getLine("Your choice:");
    return i;
}

int main() {
    LifeDisplay display;
    display.setTitle("Game of Life");
    display.setDimensions(40, 70);
    display.drawCellAt(0, 0, 1);
    display.drawCellAt(19, 34, 5);
    display.drawCellAt(39, 69, kMaxAge);
    welcome();
    Grid<int> board(40,70);
    board = displayGrid(display);
    string i = selectChoice();
    runSimulation(board,display,i);
    return 0;
}

static Grid<int> displayGrid(LifeDisplay& display){
    Grid<int> board;
    cout << "You can start your colony with random cells or read from a prepared file." <<endl;
    string filename = getLine("Enter name of colony file (or RETURN to seed randomly):");
    if(filename == ""){
        board = randomGrid(display);
    } else {
        board = generatedByFile(display,filename);
    }

    return board;
}

static Grid<int> readFile(string filename){
    Stack<string> lines;
    ifstream input;
    filename += ".txt";
    const char * ch = filename.c_str();
    input.open(ch);
    while (true) {
        string line;
        getline(input,line);
        if(input.fail()) break;
        lines.push(line);
    }

    Grid<int> board;
    bool isRowNum = true;
    int row;
    int col;
    while (!lines.isEmpty()){
        string line = lines.pop();
        if(startsWith(line,"#")){
            continue;
        } else if(startsWith(line,"-")||startsWith(line,"X")){
            for(int i=0; i<line.size(); i++){
                char ch = line[i];
                if(ch == '-') board[row][i]=0;
                if(ch == 'X') board[row][i]=1;
            }
        } else if(isRowNum){
            isRowNum = false;
            row = stringToInteger(line);
        } else {
            col = stringToInteger(line);
        }
    }
    return board;

}

//reading a local file
static Grid<int> generatedByFile(LifeDisplay& display, string filename){
    Grid<int> board = readFile(filename);
    for (int row=0; row<board.nRows; row++){
        for(int col=0; col<board.nCols; col++){
            display.drawCellAt(row,col,board[row][col]);
        }
    }
    return board;
}

static Grid<int> randomGrid(LifeDisplay& display){
    Grid<int> board;
    board.resize(40,70);
        for(int i=0;i<40;i++){
            for(int j=0;j<70;j++){
                int value = randomInteger(0,kMaxAge);
                display.drawCellAt(i,j,value);
                board[i][j] = value;
            }
        } 
    return board;
}

//check one cell's neighbor to see if the neighbors are alive
static int checkNeighbor(Grid<int>& board, int row, int column){
    int result;
    if(board.inBounds(row-1,column-1) && board[row-1][column-1] !=0) result++;
    if(board.inBounds(row-1,column) && board[row-1][column] !=0) result++;
    if(board.inBounds(row-1,column+1) && board[row-1][column+1] !=0) result++;
    if(board.inBounds(row,column-1) && board[row][column-1] !=0) result++;
    if(board.inBounds(row,column+1) && board[row][column+1] !=0) result++;
    if(board.inBounds(row+1,column-1) && board[row+1][column-1] !=0) result++;
    if(board.inBounds(row+1,column) && board[row+1][column] !=0) result++;
    if(board.inBounds(row+1,column+1) && board[row+1][column+1] !=0) result++;
    return result;
}


static Grid<int> nextGeneration(Grid<int>& board, LifeDisplay& display){
    Grid<int> nextBoard(40,70);
    for(int i=0; i<board.numRows(); i++){
        for(int j=0; j<board.numCols(); j++){
            int result = checkNeighbor(board,i,j);
           if(result == 2){
                nextBoard[i][j]=board[i][j];
                display.drawCellAt(i,j,nextBoard[i][j]);
            } else if(result == 3){
                board[i][j]++;
                nextBoard[i][j]=board[i][j];
                display.drawCellAt(i,j,nextBoard[i][j]);
            } else {
                board[i][j]=0;
                nextBoard[i][j]=board[i][j];
                display.drawCellAt(i,j,nextBoard[i][j]);
            }
        }
    }
    return nextBoard;
}

static void runSimulation(Grid<int>& board,LifeDisplay& display,string speed){
    while(true){
        Grid<int> nextBoard(40,70);
        nextBoard = nextGeneration(board,display);
        if(speed=="1") pause(0);
        if(speed=="2") pause(100);
        if(speed=="3") pause(500);
        if(speed=="4") waitForEnter("Enter to see next generation");
    }
}

