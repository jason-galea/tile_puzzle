#include <iostream>
#include <fstream>
#include <string.h>

#include "classes/grid.h"

using namespace std;

int main(int argc, char** argv)
{
    int r = 4;
    int c = 4;
    bool d = false;

    for (auto i = 0; i<argc; i++) {
        // cout << "ARG #" << i << ": "<< argv[i] << endl;
        char* arg = argv[i]; // It just looks so much nicer

        if (!strcmp(arg, "-h") || !strcmp(arg, "--help")) {
            ifstream f("help/help.txt");
            if (f.is_open())
                std::cout << f.rdbuf();
            exit(1);

        } else if (!strcmp(arg, "-d") || !strcmp(arg, "--debug")) {
            cout << "\nDebug mode\n" << endl;
            d = true;
        }

        // else if (argv == "" || argv == "") {
        //     ;;
        // }
    }

    Grid NewGame(r, c, d);

    return 0;
}