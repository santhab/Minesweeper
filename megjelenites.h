
#ifndef megjelenites_h
#define megjelenites_h

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
//#include <stdbool.h>


#include "palya.h"
#include "jatekos.h"
typedef struct icondatas{
    SDL_Texture* texture;
    int ws,hs;
    SDL_Rect srcicon;
    SDL_Rect desticon;

}icondatas;

typedef struct widthheight{
    int w1;
    int h1;
    int ws;
    int hs;
}widthheight;

    //jatekallas jatek(cella** palya,SDL_Renderer* renderer, SDL_Window* window, adatok datas, icondatas* icon,int* elteltido);
    int sdlinit(void);

    SDL_Window* sdlwindow(int magassag, int szelesseg);

    SDL_Renderer* sdlrenderer(SDL_Window* window);

    //a kezd�k�perny� kirajzol�sa
    bool kezdokep(SDL_Window* window, SDL_Renderer* renderer, jatekallas* allas,eredmeny* eredmenyek,int cnt);

    //az �j j�t�k ablaknak gombjainak megjelen�t�s�t v�gzi
    widthheight ujjatek(SDL_Renderer *renderer);

    //az �jonnan l�trehozott p�ly�t rajzolja fel
    void ujpalya(adatok datas, SDL_Renderer* renderer);

    //�j j�t�k men�pontba val� l�p�skor, a gombok �ltal v�ltoztathat� �rt�kek megjelen�t�s�t (magass�g, sz�less�g, aknasz�m) v�gzi
    adatok ertekek(SDL_Renderer* renderer,SDL_Window* window, widthheight wh);

    //az �rt�kek f�ggv�ny egy seg�df�ggv�nye
    void magassagrender(SDL_Renderer* renderer, adatok data);

    //az �rt�kek f�ggv�ny egy seg�df�ggv�nye
    void szelessegrender(SDL_Renderer* renderer, adatok data);

    //az �rt�kek f�ggv�ny egy seg�df�ggv�nye
    void aknakrender(SDL_Renderer* renderer, adatok data);

    void iconinit(icondatas* icon, SDL_Renderer* renderer);

    void valtoztat(cella** palya, SDL_Renderer* renderer, adatok datas, bool vegallapot, icondatas* icon);

    bool gameover(void);

    void jobbklikk(cella** palya,int m, int sz,SDL_Renderer* renderer, icondatas* icon);

    //ha nyert a j�t�kos, de nem rakta ki az �sszes z�szl�t az akn�k f�l�, akkor ez a f�ggv�ny kiteszi
    void osszes_zaszlo(cella** palya, SDL_Renderer* renderer, adatok datas, icondatas* icon);

    //void torolminden(cella** palya, SDL_Window* window, SDL_Renderer* renderer,icondatas* icon);

    //ez a f�ggv�ny rajzolja ki az ablak jobb fels� sark�ba hogy mennyi id� telt el a j�t�k kezdete �ta.
    void idorajzol(SDL_Renderer* renderer, int* elteltido,adatok datas);

    //amennyiben a felhaszn�l� a f�men�b�l a "Toplist�t" v�lasztja akkor ez a f�ggv�ny h�v�dik meg, ami el�bb tiszt�zza az ablakot �s a h�rom legjobb j�t�kos nev�t �rja ki.
    void toplista(SDL_Renderer* renderer,eredmeny* eredmenyek,int cnt);

    //ha a j�t�kos bel�pett a toplist�ba, megh�v�dik ez a f�ggv�ny, amely egy esem�nyre v�r. Ha kattintunk akkor a program �jra a f�men�be dob.
    void toplistamukodes(SDL_Window* window, SDL_Renderer* renderer);

    Uint32 idozit(Uint32 ms, void *param);
#endif //megjelenites_h

