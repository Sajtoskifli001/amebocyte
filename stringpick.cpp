#include "graphics.hpp"
#include "stringpick.hpp"
#include "application.hpp"

#include <vector>
#include <string>

using namespace std;
using namespace genv;

StringPick::StringPick(Application* parent, int x, int y, int sx, int sy, vector<string> options, int sc): Widget(parent,x,y,sx,sy)     //konstruktor, Widget konstruktor megh�v�sa
{
    _options=options;                                       //�sszes opci� stringvektora
    _showCount=sc;                                          //megjelen�tend� opci�k sz�ma nyitott �llapotban
    _btnSize=_sy;                                           //gomb sz�less�g

    construct();                                            //megjelen�tend� opci�k vektor�nak (men� vektor) fel�p�t�se
}
StringPick::~StringPick(){}                                 //destruktor

bool StringPick::selected(int cx, int cy)                   //kurzor widgeten van-e, nyitott �llapotban men�t bele�rtve
{
    if(_open)
        return Widget::selected(cx,cy) || on_menu(cx,cy);
    else
        return Widget::selected(cx,cy);
}

void StringPick::construct()                                //megjelen�tend� opci�k vektor�nak l�trehoz�sa
{
    vector<optionBox> v;
    for(int i=_offset;i<_showCount+_offset;i++)             //megjelen�tend� opci�k l�trehoz�sa a megadott opci�k vektorb�l, t�bb elem mint megjelen�t�s eset�n offset belekalkul�l�s�val
    {
        optionBox add;
        add.x=_x;
        if(i==_offset)
            add.y=_y+_sy;
        else
            add.y=v[i-_offset-1].y+_sy;
        if(i<_options.size())
            add.option=_options[i];
        else
            add.option="";
        v.push_back(add);
    }
    _menu=v;
}

void StringPick::draw()                                                                                                                 //widget kirajzol�sa
{
    gout.load_font("LiberationSans-Regular.ttf",30);
    int textheight=gout.cascent()+gout.cdescent();                                                                                      //sz�vegmagass�g, bet�t�pust�l, m�rett�l f�gg

    gout << color(150,150,150) << move_to(_x,_y) << box(_sx,_sy)                                                                        //keret kirajzol�sa
         << color(255,255,255) << move_to(_x+_border,_y+_border) << box(_sx-_border-_btnSize,_sy-_border*2)                             //kijelz� kirajzol�sa
         << color(0,0,0) << move_to(_x+_border+5,_y+_sy/2-textheight/2) << text(_pick);                                                 //v�lasztott opci� ki�r�sa (ederetileg �res)

    if(_hover)                                                                                                                          //          gomb kirajzol�sa
        gout << color (100,100,100) << move_to(_x+_sx-_btnSize+_border,_y+_border) << box(_btnSize-_border*2,_btnSize-_border*2);       //  ha kurzor rajta van, m�s sz�nnel

    int xmid=_x+_sx-_border/2-_btnSize/2;                                                                                               //gomb k�zep�nek x koordin�t�ja
    gout << color(0,0,0);
    if(!_open)                                                                                                                          //ha men� nincs nyitva
    {
        int blocks=0;                                                                                                                       //ny�l(h�romsz�g) pontjainak sz�ma egy sorban -1
        for(int ypos=_y+_sy-_border-_btnSize/5;ypos>_y+_sy-_border-_btnSize/2;ypos--)                                                   //
        {                                                                                                                               //
            for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)                                                                          //  le ny�l kirajzol�sa
                gout << move_to(xpos,ypos) << dot;                                                                                      //  (widgetm�rett�l f�gg)
            blocks++;                                                                                                                   //
        }                                                                                                                               //
    }
    else                                                                                                                                //ha a men� nyitva van
    {
        int blocks=0;                                                                                                                       //ny�l(h�romsz�g) pontjainak sz�ma egy sorban
        for(int ypos=_y+_border+_btnSize/5;ypos<_y+_border+_btnSize/2;ypos++)                                                           //
        {                                                                                                                               //
            for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)                                                                          //  fel ny�l kirajzol�sa
                gout << move_to(xpos,ypos) << dot;                                                                                      //  (widgetm�rett�l f�gg)
            blocks++;                                                                                                                   //
        }                                                                                                                               //

        for(int i=0;i<_showCount;i++)                                                                                                   //men� kirajzol�sa
        {
            gout << color(150,150,150) << move_to(_menu[i].x,_menu[i].y) << box(_sx-_btnSize,_sy);                                          //keret kirajzol�sa
            if(_optionHover==i)                                                                                                         //
            {                                                                                                                           //
                if(_menu[i].option==_pick && _menu[i].option!="")                                                                       //
                    gout << color(170,170,210);                                                                                         //
                else                                                                                                                    //                  opci�k k�l�nb�z� sz�nekben
                    gout << color(200,200,200);                                                                                         //  ha nincs rajta kurzor, ha van rajta kurzor, ha ki van v�lasztva,
            }                                                                                                                           //                      �s ezek kombin�ci�i
            else if(_menu[i].option==_pick && _menu[i].option!="")                                                                      //
                gout << color(200,200,255);                                                                                             //
            else                                                                                                                        //
                gout << color(255,255,255);                                                                                             //
            gout << move_to(_menu[i].x+_border,_menu[i].y+_border) << box(_sx-_btnSize-_border*2,_sy-_border*2)                         //
                 << color(0,0,0) << move_to(_menu[i].x+_border+5,_menu[i].y+_sy/2-textheight/2) << text(_menu[i].option);                   //opci� ki�r�sa, v�zszintesen k�z�pre igaz�tva
        }
        gout << color(0,150,255);
        if(_menu[_showCount-1].option!=_options[_options.size()-1] && _menu[_showCount-1].option!="")                                   //ha van a men�ben fentebb nem l�tsz� opci�
            gout << move_to(_x,_menu[_showCount-1].y+_sy-_border) << box(_sx-_btnSize,_border);                                         //k�k vonal a men� tetej�n
        if(_menu[0].option!=_options[0])                                                                                                //ha van a men�ben lentebb nem l�tsz� opci�
            gout << move_to(_x,_menu[0].y) << box(_sx-_btnSize,_border);                                                                //k�k vonal a men� alj�n
    }
}

bool StringPick::on_btn(int cx, int cy)                                                                 //kurzor gombon van-e
{
    return cx>_x+_sx-_btnSize && cx<_x+_sx && cy>_y && cy<_y+_sy;
}

bool StringPick::on_menu(int cx, int cy)                                                                //kurzor men�n van-e
{
    return cx>_x && cx<_x+_sx-_btnSize && cy>_menu[0].y && cy<_menu[_showCount-1].y+_sy;
}

int StringPick::on_option(int cx, int cy)                                                               //kurzor h�nyadik opci�n van (ha egyiken sem, vagy �res opci�, akkor -1)
{
    if(on_menu(cx,cy))
    {
        for(size_t i=0;i<_menu.size();i++)
            if(cx>_menu[i].x && cx<_menu[i].x+(_sx-_btnSize) && cy>_menu[i].y && cy<_menu[i].y+_sy
               && _menu[i].option!="")
                return i;
        return -1;
    }
    else
        return -1;
}

string StringPick::getPick()                                                                            //v�lasztott opci� lek�r�se
{
    return _pick;
}

void StringPick::removePick()
{
    int pickindex=-1;
    for(size_t i=0;i<_options.size();i++)
    {
        if(_options[i]==_pick)
            pickindex=i;
    }
    if(pickindex!=-1)
        _options.erase(_options.begin()+pickindex);
    _pick="";
    construct();
}

void StringPick::addOption(string newop)
{
    if(newop!="")
        _options.push_back(newop);
    construct();
}

void StringPick::handle(event ev)                                                                       //kezel�s
{
    if(ev.type==ev_mouse)                                                                               //eg�r mozgat�sa eset�n
    {
        if(on_btn(ev.pos_x,ev.pos_y))                                                                   //
            _hover=true;                                                                                //  kurzor hely�nek t�rol�sa
        else                                                                                            //       (gombon van-e)
            _hover=false;                                                                               //
        if(_open)                                                                                           //ha nyitva a men�
            _optionHover=on_option(ev.pos_x,ev.pos_y);                                                  //kurzor melyik opci�n van (men� vektorban index lek�r�se, ha egyiken sem, vagy �res opci�, akkor -1)

        if(ev.button==btn_left)                                                                         //bal kattint�s eset�n
        {
            if(on_btn(ev.pos_x,ev.pos_y))                                                               //ha a kurzor a gombon van
            {
                if(_open)                                                                                   //ha a men� nyitva van
                    gout << color(0,0,0) << move_to(_x,_y+_sy) << box(_sx-_btnSize,_showCount*_sy);         //men� hely�nek t�rl�se
                _open=!_open;                                                                           //men� kinyit�sa/becsuk�sa
            }

            else if(_open && on_option(ev.pos_x,ev.pos_y)!=-1)                                          //ha men� nyitva, �s kurzor opci�n van (nem -1)
            {
                _pick=_menu[on_option(ev.pos_x,ev.pos_y)].option;                                       //v�lasztott opci� be�ll�t�sa
                _optionHover=-1;                                                                        //kurzor opci� -1-re �ll�t�sa
                _open=!_open;                                                                           //men� bez�r�sa
                gout << color(0,0,0) << move_to(_x,_y+_sy) << box(_sx-_btnSize,_showCount*_sy);         //men� hely�nek t�rl�se

                _parent->turnMaster();
            }
        }

        else if(ev.button==btn_wheelup && on_menu(ev.pos_x,ev.pos_y) && _offset!=0)                                 //fel g�rg� eset�n, ha kurzor a men�n van, �s van offset
        {
            _offset--;                                                                                              //offset cs�kkent�se
            construct();                                                                                            //men� vektor �jra fel�p�t�se
        }
        else if(ev.button==btn_wheeldown && on_menu(ev.pos_x,ev.pos_y) && _showCount+_offset<_options.size())       //le g�rg� eset�n, ha kurzor a men�n van, �s nem l�that� az utols� opci�
        {
            _offset++;                                                                                              //offset n�vel�se
            construct();                                                                                            //men� vektor �jra fel�p�t�se
        }
    }
}
