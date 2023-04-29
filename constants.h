//
//  constants.h
//  Group Project
//
//  Created by Aaron Peercy on 3/27/23.
//

#ifndef constants_h
#define constants_h

#include "SDL_Plotter.h"

const int NUM_ROW = 800;
const int NUM_COL = 500;

const int NUM_TILES = 4;

const color RED = color(220, 20, 20);
const color BLACK = color(0, 0, 0);
const color BACKGROUND = color(255, 255, 255)

enum tileType {bar, square, l_shape, t_shape, z_shape};
enum direction {up, right, down, left};

#endif /* constants_h */
