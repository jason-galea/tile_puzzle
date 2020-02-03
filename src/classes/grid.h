#include <string>
#include <vector>

using namespace std;

class Grid {
    private:
        const int i_rows;
        const int i_cols;
        // static const int i_rows = 4;
        // static const int i_cols = 4;

        // int grid[i_rows][i_cols];
        vector< vector<int> > grid;

        int zero_row;
        int zero_col;

        bool finished = false;
        bool debug = false;

        void Run();
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
        Grid(int r, int c);
        // Grid(int r, int c);
        // Grid();
        

};