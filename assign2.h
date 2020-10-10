/*
Kaylee Chan
2348244
kaychan@chapman.edu
CPSC 350-03
Assignment 2

This assignment uses 2D arrays to model Conway's Game of Life. It implements 3 different modes to calculate boundaries of the grid.
*/
#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;

//Life class
class Life{
public:
  //public methods
  Life();
  ~Life();
  // void start();
  void chooseMode(int height, int width, char**& board);
  void runGame();
  void choosePauseOptions();
  bool print(int rows, int columns, char**& board, int generationCount, string print, bool countingFile);
  //modes
  void classicMode(int row, int column, char**& currGen);
  void mirrorMode(int row, int column, char** board);
  void doughnutMode(int row, int column, char** board);

  void randomWorld(int height, int width, double density);
  void fileWorld(string filename);

//private variables
private:
  int row;
  int column;
  int genCount  = 0;
  bool runningSimulation = true;
  string printOption;
  string filename;
  ofstream writeFile;
};
