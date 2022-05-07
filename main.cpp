#include "graphics.hpp"
#include "application.hpp"
#include "widget.hpp"
#include "intbox.hpp"
#include "stringpick.hpp"
#include "button.hpp"
#include "board.hpp"
#include "picdisplay.hpp"
#include "textdisplay.hpp"

#include <fstream>
#include <iostream>

using namespace std;
using namespace genv;

class App: public Application
{
    public:
        App(int W, int H): Application(W,H)                                             //konstruktor, Applikáció konstruktor meghívása
        {
            background = new PicDisplay(this,0,0,1100,900,"bg.kep",false);
            gameboard = new Board(this,20,20,800,800,30,'o');
            placing = new TextDisplay(this,880,30,200,50,"Now placing:");
            turndisplay = new PicDisplay(this,930,100,100,100,"x-hires.kep");
        }

        void CTD(char turn)
        {
            if(turn=='o')
                turndisplay->redraw("o-hires.kep");
            else
                turndisplay->redraw("x-hires.kep");
        }

    protected:
        PicDisplay* background;
        Board* gameboard;
        TextDisplay* placing;
        PicDisplay* turndisplay;
};

int main()
{
    App GameApp(1100,900);       //Game App létrehozása: szélesség, magasság
    GameApp.event_loop();       //Game Apphoz tartozó event loop indítása
    return 0;
}
