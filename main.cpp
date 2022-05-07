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
        App(int W, int H): Application(W,H)                                             //konstruktor, Applik�ci� konstruktor megh�v�sa
        {

        }



    protected:

};

int main()
{
    App DemoApp(800,800);       //Demo App l�trehoz�sa: sz�less�g, magass�g
    DemoApp.event_loop();       //Demo Apphoz tartoz� event loop ind�t�sa
    return 0;
}
