#include "graphics.hpp"
#include "widget.hpp"
#include "application.hpp"

using namespace genv;

Widget::Widget(Application* parent, int x, int y, int sx, int sy)       //konstruktor
{
    _parent=parent;                                                     //Applikáció, amihez tartozik
    _x=x;                                                               //bal felsõ sarok x koordinátája
    _y=y;                                                               //bal felsõ sarok y koordinátája
    _sx=sx;                                                             //szélesség
    _sy=sy;                                                             //magasság
    _parent->push(this);                                                //Applikáció vektorához adja magát
}
Widget::~Widget(){}                                                     //destruktor

bool Widget::selected(int cx, int cy)                                   //kurzor widgeten van-e
{
    return cx>_x && cx<_x+_sx && cy>_y && cy<_y+_sy;
}
