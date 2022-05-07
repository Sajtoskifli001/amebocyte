#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include <string>

class Widget;

class Application
{
    public:
        Application(int,int);                       //konstruktor, kér: vászonszélesség, magasság
        virtual ~Application();                     //destruktor
        void push(Widget*);                         //widget pointer vektorhoz adása, kér: widget pointer
        void draw_all();                            //widget vektor összes elemének kirajzolása
        void event_loop();                          //event loop
        virtual void CTD(char)=0;

    protected:
        std::vector<Widget*> widgets;               //widgetek
        int _W,_H;                                  //szélesség, magasság
};

#endif // APPLICATION_HPP
