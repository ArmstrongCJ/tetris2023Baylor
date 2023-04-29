//
//  font.h
//  Group Project
//
//  Created by Aaron Peercy on 4/26/23.
//

#ifndef font_h
#define font_h

#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include "SDL_Plotter.h"
using namespace std;

const int MAX_FONT_SIZE = 25;

//make a file for font - each file for letter starts with row and column, then in an array of 1 and 0 draw letter with 1s

class letter {
private:
    int row = 0, col = 0;
    char data[MAX_FONT_SIZE][MAX_FONT_SIZE];
public:
    letter() {}
    void init(string fname) {
        ifstream input;
        input.open(fname);
        assert(input);
        
        input >> row >> col;
        for(int r = 0; r < row; r++) {
            for(int c = 0; c < col; c++) {
                input >> data[r][c];
            }
        }
        input.close();
    }
    
    void draw(int n, point p, DL_Plotter& g) {
        for(int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                if(data[r][c] == '1') {
                    for(int xoff = 0; xoff < n; xoff++) {
                        for(int yoff = 0; yoff < n; xoff++) {
                            g.plotPixel(xoff + p.x + c*n, yoff + p.y + r*n, 0,0,0);
                        }
                    }
                }
            }
        }
    }
    
    void display (ostream& out) {
        for(int r = 0; r < row; r++) {
            for(int c = 0; c < col; c++) {
                if(data[r][c] == '1') {
                    out << data[r][c];
                }
                else {
                    out << " ";
                }
            }
            out << endl;
        }
    }
};

class font {
private:
    letter data[256];
    point loc;
    int size;
public:
    font() {
        string fname;
        for(char c = 'A'; c <= 'Z'; c++) {
            fname = "font\\";
            fname += c;
            fname += ".txt";
            data[c].init(fname);
            cout << fname << endl;
        }
        loc.x = 0;
        loc.y = 0;
        size = 1;
    }
    
    void setLoc(point p) {
        loc = p;
    }
    
    void setSize(int n) {
        if (n >= 1) {
            size = n;
        }
    }
    
    void display(char c, ostream& out = cout) {
        data[c].display(out);
    }
    
    void draw(char c, SDL_Plotter& g) {
        data[c].draw(size, loc, g);
    }
};

#endif /* font_h */
