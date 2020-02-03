#include <string>

using namespace std;

class Grid {
    private:
        // int i_rows;
        // int i_cols;
        static const int i_rows = 4;
        static const int i_cols = 4;

        // char ch = '#';

        int grid[i_rows][i_cols];
        int zero_row;
        int zero_col;

        bool finished = false;
        bool debug = false;

        void Randomise();
        void Debug();

        void SwapUp();
        void SwapDown();
        void SwapLeft();
        void SwapRight();

        bool IsFinished();

        void DrawLine(int iter, string s_start, string s_mid, string s_end, string s_line);
        void DrawGrid();

        
    public:
        // Grid(int i_rows, int i_cols);
        Grid();

        void Run();
};