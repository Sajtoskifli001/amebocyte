#include "graphics.hpp"
#include "board.hpp"
#include "application.hpp"

#include <vector>
#include <fstream>

using namespace std;
using namespace genv;

struct rgb
{
    int r,g,b;
};

Board::Board(Application* parent, int x, int y, int cellCount, char turn, bool sticky): Widget(parent,x,y,0,0)
{
    _cellCount=cellCount;
    _freeCount=_cellCount*_cellCount;
    _turn=turn;
    _sticky=sticky;
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
            if(cx>=_cells[i][j].x && cx<_cells[i][j].x+_cellSize && cy>=_cells[i][j].y && cy<_cells[i][j].y+_cellSize)
            {
                retCell.x=j;
                retCell.y=i;
                retCell.status=_cells[i][j].status;
                return retCell;
            }
    return retCell;
}

char Board::getTurnChar()
{
    return _turn;
}

bool Board::checkRow(cell center, int centerx, int length, char readstat)
{
    if(center.x!=0)
    {
        do
        {
            centerx--;
            readstat=_cells[center.y][centerx].status;
            if(readstat==center.status)
                length++;
        } while(centerx>center.x-5 && readstat==center.status && centerx>0);
    }
    centerx=center.x;
    if(center.x!=_cellCount-1)
    {
        do
        {
            centerx++;
            readstat=_cells[center.y][centerx].status;
            if(readstat==center.status)
                length++;
        } while(centerx<center.x+5 && readstat==center.status && centerx<_cellCount-1);
    }
    if(length>=5)
        return true;
    else
        return false;
}

bool Board::checkColumn(cell center, int centery, int length, char readstat)
{
    if(center.y!=0)
    {
        do
        {
            centery--;
            readstat=_cells[centery][center.x].status;
            if(readstat==center.status)
                length++;
        } while(centery>center.y-5 && readstat==center.status && centery>0);
    }
    centery=center.y;
    if(center.y!=_cellCount-1)
    {
        do
        {
            centery++;
            readstat=_cells[centery][center.x].status;
            if(readstat==center.status)
                length++;
        } while(centery<center.y+5 && readstat==center.status && centery<_cellCount-1);
    }
    if(length>=5)
        return true;
    else
        return false;
}

bool Board::checkDiagBS(cell center, int centerx, int centery, int length, char readstat)
{
    if(center.x!=0 && center.y!=0)
    {
        do
        {
            centerx--;
            centery--;
            readstat=_cells[centery][centerx].status;
            if(readstat==center.status)
                length++;
        } while(centerx>center.x-5 && centery>center.y-5 && readstat==center.status && centerx>0 && centery>0);
    }
    centerx=center.x;
    centery=center.y;
    if(center.x!=_cellCount-1 && center.y!=_cellCount-1)
    {
        do
        {
            centerx++;
            centery++;
            readstat=_cells[centery][centerx].status;
            if(readstat==center.status)
                length++;
        } while(centerx<center.x+5 && centery<center.y+5 && readstat==center.status && centerx<_cellCount-1 && centery<_cellCount-1);
    }
    if(length>=5)
        return true;
    else
        return false;
}

bool Board::checkDiagS(cell center, int centerx, int centery, int length, char readstat)
{
    if(center.x!=0 && center.y!=_cellCount-1)
    {
        do
        {
            centerx--;
            centery++;
            readstat=_cells[centery][centerx].status;
            if(readstat==center.status)
                length++;
        } while(centerx>center.x-5 && centery<center.y+5 && readstat==center.status && centerx>0 && centery<_cellCount-1);
    }
    centerx=center.x;
    centery=center.y;
    if(center.x!=_cellCount-1 && center.y!=0)
    {
        do
        {
            centerx++;
            centery--;
            readstat=_cells[centery][centerx].status;
            if(readstat==center.status)
                length++;
        } while(centerx<center.x+5 && centery>center.y-5 && readstat==center.status && centerx<_cellCount-1 && centery>0);
    }
    if(length>=5)
        return true;
    else
        return false;
}

bool Board::checkFive(cell center)
{
    int centerx=center.x, centery=center.y, length=1;
    char readstat='f';
    if(!checkRow(center,centerx,length,readstat))
        if(!checkColumn(center,centery,length,readstat))
            if(!checkDiagBS(center,centerx,centery,length,readstat))
                if(!checkDiagS(center,centerx,centery,length,readstat))
                    return false;
                else
                    return true;
            else
                return true;
        else
            return true;
    else
        return true;
}

bool Board::checkStick(cell center)
{
    if(_freeCount==_cellCount*_cellCount || _sticky==false)
        return true;

    int ystart=-1,ylimit=1,xstart=-1,xlimit=1;
    if(center.y==0)
        ystart=0;
    else if(center.y==_cellCount-1)
        ylimit=0;
    if(center.x==0)
        xstart=0;
    else if(center.x==_cellCount-1)
        xlimit=0;

    for(int i=center.y+ystart;i<=center.y+ylimit;i++)
        for(int j=center.x+xstart;j<=center.x+xlimit;j++)
            if(_cells[i][j].status!='f')
                return true;
    return false;
}

bool Board::getFive()
{
    return _five;
}

int Board::getFree()
{
    return _freeCount;
}

void Board::takeTurn(cell c)
{

    if(c.status=='f' && checkStick(c))
    {
        _cells[c.y][c.x].status=_turn;

        c.status=_turn;
        _five=checkFive(c);

        if(!_five)
        {
            if(_turn=='x')
                _turn='o';
            else
                _turn='x';
            _freeCount--;
        }

        _parent->turnMaster();
    }
}

void Board::handle(event ev)
{
    if(ev.type==ev_mouse && !_five)
    {
        if(ev.button==btn_left && selected(ev.pos_x,ev.pos_y))
            takeTurn(getCell(ev.pos_x,ev.pos_y));
    }
}
