// ProgrammingAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.



//*********************************************************************************************************************************************
//
//		Program:- ProgrammingAssignment.cpp
//
//		Purpose:- First year assignment. To create a word search, searching vertically, horizontally and orthoganaly, finds preset words.
//
//		Author:- Tom Booth
//
//		Date:- Rework 22/09/2020
//
//*********************************************************************************************************************************************

//*********************************************************************************************************************************************
//
//		Include Files
//
//*********************************************************************************************************************************************
#include <fstream> //This imports the library support for opening and reading files.
#include <iostream> // This allows me to input and output to the console. cout ect.
#include <string> // This allows me to create strings.  Ie String Name.
#include <stdlib.h> //This allows me to use the exit(1) command to close the program from the menu

//*********************************************************************************************************************************************
//
//		Constants
//
//*********************************************************************************************************************************************
const int GRID_2D_HEIGHT = 4L; // Defines the Max Height of the 2D Grid
const int GRID_2D_WIDTH = 14L; // Defines the Max Width of the 2D Grid
char Grid2D[GRID_2D_HEIGHT][GRID_2D_WIDTH]; // Declares a 2D array with the parameters GRID_2D_HEIGHT and GRID_2D_WIDTH.

const int GRID_2D_FOUND_HEIGHT = 4L; // Defines the Max Height of the 2D Grid for Found Words
const int GRID_2D_FOUND_WIDTH = 14L; // Sets a constant value of 14
char Grid_2D_Found[GRID_2D_FOUND_HEIGHT][GRID_2D_FOUND_WIDTH];  // Declares a 2D array with the parameters Grid_2D_FoundHEIGHT and Grid_2D_FoundWIDTH.

const int TERMS_2D_HEIGHT = 17L; // Sets a constant value of 17
const int TERMS_2D_WIDTH = 3L; // Sets a constant value of 3
char SearchTerms2D[TERMS_2D_HEIGHT][TERMS_2D_WIDTH]; // Declares a 2D array with the parameters TERMS_2D_HEIGHT and TERMS_2D_WIDTH.

const int GRID_1D_WIDTH = 14L; // Sets a constant value of 14
char Grid1D[GRID_1D_WIDTH]; // Declares a 1D with the constant GRID_1D_WIDTH

const int GRID_1D_FOUND_WIDTH = 14L; //Sets a constant value of 14
char Grid1DFound[GRID_1D_FOUND_WIDTH]; //Declares an array with the constant GRID_1D_FOUND_WIDTH

const int TERMS1DWIDTH = 6L; // Sets a constant value of 6
const int TERMS1DHEIGHT = 3L; // Sets a constant value 3
char SearchTerms1D[TERMS1DHEIGHT][TERMS1DWIDTH]; // Declares a 2D array with the parameters TERMS1DHEIGHT and TERMS1DWIDTH.

const int FOUND_WORDS_HEIGHT = 16L; // Sets a constant value of 16
const int FOUND_WORDS_WIDTH = 3L; // Sets a constant value of 3
int Height = 0L; //Declares a variable and sets it to the value 0
char FoundWords[FOUND_WORDS_HEIGHT][FOUND_WORDS_WIDTH]; //Declares an array with the parameters FOUND_WORDS_HEIGHT and FOUND_WORDS_WIDTH.

const int FOUND_WORDS_1D_HEIGHT = 6L; // Sets a constant value of 6
const int FOUND_WORDS_1D_WIDTH = 3L; // Sets a constant value of 3
int Height1D = 0L; //Declares a variable and sets it to the value 0
char FoundWords1D[FOUND_WORDS_1D_HEIGHT][FOUND_WORDS_1D_WIDTH]; //Declares an array with the parameters FOUND_WORDS_HEIGHT and FOUND_WORDS_WIDTH.


const int Upper_Bound_2D = 16L;
const int Upper_Bound_1D = 6L;
const int Lower_Bound = 2L;
int Positions[Upper_Bound_2D][Lower_Bound];
int Positions1D[Upper_Bound_1D][Lower_Bound];

int x = 0;
int y = 0;
char ch; // Declares a char ch

using namespace std; // Defines scope

//*************************************************************************************************************************************************
//
//	Function Prototypes:-
//
//		1,static void OutputFoundFile()			;
//		2,static void OutputFoundFileFor1D()	;
//		3,void SingleSearch()					;
//		4,void SingleArray()					;
//		5,void MultiArray()						;
//		6,void PopulateSearchTerms2D()			;
//
//		7,void Search2DFragment(int x1, int y1,
//							    int x2, int y2,
//							    int x3, int y3) ;
//
//		8,void Search1DFragment(int x1, int x2, int x3);
//		9,void CreateFoundWordFile();
//		10,void CreateFoundWordFile1D();
//
//***************************************************************************************************************************************************


void OutputFoundFile();

void OutputFoundFileFor1D();

void SingleSearch();

void SingleArray();

void MultiArray();

void PopulateSearchTerms2D();

void CreateFoundWordFile();

void CreateFoundWordFile1D();

void Search2DFragment(
        int x_position1, int y_position1,
        int x_position2, int y_position2,
        int x_position3, int y_position3);

void Search1DFragment(int x_position1, int x_position2, int x_position3);

//****************************************************************************************************************************************************
//
//	Name:- Menu
//
//	Purpose:- Create a simple user interface to choose between searching the 2D/1D array Word search
//
//****************************************************************************************************************************************************


void Menu() // Declares a function
{
    char selection;
    //Ask user for input
    cout << "--------------------Menu:---------------------" << endl << endl;
    cout << "Choose which search. " << endl;
    cout << "1. Single Line " << endl;
    cout << "2. Multiple Line " << endl;
    cout << "3. Exit " << endl;

    cin >> selection; // Takes the user choice as an input.

    switch (selection) // Declares a switch statement
    {
        case '1': {
            cout << "1 Chosen \n" << endl;
        }
            SingleSearch();
            CreateFoundWordFile1D();
            SingleArray();
            OutputFoundFileFor1D();
            break; //Breaks out of the case

        case '2': {
            cout << "2 Chosen \n" << endl;
        }
            PopulateSearchTerms2D();
            CreateFoundWordFile();
            MultiArray();
            OutputFoundFile();
            break;


        case '3': {
            exit(1);
        }
        default:
            exit(1);
    }
}

//****************************************************************************************************************************************************
//
//	Name:- PopulateSearchTerms2D
//
//	Purpose:- Reads in from the text file to create an array, used then to compare with the word search
//
//****************************************************************************************************************************************************

void PopulateSearchTerms2D() {
    ifstream infile("search2d.txt");
    if (!infile) {
        cout << "ERROR: ";
        cout << "Cannot open input file \n";
    }


    while (infile >> ch) {
        if (ch != '\n') {
            SearchTerms2D[y][x] = ch;
            x++;
            if (infile.peek() == '\n') {
                x = 0;
                y++;
            }
        }
    }

    cout << endl << endl;

    cout << "--------------------Words To Search For:-------------------- " << endl << endl;
    for (y = 0; y != 16; y++) {
        for (x = 0; x != 3; x++) {
            cout << SearchTerms2D[y][x];

            cout << endl;
        }
        cout << "\n";
    }
}

//****************************************************************************************************************************************************
//
//	Name:- MultiArray
//
//	Purpose:- Opens the word search file for searching and comparing
//
//****************************************************************************************************************************************************

void MultiArray() {
    ifstream infile("text2D.txt");
    if (!infile) {
        cout << "ERROR: ";
        cout << "Cannot open input file \n";
    }

    x = 0;
    y = 0;
    while (infile >> ch) {
        if (ch != '\n') {
            Grid2D[y][x] = ch;
            x++;
            if (infile.peek() == '\n') {
                x = 0;
                y++;
            }
        }
    }

    cout << "--------------------Word Search Grid:-------------------- " << endl << endl;
    for (y = 0; y != 4; y++) {
        for (x = 0; x != 14; x++) {
            cout << Grid2D[y][x];
        }
        cout << endl;
    }

    cout << "\n";
    cout << "--------------------Found Words:-------------------- " << endl << endl;

    int x_position1 = 0;
    int x_position2 = 1;
    int x_position3 = 2;
    int y_position1 = 0;
    int y_position2 = 0;
    int y_position3 = 0;

    //Horizontal Search.
    for (y = 0; y <= 4; y++) {
        if (y_position1 >= 4) {
            break;
        } else {
            x_position1 = 0;
            x_position2 = 1;
            x_position3 = 2;
            for (x = 0; x <= 14; x++) {
                if (x_position3 >= 14) {
                    break;
                } else {
                    Search2DFragment(x_position1, y_position1,
                                     x_position2, y_position2,
                                     x_position3, y_position3);
                    x_position1++, x_position2++, x_position3++;
                }
            }
            y_position1++, y_position2++, y_position3++;
        }
    }

    // Backwards Horizontal Search
    y_position1 = 0;
    y_position2 = 0;
    y_position3 = 0;

    for (y = 0; y <= 4; y++) {
        if (y_position1 >= 4) {
            break;
        } else {
            x_position1 = 14;
            x_position2 = 13;
            x_position3 = 12;
            for (x = 14; x >= 0; x--) {
                if (x_position1 <= 0) {
                    break;
                } else {
                    Search2DFragment(x_position1, y_position1,
                                     x_position2, y_position2,
                                     x_position3, y_position3);
                    x_position1--, x_position2--, x_position3--;
                }
            }
            y_position1++, y_position2++, y_position3++;
        }
    }

    // Vertical Search Descending
    y_position1 = 0;
    y_position2 = 1;
    y_position3 = 2;

    for (y = 0; y <= 4; y++) {
        if (y_position1 >= 4) {
            break;
        } else {
            x_position1 = 0;
            x_position2 = 0;
            x_position3 = 0;
            for (x = 14; x >= 0; x++) {
                if (x_position1 >= 14) {
                    break;
                } else {
                    Search2DFragment(x_position1, y_position1,
                                     x_position2, y_position2,
                                     x_position3, y_position3);
                    x_position1++, x_position2++, x_position3++;
                }
            }
            y_position1++, y_position2++, y_position3++;
        }
    }

    // Vertical Search Ascending
    y_position1 = 2;
    y_position2 = 3;
    y_position3 = 4;

    for (y = 4; y >= 0; y--) {
        if (y_position1 <= 0) {
            break;
        } else {
            x_position1 = 0;
            x_position2 = 0;
            x_position3 = 0;
            for (x = 14; x >= 0; x++) {
                if (x_position1 >= 14) {
                    break;
                } else {
                    Search2DFragment(x_position3, y_position3,
                                     x_position2, y_position2,
                                     x_position1, y_position1);
                    x_position1++, x_position2++, x_position3++;
                }
            }

            y_position1--, y_position2--, y_position3--;
        }
    }

    // Diagonal Search #1
    y_position1 = 4;
    y_position2 = 3;
    y_position3 = 2;

    for (y = 4; y >= 0; y--) {
        if (y_position1 <= 0) {
            break;
        } else {
            x_position1 = 0;
            x_position2 = 1;
            x_position3 = 2;
            for (x = 14; x >= 0; x++) {
                if (x_position1 >= 14) {
                    break;
                } else {
                    Search2DFragment(x_position3, y_position3,
                                     x_position2, y_position2,
                                     x_position1, y_position1);
                    x_position1++, x_position2++, x_position3++;
                }
            }
            y_position1--, y_position2--, y_position3--;
        }
    }

    //Diagonal Search #2
    y_position1 = 4;
    y_position2 = 3;
    y_position3 = 2;

    for (y = 4; y >= 0; y--) {
        if (y_position1 <= 0) {

            break;
        } else {
            x_position1 = 14;
            x_position2 = 13;
            x_position3 = 12;
            for (x = 0; x <= 14; x--) {
                if (x_position1 <= 0) {
                    break;
                } else {
                    Search2DFragment(x_position3, y_position3,
                                     x_position2, y_position2,
                                     x_position1, y_position1);
                    x_position1--, x_position2--, x_position3--;
                }
            }
            y_position1--, y_position2--, y_position3--;
        }
    }

    // Orthogonal Search #1

    y_position1 = 0;
    y_position2 = 1;
    y_position3 = 1;

    for (y = 0; y <= 4; y++) {
        if (y_position1 >= 4) {
            break;
        } else {
            x_position1 = 0;
            x_position2 = 0;
            x_position3 = 1;
            for (x = 0; x <= 14; x++) {
                if (x_position1 >= 14) {
                    break;
                } else {
                    Search2DFragment(x_position1, y_position1,
                                     x_position2, y_position2,
                                     x_position3, y_position3);
                    x_position1++, x_position2++, x_position3++;
                }
            }
            y_position1++, y_position2++, y_position3++;
        }
    }

    // Orthogonal Search #2
    y_position1 = 0;
    y_position2 = 1;
    y_position3 = 1;


    for (y = 0; y <= 4; y++) {
        if (y_position1 >= 4) {
            break;
        } else {
            x_position1 = 14;
            x_position2 = 14;
            x_position3 = 13;
            for (x = 14; x >= 0; x--) {
                if (x_position1 <= 0) {
                    break;
                } else {
                    Search2DFragment(x_position1, y_position1,
                                     x_position2, y_position2,
                                     x_position3, y_position3);
                    x_position1--, x_position2--, x_position3--;
                }
            }
            y_position1++, y_position2++, y_position3++;
        }
    }

    // Orthogonal Search #3
    y_position1 = 0;
    y_position2 = 0;
    y_position3 = 1;

    for (y = 0; y <= 4; y++) {
        if (y_position1 >= 4) {
            break;
        } else {
            x_position1 = 14;
            x_position2 = 13;
            x_position3 = 13;
            for (x = 14; x >= 0; x++) {
                if (x_position1 <= 0) {

                    break;
                } else {
                    Search2DFragment(x_position1, y_position1,
                                     x_position2, y_position2,
                                     x_position3, y_position3);
                    x_position1--, x_position2--, x_position3--;
                }
            }
            y_position1++, y_position2++, y_position3++;
        }
    }

    // Orthogonal Search #4

    y_position1 = 0;
    y_position2 = 0;
    y_position3 = 1;

    for (y = 0; y <= 4; y++) {
        if (y_position1 >= 4) {
            break;
        } else {
            x_position1 = 13;
            x_position2 = 14;
            x_position3 = 14;
            for (x = 14; x >= 0; x++) {
                if (x_position1 >= 14) {
                    break;
                } else {

                    Search2DFragment(x_position1, y_position1,
                                     x_position2, y_position2,
                                     x_position3, y_position3);
                    x_position1++, x_position2++, x_position3++;
                }
            }
            y_position1++, y_position2++, y_position3++;
        }
    }
    infile.close();
}

//****************************************************************************************************************************************************
//
//	Name:- Search2DFragment
//
//	Purpose:- Goes through the two documents and compares the two populated arrays X_position/y_position.
//
//****************************************************************************************************************************************************

void Search2DFragment(int x_position1, int y_position1, int x_position2, int y_position2, int x_position3,
                      int y_position3)  //Declares a function with the required parameters
{
    char char1, char2, char3, Replace;
    char1 = Grid2D[y_position1][x_position1];
    char2 = Grid2D[y_position2][x_position2];
    char3 = Grid2D[y_position3][x_position3];
    Replace = '.';
    int x_positionPos = x_position1;
    int y_positionPos = y_position1;

    string searchterm = "";
    searchterm += SearchTerms2D[0][0];
    searchterm += SearchTerms2D[0][1];
    searchterm += SearchTerms2D[0][2];

    string compstring;
    compstring.push_back(char1);
    compstring.push_back(char2);
    compstring.push_back(char3);

    for (int i = 0; i < 17; i++) {
        searchterm = "";
        searchterm += SearchTerms2D[i][0];
        searchterm += SearchTerms2D[i][1];
        searchterm += SearchTerms2D[i][2];

        if (searchterm == compstring) {
            cout << compstring
                 << " is in search terms! Found in position "
                 << "Line: "
                 << y_positionPos
                 << " Location: "
                 << x_positionPos
                 << endl;
            Positions[Height][0] = y_positionPos;
            Positions[Height][1] = x_positionPos;

            FoundWords[Height][0] = char1;
            FoundWords[Height][1] = char2;
            FoundWords[Height][2] = char3;
            Height++;

            Grid_2D_Found[y_position1][x_position1] = Replace;
            Grid_2D_Found[y_position2][x_position2] = Replace;
            Grid_2D_Found[y_position3][x_position3] = Replace;
        }
    }
}

void CreateFoundWordFile() {
    ifstream infile("text2D.txt");
    if (!infile) {
        cout << "ERROR: ";
        cout << "Cannot open input file \n";
    }

    x = 0;
    y = 0;
    ch;
    while (infile >> ch) {
        if (ch != '\n') {
            Grid_2D_Found[y][x] = ch;
            x++;
            if (infile.peek() == '\n') {
                x = 0;
                y++;
            }
        }
    }
    infile.close();
}

void OutputFoundFile() {
    ofstream outfile("LeftCharecters2D.txt");
    outfile << "--------------------Words To Search For:-------------------- " << endl << endl;
    for (y = 0; y != 16; y++) {
        for (x = 0; x != 3; x++) {
            outfile << SearchTerms2D[y][x];
        }
        outfile << endl;
    }
    outfile << "\n";

    outfile << "--------------------Word Search Grid:-------------------- " << endl << endl;

    for (y = 0; y != 4; y++) {
        for (x = 0; x != 14; x++) {
            outfile << Grid2D[y][x];
        }
        outfile << endl;
    }
    outfile << "\n";
    outfile << endl;
    cout << endl;
    outfile << "--------------------Found Words:-------------------- " << endl << endl;

    for (y = 0; y < 16; y++) {
        outfile << FoundWords[y][0]
                << FoundWords[y][1]
                << FoundWords[y][2]
                << "Line:	   "
                << Positions[y][0]
                << " Location: "
                << Positions[y][1] << endl;
    }
    cout << "--------------------Charecters Left In The Grid:-------------------- " << endl << endl;
    outfile << "--------------------Charecters Left In The Grid:-------------------- " << endl << endl;
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 14; x++) {
            cout << Grid_2D_Found[y][x];
            outfile << Grid_2D_Found[y][x];
        }
        cout << endl;
        outfile << endl;
    }
    cout << endl;
    outfile << endl;

    outfile.close();
}

void SingleSearch() {
    ifstream infile("search1.txt");
    if (!infile) {
        cout << "ERROR: ";
        cout << "Cannot open input file \n";
    }

    x = 0;
    y = 0;
    ch;
    while (infile >> ch) {
        if (ch != '\n') {
            SearchTerms1D[y][x] = ch;
            x++;
            if (infile.peek() == '\n') {
                x = 0;
                y++;
            }
        }
    }
    cout << endl << endl;
    cout << "--------------------Search Terms:-------------------- " << endl << endl;

    for (y = 0; y != 6; y++) {
        for (x = 0; x != 3; x++) {
            cout << SearchTerms1D[y][x];
        }
        cout << endl;
    }
    infile.close();
}

void SingleArray() {
    ifstream infile("text1.txt");
    if (!infile) {
        cout << "ERROR: ";
        cout << "Cannot open input file \n";
    }
    x = 0;
    ch;
    while (infile >> ch) {
        if (ch != '\n') {
            Grid1D[x] = ch;
            x++;
            if (infile.peek() == '\n') {
                x = 0;
            }
        }
    }
    cout << endl << endl;
    cout << "--------------------WordSearch:-------------------- " << endl << endl;
    for (x = 0; x != 14; x++) {
        cout << Grid1D[x];

    }
    cout << "\n" << endl;
    cout << "--------------------Found Words:-------------------- " << endl << endl;


    int x_position1 = 0;
    int x_position2 = 1;
    int x_position3 = 2;

    //Horizontal Search.
    for (x = 0; x <= 14; x++) {
        if (x_position3 >= 14) {
            break;
        } else {
            Search1DFragment(x_position1, x_position2, x_position3);
            x_position1++, x_position2++, x_position3++;
        }
    }
    cout << endl;

    infile.close();
}

void Search1DFragment(int x_position1, int x_position2, int x_position3) {
    char char1, char2, char3, Replace;
    char1 = Grid1D[x_position1];
    char2 = Grid1D[x_position2];
    char3 = Grid1D[x_position3];
    Replace = '.';
    int x_positionPos = x_position1;
    string searchterm = "";
    searchterm += SearchTerms1D[0];
    searchterm += SearchTerms1D[1];
    searchterm += SearchTerms1D[2];
    string compstring;
    compstring.push_back(char1);
    compstring.push_back(char2);
    compstring.push_back(char3);

    for (int i = 0; i < 6; i++) {
        searchterm = "";
        searchterm += SearchTerms1D[i][0];
        searchterm += SearchTerms1D[i][1];
        searchterm += SearchTerms1D[i][2];
        if (searchterm == compstring) {
            cout << compstring
                 << " is in search terms! Found in position "
                 << " Location: "
                 << x_positionPos
                 << endl;
            Positions1D[Height1D][1] = x_positionPos;

            FoundWords1D[Height1D][0] = char1;
            FoundWords1D[Height1D][1] = char2;
            FoundWords1D[Height1D][2] = char3;
            Height1D++;

            Grid1DFound[x_position1] = Replace;
            Grid1DFound[x_position2] = Replace;
            Grid1DFound[x_position3] = Replace;
        }
    }
}

void CreateFoundWordFile1D() {
    ifstream infile("text1.txt");
    if (!infile) {
        cout << "ERROR: ";
        cout << "Cannot open input file \n";
    }

    x = 0;
    ch;
    while (infile >> ch) {
        if (ch != '\n') {
            Grid1DFound[x] = ch;
            x++;
        }
    }
    infile.close();
}

void OutputFoundFileFor1D() {
    ofstream outfile("LeftCharecters1D.txt");
    outfile << "--------------------Words To Search For:-------------------- " << endl << endl;
    for (y = 0; y != 6; y++) {
        for (x = 0; x != 3; x++) {
            outfile << SearchTerms1D[y][x];
        }
        outfile << endl;
    }
    outfile << "\n";
    cout << "\n";
    outfile << "--------------------Word Search Grid:-------------------- " << endl << endl;

    for (x = 0; x != 14; x++) {
        outfile << Grid1D[x];
    }
    outfile << endl;

    outfile << "\n";
    outfile << endl;
    outfile << "--------------------Found Words:-------------------- " << endl << endl;

    for (y = 0; y < 3; y++) {
        outfile << FoundWords1D[y][0]
                << FoundWords1D[y][1]
                << FoundWords1D[y][2]
                << " Location: " << Positions1D[y][1]
                << endl;
    }

    outfile << "--------------------Charecters Left In The Grid:-------------------- " << endl << endl;
    cout << "--------------------Charecters Left In The Grid:-------------------- " << endl << endl;

    for (x = 0; x < 14; x++) {
        cout << Grid1DFound[x];
        outfile << Grid1DFound[x];
    }
    cout << endl;
    outfile << endl;

    cout << endl;
    outfile << endl;

    outfile.close();
}

int main() {
    Menu();
    system("pause");
}
