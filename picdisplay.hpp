#ifndef PICDISPLAY_HPP
#define PICDISPLAY_HPP

#include "widget.hpp"


class PicDisplay : public Widget
{
    public:
        PicDisplay(Application*,int,int,int,int,std::string,bool=true);
        virtual ~PicDisplay();

        virtual void draw();                                //widget kirajzol�sa
        virtual void handle(genv::event);                   //widget kezel�se, k�r: event
        virtual bool selected(int,int);

        void import(std::string,genv::canvas&);
        void redraw(std::string);

    protected:
        genv::canvas _pic;
};

#endif // PICDISPLAY_HPP
