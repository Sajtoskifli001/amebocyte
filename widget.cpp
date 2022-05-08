#include "graphics.hpp"
#include "widget.hpp"
#include "application.hpp"

using namespace genv;

Widget::Widget(Application* parent, int x, int y, int sx, int sy)       //konstruktor
{
    _parent=parent;                                                     //Applik�ci�, amihez tartozik
    _x=x;                                                               //bal fels� sarok x koordin�t�ja
    _y=y;                                                               //bal fels� sarok y koordin�t�ja
    _sx=sx;                                                             //sz�less�g
    _sy=sy;                                                             //magass�g
    _parent->push(this);                                                //Applik�ci� vektor�hoz adja mag�t
}
Widget::~Widget(){}                                                     //destruktor

bool Widget::selected(int cx, int cy)                                   //kurzor widgeten van-e
{
    return cx>_x && cx<_x+_sx && cy>_y && cy<_y+_sy;
}
