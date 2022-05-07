#include "graphics.hpp"
#include "intbox.hpp"
#include "application.hpp"

#include <sstream>

using namespace std;
using namespace genv;

IntBox::IntBox(Application* parent, int x, int y, int sx, int sy, int intervalL, int intervalR): Widget(parent,x,y,sx,sy)       //konstruktor, Widget konstruktor meghívása
{
    if(intervalL<=intervalR)                                    //
    {                                                           //
        _intervalL=intervalL;                                   //
        _intervalR=intervalR;                                   //
    }                                                           //  intervallum kezdõ- és végpontok
    else                                                        //            elrendezése
    {                                                           //
        _intervalL=intervalR;                                   //
        _intervalR=intervalL;                                   //
    }                                                           //

    /*stringstream ssL,ssR;                                     //
    ssL << _intervalL;                                          //
    ssR << _intervalR;                                          //
    if(gout.twidth(ssL.str())>=gout.twidth(ssR.str()))          //  adaptív magasság, legnagyobb ábrázolandó szövegszélességtõl függ, opcionális
        _sx=gout.twidth(ssL.str())+30;                          //
    else                                                        //
        _sx=gout.twidth(ssR.str())+30;*/                        //

    _btnSize=_sy/2+_border;                                     //növelõ/csökkentõ gomb szélessége, magasságtól függ
    _number=(_intervalL+_intervalR)/2;                          //alapból megjelenítendõ szám, intervallum (egyik) középsõ eleme
}
IntBox::~IntBox(){}                                             //destruktor

void IntBox::draw()                                             //widget kirajzolása
{
    int fieldy=_y+_border,                                      //widget kijelzõ felsõ széle
        fieldwidth=_x+_sx-_btnSize,                             //widget kijelzõ jobb széle (gomb nélkül)
        btnboxsize=_btnSize-_border*2,                          //gomb szélesség keret nélkül
        textheight=gout.cascent()+gout.cdescent();              //szövegmagasság, betûtípustól, mérettõl függ

    gout.load_font("LiberationSans-Regular.ttf",30);
    stringstream ss;
    ss << _number;
    gout << color(150,150,150) << move_to(_x,_y) << box(_sx,_sy)                                                            //keret kirajzolása
    << color(255,255,255) << move_to(_x+_border,_y+_border) << box(_sx-_border-_btnSize,_sy-_border*2)                      //kijelzõ kirajzolása
    << color(0,0,0) << move_to(_x+_sx/2-gout.twidth(ss.str())/2-_btnSize/2,_y+_sy/2-textheight/2) << text(ss.str());        //szám kiírása, középre igazítva

    if(_hoverUp)                                                                                                            //
        gout << color(100,100,100) << move_to(fieldwidth+_border,_y+_border) << box(btnboxsize,btnboxsize);                 //         gomb kirajzolása
    if(_hoverDown)                                                                                                          //  ha kurzor rajta van, más színnel
        gout << color(100,100,100) << move_to(fieldwidth+_border,_y+_sy-_border-1) << box(btnboxsize,-btnboxsize);          //

    int xmid=_x+_sx-_border/2-_btnSize/2,                                               //gomb közepének x koordinátája
        blocks=0;                                                                       //nyíl(háromszög) pontjainak száma egy sorban -1
    gout << color(0,0,0);
    for(int ypos=fieldy+_btnSize/5;ypos<fieldy+_btnSize/2;ypos++)                       //
    {                                                                                   //
        for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)                              //   fel nyíl kirajzolása
            gout << move_to(xpos,ypos) << dot;                                          //   (widgetmérettõl függ)
        blocks++;                                                                       //
    }                                                                                   //
    blocks=0;                                                                               //blockszám nullázása
    for(int ypos=_y+_sy-_border-_btnSize/5;ypos>_y+_sy-_border-_btnSize/2;ypos--)       //
    {                                                                                   //
        for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)                              //   le nyíl kirajzolása
            gout << move_to(xpos,ypos) << dot;                                          //   (widgetmérettõl függ)
        blocks++;                                                                       //
    }                                                                                   //
}

bool IntBox::on_up(int cx, int cy)                                                      //kurzor fel gombon van-e
{
    return cx>_x+_sx-_btnSize && cx<_x+_sx && cy>_y && cy<_y+_sy/2;
}

bool IntBox::on_down(int cx, int cy)                                                    //kurzor le gombon van-e
{
    return cx>_x+_sx-_btnSize && cx<_x+_sx && cy>_y+_sy/2 && cy<_y+_sy;
}

void IntBox::increase(int x)                                                            //kiírt szám növelése
{
    _number+=x;
}

void IntBox::decrease(int x)                                                            //kiírt szám csökkentése
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

int IntBox::getNumber()                                                                 //kiírt szám lekérése
{
    return _number;
}

void IntBox::handle(event ev)                                                           //kezelés
{
    if(ev.type==ev_mouse)                                                               //egér mozgatása esetén
    {
        if(on_up(ev.pos_x,ev.pos_y))                                                    //
            _hoverUp=true;                                                              //
        else                                                                            //
            _hoverUp=false;                                                             //  kurzor helyének tárolása
        if(on_down(ev.pos_x,ev.pos_y))                                                  //      (gombon van-e)
            _hoverDown=true;                                                            //
        else                                                                            //
            _hoverDown=false;                                                           //

        if(ev.button==btn_left)                                                         //bal kattintás esetén
        {
            if(on_up(ev.pos_x,ev.pos_y))                                                //ha fel gombon, kiírt szám növelése 1-el
                increase(1);
            else if(on_down(ev.pos_x,ev.pos_y))                                         //ha le gombon, kiírt szám csökkentése 1-el
                decrease(1);
            enforce();                                                                  //intervallum betartatása
        }
    }
    else if(ev.type==ev_key)                                                            //gombnyomásra
    {
        if(ev.keycode==key_up)                                                          //fel billentyû esetén növelés 1-el
            increase(1);
        else if(ev.keycode==key_down)                                                   //le billentyû esetén csökkentés 1-el
            decrease(1);
        else if(ev.keycode==key_pgup)                                                   //page up billentyû esetén növelés 10-el
            increase(10);
        else if(ev.keycode==key_pgdn)                                                   //page down billentyû esetén csökkentés 10-el
            decrease(10);
        enforce();                                                                      //intervallum betartatása
    }
}
