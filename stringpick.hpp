#ifndef STRINGPICK_HPP
#define STRINGPICK_HPP

#include "widget.hpp"

#include <string>
#include <vector>

struct optionBox
{
    int x,y;
    std::string option;
};

class StringPick : public Widget
{
    public:
        StringPick(Application*,int,int,int,int,std::vector<std::string>,int);      //konstruktor, k�r: Applik�ci� amihez tartozik, bal fels� sarok x koordin�t�ja, y koordin�t�ja, sz�less�g, magass�g, opci�k stringvektora, megjelen�tend� opci�k sz�ma
        virtual ~StringPick();

        virtual bool selected(int,int);                                             //kurzor rajta van-e, k�r: kurzor x koordin�ta, y koordin�ta, ad: igaz/hamis
        void construct();                                                           //megjelen�tend� opci�k vektor�nak (men� vektor) l�trehoz�sa, t�bb opci� mint megjelen�teni k�v�nt eset�n offsetet belesz�m�tva (g�rget�s), kevesebb opci� mint megjelen�teni k�v�nt eset�n �res, nem v�laszthat� opci� hozz�ad�sa
        virtual void draw();                                                        //widget kirajzol�sa
        bool on_btn(int,int);                                                       //kurzor gombon van-e, k�r: kurzor x koordin�t�ja, y koordin�t�ja, ad: igaz/hamis
        bool on_menu(int,int);                                                      //kurzor men�n van-e, k�r: kurzor x koordin�t�ja, y koordin�t�ja, ad: igaz/hamis
        int on_option(int,int);                                                     //kurzor melyik opci�n van, k�r: kurzor x koordin�t�ja, y koordin�t�ja, ad: men� vektorban opci� indexe, vagy -1, ha egyiken sem
        std::string getPick();                                                      //v�lasztott opci� lek�r�se
        virtual void handle(genv::event);                                           //widget kezel�se, k�r: event

        void removePick();                                                          //kiv�lasztott opci� t�rl�se az opci�vektorb�l
        void addOption(std::string);                                                //opci� hozz�ad�sa, k�r: �j opci�

    protected:
        std::vector<std::string> _options;                                          //beadott opci�k vektora
        std::vector<optionBox> _menu;                                               //megjelen�tett opci�k vektora, opci� t�pussal
        std::string _pick="";                                                       //v�lasztott opci�
        int _showCount,_btnSize,_optionHover=-1,_offset=0;                          //megjelen�tend� opci�k sz�ma, gomb sz�less�ge, kurzor melyik opci�n, megjelen�t�sn�l eltol�s a men�ben
        bool _open=false, _hover=false;                                             //men� nyitva van-e, kurzor gombon van-e
};

#endif // STRINGPICK_HPP
