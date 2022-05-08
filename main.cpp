#include "graphics.hpp"
#include "application.hpp"
#include "widget.hpp"
#include "intbox.hpp"
#include "stringpick.hpp"
#include "button.hpp"
#include "board.hpp"
#include "picdisplay.hpp"
#include "textdisplay.hpp"

#include <fstream>

using namespace std;
using namespace genv;

class App: public Application
{
    public:
        App(int W, int H): Application(W,H)                                             //konstruktor, Applikáció konstruktor meghívása
        {
            pic_background = new PicDisplay(this,0,0,1100,900,"bg.kep",false);
            preGame();
        }

        void clearApp()
        {
            for(size_t i=1;i<widgets.size();i++)
                delete widgets[i];
            widgets.erase(widgets.begin()+1,widgets.begin()+widgets.size());
            _focus=-1;
        }

        void preGame()
        {
            clearApp();

            pic_title = new PicDisplay(this,250,50,600,100,"title3.kep");
            //pic_title = new PicDisplay(this,75,50,600,100,"title2.kep",false,true);
            txt_boardsize = new TextDisplay(this,200,300,200,50,"Boardsize:");
            ib_sizebox = new IntBox(this,250,400,100,50,15,30);
            txt_player = new TextDisplay(this,700,300,200,50,"First player:");
            vector<string> players={"X (red)","O (blue)"};
            sp_playerbox = new StringPick(this,710,400,180,50,players,2);
            btn_start = new Button(this,330,600,440,100,"Start",[this](){startGame();});
            btn_quit = new Button(this,425,750,250,80,"Quit",[this](){_over=true;});

            _gamePhase=0;
        }

        void startGame()
        {
            if(sp_playerbox->getPick()!="")
            {
                _boardsize=ib_sizebox->getNumber();
                char startplayer;
                string turnfile;
                if(sp_playerbox->getPick()=="O (blue)")
                {
                    startplayer='o';
                    turnfile="o-hires.kep";
                }
                else
                {
                    startplayer='x';
                    turnfile="x-hires.kep";
                }

                clearApp();

                gameboard = new Board(this,20+(30-_boardsize)*10,25+(30-_boardsize)*13,800,800,_boardsize,startplayer);
                txt_placing = new TextDisplay(this,880-(30-_boardsize)*10,130,200,50,"Now placing:");
                pic_turndisplay = new PicDisplay(this,930-(30-_boardsize)*10,200,100,100,turnfile);

                _gamePhase++;
            }
            else
                btn_start->setText("Choose a player!");
        }

        void endGame()
        {
            txt_congrats = new TextDisplay(this,870-(30-_boardsize)*10,350,220,50,"Well played! :)");
            btn_retry = new Button(this,880-(30-_boardsize)*10,500,200,80,"Retry",[this](){preGame();});
            btn_quit = new Button(this,880-(30-_boardsize)*10,620,200,80,"Quit",[this](){_over=true;});
        }

        void turnMaster()
        {
            if(_gamePhase==0)
            {
                btn_start->setText("Start");
            }
            else if(_gamePhase==1)
            {
                char turnChar=gameboard->getTurnChar();
                if(turnChar=='o')
                    pic_turndisplay->redraw("o-hires.kep");
                else
                    pic_turndisplay->redraw("x-hires.kep");

                if(gameboard->getFive())
                {
                    _gamePhase++;
                    turnMaster();
                }
            }
            else
            {
                endGame();
                txt_placing->setText("Winner:");
            }
        }

    protected:
        PicDisplay* pic_title;
        TextDisplay* txt_boardsize;
        TextDisplay* txt_player;
        IntBox* ib_sizebox;
        StringPick* sp_playerbox;
        Button* btn_start;
        Button* btn_quit;

        PicDisplay* pic_background;
        Board* gameboard;
        TextDisplay* txt_placing;
        PicDisplay* pic_turndisplay;

        TextDisplay* txt_congrats;
        Button* btn_retry;

        int _gamePhase;
        int _boardsize;
};

int main()
{
    App GameApp(1100,900);       //Game App létrehozása: szélesség, magasság
    GameApp.event_loop();       //Game Apphoz tartozó event loop indítása
    return 0;
}
