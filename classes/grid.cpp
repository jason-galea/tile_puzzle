#include <iostream>
#include <string>

#include "grid.h"

using namespace std;

// Grid::Grid(int rows, int cols) {
//     i_rows == rows;
//     i_cols == cols;
Grid::Grid() {
    // Populate grid with consecutive numbers
    for (unsigned r=0; r<i_rows; r++) {
        for (unsigned c=0; c<i_cols; c++) {
            a_grid[r][c] = c + (r * 4);
            // cout << c + (r * 4) << endl; 
        }
    }

    Randomise(); // duh

    while (finished == false) {
        Draw();
    } 
}

void Grid::Randomise() {
    // For each position, generate random position and swap them
    srand(time(NULL));
    for (unsigned r=0; r<i_rows; r++) {
        for (unsigned c=0; c<i_cols; c++) {
            int rand_r = rand() % i_rows;
            int rand_c = rand() % i_cols;
            int rand_value = a_grid[rand_r][rand_c]; // 3-way swap
            a_grid[rand_r][rand_c] = a_grid[r][c];
            a_grid[r][c] = rand_value;
            // cout<<"Swapped ["<<r<<"]["<<c<<"] with ["<<rand_r<<"]["<<rand_c<<"]"<<endl;
        }
    }
}

void Grid::Draw() {
    system("clear");

    // Somehow find width of terminal, display game board at the centre
    // asdasd

    // Starting line
    cout << "\t" << "┏";
    for (unsigned i=0; i<i_cols - 1; i++) {cout << "━━━━━━┳";}
    cout << "━━━━━━┓" << endl;

    for (unsigned r=0; r<i_rows; r++) {
        // Broken line
        cout << "\t" << "┃";
        for (unsigned c=0; c<i_cols; c++) {cout << "      ┃";}
        cout << endl;

        // Numbers line
        cout << "\t" << "┃" << "  ";
        for (unsigned c=0; c<i_cols; c++) {
            cout << a_grid[r][c];
            if (a_grid[r][c] < 10) {cout << " ";} // Add a space to single digits
            cout << "  " << "┃" << "  ";
        }
        cout << endl;

        // Broken line
        cout << "\t" << "┃";
        for (unsigned c=0; c<i_cols; c++) {cout << "      " << "┃";}
        cout << endl;

        // Middle line
        cout << "\t" << "┣";
        for (unsigned i=0; i<i_cols - 1; i++) {cout << "━━━━━━╋";}
        cout << "━━━━━━┫" << endl;
    }

    // Ending line
    cout << "\t" << "┗";
    for (unsigned i=0; i<i_cols - 1; i++) {cout << "━━━━━━┻";}
    cout << "━━━━━━┛" << endl;


    // if (debug) {
    //     Debug();
    // } 

    cin.ignore();
}

void Grid::Debug() {
    cout << "\nRows = " << i_rows << endl;
    cout << "Cols = " << i_cols << endl;
    cout << "Grid = \t";
    for (unsigned r=0; r<i_rows; r++) {
        cout << "[";
        for (unsigned c=0; c<(i_cols - 1); c++) {
            cout << a_grid[r][c] << ", ";
        }
        cout << a_grid[r][i_cols - 1] << "]\n\t";
    }
    cout << endl;
}