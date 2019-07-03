#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include "palya.h"
#include "megjelenites.h"
#include "jatekos.h"
#include "mukodes.h"



int main(int argc, char *argv[])
{
    FILE* fp = fopen("eredmenyek.txt", "a+");
    int cnt=0; //betöltött eredmények száma
    eredmeny eredmenyek[EREDMENYEKSZAMA];
    beolvas(eredmenyek,fp,&cnt);
    int windowparameter=10;
    srand(time(0));
    sdlinit();
    int ido=0;
    bool quit=false;
    jatekallas allas;
    allas.aknaralepett_e=false;
    allas.kilepes=false;
    allas.nyert_e=false;
    allas.tovabbuj=false;
    allas.toplista=false;
    SDL_Window* window2;
    SDL_Renderer* renderer2;
    while(quit!=true)
    {
        SDL_Window* window1 = sdlwindow(windowparameter,windowparameter);
        SDL_Renderer* renderer1 = sdlrenderer(window1);
        adatok datas;
        datas.mehet=false;
        widthheight wh;
        icondatas icon[12];
        allas.tovabbuj=kezdokep(window1, renderer1,&allas,eredmenyek,cnt);
        cella** palya;
        if(allas.tovabbuj)
        {
            wh=ujjatek(renderer1);
            datas=ertekek(renderer1,window1,wh);
            if(datas.mehet!=true){
                quit=true;
            }
        }
        else if(allas.toplista!=true){
            quit=true;
        }
        if(datas.mehet)
        {
            palya=palyafoglal(datas);
            palyainicializalo(palya,datas,0);
            aknaszoro(palya, datas);
            palyakitolto(palya, datas);
            window2=sdlwindow(datas.magassag+1, datas.szelesseg);
            renderer2 = sdlrenderer(window2);
            ujpalya(datas,renderer2);
            iconinit(icon, renderer2);
            allas=jatek(palya,renderer2, window2,datas,icon,&ido);
        }
        if(allas.aknaralepett_e)
        {
            quit=gameover();
        }
        else if(allas.nyert_e)
        {
            osszes_zaszlo(palya,renderer2, datas,icon);
            quit=gameover();
            mentes(renderer2,datas, ido, eredmenyek, fp);
            fseek(fp, 0, SEEK_SET);
            beolvas(eredmenyek,fp,&cnt);
        }
        if(allas.kilepes){
            quit=true;
        }
        if(datas.mehet){
            torolminden(palya,window2,renderer2,icon);
        }
        ido=0;
        allas.aknaralepett_e=false;
        allas.kilepes=false;
        allas.nyert_e=false;
        allas.toplista=false;
    }
    return 0;
}
