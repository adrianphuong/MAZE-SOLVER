#include <iostream>
#include <fstream>
#include <getopt.h>

#include "grid.h"
#include "util.h"

std::string usage();

#define OPTS "i:o:s:e:p:h"

int main (int const argc, char *argv[]) {
    exec::execname(argv[0]);

    std::string outfile;
    std::string imgfile;
    std::string infile;
    Point start;
    start.x = 0;
    start.y = 0;
    Point end;
    end.x = 0;
    end.y = 0;
    int opt;
    while ((opt = getopt(argc, argv, OPTS)) != -1) {
        switch (opt) {
		case 'i': infile = optarg; break;
		case 'o': outfile = optarg; break;
		case 's': sscanf(optarg,"%u:%u", &start.x, &start.y); break;
		case 'e': sscanf(optarg,"%u:%u", &end.x, &end.y); break;
		case 'p': imgfile = optarg; break;
		case 'h': std::cout << usage(); return 0;
		default: std::cerr << usage(); return 1;
	}
    }
    Grid Gr(0,0);
    if (infile == "-") {
           Gr = Grid::load(std::cin);
    } else {
        std::ifstream in {infile};
        Gr = Grid::load(in);
    }
    //Grid Gr = load(infile);
    if(end.x == 0 && end.y == 0) {
	    end.x = Gr.getWidth()-1;
	    end.y = Gr.getHeight()-1;
    }
    Gr.findPath(start, end);
    if (outfile == "-") {
        Gr.serialize(std::cout);
    } else {
        std::ofstream out {outfile};
        Gr.serialize(out);
    }

    // Output ppm
    if (imgfile == "-") {
        Gr.draw(std::cout);
    } else if (imgfile.length() > 0){
        std::ofstream out {imgfile};
        Gr.draw(out);
    }
    return exec::status();
}

std::string usage() {
    return std::string{}
        + "SYNOPSIS\n"
        + "     Find the path between two points in a maze\n"
        + "\n"
        + "USAGE\n"
        + "     " + exec::execname() + " [-" + OPTS + "]\n"
        + "\n"
        + "OPTIONS\n"
        + "     -i input.dat        input file with serialized data [default: stdin]\n"
        + "     -o outfile.dat      output file in serialized form [default: stdout]\n"
        + "     -s x:y              starting point for finding path [default: 0:0]\n"
        + "     -e x:y              ending point for finding path [default: bottom right]\n"
        + "     -p img.ppm          generate ppm image of solved maze\n"
        + "     -h                  Print out helpful information\n"
        ;
}
