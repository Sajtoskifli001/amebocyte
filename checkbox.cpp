#include "graphics.hpp"
#include "checkbox.hpp"
#include "application.hpp"

using namespace std;
using namespace genv;

Checkbox::Checkbox(Application* parent, int x, int y, int sx, int sy): Widget(parent,x,y,sx,sy)
{}
Checkbox::~Checkbox(){}

void Checkbox::draw()
{
    gout << color(150,150,150) << move_to(_x,_y) << box(_sx,_sy)
         << color(255,255,255) << move_to(_x+_border,_y+_border) << box(_sx-_border*2,_sy-_border*2);
    if(_check)
    {
        gout << color(0,0,0);
        for(int i=-1;i<=1;i++)
        gout << move_to(_x+_border+i,_y+_border) << line(_sx-_border*2,_sy-_border*2)
             << move_to(_x+_sx-_border-1-i,_y+_border) << line(-(_sx-_border*2),_sy-_border*2);
    }
}

bool Checkbox::getCheck()
{
    return _check;
}

void Checkbox::handle(event ev)
{
    if(ev.type==ev_mouse)
    {
        if(ev.button==btn_left && selected(ev.pos_x,ev.pos_y))
            _check=!_check;
    }
}
