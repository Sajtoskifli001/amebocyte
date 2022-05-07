#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"
#include "application.hpp"

#include <functional>

class Button : public Widget
{
    public:
        Button(Application*,int,int,int,int,std::string,std::function<void()>);
        virtual ~Button();
        virtual void draw();
        virtual void handle(genv::event ev);
        bool pressed();
        void action();

    protected:
        std::string _text;
        std::function<void()> _funk;
        bool _pressed=false;
};

#endif // BUTTON_HPP
