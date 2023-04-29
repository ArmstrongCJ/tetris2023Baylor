//
//  tile.h
//  Group Project
//
//  Created by Aaron Peercy on 3/27/23.
//

#ifndef tile_h
#define tile_h


#include "SDL_Plotter.h"
#include "constants.h"

class tile {
private:
    point location, prevLocation;
    color shade;
    int size;
    
public:
    tile() {
        size = 20;
    }
    
    //accessor funcitons
    point getLocation() const;
    color getColor() const;
    int getSize() const;
    
    //mutator functions
    void setLocation(const point&);
    void setColor(const color&);
    void setSize(int);
    
    void draw(SDL_Plotter& g);
    void move();
    void moveLeft();
    void moveRight();
};

#endif /* tile_h */
