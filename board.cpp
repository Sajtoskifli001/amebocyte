#include "graphics.hpp"
#include "board.hpp"
#include "application.hpp"

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
using namespace genv;

struct rgb
{
    int r,g,b;
};

Board::Board(Application* parent, int x, int y, int sx, int sy, int cellCount, char turn): Widget(parent,x,y,sx,sy)
{
    _cellCount=cellCount;
    _turn=turn;
    _sx=cellCount*(_cellSize+_border)+_border;
    _sy=_sx;

    _cells=vector<vector<cell>>(cellCount,vector<cell>(cellCount));
    for(size_t i=0;i<_cells.size();i++)
        for(size_t j=0;j<_cells[i].size();j++)
        {
            if(j==0)
                _cells[i][j].x=_x+_border;
            else
                _cells[i][j].x=_cells[i][j-1].x+_cellSize+_border;
            if(i==0)
                _cells[i][j].y=_y+_border;
            else
                _cells[i][j].y=_cells[i-1][j].y+_cellSize+_border;
            _cells[i][j].status='f';
        }

    import("x.kep",_cX);
    import("o.kep",_cO);
}
Board::~Board(){}

void Board::import(string file, canvas &c)
{
    ifstream is(file);
    vector<vector<rgb>> pic;
    int picw, pich;
    is >> picw >> pich;
    c.open(picw,pich);
    pic=vector<vector<rgb>>(pich,vector<rgb>(picw));
    for(size_t i=0;i<pic.size();i++)
        for(size_t j=0;j<pic[i].size();j++)
        {
            is >> pic[i][j].r >> pic[i][j].g >> pic[i][j].b;
            c << move_to(j,i) << color(pic[i][j].r,pic[i][j].g,pic[i][j].b) << dot;
        }
    is.close();
}

void Board::draw()
{
    gout << color(150,150,150) << move_to(_x,_y) << box(_sx,_sy);
    gout << color(255,255,255);
    for(size_t i=0;i<_cells.size();i++)
        for(size_t j=0;j<_cells[i].size();j++)
        {
            gout << move_to(_cells[i][j].x,_cells[i][j].y) << box(_cellSize,_cellSize);
            if(_cells[i][j].status=='x')
                gout << stamp(_cX,_cells[i][j].x,_cells[i][j].y);
            if(_cells[i][j].status=='o')
                gout << stamp(_cO,_cells[i][j].x,_cells[i][j].y);
        }
}

cell Board::getCell(int cx, int cy)
{
    cell retCell={-1,-1,'n'};
    for(size_t i=0;i<_cells.size();i++)
        for(size_t j=0;j<_cells[i].size();j++)
            if(cx>_cells[i][j].x && cx<_cells[i][j].x+_cellSize && cy>_cells[i][j].y && cy<_cells[i][j].y+_cellSize)
            {
                retCell.x=j;
                retCell.y=i;
                retCell.status=_cells[i][j].status;
                return retCell;
            }
    return retCell;
}

void Board::takeTurn(cell c)
{
    string notext="Invalid move!";
    gout.load_font("LiberationSans-Regular.ttf",30);
    gout << color(0,0,0) << move_to(_x+_sx+20,_y+_sy/3*2) << box(gout.twidth(notext),gout.cascent());
    if(c.status=='f')
    {
        _cells[c.y][c.x].status=_turn;
        if(_turn=='x')
            _turn='o';
        else
            _turn='x';
        _parent->CTD(_turn);
    }
    else
        gout << color(200,0,0) << move_to(_x+_sx+20,_y+_sy/3*2) << text(notext);
}

void Board::handle(event ev)
{
    if(ev.type==ev_mouse)
    {
        if(ev.button==btn_left && selected(ev.pos_x,ev.pos_y))
            takeTurn(getCell(ev.pos_x,ev.pos_y));
    }
}
