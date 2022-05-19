#include "graphics.hpp"
#include "stringpick.hpp"
#include "application.hpp"

#include <vector>
#include <string>

using namespace std;
using namespace genv;

StringPick::StringPick(Application* parent, int x, int y, int sx, int sy, vector<string> options, int sc): Widget(parent,x,y,sx,sy)     //konstruktor, Widget konstruktor megh�v�sa
{
    _options=options;
    _showCount=sc;
    _btnSize=_sy;

    construct();
}
StringPick::~StringPick(){}

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
            add.option="";                                  //t�bb k�rt megjelen�t�s mint opci� eset�n felt�lt�s �res (nem v�laszthat�) elemekkel
        v.push_back(add);
    }
    _menu=v;
}

void StringPick::draw()
{
    gout.load_font("LiberationSans-Regular.ttf",30);
    int textheight=gout.cascent()+gout.cdescent();                                                                                      //sz�vegmagass�g, bet�t�pust�l, m�rett�l f�gg

    gout << color(150,150,150) << move_to(_x,_y) << box(_sx,_sy)
         << color(255,255,255) << move_to(_x+_border,_y+_border) << box(_sx-_border-_btnSize,_sy-_border*2)
         << color(0,0,0) << move_to(_x+_border+5,_y+_sy/2-textheight/2) << text(_pick);

    if(_hover)                                                                                                                          //gomb kirajzol�sa, ha kurzor rajta van, m�s sz�nnel
        gout << color (100,100,100) << move_to(_x+_sx-_btnSize+_border,_y+_border) << box(_btnSize-_border*2,_btnSize-_border*2);

    int xmid=_x+_sx-_border/2-_btnSize/2;                                                                                               //gomb k�zep�nek x koordin�t�ja
    gout << color(0,0,0);
    if(!_open)
    {
        int blocks=0;                                                                                                                   //ny�l(h�romsz�g) pontjainak sz�ma egy sorban -1
        for(int ypos=_y+_sy-_border-_btnSize/5;ypos>_y+_sy-_border-_btnSize/2;ypos--)                                                   //le ny�l kirajzol�sa (widgetm�rett�l f�gg)
        {
            for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)
                gout << move_to(xpos,ypos) << dot;
            blocks++;
        }
    }
    else
    {
        int blocks=0;
        for(int ypos=_y+_border+_btnSize/5;ypos<_y+_border+_btnSize/2;ypos++)                                                           //fel ny�l kirajzol�sa (widgetm�rett�l f�gg)
        {
            for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)
                gout << move_to(xpos,ypos) << dot;
            blocks++;
        }

        for(int i=0;i<_showCount;i++)                                                                                                   //men� kirajzol�sa
        {
            gout << color(150,150,150) << move_to(_menu[i].x,_menu[i].y) << box(_sx-_btnSize,_sy);
            if(_optionHover==i)                                                                                                         //opci�k k�l�nb�z� sz�nekben, ha nincs rajta kurzor, ha van rajta kurzor, ha ki van v�lasztva, �s ezek kombin�ci�i
            {
                if(_menu[i].option==_pick && _menu[i].option!="")
                    gout << color(170,170,210);
                else
                    gout << color(200,200,200);
            }
            else if(_menu[i].option==_pick && _menu[i].option!="")
                gout << color(200,200,255);
            else
                gout << color(255,255,255);
            gout << move_to(_menu[i].x+_border,_menu[i].y+_border) << box(_sx-_btnSize-_border*2,_sy-_border*2)
                 << color(0,0,0) << move_to(_menu[i].x+_border+5,_menu[i].y+_sy/2-textheight/2) << text(_menu[i].option);               //opci� ki�r�sa, v�zszintesen k�z�pre igaz�tva
        }
        gout << color(0,150,255);
        if(_menu[_showCount-1].option!=_options[_options.size()-1] && _menu[_showCount-1].option!="")                                   //ha van a men�ben fentebb nem l�tsz� opci�, k�k vonal a men� tetej�n
            gout << move_to(_x,_menu[_showCount-1].y+_sy-_border) << box(_sx-_btnSize,_border);
        if(_menu[0].option!=_options[0])                                                                                                //ha van a men�ben lentebb nem l�tsz� opci�, k�k vonal a men� alj�n
            gout << move_to(_x,_menu[0].y) << box(_sx-_btnSize,_border);
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

string StringPick::getPick()
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

void StringPick::handle(event ev)
{
    if(ev.type==ev_mouse)
    {
        if(on_btn(ev.pos_x,ev.pos_y))                                                                   //kurzor gombon van-e
            _hover=true;
        else
            _hover=false;
        if(_open)
            _optionHover=on_option(ev.pos_x,ev.pos_y);

        if(ev.button==btn_left)
        {
            if(on_btn(ev.pos_x,ev.pos_y))
            {
                if(_open)                                                                               //ha a men� nyitva van, men� hely�nek t�rl�se
                    gout << color(0,0,0) << move_to(_x,_y+_sy) << box(_sx-_btnSize,_showCount*_sy);
                _open=!_open;
            }

            else if(_open && on_option(ev.pos_x,ev.pos_y)!=-1)                                          //ha men� nyitva, �s kurzor opci�n van (nem -1)
            {
                _pick=_menu[on_option(ev.pos_x,ev.pos_y)].option;
                _optionHover=-1;
                _open=!_open;
                gout << color(0,0,0) << move_to(_x,_y+_sy) << box(_sx-_btnSize,_showCount*_sy);

                _parent->turnMaster();
            }
        }

        else if(ev.button==btn_wheelup && on_menu(ev.pos_x,ev.pos_y) && _offset!=0)                                 //fel g�rg� eset�n, ha kurzor a men�n van, �s van offset: offset cs�kkent�se, men� vektor �jra fel�p�t�se
        {
            _offset--;
            construct();
        }
        else if(ev.button==btn_wheeldown && on_menu(ev.pos_x,ev.pos_y) && _showCount+_offset<_options.size())       //le g�rg� eset�n, ha kurzor a men�n van, �s nem l�that� az utols� opci�: offset n�vel�se, men� vektor �jra fel�p�t�se
        {
            _offset++;
            construct();
        }
    }
}
