#ifndef TEXTDISPLAY_HPP
#define TEXTDISPLAY_HPP

#include "widget.hpp"


class TextDisplay : public Widget
{
    public:
        TextDisplay(Application*,int,int,int,int,std::string);
        virtual ~TextDisplay();

        virtual void draw();                                //widget kirajzol�sa
        virtual void handle(genv::event);                   //widget kezel�se, k�r: event
        virtual bool selected(int,int);

    protected:
        std::string _text;
};

#endif // TEXTDISPLAY_HPP
