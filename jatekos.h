
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

    //ez a f�ggv�ny olvassa be az "eredmenyek.txt"-b�l soronk�nt a j�t�kosok eredm�nyeit, �s amennyiben belef�r a top3-ba �gy besz�rja azt egy eredmeny t�pus� 3 nagys�g� t�mbbe. A besz�r�shoz a "beszuras" nev� seg�df�ggv�nyt haszn�lja.
    void beolvas(eredmeny* tomb, FILE* fp,int* cnt);

    //ez a f�ggv�ny a "beolvas" f�ggv�ny seg�df�ggv�nye, ez sz�rja be az eredemeny t�pus� t�mbbe a beolvasott eredm�nyt
    void beszur(eredmeny* tomb, eredmeny e, int index);


#endif // jatekos_h
