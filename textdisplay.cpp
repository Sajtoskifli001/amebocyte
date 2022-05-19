#include "graphics.hpp"
#include "textdisplay.hpp"
#include "application.hpp"

using namespace std;
using namespace genv;

TextDisplay::TextDisplay(Application* parent, int x, int y, int sx, int sy, string text): Widget(parent,x,y,sx,sy)
{
    _text=text;
}
TextDisplay::~TextDisplay(){}

void TextDisplay::draw()
{
    gout.load_font("LiberationSans-Regular.ttf",30);
    int textheight=gout.cascent()+gout.cdescent();
    gout << color(150,150,150) << move_to(_x,_y) << box(_sx,_sy)
         << color(255,255,255) << move_to(_x+_border,_y+_border) << box(_sx-_border*2,_sy-_border*2)
         << color(0,0,0) << move_to(_x+_sx/2-gout.twidth(_text)/2,_y+_sy/2-textheight/2) << text(_text);        //szöveg kirajzolása, középre igazítva
}

void TextDisplay::setText(string newtext)
{
    _text=newtext;
}

void TextDisplay::handle(event ev){}

bool TextDisplay::selected(int cx, int cy)          //nem fókuszálható
{
    return false;
}
