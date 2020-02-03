#include <cstdlib>
#include <iostream>
// #include <string>
#include <vector>

#include "grid.h"

using namespace std;

Grid::Grid(int r, int c, bool d)
    : i_rows(r), i_cols(c), debug(debug)
{
    // Resize 2D vector
    grid.resize(i_rows);
    for (auto &i : grid) {
        i.resize(i_cols);
    }

    // Populate grid with consecutive numbers
    for (auto r=0; r<i_rows; r++) {
        for (auto c=0; c<i_cols; c++) {
            grid[r][c] = c + (r * i_rows);
            // cout << c + (r * 4) << endl; 
        }
    }

    Randomise();
    Run();
}

void Grid::Run() {
    while (true) {
        system("clear");
        
        cout << endl;

        DrawGrid();
        
        if (debug == true) {
            cout << "Debugging mode enabled" << endl;
            Debug();
        }

        if (IsFinished() == false) {
                
            system("stty -echo"); // supress echo
            system("stty cbreak"); // go to RAW mode

            char ch = getchar();
            // cout << ch << endl;

            system ("stty echo"); // Make echo work
            system("stty -cbreak");// go to COOKED mode

            if (ch == 'w') {
                SwapUp(); // Reversed
                // SwapDown();
            } else if (ch == 'a') {
                SwapLeft(); // Reversed
                // SwapRight();
            } else if (ch == 's') {
                SwapDown(); // Reversed
                // SwapUp();
            } else if (ch == 'd') {
                SwapRight(); // Reversed
                // SwapLeft();
            } else if (ch == 'q') {
                cout << "\n Quitting game" << endl;

                exit(1);
            } else if (ch == '`') {
                debug == true;
            }
        } else { // Game is completed      
            cout << "\nYou won the game! Press ENTER to exit" << endl;
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
    for (auto r=0; r<i_rows; r++) {
        for (auto c=0; c<i_cols; c++) {
            if (debug == true) {
                cout << "CURRENTLY CHECKING GRID[" << r << "][" << c << "]" << endl;
            }
            if (r != i_rows - 1 || c != i_cols - 1) { // Check all positions except zero
                if (grid[r][c] != 1 + c + (r * i_rows)) {
                    if (debug == true) {
                        cout << "\t FALSE" << endl;
                    }
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
    for (auto r=0; r<i_rows; r++) {
        for (auto c=0; c<i_cols; c++) {
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
    for (auto r=0; r<i_rows; r++) {
        cout << "[";
        for (auto c=0; c<(i_cols - 1); c++) {
            cout << grid[r][c] << ", ";
        }
        cout << grid[r][i_cols - 1] << "]\n\t";
    }
    cout << endl;
}

void Grid::DrawLine(int iter, string s_start, string s_mid, string s_end, string s_line) {    
    cout << "\t" << s_start;
    for (auto i=0; i<iter; i++) {
        for (auto x=0; x<6; x++) {cout << s_line;}
        cout << s_mid;
    }
    for (auto x=0; x<6; x++) {cout << s_line;}
    cout << s_end << endl;
}

void Grid::DrawGrid() {
    // Somehow find width of terminal, draw grid at the centre???

    DrawLine(i_cols - 1, "┏", "┳", "┓", "━"); // Starting line

    for (auto r=0; r<i_rows; r++) {
        DrawLine(i_cols - 1, "┃", "┃", "┃", " "); // Broken line

        // Numbers line
        cout << "\t" << "┃" << "  ";
        for (auto c=0; c<i_cols; c++) {
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
    cout << endl;
}