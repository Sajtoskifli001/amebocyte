#include "graphics.hpp"
#include "application.hpp"
#include "widget.hpp"
#include "intbox.hpp"
#include "stringpick.hpp"
#include "button.hpp"
#include "board.hpp"
#include "picdisplay.hpp"
#include "textdisplay.hpp"
#include "checkbox.hpp"

#include <fstream>
#include <ctime>

using namespace std;
using namespace genv;

class App: public Application
{
    public:
        App(int W, int H): Application(W,H)                                             //konstruktor, Applikáció konstruktor meghívása
        {
            pic_background = new PicDisplay(this,0,0,"bg.kep",false);
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

            pic_title = new PicDisplay(this,110,50,"title.kep",false,true);
            txt_boardsize = new TextDisplay(this,175,300,200,50,"Board size:");
            ib_sizebox = new IntBox(this,225,375,100,50,15,30);
            txt_player = new TextDisplay(this,725,300,200,50,"First player:");
            vector<string> players={"X (red)","O (blue)"};
            sp_playerbox = new StringPick(this,735,375,180,50,players,2);
            txt_sticky = new TextDisplay(this,450,400,200,50,"Sticky mode:");
            cb_stickybox = new Checkbox(this,525,475,50,50);
            txt_stickyhint = new TextDisplay(this,215,535,670,50,"In sticky mode, you can't place isolated symbols.");
            btn_start = new Button(this,330,625,440,100,"Start",[this](){startGame();});
            btn_quit = new Button(this,425,775,250,80,"Quit",[this](){_over=true;});

            _gamePhase=0;
        }

        void startGame()
        {
            if(sp_playerbox->getPick()!="")
            {
                _boardsize=ib_sizebox->getNumber();
                bool sticky=cb_stickybox->getCheck();
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

                gameboard = new Board(this,20+(30-_boardsize)*10,25+(30-_boardsize)*13,_boardsize,startplayer,sticky);
                txt_placing = new TextDisplay(this,880-(30-_boardsize)*10,130,200,50,"Now placing:");
                pic_turndisplay = new PicDisplay(this,930-(30-_boardsize)*10,200,turnfile);

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

                if(gameboard->getFive() || gameboard->getFree()==0)
                {
                    _gamePhase++;
                    turnMaster();
                }
            }
            else
            {
                endGame();
                if(gameboard->getFree()==0)
                {
                    srand(time(0));
                    int rnd=rand()%10;
                    txt_placing->setText("Draw!");
                    if(rnd==9)
                        pic_turndisplay->redraw("csirke.kep");
                    else
                        pic_turndisplay->redraw("draw.kep");
                }
                else
                    txt_placing->setText("Winner:");
            }
        }

    protected:
        PicDisplay* pic_title;
        TextDisplay* txt_boardsize;
        TextDisplay* txt_player;
        TextDisplay* txt_sticky;
        TextDisplay* txt_stickyhint;
        IntBox* ib_sizebox;
        StringPick* sp_playerbox;
        Checkbox* cb_stickybox;

        Button* btn_start;
        Button* btn_quit;

        PicDisplay* pic_background;
        Board* gameboard;
        TextDisplay* txt_placing;
        PicDisplay* pic_turndisplay;

        TextDisplay* txt_congrats;
        Button* btn_retry;

        int _gamePhase=0;
        int _boardsize=22;
};

int main()
{
    App GameApp(1100,900);       //Game App létrehozása: szélesség, magasság
    GameApp.event_loop();       //Game Apphoz tartozó event loop indítása
    return 0;
}
