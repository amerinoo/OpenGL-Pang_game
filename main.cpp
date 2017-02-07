/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <getopt.h>
using namespace std;

void usage(char *);

int main(int argc, char * argv[]){
    /* parse options */
    int option_index = 0, opt;
    static struct option loptions[] = {
        { "help", no_argument, 0, 'h' },
        { NULL,             0, 0,   0 }
    };

    while (1) {
        opt = getopt_long(argc, argv, "h",
          loptions, &option_index);
        if (opt == -1) break;
        switch (opt) {
            case '0': break;
            case 'h':
                usage(argv[0]);
                break;
        }
    }

    return 0;
} // main

void usage(char * name){
    cout << "Usage: " << name << " [OPTIONS]" << endl
         << "\nHelp options:" << endl
         << "  -h, --help         Print this help message" << endl
         << "Note: Order is not important." << endl
         << "Examples:" << endl
         << "  " << name << endl
         << endl;
    exit(EXIT_SUCCESS);
}
