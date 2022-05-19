#include "graphics.hpp"
#include "application.hpp"
#include "widget.hpp"

#include <fstream>

using namespace std;
using namespace genv;

Application::Application(int W, int H)
{
    gout.open(W,H);
    _W=W;
    _H=H;
}
Application::~Application() {}

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

void Application::event_loop()
{
    draw_all();
    event ev;
    _focus=-1;                                                          //focus: akt�v widget indexe
    while(gin >> ev && ev.keycode!=key_escape && !_over)
    {
        if(ev.type==ev_mouse && ev.button==btn_left)
        {
            for(size_t i=0;i<widgets.size();i++)
                if(widgets[i]->selected(ev.pos_x,ev.pos_y))
                    _focus=i;
        }

        if(_focus!=-1)                                                  //akt�v widget kezel�se
            widgets[_focus]->handle(ev);
        draw_all();
    }
}
