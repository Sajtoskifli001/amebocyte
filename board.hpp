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
        Board(Application*,int,int,int,int,int,char);
        virtual ~Board();

        virtual void draw();                                //widget kirajzolása
        virtual void handle(genv::event);                   //widget kezelése, kér: event

        void import(std::string,genv::canvas&);
        cell getCell(int,int);
        char getTurnChar();
        bool getFive();
        bool checkFive(cell);
        void takeTurn(cell);

        bool checkRow(cell,int,int,char);
        bool checkColumn(cell,int,int,char);
        bool checkDiagS(cell,int,int,int,char);
        bool checkDiagBS(cell,int,int,int,char);

    protected:
        int _cellCount;
        char _turn;
        bool _five=false;
        std::vector<std::vector<cell>> _cells;
        const int _cellSize=25;
        genv::canvas _cX, _cO;
};

#endif // BOARD_HPP
