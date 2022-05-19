#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"
#include "application.hpp"

class Widget
{
    public:
        Widget(Application*,int,int,int,int);       //konstruktor, kér: Applikáció amihez tartozik, bal felsõ sarok x koordinátája, y koordinátája, szélesség, magasság
        virtual ~Widget();

        virtual bool selected(int,int);             //kurzor rajta van-e, kér: kurzor x koordináta, y koordináta
        virtual void draw()=0;                      //widget kirajzolása, csak leszármazottban
        virtual void handle(genv::event)=0;         //widget kezelése, csak leszármazottban, kér: event

    protected:
        int _x, _y, _sx, _sy;                       //bal felsõ sarok x koordinátája, y koordinátája, szélesség, magasság
        int _border=3;                              //widget területébõl mennyi a keret
        Application* _parent;                       //Applikáció amihez tartozik
};

#endif // WIDGET_HPP
