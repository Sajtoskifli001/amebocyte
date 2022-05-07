#include "graphics.hpp"
#include "application.hpp"
#include "widget.hpp"

#include <fstream>

using namespace std;
using namespace genv;

Application::Application(int W, int H)                                  //konstruktor
{
    gout.open(W,H);                                                     //v�szon l�trehoz�sa: sz�less�g, magass�g
    _W=W;                                                               //sz�less�g t�rol�sa
    _H=H;                                                               //magass�g t�rol�sa
}
Application::~Application() {}                                          //destruktor

void Application::push(Widget* w)                                       //widget hozz�ad�sa a widgets vektorhoz
{
    widgets.push_back(w);
}

void Application::draw_all()                                            //�sszes widget kirajzol�sa + refresh
{
    for(size_t i=0;i<widgets.size();i++)
        widgets[i]->draw();
    gout << refresh;
}

void Application::event_loop()                                                                  //event loop
{
    int textheight=gout.cascent()+gout.cdescent();                                              //sz�veg magass�ga: bet�t�pust�l, m�rett�l f�gg
    draw_all();                                                                                 //widgetek kirajzol�sa
    event ev;                                                                                   //event v�ltoz�
    int focus=-1;                                                                               //focus: akt�v widget indexe
    while(gin >> ev && ev.keycode!=key_escape)                                                  //kil�p�s escape billenty� eset�n
    {
        if(ev.type==ev_mouse && ev.button==btn_left)                                            //bal kattint�s eset�n kurzor alatti widget f�kuszba helyez�se
        {
            for(size_t i=0;i<widgets.size();i++)
                if(widgets[i]->selected(ev.pos_x,ev.pos_y))
                    focus=i;
        }

        if(focus!=-1)                                                                           //ha van akt�v widget
            widgets[focus]->handle(ev);                                                         //akt�v widget kezel�se
        draw_all();                                                                             //widgetek kirajzol�sa
    }
}
