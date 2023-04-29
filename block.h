//
//  block.h
//  Group Project
//
//  Created by Aaron Peercy on 4/3/23.
//

#ifndef block_h
#define block_h

#include "tile.h"
#include "SDL_Plotter.h"

class Block {
private:
    tile data[NUM_TILES];
    point loc;
    color shade;
    blockTyoe tyoe;
    
public:
    Block();
    
};

#endif /* block_h */
