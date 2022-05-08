#include "button.hpp"
#include "graphics.hpp"
#include "application.hpp"

using namespace genv;
using namespace std;

Button::Button(Application* parent, int x, int y, int sx, int sy, string text, function<void()> funk): Widget(parent,x,y,sx,sy)
{
    _text=text;
    _funk=funk;
}

Button::~Button(){}

void Button::draw()
{
    gout.load_font("LiberationSans-Bold.ttf",50);
    int textheight=gout.cascent()+gout.cdescent();
    gout << color(200,200,200) << move_to(_x,_y) << box(_sx,_sy);
    if(_pressed)
        gout << color(234,76,74);
    else
        gout << color(254,96,94);
    gout << move_to(_x+5,_y+5) << box(_sx-10,_sy-10);
    gout << color(0,0,0) << move_to(_x+_sx/2-gout.twidth(_text)/2,_y+_sy/2-textheight/2) << text(_text);
}

bool Button::pressed()
{
    return _pressed;
}

void Button::setText(string newtext)
{
    _text=newtext;
}

void Button::handle(event ev)
{
    if(ev.type==ev_mouse)
    {
        if(ev.button==btn_left && selected(ev.pos_x,ev.pos_y))
        {
            _pressed=true;
            action();
        }
        else if(ev.button==-btn_left)
        {
            _pressed=false;
        }
    }
}

void Button::action()
{
    _funk();
}
