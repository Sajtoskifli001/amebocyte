#include "graphics.hpp"
#include "widget.hpp"
#include "application.hpp"

using namespace genv;

Widget::Widget(Application* parent, int x, int y, int sx, int sy)
{
    _parent=parent;
    _x=x;
    _y=y;
    _sx=sx;
    _sy=sy;
    _parent->push(this);                                                //Applikáció vektorához adja magát
}
Widget::~Widget(){}

bool Widget::selected(int cx, int cy)                                   //kurzor widgeten van-e
{
    return cx>_x && cx<_x+_sx && cy>_y && cy<_y+_sy;
}
