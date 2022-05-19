#include "graphics.hpp"
#include "intbox.hpp"
#include "application.hpp"

#include <sstream>

using namespace std;
using namespace genv;

IntBox::IntBox(Application* parent, int x, int y, int sx, int sy, int intervalL, int intervalR): Widget(parent,x,y,sx,sy)       //konstruktor, Widget konstruktor meghívása
{
    if(intervalL<=intervalR)                                    //intervallum kezdõ- és végpontok elrendezése
    {
        _intervalL=intervalL;
        _intervalR=intervalR;
    }
    else
    {
        _intervalL=intervalR;
        _intervalR=intervalL;
    }

    /*stringstream ssL,ssR;                                     //
    ssL << _intervalL;                                          //
    ssR << _intervalR;                                          //
    if(gout.twidth(ssL.str())>=gout.twidth(ssR.str()))          //  adaptív szélesség, legnagyobb ábrázolandó szövegszélességtõl függ, opcionális
        _sx=gout.twidth(ssL.str())+30;                          //
    else                                                        //
        _sx=gout.twidth(ssR.str())+30;*/                        //

    _btnSize=_sy/2+_border;                                     //növelõ/csökkentõ gomb szélessége, magasságtól függ
    _number=(_intervalL+_intervalR)/2;
}
IntBox::~IntBox(){}

void IntBox::draw()
{
    gout.load_font("LiberationSans-Regular.ttf",30);
    int fieldy=_y+_border,                                      //widget kijelzõ felsõ széle
        fieldwidth=_x+_sx-_btnSize,                             //widget kijelzõ jobb széle (gomb nélkül)
        btnboxsize=_btnSize-_border*2,                          //gomb szélesség keret nélkül
        textheight=gout.cascent()+gout.cdescent();              //szövegmagasság, betûtípustól, mérettõl függ

    stringstream ss;
    ss << _number;
    gout << color(150,150,150) << move_to(_x,_y) << box(_sx,_sy)
    << color(255,255,255) << move_to(_x+_border,_y+_border) << box(_sx-_border-_btnSize,_sy-_border*2)
    << color(0,0,0) << move_to(_x+_sx/2-gout.twidth(ss.str())/2-_btnSize/2,_y+_sy/2-textheight/2) << text(ss.str());        //szám kiírása, középre igazítva

    if(_hoverUp)                                                                                                            //gomb kirajzolása, ha kurzor rajta van, más színnel
        gout << color(100,100,100) << move_to(fieldwidth+_border,_y+_border) << box(btnboxsize,btnboxsize);
    if(_hoverDown)
        gout << color(100,100,100) << move_to(fieldwidth+_border,_y+_sy-_border-1) << box(btnboxsize,-btnboxsize);

    int xmid=_x+_sx-_border/2-_btnSize/2,                                               //gomb közepének x koordinátája
        blocks=0;                                                                       //nyíl(háromszög) pontjainak száma egy sorban -1
    gout << color(0,0,0);
    for(int ypos=fieldy+_btnSize/5;ypos<fieldy+_btnSize/2;ypos++)                       //fel nyíl kirajzolása (widgetmérettõl függ)
    {
        for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)
            gout << move_to(xpos,ypos) << dot;
        blocks++;
    }
    blocks=0;
    for(int ypos=_y+_sy-_border-_btnSize/5;ypos>_y+_sy-_border-_btnSize/2;ypos--)       //le nyíl kirajzolása (widgetmérettõl függ)
    {
        for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)
            gout << move_to(xpos,ypos) << dot;
        blocks++;
    }
}

bool IntBox::on_up(int cx, int cy)                                                      //kurzor fel gombon van-e
{
    return cx>_x+_sx-_btnSize && cx<_x+_sx && cy>_y && cy<_y+_sy/2;
}

bool IntBox::on_down(int cx, int cy)                                                    //kurzor le gombon van-e
{
    return cx>_x+_sx-_btnSize && cx<_x+_sx && cy>_y+_sy/2 && cy<_y+_sy;
}

void IntBox::increase(int x)
{
    _number+=x;
}

void IntBox::decrease(int x)
{
    _number-=x;
}

void IntBox::enforce()                                                                  //intervallum határok túllépése esetén kiírt szám visszaállítása
{
    if(_number<_intervalL)
        _number=_intervalL;
    else if(_number>_intervalR)
        _number=_intervalR;
}

int IntBox::getNumber()
{
    return _number;
}

void IntBox::handle(event ev)
{
    if(ev.type==ev_mouse)
    {
        if(on_up(ev.pos_x,ev.pos_y))                                                    //kurzor gombon van-e
            _hoverUp=true;
        else
            _hoverUp=false;
        if(on_down(ev.pos_x,ev.pos_y))
            _hoverDown=true;
        else
            _hoverDown=false;

        if(ev.button==btn_left)
        {
            if(on_up(ev.pos_x,ev.pos_y))
                increase(1);
            else if(on_down(ev.pos_x,ev.pos_y))
                decrease(1);
            enforce();
        }
    }
    else if(ev.type==ev_key)
    {
        if(ev.keycode==key_up)
            increase(1);
        else if(ev.keycode==key_down)
            decrease(1);
        else if(ev.keycode==key_pgup)
            increase(10);
        else if(ev.keycode==key_pgdn)
            decrease(10);
        enforce();
    }
}
