#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include <string>

class Widget;

class Application
{
    public:
        Application(int,int);                       //konstruktor, k�r: v�szonsz�less�g, magass�g
        virtual ~Application();                     //destruktor
        void push(Widget*);                         //widget pointer vektorhoz ad�sa, k�r: widget pointer
        void draw_all();                            //widget vektor �sszes elem�nek kirajzol�sa
        void event_loop();                          //event loop
        virtual void CTD(char)=0;

    protected:
        std::vector<Widget*> widgets;               //widgetek
        int _W,_H;                                  //sz�less�g, magass�g
};

#endif // APPLICATION_HPP
