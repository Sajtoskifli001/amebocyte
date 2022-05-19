#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include <string>

class Widget;

class Application
{
    public:
        Application(int,int);                       //konstruktor, k�r: v�szonsz�less�g, magass�g
        virtual ~Application();
        void push(Widget*);                         //widget pointer vektorhoz ad�sa, k�r: widget pointer
        void draw_all();                            //widget vektor �sszes elem�nek kirajzol�sa
        void event_loop();
        virtual void turnMaster()=0;                //j�t�kn�l k�r�k kezel�se

    protected:
        int _focus=-1;                              //akt�v widget indexe
        bool _over=false;                           //program bez�r�sa igaz �rt�k eset�n
        std::vector<Widget*> widgets;               //widgetek
        int _W,_H;                                  //sz�less�g, magass�g
};

#endif // APPLICATION_HPP
