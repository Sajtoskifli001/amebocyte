#ifndef INTBOX_HPP
#define INTBOX_HPP

#include "widget.hpp"

class IntBox : public Widget
{
    public:
        IntBox(Application*,int,int,int,int,int,int);       //konstruktor, kér: Applikáció amihez tartozik, bal felsõ sarok x koordinátája, y koordinátája, szélesség, magasság, intervallum egyik határa, másik határa (még tartalmazza, sorrend mindegy)
        virtual ~IntBox();                                  //destruktor

        virtual void draw();                                //widget kirajzolása
        virtual void handle(genv::event);                   //widget kezelése, kér: event
        bool on_up(int,int);                                //kurzor fel gombon van-e, kér: kurzor x koordinátája, y koordinátája, ad: igaz/hamis
        bool on_down(int,int);                              //kurzor le gombon van-e, kér: kurzor x koordinátája, y koordinátája, ad: igaz/hamis
        void increase(int);                                 //kiírt szám növelése, kér: mennyivel
        void decrease(int);                                 //kiírt szám csökkentése, kér: mennyivel
        void enforce();                                     //intervallum betartatása, túllépés esetén kiírt szám csökkentése/növelése
        int getNumber();                                    //kiírt szám lekérése

    protected:
        int _number, _intervalL, _intervalR, _btnSize;      //kiírt szám, intervallum bal határa, jobb határa, gomb szélessége
        bool _hoverUp=false, _hoverDown=false;              //kurzor fel gombon van-e, le gombon van-e
};

#endif // INTBOX_HPP
