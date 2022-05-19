#ifndef BOARD_HPP
#define BOARD_HPP

#include "widget.hpp"

#include <vector>

struct cell
{
    int x,y;
    char status;
};

class Board : public Widget
{
    public:
        Board(Application*,int,int,int,char,bool);          //konstruktor, k�r: Applik�ci� amihez tartozik, bal fels� sarok x koordin�t�ja, y koordin�t�ja, t�blam�ret (blockban), sticky mode
        virtual ~Board();

        virtual void draw();                                //widget kirajzol�sa
        virtual void handle(genv::event);                   //widget kezel�se, k�r: event

        void import(std::string,genv::canvas&);             //.kep f�jl beolvas�sa, k�r: f�jln�v, canvas mez�
        cell getCell(int,int);                              //kattintott cella visszak�ld�se
        char getTurnChar();                                 //k�rszimb�lum visszak�ld�se
        bool getFive();                                     //5 egym�s melleti szimb�lum felt�tel�nek visszak�ld�se
        int getFree();                                      //�res mez�k sz�m�nak visszak�ld�se
        bool checkFive(cell);                               //k�rnyezetben 5 hasonl� szimb�lum keres�se
        bool checkStick(cell);                              //sticky m�dban, 3x3 k�rnyezetben szimb�lum keres�se
        void takeTurn(cell);                                //szab�lyos kattint�s eset�n m�veletek

        bool checkRow(cell,int,int,char);                   //sorban hasonl� szimb�lumok keres�se
        bool checkColumn(cell,int,int,char);                //oszlopban hasonl� szimb�lumok keres�se
        bool checkDiagS(cell,int,int,int,char);             //�tl�ban hasonl� szimb�lumok keres�se
        bool checkDiagBS(cell,int,int,int,char);            //�tl�ban hasonl� szimb�lumok keres�se

    protected:
        int _cellCount, _freeCount;                         //mez�sz�m, szabad mez�sz�m
        char _turn;                                         //akt�v k�r szimb�luma ('x' vagy 'o')
        bool _sticky, _five=false;                          //sticky m�d, 5 egym�s melletti hasonl� szimb�lum a p�ly�n
        std::vector<std::vector<cell>> _cells;              //cellavektor (x koordin�ta, y koordin�ta, st�tus (f=free, x, o))
        const int _cellSize=25;                             //cellam�ret (text�r�k 25 k�r� k�sz�ltek)
        genv::canvas _cX, _cO;                              //x �s o �br�k
};

#endif // BOARD_HPP
