#include "graphics.hpp"
#include "application.hpp"
#include "widget.hpp"
#include "intbox.hpp"
#include "stringpick.hpp"
#include "button.hpp"

#include <fstream>
#include <iostream>

using namespace std;
using namespace genv;

class App: public Application
{
    public:
        App(int W, int H): Application(W,H)                                             //konstruktor, Applikáció konstruktor meghívása
        {

        }



    protected:

};

int main()
{
    App DemoApp(800,800);       //Demo App létrehozása: szélesség, magasság
    DemoApp.event_loop();       //Demo Apphoz tartozó event loop indítása
    return 0;
}
