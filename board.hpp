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

        virtual void draw();                                //widget kirajzol�sa
        virtual void handle(genv::event);                   //widget kezel�se, k�r: event

        void import(std::string,genv::canvas&);
        cell getCell(int,int);
        void takeTurn(cell);

    protected:
        int _cellCount;
        char _turn;
        std::vector<std::vector<cell>> _cells;
        const int _cellSize=25;
        genv::canvas _cX, _cO;
};

#endif // BOARD_HPP
