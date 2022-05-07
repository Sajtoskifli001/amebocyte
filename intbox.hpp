#ifndef INTBOX_HPP
#define INTBOX_HPP

#include "widget.hpp"

class IntBox : public Widget
{
    public:
        IntBox(Application*,int,int,int,int,int,int);       //konstruktor, k�r: Applik�ci� amihez tartozik, bal fels� sarok x koordin�t�ja, y koordin�t�ja, sz�less�g, magass�g, intervallum egyik hat�ra, m�sik hat�ra (m�g tartalmazza, sorrend mindegy)
        virtual ~IntBox();                                  //destruktor

        virtual void draw();                                //widget kirajzol�sa
        virtual void handle(genv::event);                   //widget kezel�se, k�r: event
        bool on_up(int,int);                                //kurzor fel gombon van-e, k�r: kurzor x koordin�t�ja, y koordin�t�ja, ad: igaz/hamis
        bool on_down(int,int);                              //kurzor le gombon van-e, k�r: kurzor x koordin�t�ja, y koordin�t�ja, ad: igaz/hamis
        void increase(int);                                 //ki�rt sz�m n�vel�se, k�r: mennyivel
        void decrease(int);                                 //ki�rt sz�m cs�kkent�se, k�r: mennyivel
        void enforce();                                     //intervallum betartat�sa, t�ll�p�s eset�n ki�rt sz�m cs�kkent�se/n�vel�se
        int getNumber();                                    //ki�rt sz�m lek�r�se

    protected:
        int _number, _intervalL, _intervalR, _btnSize;      //ki�rt sz�m, intervallum bal hat�ra, jobb hat�ra, gomb sz�less�ge
        bool _hoverUp=false, _hoverDown=false;              //kurzor fel gombon van-e, le gombon van-e
};

#endif // INTBOX_HPP
