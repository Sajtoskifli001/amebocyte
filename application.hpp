#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include <string>

class Widget;

class Application
{
    public:
        Application(int,int);                       //konstruktor, kér: vászonszélesség, magasság
        virtual ~Application();
        void push(Widget*);                         //widget pointer vektorhoz adása, kér: widget pointer
        void draw_all();                            //widget vektor összes elemének kirajzolása
        void event_loop();
        virtual void turnMaster()=0;                //játéknál körök kezelése

    protected:
        int _focus=-1;                              //aktív widget indexe
        bool _over=false;                           //program bezárása igaz érték esetén
        std::vector<Widget*> widgets;               //widgetek
        int _W,_H;                                  //szélesség, magasság
};

#endif // APPLICATION_HPP
