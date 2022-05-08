#include "graphics.hpp"
#include "stringpick.hpp"
#include "application.hpp"

#include <vector>
#include <string>

using namespace std;
using namespace genv;

StringPick::StringPick(Application* parent, int x, int y, int sx, int sy, vector<string> options, int sc): Widget(parent,x,y,sx,sy)     //konstruktor, Widget konstruktor meghívása
{
    _options=options;                                       //összes opció stringvektora
    _showCount=sc;                                          //megjelenítendõ opciók száma nyitott állapotban
    _btnSize=_sy;                                           //gomb szélesség

    construct();                                            //megjelenítendõ opciók vektorának (menü vektor) felépítése
}
StringPick::~StringPick(){}                                 //destruktor

bool StringPick::selected(int cx, int cy)                   //kurzor widgeten van-e, nyitott állapotban menüt beleértve
{
    if(_open)
        return Widget::selected(cx,cy) || on_menu(cx,cy);
    else
        return Widget::selected(cx,cy);
}

void StringPick::construct()                                //megjelenítendõ opciók vektorának létrehozása
{
    vector<optionBox> v;
    for(int i=_offset;i<_showCount+_offset;i++)             //megjelenítendõ opciók létrehozása a megadott opciók vektorból, több elem mint megjelenítés esetén offset belekalkulálásával
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

void StringPick::draw()                                                                                                                 //widget kirajzolása
{
    gout.load_font("LiberationSans-Regular.ttf",30);
    int textheight=gout.cascent()+gout.cdescent();                                                                                      //szövegmagasság, betûtípustól, mérettõl függ

    gout << color(150,150,150) << move_to(_x,_y) << box(_sx,_sy)                                                                        //keret kirajzolása
         << color(255,255,255) << move_to(_x+_border,_y+_border) << box(_sx-_border-_btnSize,_sy-_border*2)                             //kijelzõ kirajzolása
         << color(0,0,0) << move_to(_x+_border+5,_y+_sy/2-textheight/2) << text(_pick);                                                 //választott opció kiírása (ederetileg üres)

    if(_hover)                                                                                                                          //          gomb kirajzolása
        gout << color (100,100,100) << move_to(_x+_sx-_btnSize+_border,_y+_border) << box(_btnSize-_border*2,_btnSize-_border*2);       //  ha kurzor rajta van, más színnel

    int xmid=_x+_sx-_border/2-_btnSize/2;                                                                                               //gomb közepének x koordinátája
    gout << color(0,0,0);
    if(!_open)                                                                                                                          //ha menü nincs nyitva
    {
        int blocks=0;                                                                                                                       //nyíl(háromszög) pontjainak száma egy sorban -1
        for(int ypos=_y+_sy-_border-_btnSize/5;ypos>_y+_sy-_border-_btnSize/2;ypos--)                                                   //
        {                                                                                                                               //
            for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)                                                                          //  le nyíl kirajzolása
                gout << move_to(xpos,ypos) << dot;                                                                                      //  (widgetmérettõl függ)
            blocks++;                                                                                                                   //
        }                                                                                                                               //
    }
    else                                                                                                                                //ha a menü nyitva van
    {
        int blocks=0;                                                                                                                       //nyíl(háromszög) pontjainak száma egy sorban
        for(int ypos=_y+_border+_btnSize/5;ypos<_y+_border+_btnSize/2;ypos++)                                                           //
        {                                                                                                                               //
            for(int xpos=xmid-blocks;xpos<=xmid+blocks;xpos++)                                                                          //  fel nyíl kirajzolása
                gout << move_to(xpos,ypos) << dot;                                                                                      //  (widgetmérettõl függ)
            blocks++;                                                                                                                   //
        }                                                                                                                               //

        for(int i=0;i<_showCount;i++)                                                                                                   //menü kirajzolása
        {
            gout << color(150,150,150) << move_to(_menu[i].x,_menu[i].y) << box(_sx-_btnSize,_sy);                                          //keret kirajzolása
            if(_optionHover==i)                                                                                                         //
            {                                                                                                                           //
                if(_menu[i].option==_pick && _menu[i].option!="")                                                                       //
                    gout << color(170,170,210);                                                                                         //
                else                                                                                                                    //                  opciók különbözõ színekben
                    gout << color(200,200,200);                                                                                         //  ha nincs rajta kurzor, ha van rajta kurzor, ha ki van választva,
            }                                                                                                                           //                      és ezek kombinációi
            else if(_menu[i].option==_pick && _menu[i].option!="")                                                                      //
                gout << color(200,200,255);                                                                                             //
            else                                                                                                                        //
                gout << color(255,255,255);                                                                                             //
            gout << move_to(_menu[i].x+_border,_menu[i].y+_border) << box(_sx-_btnSize-_border*2,_sy-_border*2)                         //
                 << color(0,0,0) << move_to(_menu[i].x+_border+5,_menu[i].y+_sy/2-textheight/2) << text(_menu[i].option);                   //opció kiírása, vízszintesen középre igazítva
        }
        gout << color(0,150,255);
        if(_menu[_showCount-1].option!=_options[_options.size()-1] && _menu[_showCount-1].option!="")                                   //ha van a menüben fentebb nem látszó opció
            gout << move_to(_x,_menu[_showCount-1].y+_sy-_border) << box(_sx-_btnSize,_border);                                         //kék vonal a menü tetején
        if(_menu[0].option!=_options[0])                                                                                                //ha van a menüben lentebb nem látszó opció
            gout << move_to(_x,_menu[0].y) << box(_sx-_btnSize,_border);                                                                //kék vonal a menü alján
    }
}

bool StringPick::on_btn(int cx, int cy)                                                                 //kurzor gombon van-e
{
    return cx>_x+_sx-_btnSize && cx<_x+_sx && cy>_y && cy<_y+_sy;
}

bool StringPick::on_menu(int cx, int cy)                                                                //kurzor menün van-e
{
    return cx>_x && cx<_x+_sx-_btnSize && cy>_menu[0].y && cy<_menu[_showCount-1].y+_sy;
}

int StringPick::on_option(int cx, int cy)                                                               //kurzor hányadik opción van (ha egyiken sem, vagy üres opció, akkor -1)
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

string StringPick::getPick()                                                                            //választott opció lekérése
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

void StringPick::handle(event ev)                                                                       //kezelés
{
    if(ev.type==ev_mouse)                                                                               //egér mozgatása esetén
    {
        if(on_btn(ev.pos_x,ev.pos_y))                                                                   //
            _hover=true;                                                                                //  kurzor helyének tárolása
        else                                                                                            //       (gombon van-e)
            _hover=false;                                                                               //
        if(_open)                                                                                           //ha nyitva a menü
            _optionHover=on_option(ev.pos_x,ev.pos_y);                                                  //kurzor melyik opción van (menü vektorban index lekérése, ha egyiken sem, vagy üres opció, akkor -1)

        if(ev.button==btn_left)                                                                         //bal kattintás esetén
        {
            if(on_btn(ev.pos_x,ev.pos_y))                                                               //ha a kurzor a gombon van
            {
                if(_open)                                                                                   //ha a menü nyitva van
                    gout << color(0,0,0) << move_to(_x,_y+_sy) << box(_sx-_btnSize,_showCount*_sy);         //menü helyének törlése
                _open=!_open;                                                                           //menü kinyitása/becsukása
            }

            else if(_open && on_option(ev.pos_x,ev.pos_y)!=-1)                                          //ha menü nyitva, és kurzor opción van (nem -1)
            {
                _pick=_menu[on_option(ev.pos_x,ev.pos_y)].option;                                       //választott opció beállítása
                _optionHover=-1;                                                                        //kurzor opció -1-re állítása
                _open=!_open;                                                                           //menü bezárása
                gout << color(0,0,0) << move_to(_x,_y+_sy) << box(_sx-_btnSize,_showCount*_sy);         //menü helyének törlése

                _parent->turnMaster();
            }
        }

        else if(ev.button==btn_wheelup && on_menu(ev.pos_x,ev.pos_y) && _offset!=0)                                 //fel görgõ esetén, ha kurzor a menün van, és van offset
        {
            _offset--;                                                                                              //offset csökkentése
            construct();                                                                                            //menü vektor újra felépítése
        }
        else if(ev.button==btn_wheeldown && on_menu(ev.pos_x,ev.pos_y) && _showCount+_offset<_options.size())       //le görgõ esetén, ha kurzor a menün van, és nem látható az utolsó opció
        {
            _offset++;                                                                                              //offset növelése
            construct();                                                                                            //menü vektor újra felépítése
        }
    }
}
