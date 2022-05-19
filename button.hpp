#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"
#include "application.hpp"

#include <functional>

class Button : public Widget
{
    public:
        Button(Application*,int,int,int,int,std::string,std::function<void()>);     //konstruktor, kér: Applikáció amihez tartozik, bal felsõ sarok x koordinátája, y koordinátája, szélesség, magasság, felirat, funktor végrehajtásra
        virtual ~Button();
        virtual void draw();                                                        //widget kirajzolása
        virtual void handle(genv::event ev);                                        //widget kezelése, kér: event
        void setText(std::string);                                                  //felirat beállítása, kér: új felirat
        void action();                                                              //funktor végrehajtása

    protected:
        std::string _text;                                                          //felirat
        std::function<void()> _funk;                                                //funktor
        bool _pressed=false;                                                        //meg van-e nyomva
};

#endif // BUTTON_HPP
