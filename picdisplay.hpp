#ifndef PICDISPLAY_HPP
#define PICDISPLAY_HPP

#include "widget.hpp"

class PicDisplay : public Widget
{
    public:
        PicDisplay(Application*,int,int,std::string,bool=true,bool=false);      //konstruktor, kér: Applikáció amihez tartozik, bal felsõ sarok x koordinátája, y koordinátája, fájlnév, keret (opcionális, alapból igen), átlátszóság (opcionális, alapból nem)
        virtual ~PicDisplay();

        virtual void draw();                                                    //widget kirajzolása
        virtual void handle(genv::event);                                       //widget kezelése, kér: event
        virtual bool selected(int,int);                                         //kurzor rajta van-e, kér: kurzor x koordináta, y koordináta

        void import(std::string,genv::canvas&);                                 //.kep fájl beolvasása, kér: fájlnév, canvas mezõ
        void redraw(std::string);                                               //kép változtatása, kér: fájlnév

    protected:
        genv::canvas _pic;                                                      //kép canvas
};

#endif // PICDISPLAY_HPP
