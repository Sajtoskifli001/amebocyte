#include "graphics.hpp"
#include "picdisplay.hpp"
#include "application.hpp"

#include <vector>
#include <fstream>

using namespace std;
using namespace genv;

struct rgb
{
    int r,g,b;
};

PicDisplay::PicDisplay(Application* parent, int x, int y, int sx, int sy, string file, bool border, bool transp): Widget(parent,x,y,sx,sy)
{
    if(!border)
        _border=0;
    _pic.transparent(transp);
    import(file,_pic);
}
PicDisplay::~PicDisplay(){}

void PicDisplay::import(string file, canvas &c)
{
    ifstream is(file);
    vector<vector<rgb>> pic;
    int picw, pich;
    is >> picw >> pich;
    c.open(picw,pich);
    pic=vector<vector<rgb>>(pich,vector<rgb>(picw));
    for(size_t i=0;i<pic.size();i++)
        for(size_t j=0;j<pic[i].size();j++)
        {
            is >> pic[i][j].r >> pic[i][j].g >> pic[i][j].b;
            c << move_to(j,i) << color(pic[i][j].r,pic[i][j].g,pic[i][j].b) << dot;
        }
    is.close();
    _sx=picw+_border*2;
    _sy=pich+_border*2;
}

void PicDisplay::draw()
{
    if(_border!=0)
        gout << color(150,150,150) << move_to(_x,_y) << box(_sx,_sy);
    gout << stamp(_pic,_x+_border,_y+_border);
}

void PicDisplay::redraw(string file)
{
    import(file,_pic);
}

void PicDisplay::handle(event ev){}

bool PicDisplay::selected(int cx, int cy)
{
    return false;
}
