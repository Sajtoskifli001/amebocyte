#ifndef TEXTDISPLAY_HPP
#define TEXTDISPLAY_HPP

#include "widget.hpp"

class TextDisplay : public Widget
{
    public:
        TextDisplay(Application*,int,int,int,int,std::string);      //konstruktor, kér: Applikáció amihez tartozik, bal felsõ sarok x koordinátája, y koordinátája, szélesség, magasság, szöveg
        virtual ~TextDisplay();

        virtual void draw();                                        //widget kirajzolása
        virtual void handle(genv::event);                           //widget kezelése, kér: event
        virtual bool selected(int,int);                             //kurzor rajta van-e, kér: kurzor x koordináta, y koordináta

        void setText(std::string);                                  //szöveg módosítása

    protected:
        std::string _text;                                          //szöveg
};

#endif // TEXTDISPLAY_HPP
