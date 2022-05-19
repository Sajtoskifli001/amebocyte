#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "widget.hpp"


class Checkbox : public Widget
{
    public:
        Checkbox(Application*,int,int,int,int);             //konstruktor, k�r: Applik�ci� amihez tartozik, bal fels� sarok x koordin�t�ja, y koordin�t�ja, sz�less�g, magass�g
        virtual ~Checkbox();

        virtual void draw();                                //widget kirajzol�sa
        virtual void handle(genv::event);                   //widget kezel�se, k�r: event

        bool getCheck();                                    //check �llapot visszak�ld�se

    protected:
        bool _check=false;                                  //check �llapot
};

#endif // CHECKBOX_HPP
