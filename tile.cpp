//
//  tile.cpp
//  Group Project
//
//  Created by Aaron Peercy on 3/27/23.
//

#include "tile.h"


void tile::draw(SDL_Plotter& g) {
    color currColor;
    //erase
    for(int r = 0; r < size; r++) {
        for(int c = 0; c < size; c++) {
            g.plotPixel(prevLocation.x + c, prevLocation.y + r, BACKGROUND);
        }
    }
    
    //draw
    for(int r = 0; r < size; r++) {
        for(int c = 0; c < size; c++) {
            currColor = shade;
            if(c == 0 or r == 0 or r == size-1 or c == size-1) {
                currColor = BLACK;
            }
            g.plotPixel(location.x + c, location.y + r, currColor);
        }
    }
    prevLocation = location;
}

point tile::getLocation() const {
    return location;
}


color tile::getColor() const {
    return shade;
}


int tile::getSize() const{
    return size;
}


void tile::setLocation(const point& p) {
    if(p.x >= 0 and p.y >= 0 and
       p.x < NUM_COL - size and p.y < NUM_ROW - size) {
        location = p;
    }
}


void tile::setColor(const color& c) {
    shade = c;
}


void tile::setSize(int s) {
    size = s;
}

void tile::move() {
    point p = getLocation();
    p.y++;
    setLocation(p);
}

void tile::moveLeft() {
    point p = getLocation();
    p.x -= size;
    setLocation(p);
}

void tile::moveRight() {
    point p = getLocation();
    p.x += size;
    setLocation(p);
}
