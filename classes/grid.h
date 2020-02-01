#include <string>

using namespace std;

class Grid {
    private:
        // int i_rows;
        // int i_cols;
        // int a_grid[1][1] = {0};
        static const int i_rows = 4;
        static const int i_cols = 4;

        // char ch = '#';

        int a_grid[i_rows][i_cols];
        int zero_row;
        int zero_col;

        bool finished = false;
        bool debug = false;

        void Randomise();
        void Debug();

        void DrawLine(int iter, string s_start, string s_mid, string s_end, string s_line);
        void Draw();
        // string ConsecutiveChars(int n, char s);

        
    public:
        // Grid(int i_rows, int i_cols);
        Grid();
};