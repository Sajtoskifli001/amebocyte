#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "widget.hpp"


class Checkbox : public Widget
{
    public:
        Checkbox(Application*,int,int,int,int);
        virtual ~Checkbox();

        virtual void draw();                                //widget kirajzolása
        virtual void handle(genv::event);                   //widget kezelése, kér: event

        bool getCheck();

    protected:
        bool _check=false;
};

#endif // CHECKBOX_HPP
