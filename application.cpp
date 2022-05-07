#include "graphics.hpp"
#include "application.hpp"
#include "widget.hpp"

#include <fstream>

using namespace std;
using namespace genv;

Application::Application(int W, int H)                                  //konstruktor
{
    gout.open(W,H);                                                     //vászon létrehozása: szélesség, magasság
    _W=W;                                                               //szélesség tárolása
    _H=H;                                                               //magasság tárolása
}
Application::~Application() {}                                          //destruktor

void Application::push(Widget* w)                                       //widget hozzáadása a widgets vektorhoz
{
    widgets.push_back(w);
}

void Application::draw_all()                                            //összes widget kirajzolása + refresh
{
    for(size_t i=0;i<widgets.size();i++)
        widgets[i]->draw();
    gout << refresh;
}

void Application::event_loop()                                                                  //event loop
{
    int textheight=gout.cascent()+gout.cdescent();                                              //szöveg magassága: betûtípustól, mérettõl függ
    draw_all();                                                                                 //widgetek kirajzolása
    event ev;                                                                                   //event változó
    int focus=-1;                                                                               //focus: aktív widget indexe
    while(gin >> ev && ev.keycode!=key_escape)                                                  //kilépés escape billentyû esetén
    {
        if(ev.type==ev_mouse && ev.button==btn_left)                                            //bal kattintás esetén kurzor alatti widget fókuszba helyezése
        {
            for(size_t i=0;i<widgets.size();i++)
                if(widgets[i]->selected(ev.pos_x,ev.pos_y))
                    focus=i;
        }

        if(focus!=-1)                                                                           //ha van aktív widget
            widgets[focus]->handle(ev);                                                         //aktív widget kezelése
        draw_all();                                                                             //widgetek kirajzolása
    }
}
