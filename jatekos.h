
#ifndef jatekos_h
#define jatekos_h
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <string.h>

#define EREDMENYEKSZAMA 3
#include "palya.h"


    typedef struct jatekallas{
        bool aknaralepett_e; //0 ha nem, 1 ha igen
        bool kilepes;   //0 ha nem, 1 ha igen
        bool nyert_e;   //0 ha nem, 1 ha igen
        bool tovabbuj;
        bool toplista;
    }jatekallas;

    typedef struct eredmeny
    {
        char nev[100+1];
        int szeles;
        int magas;
        int aknakszama;
        int ido;
    } eredmeny;

    void mentes(SDL_Renderer* renderer,adatok datas, int elteltido,eredmeny* eredmenyek,FILE* fp);

    bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);

    double pontszamito(eredmeny e);

    //ez a függvény olvassa be az "eredmenyek.txt"-bõl soronként a játékosok eredményeit, és amennyiben belefér a top3-ba úgy beszúrja azt egy eredmeny típusú 3 nagyságú tömbbe. A beszúráshoz a "beszuras" nevû segédfüggvényt használja.
    void beolvas(eredmeny* tomb, FILE* fp,int* cnt);

    //ez a függvény a "beolvas" függvény segédfüggvénye, ez szúrja be az eredemeny típusú tömbbe a beolvasott eredményt
    void beszur(eredmeny* tomb, eredmeny e, int index);


#endif // jatekos_h
