#include <string>

using namespace std;

class Grid {
    private:
        // int i_rows;
        // int i_cols;
        // int a_grid[1][1] = {0};
        static const int i_rows = 4;
        static const int i_cols = 4;

        char ch = '#';

        int a_grid[i_rows][i_cols];

        bool finished = false;
        bool debug = false;
    public:
        // Grid(int i_rows, int i_cols);
        Grid();

        void Randomise();
        void Draw();
        string ConsecutiveChars(int n, char s);

        void Debug();
};