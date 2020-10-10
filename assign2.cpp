/*
Kaylee Chan
2348244
kaychan@chapman.edu
CPSC 350-03
Assignment 2

This assignment uses 2D arrays to model Conway's Game of Life. It implements 3 different modes to calculate boundaries of the grid.
*/
#include "assign2.h"
#include <math.h>
#include <sstream>
#include <cstdlib>
#include <limits> //for enter
#include <unistd.h>
#include <climits>

//default constructor
Life::Life(){
  genCount= 0;
  row = 0;
  column = 0;
}

//destructor
Life::~Life(){
  //
}

/*
runGame method - asks user if they want a random configuration or use a file
void - does not have return type
parameter - none
*/
void Life::runGame(){
  genCount = 0;
  bool playing = true;
  string config;
  int userRow;
  int userCol;
  double userDensity;
  string userFile;

  while (playing) {
    cout << "Do you want a randomly generated board or read from a file? (rand/file) " << endl;
    cin >> config;

    //check if user entered rand
    if (config.compare("rand") == 0){
      cout << "Enter height of grid as an int: " << endl;
      cin >> userRow;
      while(userRow <= 0 || cin.fail()){
        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(INT_MAX, '\n'); // ignore last input
        cout << "ERROR! You can only enter an integer for the grid's height " << endl;
        cin >> userRow;
      }

      cout << "Enter width of grid as an int: " << endl;
      cin >> userCol;
      while(userCol <= 0 || cin.fail()){
        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(INT_MAX, '\n'); // ignore last input
        cout << "ERROR! You can only enter an integer for the grid's width " << endl;
        cin >> userCol;
      }
        cout << "Enter initial population density of the world as a decimal (a number greater than 0 or equal to 1): " << endl;
        //while loop checks if user enters a double
        while (1) {
          if (cin >> userDensity && (userDensity >0) && (userDensity <= 1)) {
            // valid number
            break;
        } else {
          // not a valid number
          cout << "Invalid Input! Please input a decimal number." << endl;
          cin.clear();
          while (cin.get() != '\n') ; // empty loop
          }
        }

      randomWorld(userRow, userCol, userDensity);
      playing = false;
      //if user wants a file configuration
    }else if(config.compare("file") == 0){
       cout << "Enter the file path for your map file (include .txt extension): " << endl;
       cin >> userFile;
       fileWorld(userFile);
       playing = false;
    }else{
      cout << "ERROR: not an option. Try entering 'rand' or 'file' " << endl;
    }

  }
}

/*
chooseMode method - prompts user to choose between the 3 modes
void - does not have return type
parameter - int of grid's height, int of grid's width, pointer address of grid
*/
void Life::chooseMode(int height, int width, char**& board){
  string mode;
  bool selecting = true;
  cout << "What mode do you want to run in? (classic, doughnut, mirror) " << endl;
  cin >> mode;
  while(selecting){
    if(mode == "classic"){
      //cout << "chooseMode () rows : " << height << endl;
      classicMode(height, width, board);
      selecting = false;
    }else if(mode == "mirror"){
      mirrorMode(height, width, board);
      selecting = false;
    }else if(mode == "doughnut"){
      doughnutMode(height, width, board);
      selecting = false;
    }else{
      cout << "ERROR! Not an available mode! Try entering 'classic', 'mirror', or 'doughnut' " << endl;
      cin >> mode;
      continue;
    }
  }
}

/*
choosePauseOptions method - starts game by prompting user to choose how they want results to be shown
void - does not have return type
parameter - none
*/
void Life::choosePauseOptions(){
  genCount = 0;
  bool choosingOption= true;
  cout << "How would you like your brief pause between generations? " << endl;
  cout << "Press '1' for brief pause between generations, '2' to press 'Enter' key, '3' output to a file " << endl;
  cin >> printOption;

  while(choosingOption){
    if(printOption == "1"){
      choosingOption =  false;
    }else if(printOption == "2" ){
      choosingOption =  false;
    }else if(printOption == "3"){
      cout << "What is the file name for the results to be outputted to (include .txt extension) " << endl;
      cin >> filename;
      choosingOption =  false;
    }else{
      cout << "Invalid option! Try entering '1', '2'. or '3' " << endl;
      cin >> printOption;
      continue;
    }
  }

  while(!choosingOption){
    runGame();
    break;
  }

}

/*
print method - method that prints each generation
bool - returns true of false to stop the program from printing further generations
parameter - int rows of grid, int columns of grid, pointer to board , int genCount to count current generation, string print, bool fileCounter
*/
bool Life::print(int rows, int columns, char**& board, int genCount, string print, bool fileCounter){
  if(printOption == "1"){
    sleep(2); //automated pause
    cout << "Generation: " << genCount << endl;
    int same = 0;
    //check if board has stabilized
    for(int i = 0; i< rows; ++i){
      for(int j = 0; j < columns; ++j){
        cout << board[i][j];
        if(board[i][j] == '-'){
          same++;
        }
      }
      cout << endl;
    }

    //asks user to press enter to exit program because world has now stabilized
    if(same == (rows*columns)){
      cout << "WORLD HAS NOW STABILIZED! PRESS 'ENTER' TO EXIT PROGRAM: " << endl;
      cin.get();
      while(cin.get()!= '\n'){
        cin.get();
        cout<< "PRESS ENTER TO EXIT" << endl;
      }
      return false; //exit program
    }else{
      return true; //continue program
    }

  }else if(printOption == "2"){
    //string temp;
    cout << "Press 'Enter' to continue printing: " << endl;
    char temp = 'x';
    while (temp != '\n'){
      cin.get(temp);
    }

    cout << "Generation: " << genCount << endl;
    int same = 0;
    //checks if world has stabilized
    for(int i = 0; i< rows; ++i){
      for(int j = 0; j < columns; ++j){
        cout << board[i][j];
        if(board[i][j] == '-'){
          same++;
        }
      }
      cout << endl;
    }

    //asks user to press enter since world has now stabilized
    if(same == (rows*columns)){
      cout << "WORLD HAS NOW STABILIZED! PRESS 'ENTER' TO EXIT PROGRAM: " << endl;
      cin.get();
      while(cin.get()!= '\n'){
        cin.get();
        cout<< "PRESS ENTER TO EXIT" << endl;
      }
      return false; //exit program
    }else{
      return true; //continue program
    }

  }else if(printOption == "3"){
    int same = 0;
    if(fileCounter == true){
    writeFile << "Generation: " << genCount << endl;
    //check if world has stabilized
    for(int i = 0; i < rows; ++i){
      for(int j = 0; j < columns; ++j){
        writeFile << board[i][j];
        if(board[i][j] == '-' ){
          same++;
        }
      }
      writeFile << endl;
    }
  }else{
    writeFile.close();
  }

  //if world has stabilized, user presses  enter to exit program
    if(same == (rows*columns)){
      cout << "WORLD HAS BEEN PRINTED TO TEXT FILE! PRESS 'ENTER' TO EXIT PROGRAM: " << endl;
      cin.get();
      while(cin.get()!= '\n'){
        cin.get();
        cout<< "PRESS ENTER TO EXIT" << endl;
      }
      return false; //exit program

    }else{
      return true; //continue program
    }

  }else{
    //nothign
  }

}

/*
randomWorld method - to create a randomly generated board
void - doesn't return anything
parameter - int height of grid, int width of grid, double population density of grid
*/
void Life::randomWorld(int height, int width, double popDensity){
  int totalCells = 0;
  totalCells = height*width;
  double population = 0.0;
  bool fileCounter = true;
  population = ceil(popDensity*totalCells);


  char** gridBoard = new char*[height];
  for(int i = 0; i < height; ++i){
    gridBoard[i] = new char[width];
  }

  for(int i = 0; i< height; ++i){
    for(int j = 0; j < width; ++j){
      gridBoard[i][j] = '-';
    }
  }

  //generate random cells in world
  int randHeight = rand() % (height);
  int randWidth = rand() % (width);
  while(population > 0){
    if(gridBoard[randHeight][randWidth] == '-'){
      gridBoard[randHeight][randWidth] = 'X';
      population--;
      continue;
    }else{
      randHeight = rand() % (height);
      randWidth = rand() % (width);
    }
  }

  chooseMode(height, width, gridBoard);
}//end of randomWorld method

/*
fileWorld method - to create a board based on user file
void - doesn't return anything
parameter - string filename to be opened
*/
void Life::fileWorld(string filename){
  ifstream readFile;
  int lineNum = 0;
  int row;
  int column;
  char ch;
  char** gridBoard;
  readFile.open(filename, ios::in);
  while(!readFile.is_open()){
    cout << "ERROR: FILE NOT OPENED! Try entering an applicable '.txt' file: " << endl;
    cin >> filename;
    readFile.open(filename, ios::in);
  }
  while(!readFile.eof()){
    string str;
    getline(readFile, str);
    if(lineNum == 0){
      stringstream heightDimen(str); //get first number in file, convert to int, and set it to row
      heightDimen >> row;
    }else if (lineNum == 1){
      stringstream widthDimen(str); //get second number in file, convert to int, and set it to column
      widthDimen >> column;
    }else{
      break;
    }
    lineNum++;
  }

  gridBoard = new char*[row];
  for(int i = 0; i < row; ++i){
    gridBoard[i] = new char[column];
  }

  //restart .eof() stream and read file starting from the top
  readFile.clear();
  readFile.seekg(0);
  string currLine;
  int currLineNum = 0;
  int ignore = 0;
  while(!readFile.eof()){
    getline(readFile, currLine);
    if(ignore == 0){
      //ignore
    }else if (ignore == 1){
      //ignore
    }else{
      for(int i = 0; i < column; ++i){
        if(currLineNum != row){
          ch = currLine[i];
          gridBoard[currLineNum][i] = ch;
        }
      }
      //boundary check
      currLineNum++;
    }
    ignore++;
  }
  chooseMode(row, column, gridBoard);


}

/*
classicMode method - to create a board based on the rules of classic mode
void - doesn't return anything
parameter - int rows of grid, int columns of grid, pointer to grid
*/
void Life::classicMode(int row, int column, char**& currGen){
  int infinity = 1000;
  int infinityCounter = 0;
  genCount = 0;
  bool fileCounter = true;
  char **nextGen = new char*[row];
  for(int i = 0; i < row; ++i){
    nextGen[i] = new char[column];
  }

  bool runningSimulation = true;
  while(runningSimulation){
    for(int i =0; i < row; ++i){
      for(int j = 0; j < column; ++j){
        int cells = 0;
        if(i!= 0 && currGen[i-1][j] == 'X')
          ++cells;
        if(i!=0 && j!=0 && currGen[i-1][j-1] == 'X')
          ++cells;
        if(i!=0 && j!=(column-1) && currGen[i-1][j+1] == 'X')
          cells++;
        if(j!=0 && currGen[i][j-1] == 'X')
          ++cells;
        if( (j!=column-1) && currGen[i][j+1] == 'X')
          ++cells;
        if( (i!= (row-1)) && j !=0 && currGen[i+1][j-1] == 'X')
          ++cells;
        if( i!= row-1 && currGen[i+1][j] == 'X')
          ++cells;
        if( i!= row-1 && j!= column && currGen[i+1][j+1] == 'X' )
          ++cells;

        if(cells <= 1){
          nextGen[i][j] = '-';
        }else if(cells == 2) {
          nextGen[i][j] = currGen[i][j];
        }else if(cells == 3){
          nextGen[i][j] = 'X';
        }else if(cells >= 4){
          nextGen[i][j] = '-';
        }
      }
    }//end of first for loop


    if(runningSimulation){

      //print original generation
      if(printOption == "3" && genCount ==0){
        writeFile.open(filename);
        writeFile << "Generation: " << genCount << endl;
        for(int i = 0; i< row; ++i){
          for(int j = 0; j < column; ++j){
            writeFile << currGen[i][j];
          }
          writeFile << endl;
        }
      }else if(genCount == 0){
        cout << "Generation: " << genCount << endl;

      //print array
        for(int i = 0; i< row; ++i){
          for(int j = 0; j < column; ++j){
            cout << currGen[i][j];
            }
          cout << endl;
        }

        if(printOption == "2"){
          char temp = 'x';
          while (temp != '\n'){
            cin.get(temp);
          }
        }


      }

      //check to see if both arrays are the same
        genCount++;
        int genAreSame = 0;
        for(int i = 0; i< row; ++i){
          for(int j = 0; j < column; ++j){
            if(currGen[i][j] == nextGen[i][j]){
              genAreSame++;
            }
          }
        }


        //if they are the same, update infinity counter
        if(genAreSame == (row*column)){
          infinityCounter++;

        }

        runningSimulation = print(row, column, nextGen, genCount, printOption, fileCounter);
        //set currGen = nextGen, so the next time it runs, it will update the nextGen
        for(int i = 0; i< row; ++i){
          for(int j = 0; j < column; ++j){
            currGen[i][j] = nextGen[i][j];
            }
        }

        //if simulation is infinite, only run code up to 1000th generation and exit
        if(infinityCounter == infinity){
          cout << "STOPPED AFTER PRINTING 1000 GENERATIONS FROM WHEN GRIDS STABILIZED :)" << endl;
          runningSimulation = false;
        }

    }

  }
  if(writeFile.is_open()){
    writeFile.close();
  }

}

/*
doughnutMode method - to create a board based on the rules of doughnut mode
void - doesn't return anything
parameter - int rows of grid, int columns of grid, pointer to grid
*/
void Life::doughnutMode(int row, int column, char** currGen){
  int infinity = 1000;
  int infinityCounter = 0;
  bool fileCounter = true;

  //cout << "in doughnut mode " << endl;
  char **nextGen = new char*[row];
  for(int i = 0; i < row; ++i){
    nextGen[i] = new char[column];
  }

  for(int m = 0; m < row; ++m){
    for(int n =0; n < column; ++n){
      nextGen[m][n] = '-';
    }
  }
  bool runningSimulation = true;
  while(runningSimulation){
    for(int i = 0; i < row; ++i){
      for(int j = 0; j < column; ++j){
        int cells = 0;
        if(i == 0 && j == 0){
          if(currGen[i][j+1] == 'X')
            cells++;
          if(currGen[i+1][j+1] == 'X')
            cells++;
          if(currGen[i+1][j] == 'X')
            cells++;
          if(currGen[row-1][j] == 'X')
            cells++;
          if(currGen[row-1][j+1] == 'X')
            cells++;
          if(currGen[row-1][column-1] == 'X')
            cells++;
          if(currGen[i][column-1] == 'X')
            cells++;
          if(currGen[i+1][column-1] == 'X')
            cells++;
        } else if(i == 0 && j == (column-1)){
          if(currGen[i][j-1] == 'X')
            cells++;
          if(currGen[i+1][j-1] == 'X')
            cells++;
          if(currGen[i+1][j] == 'X')
            cells++;
          if(currGen[row-1][j] == 'X')
            cells++;
          if(currGen[row-1][j-1] == 'X')
            cells++;
          if(currGen[row-1][0] == 'X')
            cells++;
          if(currGen[i][0] == 'X')
            cells++;
          if(currGen[i+1][0] == 'X')
            cells++;
        }else if (i!= 0 && i!= (row-1)  && j!= (column-1) && j!=0){
          if(i!= 0 && currGen[i-1][j] == 'X')
            ++cells;
          if(i!=0 && j!=0 && currGen[i-1][j-1] == 'X')
            ++cells;
          if(i!=0 && j!=(column-1) && currGen[i-1][j+1] == 'X')
            cells++;
          if(j!=0 && currGen[i][j-1] == 'X')
            ++cells;
          if( (j!=column-1) && currGen[i][j+1] == 'X')
            ++cells;
          if( (i!= (row-1)) && j !=0 && currGen[i+1][j-1] == 'X')
            ++cells;
          if( i!= row-1 && currGen[i+1][j] == 'X')
            ++cells;
          if( i!= row-1 && j!= column && currGen[i+1][j+1] == 'X' )
            ++cells;
        }else if(i == (row-1) && j ==0){
          if(currGen[i-1][j] == 'X')
            cells++;
          if(currGen[i][j+1] == 'X')
            cells++;
          if(currGen[i-1][j+1] == 'X')
            cells++;
          if(currGen[0][j] == 'X')
            cells++;
          if(currGen[0][j+1] == 'X')
            cells++;
          if(currGen[0][column-1] == 'X')
            cells++;
          if(currGen[i][column-1] == 'X')
            cells++;
          if(currGen[i-1][column-1] == 'X')
            cells++;
        }else if(i == (row-1) && j == (column-1)){
          if(currGen[i][j-1] == 'X')
            cells++;
          if(currGen[i-1][j] == 'X')
            cells++;
          if(currGen[i-1][j-1] == 'X')
            cells++;
          if(currGen[i][0] == 'X')
            cells++;
          if(currGen[i-1][0] == 'X')
            cells++;
          if(currGen[0][0] == 'X')
            cells++;
          if(currGen[0][j] == 'X')
            cells++;
          if(currGen[0][j-1] == 'X')
            cells++;
      }else if(i == (row-1)){
          if(currGen[i][j+1] == 'X')
            cells++;
          if(currGen[i][j-1] == 'X')
            cells++;
          if(currGen[i-1][j-1] == 'X')
            cells++;
          if(currGen[i-1][j] == 'X')
            cells++;
          if(currGen[i-1][j+1] == 'X')
            cells++;
          if(currGen[0][j] == 'X')
            cells++;
          if(currGen[0][j+1] == 'X')
            cells++;
          if(currGen[0][j-1] == 'X')
            cells++;
        } else if(j == 0 ){
          if(currGen[i+1][j] == 'X')
            cells++;
          if(currGen[i-1][j] == 'X')
            cells++;
          if(currGen[i][j+1] == 'X')
            cells++;
          if(currGen[i+1][j+1] == 'X')
            cells++;
          if(currGen[i-1][j+1] == 'X')
            cells++;
          if(currGen[i-1][column-1] == 'X')
            cells++;
          if(currGen[i+1][column-1] == 'X')
            cells++;
          if(currGen[i][column-1] == 'X')
            cells++;
        }else if(j == (column -1)){
          if(currGen[i][j-1] == 'X')
            cells++;
          if(currGen[i-1][j] == 'X')
            cells++;
          if(currGen[i-1][j-1] == 'X')
            cells++;
          if(currGen[i+1][j] == 'X')
            cells++;
          if(currGen[i+1][j-1] == 'X')
            cells++;
          if(currGen[i][0] == 'X')
            cells++;
          if(currGen[i-1][0] == 'X')
            cells++;
          if(currGen[i+1][0] == 'X')
            cells++;
        }else if(i == 0){
          if(currGen[i+1][j] == 'X')
            cells++;
          if(currGen[i][j+1] == 'X')
            cells++;
          if(currGen[i+1][j+1] == 'X')
            cells++;
          if(currGen[i][j-1] == 'X')
            cells++;
          if(currGen[i+1][j-1] == 'X')
            cells++;
          if(currGen[row-1][j] == 'X')
            cells++;
          if(currGen[row-1][j-1] == 'X')
            cells++;
          if(currGen[row-1][j+1] == 'X')
            cells++;
        }else {
          //cout << "not in if statements" << endl;
        }

        if(cells <= 1){
          nextGen[i][j] = '-';
        }else if(cells == 2) {
          nextGen[i][j] = currGen[i][j];
        }else if(cells == 3){
          nextGen[i][j] = 'X';
        }else if(cells >= 4){
          nextGen[i][j] = '-';
        }
      }//end of second for loop
    }//end of first for loop


        if(runningSimulation){
          if(printOption == "3" && genCount ==0){
            writeFile.open(filename);
            writeFile << "Generation: " << genCount << endl;
            for(int i = 0; i< row; ++i){
              for(int j = 0; j < column; ++j){
                writeFile << currGen[i][j];
              }
              writeFile << endl;
            }
          }else if(genCount == 0){
            cout << "Generation: " << genCount << endl;

          //print arrayclear
            for(int i = 0; i< row; ++i){
              for(int j = 0; j < column; ++j){
                cout << currGen[i][j];
                }
              cout << endl;
            }

            if(printOption == "2"){
              //wait for enter key to be pressed to continue
              char temp = 'x';
              while (temp != '\n'){
                cin.get(temp);
              }
            }
          }
            genCount++;

            int genAreSame = 0;
            for(int i = 0; i< row; ++i){
              for(int j = 0; j < column; ++j){
                if(currGen[i][j] == nextGen[i][j]){
                  genAreSame++;
                }
              }
            }

            if(genAreSame == (row*column)){
              infinityCounter++;

            }
            runningSimulation = print(row, column, nextGen, genCount, printOption, fileCounter);
            //set currGen = nextGen, so the next time it runs, it will update the nextGen
            for(int i = 0; i< row; ++i){
              for(int j = 0; j < column; ++j){
                currGen[i][j] = nextGen[i][j];
                }
            }

            if(infinityCounter == infinity){
              cout << "STOPPED AFTER PRINTING 1000 GENERATIONS FROM WHEN GRIDS STABILIZED :)" << endl;
              runningSimulation = false;
            }

        }

  }//end of while loop
  if(writeFile.is_open()){
    writeFile.close();
  }


}//end of doughnutMode()

/*
mirrorMode method - to create a board based on the rules of mirror mode
void - doesn't return anything
parameter - int rows of grid, int columns of grid, pointer to grid
*/
void Life::mirrorMode(int row, int column, char** currGen){
  genCount = 0;
  int infinity = 1000;
  int infinityCounter = 0;
  bool runningSimulation = true;
  bool fileCounter = true;
  char **nextGen = new char*[row];
  for(int i = 0; i < row; ++i){
    nextGen[i] = new char[column];
  }

  while(runningSimulation){
  for(int i = 0; i < row; ++i){
    for(int j = 0; j < column; ++j){
      int cells = 0;
      if(i == 0 && j ==0){
        if(currGen[i][j] == 'X')
          cells+=3;
        if(currGen[i][j+1] == 'X')
          cells+=2;
        if(currGen[i+1][j] == 'X')
          cells+=2;
        if(currGen[i+1][j+1] == 'X')
          cells++;
        //top right corner
      }else if(i == 0 && j  == (column-1)){
        if(currGen[i][j] == 'X')
          cells+=3;
        if(currGen[i+1][j] == 'X')
          cells+=2;
        if(currGen[i][j-1] == 'X')
          cells+=2;
        if(currGen[i+1][j-1] == 'X')
          cells++;
        //bottom left corner
      }else if(i == (row-1) && j == 0){
        if(currGen[i][j] == 'X')
          cells+=3;
        if(currGen[i-1][j] == 'X')
          cells+=2;
        if(currGen[i][j+1] == 'X')
          cells+=2;
        if(currGen[i-1][j+1] == 'X')
          cells++;
        //bottom right corner
      }else if(i == (row-1) && j == (column-1)){
        if(currGen[i][j] == 'X')
          cells+=3;
        if(currGen[i-1][j] == 'X')
          cells+=2;
        if(currGen[i][j-1] == 'X')
          cells+=2;
        if(currGen[i-1][j-1] == 'X')
          cells++;
      }else if (i!= 0 && i!= (row-1)  && j!= (column-1) && j!=0){
        if(i!= 0 && currGen[i-1][j] == 'X')
          cells++;
        if( i!=0 && j!=0 && currGen[i-1][j-1] == 'X')
          ++cells;
        if(i!=0 && j!= column && currGen[i-1][j+1] == 'X')
          cells++;
        if(j!=0 && currGen[i][j-1] == 'X')
          cells++;
        if(j!=column && currGen[i][j+1] == 'X')
          cells++;
        if( i!= row-1 && column != 0 && currGen[i+1][j-1] == 'X')
          cells++;
        if( i!= row-1 && currGen[i+1][j] == 'X')
          cells++;
        if( i!= row-1 && j!= column && currGen[i+1][j+1] == 'X' )
          cells++;
      }else if(i == 0){
        if(currGen[i][j] == 'X')
          cells++;
        if(currGen[i][j-1] == 'X')
          cells+=2;
        if(currGen[i][j+1] == 'X')
          cells+=2;
        if(currGen[i+1][j] == 'X')
          cells++;
        if(currGen[i+1][j-1] == 'X')
          cells++;
        if(currGen[i+1][j+1] == 'X')
          cells++;
      } else if(j == 0){
        if(currGen[i][j] == 'X')
          cells++;
        if(currGen[i-1][j] == 'X')
          cells+=2;
        if(currGen[i+1][j] == 'X')
          cells+=2;
        if(currGen[i][j+1] == 'X')
          cells++;
        if(currGen[i-1][j+1] == 'X')
          cells++;
        if(currGen[i+1][j+1] == 'X')
          cells++;
      }else if(i == (row-1)){
        if(currGen[i][j] == 'X')
          cells++;
        if(currGen[i][j+1] == 'X')
          cells+=2;
        if(currGen[i][j-1] == 'X')
          cells+=2;
        if(currGen[i-1][j] == 'X')
          cells++;
        if(currGen[i-1][j+1] == 'X')
          cells++;
        if(currGen[i-1][j-1] == 'X')
          cells++;
      }else if(j == (column-1)){
        if(currGen[i][j] == 'X')
          cells++;
        if(currGen[i+1][j] == 'X')
          cells+=2;
        if(currGen[i-1][j] == 'X')
          cells+=2;
        if(currGen[i][j-1] == 'X')
          cells++;
        if(currGen[i+1][j-1] == 'X')
          cells++;
        if(currGen[i-1][j-1] == 'X')
          cells++;
      }
      else{
        cout << "not in if statements" << endl;
      }

      if(cells <= 1){
        nextGen[i][j] = '-';
      }else if(cells == 2) {
        nextGen[i][j] = currGen[i][j];
      }else if(cells == 3){
        nextGen[i][j] = 'X';
      }else if(cells >= 4){
        nextGen[i][j] = '-';
      }
    }//second for loop
  }//first for loop

      if(runningSimulation){
        if(printOption == "3" && genCount ==0){
          writeFile.open(filename);
          writeFile << "Generation: " << genCount << endl;
          for(int i = 0; i< row; ++i){
            for(int j = 0; j < column; ++j){
              writeFile << currGen[i][j];
            }
            writeFile << endl;
          }
        }else if(genCount == 0){
          cout << "Generation: " << genCount << endl;

        //print array
          for(int i = 0; i< row; ++i){
            for(int j = 0; j < column; ++j){
              cout << currGen[i][j];
              }
            cout << endl;
          }

          if(printOption == "2"){
            char temp = 'x';
            while (temp != '\n'){
              cin.get(temp);
            }
          }
        }
          genCount++;

          int genAreSame = 0;
          for(int i = 0; i< row; ++i){
            for(int j = 0; j < column; ++j){
              if(currGen[i][j] == nextGen[i][j]){
                genAreSame++;
              }
            }
          }

          if(genAreSame == (row*column)){
            infinityCounter++;
          }

          runningSimulation = print(row, column, nextGen, genCount, printOption, fileCounter);
          for(int i = 0; i< row; ++i){
            for(int j = 0; j < column; ++j){
              currGen[i][j] = nextGen[i][j];
              }
          }

          if(infinityCounter == infinity){
            cout << "STOPPED AFTER PRINTING 1000 GENERATIONS FROM WHEN GRIDS STABILIZED :)" << endl;
            runningSimulation = false;
            //if in mirror mode and want to print to file and simualtion is infite, it stops the program after 1000 generations have been printed
            if(printOption == "3"){
              bool fileCounter = false;
            }

          }

      }

}//end of while loop
if(writeFile.is_open()){
  writeFile.close();
}


}//end of mirrorMode()
