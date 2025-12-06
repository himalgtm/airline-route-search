#include <iostream>
#include <string>
#include <cstdlib>

#include "graph.h"
#include "queries.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

static void printUsage() {
    cerr << "Usage:\n"
         << "  routeSearch 1 <city_A> <city_B> <num_connection>\n"
         << "  routeSearch 2 <city_A> through <city_B> and <city_C> to <city_D>\n"
         << "  (or: routeSearch 2 <city_A> <city_B> <city_C> <city_D>)\n"
         << "  routeSearch 3 <city_A> <city_B> <city_C>\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    int q = std::atoi(argv[1]);
    if (q < 1 || q > 3) {
        cerr << "ERROR: Question number must be 1, 2, or 3.\n";
        printUsage();
        return 1;
    }

    Graph g;
    g.loadFromFile("data/flight.txt");

    if (q == 1) {
        if (argc != 5) {
            cerr << "ERROR: Question 1 requires 3 parameters.\n";
            printUsage();
            return 1;
        }
        string cityA = argv[2];
        string cityB = argv[3];
        int maxConn = std::atoi(argv[4]);
        handleQuestion1(g, cityA, cityB, maxConn);

    } else if (q == 2) {
        string A, B, C, D;

        if (argc == 6) {
            // Simple: routeSearch 2 A B C D
            A = argv[2];
            B = argv[3];
            C = argv[4];
            D = argv[5];
        } else if (argc == 9) {
            // routeSearch 2 A through B and C to D
            // argv: 0:prog, 1:"2", 2:A, 3:"through", 4:B, 5:"and", 6:C, 7:"to", 8:D
            A = argv[2];

            string throughWord = argv[3];
            string andWord = argv[5];
            string toWord = argv[7];

            if (throughWord != "through" || andWord != "and" || toWord != "to") {
                cerr << "ERROR: Question 2 syntax invalid.\n";
                printUsage();
                return 1;
            }
            B = argv[4];
            C = argv[6];
            D = argv[8];
        } else {
            cerr << "ERROR: Question 2 expects either 6 or 9 arguments.\n";
            printUsage();
            return 1;
        }

        handleQuestion2(g, A, B, C, D);

    } else if (q == 3) {
        if (argc != 5) {
            cerr << "ERROR: Question 3 requires 3 parameters.\n";
            printUsage();
            return 1;
        }
        string A = argv[2];
        string B = argv[3];
        string C = argv[4];
        handleQuestion3(g, A, B, C);
    }

    return 0;
}