#include <iostream>
#include <fstream>
#include <getopt.h>

#include <stdio.h>
#include "grid.h"
#include "util.h"

std::string usage();

#define OPTS "i:o:p:h"

int main(int const argc, char *argv[]) {
    exec::execname(argv[0]);
    std::string infile = "-";
    std::string outfile = "-";
    std::string imgfile;
    int opt;
    while ((opt = getopt(argc, argv, OPTS)) != -1) {
        switch (opt) {
		case 'i': infile = optarg; break;
		case 'o': outfile = optarg; break;
		case 'p': imgfile = optarg; break;
    		case 'h': std::cout << usage(); return 0;
                default: std::cerr << usage(); return 1;
        }
    }
    Grid g(0,0);
    if (infile == "-") {
	   g = Grid::load(std::cin);
    } else {
        std::ifstream in {infile};
        g = Grid::load(in);
    }
    Grid mazeGrid = g.makeMaze();
    if (outfile == "-") {
        mazeGrid.serialize(std::cout);
    } else {
        std::ofstream out {outfile};
        mazeGrid.serialize(out);
    }

    // Output ppm
    if (imgfile == "-") {
        mazeGrid.draw(std::cout);
    } else if (imgfile.length() > 0){
        std::ofstream out {imgfile};
        mazeGrid.draw(out);
    }
    // Fin
    return exec::status();
}

std::string usage() {
    return std::string{}
        + "SYNOPSIS\n"
        + "     Given a randomized \"grid-graph\", generate a maze by creating a\n"
        + " minimum spanning tree\n"
        + "\n"
        + "USAGE\n"
        + "     " + exec::execname() + " [-" + OPTS + "]\n"
        + "\n"
        + "OPTIONS\n"
        + "     -i infile           input file with serialized grid data [default: stdin]\n"
        + "     -o outfile          maze output in serialized form [default: stdout]\n"
        + "     -p img.ppm          generate ppm image of maze\n"
        + "     -h                  Print out helpful information\n"
        ;
}
