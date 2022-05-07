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
    gout.load_font("LiberationSans-Regular.ttf",30);
    gout << color(200,200,200) << move_to(_x,_y) << box(_sx,_sy);
    if(_pressed)
        gout << color(200,0,0);
    else
        gout << color(255,0,0);
    gout << move_to(_x+5,_y+5) << box(_sx-10,_sy-10);
    gout << color(0,0,0) << move_to(_x+_sx/2-gout.twidth(_text)/2,_y+_sy/2-(gout.cascent()/2+gout.cdescent()/2)) << text(_text);
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

bool Button::is_pressed()
{
    return _pressed;
}

void Button::action()
{
    _funk();
}
