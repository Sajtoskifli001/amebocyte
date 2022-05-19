#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"
#include "application.hpp"

#include <functional>

class Button : public Widget
{
    public:
        Button(Application*,int,int,int,int,std::string,std::function<void()>);     //konstruktor, k�r: Applik�ci� amihez tartozik, bal fels� sarok x koordin�t�ja, y koordin�t�ja, sz�less�g, magass�g, felirat, funktor v�grehajt�sra
        virtual ~Button();
        virtual void draw();                                                        //widget kirajzol�sa
        virtual void handle(genv::event ev);                                        //widget kezel�se, k�r: event
        void setText(std::string);                                                  //felirat be�ll�t�sa, k�r: �j felirat
        void action();                                                              //funktor v�grehajt�sa

    protected:
        std::string _text;                                                          //felirat
        std::function<void()> _funk;                                                //funktor
        bool _pressed=false;                                                        //meg van-e nyomva
};

#endif // BUTTON_HPP
