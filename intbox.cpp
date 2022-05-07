#include "graphics.hpp"
#include "intbox.hpp"
#include "application.hpp"

#include <sstream>

using namespace std;
using namespace genv;

IntBox::IntBox(Application* parent, int x, int y, int sx, int sy, int intervalL, int intervalR): Widget(parent,x,y,sx,sy)       //konstruktor, Widget konstruktor megh�v�sa
{
    if(intervalL<=intervalR)                                    //
    {                                                           //
        _intervalL=intervalL;                                   //
        _intervalR=intervalR;                                   //
    }                                                           //  intervallum kezd�- �s v�gpontok
    else                                                        //            elrendez�se
    {                                                           //
        _intervalL=intervalR;                                   //
        _intervalR=intervalL;                                   //
    }                                                           //

    /*stringstream ssL,ssR;                                     //
    ssL << _intervalL;                                          //
    ssR << _intervalR;                                          //
    if(gout.twidth(ssL.str())>=gout.twidth(ssR.str()))          //  adapt�v magass�g, legnagyobb �br�zoland� sz�vegsz�less�gt�l f�gg, opcion�lis
        _sx=gout.twidth(ssL.str())+30;                          //
    else                                                        //
        _sx=gout.twidth(ssR.str())+30;*/                        //

    _btnSize=_sy/2+_border;                                     //n�vel�/cs�kkent� gomb sz�less�ge, magass�gt�l f�gg
    _number=(_intervalL+_intervalR)/2;                          //alapb�l megjelen�tend� sz�m, intervallum (egyik) k�z�ps� eleme
}
IntBox::~IntBox(){}                                             //destruktor

void IntBox::draw()                                             //widget kirajzol�sa
{
    int fieldy=_y+_border,                                      //widget kijelz� fels� sz�le
        fieldwidth=_x+_sx-_btnSize,                             //widget kijelz� jobb sz�le (gomb n�lk�l)
        btnboxsize=_btnSize-_border*2,                          //gomb sz�less�g keret n�lk�l
        textheight=gout.cascent()+gout.cdescent();              //sz�vegmagass�g, bet�t�pust�l, m�rett�l f�gg

    gout.load_font("LiberationSans-Regular.ttf",30);
    stringstream ss;
    ss << _number;
    gout << color(150,150,150) << move_to(_x,_y) << box(_sx,_sy)                                                            //keret kirajzol�sa
    << color(255,255,255) << move_to(_x+_border,_y+_border) << box(_sx-_border-_btnSize,_sy-_border*2)                      //kijelz� kirajzol�sa
    << color(0,0,0) << move_to(_x+_sx/2-gout.twidth(ss.str())/2-_btnSize/2,_y+_sy/2-textheight/2) << text(ss.str());        //sz�m ki�r�sa, k�z�pre igaz�tva

    if(_hoverUp)                                                                                                            //
        gout << color(100,100,100) << move_to(fieldwidth+_border,_y+_border) << box(btnboxsize,btnboxsize);                 //         gomb kirajzol�sa
    if(_hoverDown)                                                                                                          //  ha kurzor rajta van, m�s sz�nnel
        gout << color(100,100,100) << move_to(fieldwidth+_border,_y+_sy-_border-1) << box(btnboxsize,-btnboxsize);          //

    int xmid=_x+_sx-_border/2-_btnSize/2,                                               //gomb k�zep�nek x koordin�t�ja
        blocks=0;                                                                       //ny�l(h�romsz�g) pontjainak sz�ma egy sorban -1
    gout << color(0,0,0);
    for(int ypos=fieldy+_btnSize/5;ypos<fieldy+_btnSize/2;ypos++)                       //
    {                                                                                   //
        for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)                              //   fel ny�l kirajzol�sa
            gout << move_to(xpos,ypos) << dot;                                          //   (widgetm�rett�l f�gg)
        blocks++;                                                                       //
    }                                                                                   //
    blocks=0;                                                                               //blocksz�m null�z�sa
    for(int ypos=_y+_sy-_border-_btnSize/5;ypos>_y+_sy-_border-_btnSize/2;ypos--)       //
    {                                                                                   //
        for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)                              //   le ny�l kirajzol�sa
            gout << move_to(xpos,ypos) << dot;                                          //   (widgetm�rett�l f�gg)
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

void IntBox::increase(int x)                                                            //ki�rt sz�m n�vel�se
{
    _number+=x;
}

void IntBox::decrease(int x)                                                            //ki�rt sz�m cs�kkent�se
{
    _number-=x;
}

void IntBox::enforce()                                                                  //intervallum hat�rok t�ll�p�se eset�n ki�rt sz�m vissza�ll�t�sa
{
    if(_number<_intervalL)
        _number=_intervalL;
    else if(_number>_intervalR)
        _number=_intervalR;
}

int IntBox::getNumber()                                                                 //ki�rt sz�m lek�r�se
{
    return _number;
}

void IntBox::handle(event ev)                                                           //kezel�s
{
    if(ev.type==ev_mouse)                                                               //eg�r mozgat�sa eset�n
    {
        if(on_up(ev.pos_x,ev.pos_y))                                                    //
            _hoverUp=true;                                                              //
        else                                                                            //
            _hoverUp=false;                                                             //  kurzor hely�nek t�rol�sa
        if(on_down(ev.pos_x,ev.pos_y))                                                  //      (gombon van-e)
            _hoverDown=true;                                                            //
        else                                                                            //
            _hoverDown=false;                                                           //

        if(ev.button==btn_left)                                                         //bal kattint�s eset�n
        {
            if(on_up(ev.pos_x,ev.pos_y))                                                //ha fel gombon, ki�rt sz�m n�vel�se 1-el
                increase(1);
            else if(on_down(ev.pos_x,ev.pos_y))                                         //ha le gombon, ki�rt sz�m cs�kkent�se 1-el
                decrease(1);
            enforce();                                                                  //intervallum betartat�sa
        }
    }
    else if(ev.type==ev_key)                                                            //gombnyom�sra
    {
        if(ev.keycode==key_up)                                                          //fel billenty� eset�n n�vel�s 1-el
            increase(1);
        else if(ev.keycode==key_down)                                                   //le billenty� eset�n cs�kkent�s 1-el
            decrease(1);
        else if(ev.keycode==key_pgup)                                                   //page up billenty� eset�n n�vel�s 10-el
            increase(10);
        else if(ev.keycode==key_pgdn)                                                   //page down billenty� eset�n cs�kkent�s 10-el
            decrease(10);
        enforce();                                                                      //intervallum betartat�sa
    }
}
