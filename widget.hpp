#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"
#include "application.hpp"

class Widget
{
    public:
        Widget(Application*,int,int,int,int);       //konstruktor, k�r: Applik�ci� amihez tartozik, bal fels� sarok x koordin�t�ja, y koordin�t�ja, sz�less�g, magass�g
        virtual ~Widget();

        virtual bool selected(int,int);             //kurzor rajta van-e, k�r: kurzor x koordin�ta, y koordin�ta
        virtual void draw()=0;                      //widget kirajzol�sa, csak lesz�rmazottban
        virtual void handle(genv::event)=0;         //widget kezel�se, csak lesz�rmazottban, k�r: event

    protected:
        int _x, _y, _sx, _sy;                       //bal fels� sarok x koordin�t�ja, y koordin�t�ja, sz�less�g, magass�g
        int _border=3;                              //widget ter�let�b�l mennyi a keret
        Application* _parent;                       //Applik�ci� amihez tartozik
};

#endif // WIDGET_HPP
