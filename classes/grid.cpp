#include <iostream>
#include <string>
// #include <ncurses>

#include "grid.h"

using namespace std;

// Grid::Grid(int rows, int cols) {
//     i_rows == rows;
//     i_cols == cols;
Grid::Grid() {
    // Populate grid with consecutive numbers
    for (unsigned r=0; r<i_rows; r++) {
        for (unsigned c=0; c<i_cols; c++) {
            grid[r][c] = c + (r * i_rows);
            // cout << c + (r * 4) << endl; 
        }
    }

    Randomise();
}

void Grid::Loop() {
    while (true) {
        system("clear");
        
        cout << endl;

        DrawGrid();
        
        if (debug) {
            cout << "Debug mode active" << endl;
            Debug();
        } else {
            cout << "Debug mode NOT active" << endl;
        }

        if (IsFinished() == false) {
                
            system("stty -echo"); // supress echo
            system("stty cbreak"); // go to RAW mode

            char ch = getchar();
            // cout << ch << endl;

            system ("stty echo"); // Make echo work
            system("stty -cbreak");// go to COOKED mode

            if (ch == 'w') {
                // SwapUp(); // Reversed
                SwapDown();
            } else if (ch == 'a') {
                // SwapLeft(); // Reversed
                SwapRight();
            } else if (ch == 's') {
                // SwapDown(); // Reversed
                SwapUp();
            } else if (ch == 'd') {
                // SwapRight(); // Reversed
                SwapLeft();
            } else if (ch == 'q') {
                exit(0);
            } else if (ch == '`') {
                cout << "Debug mode active" << endl;
                debug == true;
            }
        } else { // Game is completed      
            cout << "You won the game! Press any key to exit" << endl;
            cin.ignore();

            exit(0);
        }
        cout << endl;
    }
}

void Grid::SwapUp() {
    if (zero_row != 0) {
        int temp = grid[zero_row - 1][zero_col]; // 3-way swap
        grid[zero_row - 1][zero_col] = grid[zero_row][zero_col];
        grid[zero_row][zero_col] = temp;

        zero_row -= 1;
    }
}

void Grid::SwapDown() {
    if (zero_row != i_rows - 1) {
        int temp = grid[zero_row + 1][zero_col]; // 3-way swap
        grid[zero_row + 1][zero_col] = grid[zero_row][zero_col];
        grid[zero_row][zero_col] = temp;

        zero_row += 1;
    }
}

void Grid::SwapLeft() {
    if (zero_col != 0) {
        int temp = grid[zero_row][zero_col - 1]; // 3-way swap
        grid[zero_row][zero_col - 1] = grid[zero_row][zero_col];
        grid[zero_row][zero_col] = temp;

        zero_col -= 1;
    }
}

void Grid::SwapRight() {
    if (zero_col != i_cols - 1) {
        int temp = grid[zero_row][zero_col + 1]; // 3-way swap
        grid[zero_row][zero_col + 1] = grid[zero_row][zero_col];
        grid[zero_row][zero_col] = temp;

        zero_col += 1;
    }
}

bool Grid::IsFinished() {
    // cout << endl;
    for (unsigned r=0; r<i_rows; r++) {
        for (unsigned c=0; c<i_cols; c++) {
            // cout << "CURRENTLY CHECKING GRID[" << r << "][" << c << "]" << endl;
            if (r != i_rows - 1 || c != i_cols - 1) { // Check all positions except zero
                // int expected = 1 + c + (r * i_rows);
                if (grid[r][c] != 1 + c + (r * i_rows)) {
                    // cout << "\t FALSE" << endl;
                    return false;
                }
            } // No point in checking zero, since if we reach here zero must be correct
        }
    }
    // cout << endl;
    return true;
}

void Grid::Randomise() {
    // For each position, generate random position and swap them
    srand(time(NULL));
    for (unsigned r=0; r<i_rows; r++) {
        for (unsigned c=0; c<i_cols; c++) {
            int rand_r = rand() % i_rows;
            int rand_c = rand() % i_cols;
            int rand_value = grid[rand_r][rand_c]; // 3-way swap
            grid[rand_r][rand_c] = grid[r][c];
            grid[r][c] = rand_value;
            // cout<<"Swapped ["<<r<<"]["<<c<<"] with ["<<rand_r<<"]["<<rand_c<<"]"<<endl;
        }
    }
}

void Grid::Debug() {
    cout << "\nRows = " << i_rows << endl;
    cout << "Cols = " << i_cols << endl;
    cout << "Grid = \t";
    for (unsigned r=0; r<i_rows; r++) {
        cout << "[";
        for (unsigned c=0; c<(i_cols - 1); c++) {
            cout << grid[r][c] << ", ";
        }
        cout << grid[r][i_cols - 1] << "]\n\t";
    }
    cout << endl;
}

void Grid::DrawLine(int iter, string s_start, string s_mid, string s_end, string s_line) {    
    cout << "\t" << s_start;
    for (unsigned i=0; i<iter; i++) {
        for (unsigned x=0; x<6; x++) {cout << s_line;}
        cout << s_mid;
    }
    for (unsigned x=0; x<6; x++) {cout << s_line;}
    cout << s_end << endl;
}

void Grid::DrawGrid() {
    // Somehow find width of terminal, draw grid at the centre???

    DrawLine(i_cols - 1, "┏", "┳", "┓", "━"); // Starting line

    for (unsigned r=0; r<i_rows; r++) {
        DrawLine(i_cols - 1, "┃", "┃", "┃", " "); // Broken line
        // Numbers line
        cout << "\t" << "┃" << "  ";
        for (unsigned c=0; c<i_cols; c++) {
            int num = grid[r][c];
            if (num == 0) {
                zero_row = r; // Save the grid position of the blank space
                zero_col = c; // Save the grid position of the blank space
                cout << "  ";
            } else if (num != 0 & num < 10) {// Add a space to single digits 
                cout << num << " ";
            } else {
                cout << num;
            }
            cout << "  " << "┃" << "  ";
        }
        cout << endl;
        DrawLine(i_cols - 1, "┃", "┃", "┃", " "); // Broken line
        if (r != i_rows - 1) { // Ignore on the final loop
            DrawLine(i_cols - 1, "┣", "╋", "┫", "━"); // Middle line
        }
    }
    DrawLine(i_cols - 1, "┗", "┻", "┛", "━"); // Ending line
}