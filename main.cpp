#include <iostream>
#include <cmath>
#include "SDL_Plotter.h"
#include "tile.h"
#include "constants.h"
#include "font.h"

using namespace std;


int main(int argc, char ** argv)
{
    
    font text;
    SDL_Plotter g(NUM_ROW,NUM_COL);
    char key;
    
    
    //get sounds
    g.initSound(/* path to sound file, starting from where the program file is - if there is a \, do \\
                 */ "Sounds\\3_tone_chime.mp3");
   
    //fonts - make a font object
    text.display('B');
    text.display('A');
    text.display('Y');
    text.display('L');
    text.display('O');
    text.display('R');
        
    tile a;
    a.setColor(RED);
    a.setSize(g.getCol()/12);
    
    point p;
    p.x = 50;
    p.y = 50;
    text.setLoc(p);
    text.setSize(3);
    
    while (!g.getQuit()) {
        
        text.draw('A', g);
        if(g.kbhit()){
            key = g.getKey();
            switch(key) {
                case RIGHT_ARROW: a.moveRight();
                     g.playSound(/* path to sound file, starting from where the program file is - if there is a \, do \\
                                */ "Sounds\\3_tone_chime.mp3");
                     //g.quitSound([sound]) - stops it if playing, then forgets about sound
                     break;
                case LEFT_ARROW: a.moveLeft();
                     break;
            }
        }
        a.move();
        a.draw(g);
        g.update();
        g.Sleep(10);
    }
}
    
