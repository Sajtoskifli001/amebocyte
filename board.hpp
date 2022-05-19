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
        Board(Application*,int,int,int,char,bool);          //konstruktor, kér: Applikáció amihez tartozik, bal felsõ sarok x koordinátája, y koordinátája, táblaméret (blockban), sticky mode
        virtual ~Board();

        virtual void draw();                                //widget kirajzolása
        virtual void handle(genv::event);                   //widget kezelése, kér: event

        void import(std::string,genv::canvas&);             //.kep fájl beolvasása, kér: fájlnév, canvas mezõ
        cell getCell(int,int);                              //kattintott cella visszaküldése
        char getTurnChar();                                 //körszimbólum visszaküldése
        bool getFive();                                     //5 egymás melleti szimbólum feltételének visszaküldése
        int getFree();                                      //üres mezõk számának visszaküldése
        bool checkFive(cell);                               //környezetben 5 hasonló szimbólum keresése
        bool checkStick(cell);                              //sticky módban, 3x3 környezetben szimbólum keresése
        void takeTurn(cell);                                //szabályos kattintás esetén mûveletek

        bool checkRow(cell,int,int,char);                   //sorban hasonló szimbólumok keresése
        bool checkColumn(cell,int,int,char);                //oszlopban hasonló szimbólumok keresése
        bool checkDiagS(cell,int,int,int,char);             //átlóban hasonló szimbólumok keresése
        bool checkDiagBS(cell,int,int,int,char);            //átlóban hasonló szimbólumok keresése

    protected:
        int _cellCount, _freeCount;                         //mezõszám, szabad mezõszám
        char _turn;                                         //aktív kör szimbóluma ('x' vagy 'o')
        bool _sticky, _five=false;                          //sticky mód, 5 egymás melletti hasonló szimbólum a pályán
        std::vector<std::vector<cell>> _cells;              //cellavektor (x koordináta, y koordináta, státus (f=free, x, o))
        const int _cellSize=25;                             //cellaméret (textúrák 25 köré készültek)
        genv::canvas _cX, _cO;                              //x és o ábrák
};

#endif // BOARD_HPP
