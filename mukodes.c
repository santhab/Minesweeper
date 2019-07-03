#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "palya.h"
#include "megjelenites.h"

jatekallas jatek(cella** palya,SDL_Renderer* renderer, SDL_Window* window, adatok datas, icondatas* icon, int* elteltido)
{
    SDL_TimerID id;
    int size=50;
    int m,sz;
    jatekallas allas;
    allas.aknaralepett_e=false;
    allas.kilepes=false;
    allas.nyert_e=false;
    id = SDL_AddTimer(1000, idozit, NULL);
    bool quit=false;
    while(quit!=true)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                sz=((event.button.x)/size);
                m=((event.button.y)/size)-1;
                if(m>=0 && sz>=0 && palya[m][sz].flagged!=1)
                {
                    allas.aknaralepett_e=felfed(palya,m,sz,datas.magassag, datas.szelesseg);
                    valtoztat(palya,renderer,datas,allas.aknaralepett_e,icon);
                    if(allas.aknaralepett_e)
                    {
                        quit=true;
                    }
                    else if(nyerte(palya,datas))
                    {
                        allas.nyert_e=true;
                        quit=true;
                    }
                }
            }
            else if(event.button.button==SDL_BUTTON_RIGHT)
            {
                sz=((event.button.x)/size);
                m=((event.button.y)/size)-1;
                if(palya[m][sz].flagged==1 && palya[m][sz].allapot==0)
                {
                    palya[m][sz].flagged=0;
                }
                else if(palya[m][sz].flagged==0 && palya[m][sz].allapot==0)
                {
                    palya[m][sz].flagged=1;
                }
                jobbklikk(palya,m,sz,renderer,icon);
            }
            break;
        case SDL_USEREVENT:
            *elteltido+=1;
            idorajzol(renderer,elteltido,datas);
            break;
        case SDL_QUIT:
            allas.kilepes=true;
            quit = true;
            break;
        }
    }
    SDL_RemoveTimer(id);
    SDL_RenderPresent(renderer);
    return allas;
}
