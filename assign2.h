#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;

class Life{
public:
  Life();
  ~Life();
  // void start();
  void chooseMode(int height, int width, char**& board);
  void runGame();
  void choosePauseOptions();
  bool print(int rows, int columns, char**& board, int generationCount, string print);
  //modes
  void classicMode(int row, int column, char**& currGen);
  void mirrorMode(int row, int column, char** board);
  void doughnutMode(int row, int column, char** board);

  void randomWorld(int height, int width, double density);
  void fileWorld(string filename);

private:
  int row;
  int column;
  int genCount  = 0;
  bool runningSimulation = true;
  char **myGrid;
  string printOption;
  string filename;
  ofstream writeFile;
};
