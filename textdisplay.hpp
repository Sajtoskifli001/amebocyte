#ifndef TEXTDISPLAY_HPP
#define TEXTDISPLAY_HPP

#include "widget.hpp"

class TextDisplay : public Widget
{
    public:
        TextDisplay(Application*,int,int,int,int,std::string);      //konstruktor, k�r: Applik�ci� amihez tartozik, bal fels� sarok x koordin�t�ja, y koordin�t�ja, sz�less�g, magass�g, sz�veg
        virtual ~TextDisplay();

        virtual void draw();                                        //widget kirajzol�sa
        virtual void handle(genv::event);                           //widget kezel�se, k�r: event
        virtual bool selected(int,int);                             //kurzor rajta van-e, k�r: kurzor x koordin�ta, y koordin�ta

        void setText(std::string);                                  //sz�veg m�dos�t�sa

    protected:
        std::string _text;                                          //sz�veg
};

#endif // TEXTDISPLAY_HPP
