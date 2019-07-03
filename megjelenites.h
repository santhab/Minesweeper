
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

    //a kezdõképernyõ kirajzolása
    bool kezdokep(SDL_Window* window, SDL_Renderer* renderer, jatekallas* allas,eredmeny* eredmenyek,int cnt);

    //az új játék ablaknak gombjainak megjelenítését végzi
    widthheight ujjatek(SDL_Renderer *renderer);

    //az újonnan létrehozott pályát rajzolja fel
    void ujpalya(adatok datas, SDL_Renderer* renderer);

    //új játék menüpontba való lépéskor, a gombok által változtatható értékek megjelenítését (magasság, szélesség, aknaszám) végzi
    adatok ertekek(SDL_Renderer* renderer,SDL_Window* window, widthheight wh);

    //az értékek függvény egy segédfüggvénye
    void magassagrender(SDL_Renderer* renderer, adatok data);

    //az értékek függvény egy segédfüggvénye
    void szelessegrender(SDL_Renderer* renderer, adatok data);

    //az értékek függvény egy segédfüggvénye
    void aknakrender(SDL_Renderer* renderer, adatok data);

    void iconinit(icondatas* icon, SDL_Renderer* renderer);

    void valtoztat(cella** palya, SDL_Renderer* renderer, adatok datas, bool vegallapot, icondatas* icon);

    bool gameover(void);

    void jobbklikk(cella** palya,int m, int sz,SDL_Renderer* renderer, icondatas* icon);

    //ha nyert a játékos, de nem rakta ki az összes zászlót az aknák fölé, akkor ez a függvény kiteszi
    void osszes_zaszlo(cella** palya, SDL_Renderer* renderer, adatok datas, icondatas* icon);

    //void torolminden(cella** palya, SDL_Window* window, SDL_Renderer* renderer,icondatas* icon);

    //ez a függvény rajzolja ki az ablak jobb felsõ sarkába hogy mennyi idõ telt el a játék kezdete óta.
    void idorajzol(SDL_Renderer* renderer, int* elteltido,adatok datas);

    //amennyiben a felhasználó a fõmenübõl a "Toplistát" választja akkor ez a függvény hívódik meg, ami elõbb tisztázza az ablakot és a három legjobb játékos nevét írja ki.
    void toplista(SDL_Renderer* renderer,eredmeny* eredmenyek,int cnt);

    //ha a játékos belépett a toplistába, meghívódik ez a függvény, amely egy eseményre vár. Ha kattintunk akkor a program újra a fõmenübe dob.
    void toplistamukodes(SDL_Window* window, SDL_Renderer* renderer);

    Uint32 idozit(Uint32 ms, void *param);
#endif //megjelenites_h

