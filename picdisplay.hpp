#ifndef PICDISPLAY_HPP
#define PICDISPLAY_HPP

#include "widget.hpp"

class PicDisplay : public Widget
{
    public:
        PicDisplay(Application*,int,int,std::string,bool=true,bool=false);      //konstruktor, k�r: Applik�ci� amihez tartozik, bal fels� sarok x koordin�t�ja, y koordin�t�ja, f�jln�v, keret (opcion�lis, alapb�l igen), �tl�tsz�s�g (opcion�lis, alapb�l nem)
        virtual ~PicDisplay();

        virtual void draw();                                                    //widget kirajzol�sa
        virtual void handle(genv::event);                                       //widget kezel�se, k�r: event
        virtual bool selected(int,int);                                         //kurzor rajta van-e, k�r: kurzor x koordin�ta, y koordin�ta

        void import(std::string,genv::canvas&);                                 //.kep f�jl beolvas�sa, k�r: f�jln�v, canvas mez�
        void redraw(std::string);                                               //k�p v�ltoztat�sa, k�r: f�jln�v

    protected:
        genv::canvas _pic;                                                      //k�p canvas
};

#endif // PICDISPLAY_HPP
