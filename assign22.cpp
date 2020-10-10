// #include "assign2.h"
// #include <math.h>
// #include <sstream>
// #include <cstdlib>
// #include <limits> //for enter
// #include <unistd.h>
//
//
// Life::Life(){
//   genCount= 0;
//   row = 0;
//   column = 0;
// }
//
// Life::~Life(){
//   delete myGrid;
// }
//
// void Life::runGame(){
//   genCount = 0;
//   bool playing = true;
//   string config;
//   int userRow;
//   int userCol;
//   double userDensity;
//   string userFile;
//
//   while (playing) {
//     cout << "Do you want a randomly generated board or read from a file? (rand/file) " << endl;
//     cin >> config;
//
//     if (config.compare("rand") == 0){
//       cout << "Enter height of grid as an int: " << endl;
//       cin >> userRow;
//       cout << "Enter width of grid as an int: " << endl;
//       cin >> userCol;
//       bool notCorretDens = true;
//       while(notCorretDens){
//         cout << "Enter initial population density of the world as a decimal (a number greater than 0 or equal to 1): " << endl;
//         cin >> userDensity;
//         if( (userDensity >0) && (userDensity <= 1)){
//           notCorretDens = false;
//         }else{
//           notCorretDens = true;
//         }
//       }
//       randomWorld(userRow, userCol, userDensity);
//       playing = false;
//     }else if(config.compare("file") == 0){
//        cout << "Enter the file path for your map file (include .txt extension): " << endl;
//        cin >> userFile;
//        fileWorld(userFile);
//        playing = false;
//     }else{
//       cout << "ERROR: not an option. Try entering 'rand' or 'file' " << endl;
//     }
//
//   }
// }
//
// void Life::chooseMode(int height, int width, char**& board){
//   string mode;
//   bool selecting = true;
//   cout << "What mode do you want to run in? (classic, doughnut, mirror) " << endl;
//   cin >> mode;
//   while(selecting){
//     if(mode == "classic"){
//       //cout << "chooseMode () rows : " << height << endl;
//       classicMode(height, width, board);
//       selecting = false;
//     }else if(mode == "mirror"){
//       mirrorMode(height, width, board);
//       selecting = false;
//     }else if(mode == "doughnut"){
//       doughnutMode(height, width, board);
//       selecting = false;
//     }else{
//       cout << "not an available mode! try entering 'classic', 'mirror', or 'doughnut' " << endl;
//       cin >> mode;
//       continue;
//     }
//   }
// }
//
// void Life::choosePauseOptions(){
//   genCount = 0;
//   bool choosingOption= true;
//   cout << "How would you like your brief pause between generations? " << endl;
//   cout << "Press '1' for brief pause between generations, '2' to press 'Enter' key, '3' output to a file " << endl;
//   cin >> printOption;
//
//   while(choosingOption){
//     if(printOption == "1"){
//       choosingOption =  false;
//     }else if(printOption == "2" ){
//       choosingOption =  false;
//     }else if(printOption == "3"){
//       cout << "What is the file name for the results to be outputted to (include .txt extension) " << endl;
//       cin >> filename;
//       choosingOption =  false;
//     }else{
//       cout << "Invalid option! Try entering '1', '2'. or '3' " << endl;
//       cin >> printOption;
//       continue;
//     }
//   }
//
//   while(!choosingOption){
//     runGame();
//     break;
//   }
//
// }
//
// void Life::print(int rows, int columns, char**& board, int genCount, string print){
//   if(printOption == "1"){
//     sleep(2);
//     //cout << "print function" << endl;
//     cout << "Generation: " << genCount << endl;
//
//     for(int i = 0; i< rows; ++i){
//       for(int j = 0; j < columns; ++j){
//         cout << board[i][j];
//       }
//       cout << endl;
//     }
//
//   }else if(printOption == "2"){
//     string temp;
//     cout << "Press 'Enter' to continue printing: " << endl;
//     temp = cin.get();
//     //cout << "Generation: " << genCount << endl;
//     // for(int i = 0; i< rows; ++i){
//     //   for(int j = 0; j < columns; ++j){
//     //     cout << board[i][j];
//     //   }
//     //   cout << endl;
//     // }
//
//   }else if(printOption == "3"){
//     ofstream writeFile;
//     writeFile.open(filename, ios::in);
//     //writeFile << "Generation: " << genCount << endl;
//     for(int i = 0; i< rows; ++i){
//       for(int j = 0; j < columns; ++j){
//         writeFile << board[i][j];
//       }
//       writeFile << endl;
//     }
//     writeFile.close();
//   }else{
//     //nothign
//   }
//
// }
//
// void Life::randomWorld(int height, int width, double popDensity){
//   int totalCells = 0;
//   totalCells = height*width;
//   double population = 0.0;
//   population = ceil(popDensity*totalCells);
//   //cout << population << endl;
//
//   char** gridBoard = new char*[height];
//   for(int i = 0; i < height; ++i){
//     gridBoard[i] = new char[width];
//   }
//
//   for(int i = 0; i< height; ++i){
//     for(int j = 0; j < width; ++j){
//       gridBoard[i][j] = '-';
//     }
//   }
//
//   //generate random cells in world!!!
//   int randHeight = rand() % (height);
//   int randWidth = rand() % (width);
//   while(population > 0){
//     if(gridBoard[randHeight][randWidth] == '-'){
//       gridBoard[randHeight][randWidth] = 'X';
//       population--;
//       continue;
//     }else{
//       randHeight = rand() % (height);
//       randWidth = rand() % (width);
//     }
//   }
//
// //cout << "create random board() rows : " << height << endl;
//   chooseMode(height, width, gridBoard);
// }//end of randomWorld method
//
// void Life::fileWorld(string filename){
//   ifstream readFile;
//   readFile.open(filename, ios::in);
//   int lineNum = 0;
//   int row;
//   int column;
//   char ch;
//   char** gridBoard;
//
//   while(!readFile.eof()){
//     string str;
//     getline(readFile, str);
//     if(lineNum == 0){
//       stringstream heightDimen(str);
//       heightDimen >> row;
//       // cout << row << endl;
//     }else if (lineNum == 1){
//       stringstream widthDimen(str);
//       widthDimen >> column;
//       // cout << column << endl;
//     }else{
//       break;
//     }
//     lineNum++;
//   }
//
//   gridBoard = new char*[row];
//   for(int i = 0; i < row; ++i){
//     gridBoard[i] = new char[column];
//   }
//
//   //restart .eof() stream and read file starting from the top
//   readFile.clear();
//   readFile.seekg(0);
//   string currLine;
//   int currLineNum = 0;
//   int ignore = 0;
//   //cout << "before while loop" <<endl;
//   while(!readFile.eof()){
//     getline(readFile, currLine);
//     //cout << currLine << endl;
//     if(ignore == 0){
//       //cout << "ignoring line 1" << endl;
//     }else if (ignore == 1){
//       //cout << "ignoring line 2" << endl;
//     }else{
//       for(int i = 0; i < column; ++i){
//         if(currLineNum != row){
//           ch = currLine[i];
//           gridBoard[currLineNum][i] = ch;
//         }
//       }
//       //boundary check
//       currLineNum++;
//     }
//     ignore++;
//   }
//
//   // cout << "Generation: " << genCount << endl;
//   // for(int i = 0; i < row; ++i){
//   //   for(int j = 0; j < column; ++j){
//   //     cout << gridBoard[i][j];
//   //   }
//   //   cout << endl;
//   // }
//
//   chooseMode(row, column, gridBoard);
//
//
// }//end of fileWorld method
//
// void Life::classicMode(int row, int column, char**& currGen){
//   genCount = 0;
//   char **nextGen = new char*[row];
//   for(int i = 0; i < row; ++i){
//     nextGen[i] = new char[column];
//   }
//
//   bool runningSimulation = true;
//   while(runningSimulation){
//     for(int i =0; i < row; ++i){
//       for(int j = 0; j < column; ++j){
//         int cells = 0;
//         //cout << currGen[i][j] << "   " << i << "   " << j <<  "   " ;
//         if(i!= 0 && currGen[i-1][j] == 'X'){
//           ++cells;
//           //cout << "added 1  ";
//         }
//
//         if(i!=0 && j!=0 && currGen[i-1][j-1] == 'X'){
//           ++cells;
//           //cout << "added 2  ";
//         }
//
//         if(i!=0 && j!=(column-1) && currGen[i-1][j+1] == 'X'){
//           cells++;
//           //cout << "added 3  ";
//         }
//
//         if(j!=0 && currGen[i][j-1] == 'X'){
//           ++cells;
//         //cout << "added 4  ";
//         }
//
//         if( (j!=column-1) && currGen[i][j+1] == 'X'){
//           ++cells;
//           //cout << "added 5  ";
//         }
//
//         if( (i!= (row-1)) && j !=0 && currGen[i+1][j-1] == 'X'){
//           ++cells;
//           //cout << "added 6  ";
//         }
//
//         if( i!= row-1 && currGen[i+1][j] == 'X'){
//           ++cells;
//           //cout << "added 7  ";
//         }
//
//         if( i!= row-1 && j!= column && currGen[i+1][j+1] == 'X' ){
//           ++cells;
//           //cout << "added 8  ";
//         }
//         //cout << i << ", " << j << "  " << cells << endl;
//
//         if(cells <= 1){
//           nextGen[i][j] = '-';
//           //cout << nextGen[i][j];
//         }else if(cells == 2) {
//           nextGen[i][j] = currGen[i][j];
//           //cout << nextGen[i][j];
//         }else if(cells == 3){
//           nextGen[i][j] = 'X';
//           //cout << nextGen[i][j];
//         }else if(cells >= 4){
//           nextGen[i][j] = '-';
//           //cout << nextGen[i][j];
//         }
//         //cout << cells << endl;
//       }
//     }//end of first for loop
//
//
//     if(runningSimulation){
//
//       if(genCount == 0){
//         //cout << "in if statemnet " << endl;
//         cout << "Generation: " << genCount << endl;
//
//       //print array
//         for(int i = 0; i< row; ++i){
//           for(int j = 0; j < column; ++j){
//             // MAYBE THIS PRINT STATEMENT
//             cout << currGen[i][j];
//             }
//           cout << endl;
//         }
//
//         genCount++;
//
//         print(row, column, nextGen, genCount, printOption);
//         //set currGen = nextGen, so the next time it runs, it will update the nextGen
//         for(int i = 0; i< row; ++i){
//           for(int j = 0; j < column; ++j){
//             currGen[i][j] = nextGen[i][j];
//             }
//         }
//
//
//       } else{
//         //cout << "in else statemnet " << endl;
//         genCount++;
//
//         print(row, column, nextGen, genCount, printOption);
//         for(int i = 0; i< row; ++i){
//           for(int j = 0; j < column; ++j){
//             currGen[i][j] = nextGen[i][j];
//             }
//         }
//       }
//
//     }
//     // genCount++;
//
//   }// end of while loop
//
//
//
// }//end of classic mode
//
// void Life::doughnutMode(int row, int column, char** currGen){
//   //cout << "in doughnut mode " << endl;
//   char **nextGen = new char*[row];
//   for(int i = 0; i < row; ++i){
//     nextGen[i] = new char[column];
//   }
//
//   for(int m = 0; m < row; ++m){
//     for(int n =0; n < column; ++n){
//       nextGen[m][n] = '-';
//     }
//   }
//   bool runningSimulation = true;
//   while(runningSimulation){
//     for(int i = 0; i < row; ++i){
//       //cout << i << endl;
//       //cout << "first for loop " << endl;
//       for(int j = 0; j < column; ++j){
//         int cells = 0;
//         //cout << currGen[i][j];
//
//         if(i == 0 && j == 0){
//           //cout  << "top left corner" << endl;
//           if(currGen[i][j+1] == 'X')
//             cells++;
//           if(currGen[i+1][j+1] == 'X')
//             cells++;
//           if(currGen[i+1][j] == 'X')
//             cells++;
//           if(currGen[row-1][j] == 'X')
//             cells++;
//           if(currGen[row-1][j+1] == 'X')
//             cells++;
//           if(currGen[row-1][column-1] == 'X')
//             cells++;
//           if(currGen[i][column-1] == 'X')
//             cells++;
//           if(currGen[i+1][column-1] == 'X')
//             cells++;
//         } else if(i == 0 && j == (column-1)){
//         //  cout  << "top right corner" << endl;
//           if(currGen[i][j-1] == 'X')
//             cells++;
//           if(currGen[i+1][j-1] == 'X')
//             cells++;
//           if(currGen[i+1][j] == 'X')
//             cells++;
//           if(currGen[row-1][j] == 'X')
//             cells++;
//           if(currGen[row-1][j-1] == 'X')
//             cells++;
//           if(currGen[row-1][0] == 'X')
//             cells++;
//           if(currGen[i][0] == 'X')
//             cells++;
//           if(currGen[i+1][0] == 'X')
//             cells++;
//         }else if (i!= 0 && i!= (row-1)  && j!= (column-1) && j!=0){
//           //cout << "middle" << endl;
//           if(i!= 0 && currGen[i-1][j] == 'X')
//             ++cells;
//           if( i!=0 && j!=0 && currGen[i-1][j-1] == 'X')
//             ++cells;
//           if(i!=0 && j!= column && currGen[i-1][j+1] == 'X')
//             cells++;
//           if(j!=0 && currGen[i][j-1] == 'X')
//             ++cells;
//           if(j!=column && currGen[i][j+1] == 'X')
//             ++cells;
//           if( i!= row-1 && column != 0 && currGen[i+1][j-1] == 'X')
//             ++cells;
//           if( i!= row-1 && currGen[i+1][j] == 'X')
//             ++cells;
//           if( i!= row-1 && j!= column && currGen[i+1][j+1] == 'X' )
//             ++cells;
//         }else if(i == (row-1) && j ==0){
//         //  cout  << "bottom right corner" << endl;
//           if(currGen[i-1][j] == 'X')
//             cells++;
//           if(currGen[i][j+1] == 'X')
//             cells++;
//           if(currGen[i-1][j+1] == 'X')
//             cells++;
//           if(currGen[0][j] == 'X')
//             cells++;
//           if(currGen[0][j+1] == 'X')
//             cells++;
//           if(currGen[0][column-1] == 'X')
//             cells++;
//           if(currGen[i][column-1] == 'X')
//             cells++;
//           if(currGen[i-1][column-1] == 'X')
//             cells++;
//         }else if(i == (row-1) && j == (column-1)){
//         //  cout  << "bottom left corner" << endl;
//           if(currGen[i][j-1] == 'X')
//             cells++;
//           if(currGen[i-1][j] == 'X')
//             cells++;
//           if(currGen[i-1][j-1] == 'X')
//             cells++;
//           if(currGen[i][0] == 'X')
//             cells++;
//           if(currGen[i-1][0] == 'X')
//             cells++;
//           if(currGen[0][0] == 'X')
//             cells++;
//           if(currGen[0][j] == 'X')
//             cells++;
//           if(currGen[0][j-1] == 'X')
//             cells++;
//       // //  check last row
//       }else if(i == (row-1)){
//       //  cout << "last row" << endl;
//           if(currGen[i][j+1] == 'X')
//             cells++;
//           if(currGen[i][j-1] == 'X')
//             cells++;
//           if(currGen[i-1][j-1] == 'X')
//             cells++;
//           if(currGen[i-1][j] == 'X')
//             cells++;
//           if(currGen[i-1][j+1] == 'X')
//             cells++;
//           if(currGen[0][j] == 'X')
//             cells++;
//           if(currGen[0][j+1] == 'X')
//             cells++;
//           if(currGen[0][j-1] == 'X')
//             cells++;
//         }   else if(j == 0 ){
//           //cout << "column  is 0" << endl;
//           if(currGen[i+1][j] == 'X')
//             cells++;
//           if(currGen[i-1][j] == 'X')
//             cells++;
//           if(currGen[i][j+1] == 'X')
//             cells++;
//           if(currGen[i+1][j+1] == 'X')
//             cells++;
//           if(currGen[i-1][j+1] == 'X')
//             cells++;
//           if(currGen[i-1][column-1] == 'X')
//             cells++;
//           if(currGen[i+1][column-1] == 'X')
//             cells++;
//           if(currGen[i][column-1] == 'X')
//             cells++;
//         }else if(j == (column -1)){
//           //cout << "last column" << endl;
//           if(currGen[i][j-1] == 'X')
//             cells++;
//           if(currGen[i-1][j] == 'X')
//             cells++;
//           if(currGen[i-1][j-1] == 'X')
//             cells++;
//           if(currGen[i+1][j] == 'X')
//             cells++;
//           if(currGen[i+1][j-1] == 'X')
//             cells++;
//           if(currGen[i][0] == 'X')
//             cells++;
//           if(currGen[i-1][0] == 'X')
//             cells++;
//           if(currGen[i+1][0] == 'X')
//             cells++;
//         }else if(i = 0){
//           if(currGen[i+1][j] == 'X')
//             cells++;
//           if(currGen[i][j+1] == 'X')
//             cells++;
//           if(currGen[i+1][j+1] == 'X')
//             cells++;
//           if(currGen[i][j-1] == 'X')
//             cells++;
//           if(currGen[i+1][j-1] == 'X')
//             cells++;
//           if(currGen[row-1][j] == 'X')
//             cells++;
//           if(currGen[row-1][j-1] == 'X')
//             cells++;
//           if(currGen[row-1][j+1] == 'X')
//             cells++;
//         }else {
//           //cout << "not in if statements" << endl;
//         }
//       //  cout << cells;
//
//         //cout << "here" << endl;
//         if(cells <= 1){
//           nextGen[i][j] = '-';
//           //cout << nextGen[i][j];
//         }else if(cells == 2) {
//           nextGen[i][j] = currGen[i][j];
//           //cout << nextGen[i][j];
//         }else if(cells == 3){
//           nextGen[i][j] = 'X';
//           //cout << nextGen[i][j];
//         }else if(cells >= 4){
//           nextGen[i][j] = '-';
//           //cout << nextGen[i][j];
//         }
//       }//end of second for loop
//       //cout << endl;
//     }//end of first for loop
//
//     if(runningSimulation){
//       cout << "Generation: " << genCount << endl;
//       if(genCount == 0){
//         for(int i = 0; i< row; ++i){
//           for(int j = 0; j < column; ++j){
//             cout << currGen[i][j];
//             }
//           cout << endl;
//         }
//
//         print(row, column, currGen, genCount, printOption);
//
//         //set currGen = nextGen, so the next time it runs, it will update the nextGen
//         for(int i = 0; i< row; ++i){
//           for(int j = 0; j < column; ++j){
//             currGen[i][j] = nextGen[i][j];
//             }
//         }
//
//       } else{
//         for(int i = 0; i< row; ++i){
//           for(int j = 0; j < column; ++j){
//             currGen[i][j] = nextGen[i][j];
//             cout << currGen[i][j];
//             }
//           cout << endl;
//         }
//         print(row, column, currGen, genCount, printOption);
//       }
//
//     }
//
//     genCount++;
//
//   }
//
// }//end of doughnutMode()
//
// void Life::mirrorMode(int row, int column, char** currGen){
//   genCount = 0;
//   //cout << "in mirror mode " << endl;
//   char **nextGen = new char*[row];
//   for(int i = 0; i < row; ++i){
//     nextGen[i] = new char[column];
//   }
//
//   bool runningSimulation = true;
//   while(runningSimulation){
//   for(int i = 0; i < row; ++i){
//     for(int j = 0; j < column; ++j){
//       int cells = 0;
//       //top left corner
//       //cout << currGen[i][j] << "  ";
//       if(i == 0 && j ==0){
//         //cout << "top left corner " << endl;
//         if(currGen[i][j] == 'X')
//           cells+=3;
//         if(currGen[i][j+1] == 'X')
//           cells+=2;
//         if(currGen[i+1][j] == 'X')
//           cells+=2;
//         if(currGen[i+1][j+1] == 'X')
//           cells++;
//         //top right corner
//       }else if(i == 0 && j  == (column-1)){
//         //cout << "top right corner " << endl;
//
//         if(currGen[i][j] == 'X')
//           cells+=3;
//         if(currGen[i+1][j] == 'X')
//           cells+=2;
//         if(currGen[i][j-1] == 'X')
//           cells+=2;
//         if(currGen[i+1][j-1] == 'X')
//           cells++;
//         //bottom left corner
//       }else if(i == (row-1) && j == 0){
//         //cout << "bottom left corner " << endl;
//
//         if(currGen[i][j] == 'X')
//           cells+=3;
//         if(currGen[i-1][j] == 'X')
//           cells+=2;
//         if(currGen[i][j+1] == 'X')
//           cells+=2;
//         if(currGen[i-1][j+1] == 'X')
//           cells++;
//         //bottom right corner
//       }else if(i == (row-1) && j == (column-1)){
//         //cout << "bottom right corner " << endl;
//         if(currGen[i][j] == 'X')
//           cells+=3;
//         if(currGen[i-1][j] == 'X')
//           cells+=2;
//         if(currGen[i][j-1] == 'X')
//           cells+=2;
//         if(currGen[i-1][j-1] == 'X')
//           cells++;
//       }else if (i!= 0 && i!= (row-1)  && j!= (column-1) && j!=0){
//         //cout << "middle" << endl;
//         if(i!= 0 && currGen[i-1][j] == 'X')
//           cells++;
//         if( i!=0 && j!=0 && currGen[i-1][j-1] == 'X')
//           ++cells;
//         if(i!=0 && j!= column && currGen[i-1][j+1] == 'X')
//           cells++;
//         if(j!=0 && currGen[i][j-1] == 'X')
//           cells++;
//         if(j!=column && currGen[i][j+1] == 'X')
//           cells++;
//         if( i!= row-1 && column != 0 && currGen[i+1][j-1] == 'X')
//           cells++;
//         if( i!= row-1 && currGen[i+1][j] == 'X')
//           cells++;
//         if( i!= row-1 && j!= column && currGen[i+1][j+1] == 'X' )
//           cells++;
//       }else if(i == 0){
//         //cout << "top row " << endl;
//         if(currGen[i][j] == 'X')
//           cells+=2;
//         if(currGen[i][j-1] == 'X')
//           cells+=2;
//         if(currGen[i][j+1] == 'X')
//           cells+=2;
//         if(currGen[i+1][j] == 'X')
//           cells++;
//         if(currGen[i+1][j-1] == 'X')
//           cells++;
//         if(currGen[i+1][j+1] == 'X')
//           cells++;
//       } else if(j == 0){
//         //cout << "first column " << endl;
//         if(currGen[i][j] == 'X')
//           cells+=2;
//         if(currGen[i-1][j] == 'X')
//           cells+=2;
//         if(currGen[i+1][j] == 'X')
//           cells+=2;
//         if(currGen[i][j+1] == 'X')
//           cells++;
//         if(currGen[i-1][j+1] == 'X')
//           cells++;
//         if(currGen[i+1][j+1] == 'X')
//           cells++;
//       }else if(i == (row-1)){
//         //cout << "last row " << endl;
//         if(currGen[i][j] == 'X')
//           cells+=2;
//         if(currGen[i][j+1] == 'X')
//           cells+=2;
//         if(currGen[i][j-1] == 'X')
//           cells+=2;
//         if(currGen[i-1][j] == 'X')
//           cells++;
//         if(currGen[i-1][j+1] == 'X')
//           cells++;
//         if(currGen[i-1][j-1] == 'X')
//           cells++;
//       }else if(j == (column-1)){
//         //cout << "last column " << endl;
//         if(currGen[i][j] == 'X')
//           cells+=2;
//         if(currGen[i+1][j] == 'X')
//           cells+=2;
//         if(currGen[i-1][j] == 'X')
//           cells+=2;
//         if(currGen[i][j-1] == 'X')
//           cells++;
//         if(currGen[i+1][j-1] == 'X')
//           cells++;
//         if(currGen[i-1][j-1] == 'X')
//           cells++;
//       }
//       else{
//         cout << "not in if statements" << endl;
//       }
//
//       if(cells <= 1){
//         nextGen[i][j] = '-';
//         //cout << nextGen[i][j];
//       }else if(cells == 2) {
//         nextGen[i][j] = currGen[i][j];
//         //cout << nextGen[i][j];
//       }else if(cells == 3){
//         nextGen[i][j] = 'X';
//         //cout << nextGen[i][j];
//       }else if(cells >= 4){
//         nextGen[i][j] = '-';
//         //cout << nextGen[i][j];
//       }
//       //cout << cells;
//     }//second for loop
//     //cout << endl;
//   }//first for loop
//
//   if(runningSimulation){
//     cout << "Generation: " << genCount << endl;
//     if(genCount == 0){
//       for(int i = 0; i< row; ++i){
//         for(int j = 0; j < column; ++j){
//           cout << currGen[i][j];
//           }
//         cout << endl;
//       }
//
//       print(row, column, currGen, genCount, printOption);
//
//       //set currGen = nextGen, so the next time it runs, it will update the nextGen
//       for(int i = 0; i< row; ++i){
//         for(int j = 0; j < column; ++j){
//           currGen[i][j] = nextGen[i][j];
//           }
//       }
//
//     } else{
//       for(int i = 0; i< row; ++i){
//         for(int j = 0; j < column; ++j){
//           currGen[i][j] = nextGen[i][j];
//           cout << currGen[i][j];
//           }
//         cout << endl;
//       }
//       print(row, column, currGen, genCount, printOption);
//     }
//
//   }
//
//   genCount++;
//
// }
//
//
// }//end of mirrorMode()
