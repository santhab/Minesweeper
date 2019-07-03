#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "megjelenites.h"

#include "palya.h"
#include "jatekos.h"




Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}


int sdlinit(void)
{
    /* SDL inicializálása és ablak megnyitása */
    TTF_Init();
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    return 0;
}

SDL_Window* sdlwindow(int magassag, int szelesseg)
{

    SDL_Window *window = SDL_CreateWindow("Minesweeper_SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szelesseg*50, magassag*50, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    return window;
}

SDL_Renderer* sdlrenderer(SDL_Window* window)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);
    return renderer;

}

bool kezdokep(SDL_Window* window, SDL_Renderer* renderer, jatekallas* allas, eredmeny* eredmenyek, int cnt)
{
    TTF_Font* font = TTF_OpenFont("tnr.ttf", 25);
    SDL_Color textcolor = { 255,255,255 };

    SDL_Surface* textsurface1 = TTF_RenderText_Solid(font, "Új játék", textcolor);
    SDL_Rect textrect1 = { 250-(textsurface1->w)/2, 100, textsurface1->w, textsurface1->h };
    SDL_Texture* rendertext1 = SDL_CreateTextureFromSurface(renderer, textsurface1);
    SDL_RenderCopy(renderer, rendertext1, NULL, &textrect1);

    SDL_Surface* textsurface2 = TTF_RenderText_Solid(font, "Toplista", textcolor);
    SDL_Rect textrect2 = { 250-(textsurface2->w)/2, 200, textsurface2->w, textsurface2->h };
    SDL_Texture* rendertext2 = SDL_CreateTextureFromSurface(renderer, textsurface2);
    SDL_RenderCopy(renderer, rendertext2, NULL, &textrect2);

    SDL_Surface* textsurface3 = TTF_RenderText_Solid(font, "Kilépés", textcolor);
    SDL_Rect textrect3 = { 250-(textsurface3->w)/2, 300, textsurface3->w, textsurface3->h };
    SDL_Texture* rendertext3 = SDL_CreateTextureFromSurface(renderer, textsurface3);
    SDL_RenderCopy(renderer, rendertext3, NULL, &textrect3);

    SDL_RenderPresent(renderer);
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x > (250-(textsurface1->w)/2) && event.button.x < (250-(textsurface1->w)/2+(textsurface1->w)) && event.button.y > 100 && event.button.y < (100+textsurface1->h))
                {
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                    return true;
                }
            }
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x > (250-(textsurface2->w)/2) && event.button.x < (250-(textsurface1->w)/2+(textsurface2->w)) && event.button.y > 200 && event.button.y < (200+textsurface2->h))
                {
                    allas->toplista=true;
                    SDL_RenderClear(renderer);
                    toplista(renderer,eredmenyek,cnt);
                    toplistamukodes(window,renderer);
                    quit = true;
                }
            }
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x > (250-(textsurface1->w)/2) && event.button.x < (250-(textsurface1->w)/2+(textsurface3->w)) && event.button.y > 300 && event.button.y < (300+textsurface1->h))
                {
                    quit = true;
                }
            }
            break;
        case SDL_QUIT:
            quit = true;
            break;
        }
    }
    SDL_FreeSurface(textsurface1);
    SDL_FreeSurface(textsurface2);
    SDL_FreeSurface(textsurface3);
    SDL_DestroyTexture(rendertext1);
    SDL_DestroyTexture(rendertext2);
    SDL_DestroyTexture(rendertext3);
    SDL_Quit();
    return false;
}

widthheight ujjatek(SDL_Renderer *renderer)
{
    TTF_Font* font = TTF_OpenFont("tnr.ttf", 25);
    SDL_Color textcolor = { 255,255,255 };

    SDL_Surface* szelessegsurface = TTF_RenderText_Solid(font, "Szélesség", textcolor);
    SDL_Rect szelessegrect = { 250-(szelessegsurface->w)/2, 15, szelessegsurface->w, szelessegsurface->h };
    SDL_Texture* szelessegtext = SDL_CreateTextureFromSurface(renderer, szelessegsurface);
    SDL_RenderCopy(renderer, szelessegtext, NULL, &szelessegrect);

    SDL_Texture* left = IMG_LoadTexture(renderer, "left.png");
    int w1,h1;
    SDL_QueryTexture(left,0,0, &w1, &h1);
    SDL_Rect src1= {0,0,w1, h1 };

    SDL_Rect dest1= {(275-w1), 40, w1-50, h1-50};
    SDL_RenderCopy(renderer, left, &src1, &dest1);

    SDL_Rect dest2= {275,40, w1-50, h1-50};
    SDL_Point* center = {0};
    SDL_RenderCopyEx(renderer, left, &src1, &dest2, 0,center, SDL_FLIP_HORIZONTAL);

    SDL_Surface* magassagsurface = TTF_RenderText_Solid(font, "Magasság", textcolor);
    SDL_Rect magassagrect = { 250-(magassagsurface->w)/2, 165, magassagsurface->w, magassagsurface->h };
    SDL_Texture* magassagtext = SDL_CreateTextureFromSurface(renderer, magassagsurface);
    SDL_RenderCopy(renderer, magassagtext, NULL, &magassagrect);

    SDL_Rect dest3= {(275-w1), 185, w1-50, h1-50};
    SDL_RenderCopy(renderer, left, &src1, &dest3);
    SDL_Rect dest4= {275,185, w1-50, h1-50};
    SDL_RenderCopyEx(renderer, left, &src1, &dest4, 0, center, SDL_FLIP_HORIZONTAL);

    SDL_Surface* aknaksurface = TTF_RenderText_Solid(font, "Aknák", textcolor);
    SDL_Rect aknakrect = { 250-(aknaksurface->w)/2, 315, aknaksurface->w, aknaksurface->h };
    SDL_Texture* aknaktext = SDL_CreateTextureFromSurface(renderer, aknaksurface);
    SDL_RenderCopy(renderer, aknaktext, NULL, &aknakrect);

    SDL_Rect dest5= {(275-w1), 340, w1-50, h1-50};
    SDL_RenderCopy(renderer, left, &src1, &dest5);
    SDL_Rect dest6= {275,340, w1-50, h1-50};
    SDL_RenderCopyEx(renderer, left, &src1, &dest6, 0, center, SDL_FLIP_HORIZONTAL);

    SDL_Texture* start = IMG_LoadTexture(renderer, "start2.png");
    int ws,hs;
    SDL_QueryTexture(start,0,0, &ws, &hs);
    SDL_Rect srcstart= {0,0,ws, hs };
    SDL_Rect deststart= {(700-ws)/2,430,ws-200, hs-200};
    SDL_RenderCopy(renderer, start, &srcstart, &deststart);

    SDL_RenderPresent(renderer);
    widthheight wh;
    wh.w1=w1;
    wh.h1=h1;
    wh.ws=ws;
    wh.hs=hs;
    return wh;
}


adatok ertekek(SDL_Renderer* renderer, SDL_Window* window, widthheight wh)
{
    /*TTF_Font* font = TTF_OpenFont("tnr.ttf", 25);
    SDL_Color textcolor = { 255,255,255 };*/
    int w1=wh.w1;
    int h1=wh.h1;
    int ws=wh.ws;
    int hs=wh.hs;
    adatok data;
    data.magassag=9;
    data.szelesseg=9;
    data.aknakszama=10;
    data.mehet=false;
    magassagrender(renderer,data);
    szelessegrender(renderer,data);
    aknakrender(renderer,data);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x > (275-w1) && event.button.x < 225 && event.button.y > 40 && event.button.y < (h1-10))
                {
                    if(data.szelesseg!=0)
                    {
                        data.szelesseg-=1;
                        szelessegrender(renderer,data);
                    }
                }
                if(event.button.x > 275 && event.button.x < (225+w1) && event.button.y > 40 && event.button.y < (h1-10))
                {
                    data.szelesseg+=1;
                    szelessegrender(renderer,data);
                }

                if(event.button.x > (275-w1) && event.button.x < 225 && event.button.y > 185 && event.button.y < (135+h1))
                {
                    if (data.magassag!=0)
                    {
                        data.magassag-=1;
                        magassagrender(renderer,data);
                    }

                }
                if(event.button.x > 275 && event.button.x < (225+w1) && event.button.y > 185 && event.button.y < (135+h1))
                {
                    data.magassag+=1;
                    magassagrender(renderer,data);
                }

                if(event.button.x > (275-w1) && event.button.x < 225 && event.button.y > 340 && event.button.y < (290+h1))
                {
                    //if(data.aknakszama!=0)
                    //{
                        data.aknakszama-=1;
                        aknakrender(renderer, data);
                    //}
                }
                if(event.button.x > 275 && event.button.x < (225+w1) && event.button.y > 340 && event.button.y < (290+h1))
                {
                    data.aknakszama+=1;
                    aknakrender(renderer, data);
                }
                if(event.button.x > (700-ws)/2 && event.button.x < ((700-ws)/2+ws-200) && event.button.y > 430 && event.button.y < (430+hs-200) )
                {
                    if(data.magassag!=0 && data.szelesseg!=0 && data.aknakszama!=0)
                    {
                        data.mehet=true;
                        SDL_DestroyWindow(window);
                        SDL_DestroyRenderer(renderer);
                        return data;
                    }
                }
            }
            break;
        case SDL_QUIT:
            quit = true;
            data.mehet=false;
            break;

        }
    }

    SDL_Quit();
    return data;

}

void magassagrender(SDL_Renderer* renderer, adatok data)
{
    TTF_Font* font = TTF_OpenFont("tnr.ttf", 25);
    SDL_Color textcolor = { 255,255,255 };
    int magassag=data.magassag;
    char bufferm[20];
    itoa(magassag, bufferm, 10);
    int size=50;
    int windowsize=500;
    SDL_Surface* magassagsurface = TTF_RenderText_Solid(font,bufferm, textcolor);
    SDL_Rect magassagrect = { 250-(magassagsurface->w)/2, 210, magassagsurface->w, magassagsurface->h };
    SDL_Texture* magassagtext = SDL_CreateTextureFromSurface(renderer, magassagsurface);
    boxRGBA(renderer,(windowsize/2)-size,(windowsize*0.42),(windowsize/2)+size,(windowsize*0.42) +size,0,0,0,255);
    SDL_RenderCopy(renderer, magassagtext, NULL, &magassagrect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(magassagtext);
    SDL_FreeSurface(magassagsurface);

}

void szelessegrender(SDL_Renderer* renderer, adatok data)
{
    TTF_Font* font = TTF_OpenFont("tnr.ttf", 25);
    SDL_Color textcolor = { 255,255,255 };
    int szelesseg=data.szelesseg;
    char bufferm[20];
    itoa(szelesseg, bufferm, 10);
    int size=50;
    int windowsize=500;
    SDL_Surface* szelessegsurface = TTF_RenderText_Solid(font,bufferm, textcolor);
    SDL_Rect szelessegrect = { 250-(szelessegsurface->w)/2, 65, szelessegsurface->w, szelessegsurface->h };
    SDL_Texture* szelessegtext = SDL_CreateTextureFromSurface(renderer, szelessegsurface);
    boxRGBA(renderer,(windowsize/2)-size,windowsize*0.13,(windowsize/2)+size,windowsize*0.13 + size,0,0,0,255);
    SDL_RenderCopy(renderer, szelessegtext, NULL, &szelessegrect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(szelessegtext);
    SDL_FreeSurface(szelessegsurface);

}

void aknakrender(SDL_Renderer* renderer, adatok data)
{
    TTF_Font* font = TTF_OpenFont("tnr.ttf", 25);
    SDL_Color textcolor = { 255,255,255 };
    int akna=data.aknakszama;
    char bufferm[20];
    itoa(akna, bufferm, 10);
    int size=50;
    int windowsize=500;
    SDL_Surface* aknasurface = TTF_RenderText_Solid(font,bufferm, textcolor);
    SDL_Rect aknarect = { 250-(aknasurface->w)/2, 365, aknasurface->w, aknasurface->h };
    SDL_Texture* aknatext = SDL_CreateTextureFromSurface(renderer, aknasurface);
    boxRGBA(renderer,(windowsize/2)-size,0.73*windowsize,(windowsize/2)+size,0.73*windowsize+size,0,0,0,255);
    SDL_RenderCopy(renderer, aknatext, NULL, &aknarect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(aknatext);
    SDL_FreeSurface(aknasurface);

}

void ujpalya(adatok datas, SDL_Renderer* renderer)
{
    int size=50;
    SDL_Texture* smiley = IMG_LoadTexture(renderer, "smiley.png");
    int wsm,hsm;
    SDL_QueryTexture(smiley,0,0, &wsm, &hsm);
    SDL_Rect srcsmiley= {0,0,wsm, hsm};
    SDL_Rect destsmiley= {(datas.szelesseg)*(size/2)-(size/2),0, size, size};
    SDL_RenderCopy(renderer, smiley, &srcsmiley, &destsmiley);

    for(int i=0; i<datas.szelesseg; i++)
    {
        for(int b=0; b<datas.magassag; b++)
        {
            boxRGBA(renderer, i*size, (b+1)*size, (i+1)*size, (b+2)*size, 106, 126, 138, 255);
            rectangleRGBA(renderer, i*size, (b+1)*size, (i+1)*size, (b+2)*size, 0, 0, 0, 255);
        }
    }
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(smiley);
}
/*jatekallas jatek(cella** palya,SDL_Renderer* renderer, SDL_Window* window, adatok datas, icondatas* icon, int* elteltido)
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
}*/

void valtoztat(cella** palya, SDL_Renderer* renderer, adatok datas, bool vegallapot, icondatas* icon)
{
    int size=50;
    for(int i=0; i<datas.magassag; i++ )
    {
        for(int b=0; b<datas.szelesseg; b++)
        {
            if(vegallapot && palya[i][b].ertek==9)
            {
                icon[palya[i][b].ertek].desticon=(SDL_Rect)
                {
                    (b)*50,(i+1)*50, 50, 50
                };
                SDL_RenderCopy(renderer, icon[palya[i][b].ertek].texture, &icon[palya[i][b].ertek].srcicon, &icon[palya[i][b].ertek].desticon);
            }
            if(vegallapot && palya[i][b].ertek==9 && palya[i][b].allapot==1)
            {
                icon[palya[i][b].ertek+1].desticon=(SDL_Rect)
                {
                    b*50,(i+1)*50, 50, 50
                };
                SDL_RenderCopy(renderer, icon[palya[i][b].ertek+1].texture, &icon[palya[i][b].ertek+1].srcicon, &icon[palya[i][b].ertek+1].desticon);
            }
            if((palya[i][b]).allapot==1)
            {
                switch(palya[i][b].ertek)
                {
                case 0:
                    boxRGBA(renderer, b*size, (i+1)*size, (b+1)*size, (i+2)*size, 255, 255, 255, 255);
                    rectangleRGBA(renderer, b*size, (i+1)*size, (b+1)*size, (i+2)*size, 0, 0, 0, 255);
                    break;
                case 1:
                    icon[palya[i][b].ertek].desticon=(SDL_Rect){b*50,(i+1)*50, 50, 50};
                    SDL_RenderCopy(renderer, icon[palya[i][b].ertek].texture, &icon[palya[i][b].ertek].srcicon, &icon[palya[i][b].ertek].desticon);
                    break;
                case 2:
                    icon[palya[i][b].ertek].desticon=(SDL_Rect)
                    {
                        b*50,(i+1)*50, 50, 50
                    };
                    SDL_RenderCopy(renderer, icon[palya[i][b].ertek].texture, &icon[palya[i][b].ertek].srcicon, &icon[palya[i][b].ertek].desticon);
                    break;
                case 3:
                    icon[palya[i][b].ertek].desticon=(SDL_Rect)
                    {
                        b*50,(i+1)*50, 50, 50
                    };
                    SDL_RenderCopy(renderer, icon[palya[i][b].ertek].texture, &icon[palya[i][b].ertek].srcicon, &icon[palya[i][b].ertek].desticon);
                    break;
                case 4:
                    icon[palya[i][b].ertek].desticon=(SDL_Rect)
                    {
                        b*50,(i+1)*50, 50, 50
                    };
                    SDL_RenderCopy(renderer, icon[palya[i][b].ertek].texture, &icon[palya[i][b].ertek].srcicon, &icon[palya[i][b].ertek].desticon);
                    break;
                case 5:
                    icon[palya[i][b].ertek].desticon=(SDL_Rect)
                    {
                        b*50,(i+1)*50, 50, 50
                    };
                    SDL_RenderCopy(renderer, icon[palya[i][b].ertek].texture, &icon[palya[i][b].ertek].srcicon, &icon[palya[i][b].ertek].desticon);
                    break;
                case 6:
                    icon[palya[i][b].ertek].desticon=(SDL_Rect)
                    {
                        b*50,(i+1)*50, 50, 50
                    };
                    SDL_RenderCopy(renderer, icon[palya[i][b].ertek].texture, &icon[palya[i][b].ertek].srcicon, &icon[palya[i][b].ertek].desticon);
                    break;
                case 7:
                    icon[palya[i][b].ertek].desticon=(SDL_Rect)
                    {
                        b*50,(i+1)*50, 50, 50
                    };
                    SDL_RenderCopy(renderer, icon[palya[i][b].ertek].texture, &icon[palya[i][b].ertek].srcicon, &icon[palya[i][b].ertek].desticon);
                    break;
                case 8:
                    icon[palya[i][b].ertek].desticon=(SDL_Rect)
                    {
                        b*50,(i+1)*50, 50, 50
                    };
                    SDL_RenderCopy(renderer, icon[palya[i][b].ertek].texture, &icon[palya[i][b].ertek].srcicon, &icon[palya[i][b].ertek].desticon);
                    break;
                default:
                    break;
                }
            }
        }
    }
    SDL_RenderPresent(renderer);
}
void iconinit(icondatas* icon, SDL_Renderer* renderer)
{
    for(int i=1; i<=11; i++){
        char bufferm[20];
        char png[5]=".png";
        itoa(i, bufferm, 10);
        strcat(bufferm, png);
        icon[i].texture=IMG_LoadTexture(renderer,bufferm);
        SDL_QueryTexture(icon[i].texture,0,0, &icon[i].ws, &icon[i].hs);
        icon[i].srcicon=(SDL_Rect){0,0, icon[i].ws, icon[i].hs};
    }
}

bool gameover(void)
{
    bool exit;
    bool quit=false;
    while(quit!=true)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                quit=true;
                exit=false;
            }
            break;
        case SDL_QUIT:
            quit=true;
            exit=true;
            break;
        }
    }
    return exit;
}


void jobbklikk(cella** palya,int m, int sz,SDL_Renderer* renderer, icondatas* icon)
{
    int size=50;
    if(palya[m][sz].allapot!=1)
    {
        if(palya[m][sz].flagged==1)
        {
            icon[11].desticon=(SDL_Rect)
            {
                sz*50,(m+1)*50, 50, 50
            };
            SDL_RenderCopy(renderer, icon[11].texture, &icon[11].srcicon, &icon[11].desticon);
            SDL_RenderPresent(renderer);
        }
        else
        {
            boxRGBA(renderer, (sz)*size, (m+1)*size, (sz+1)*size, (m+2)*size, 106, 126, 138, 255);
            rectangleRGBA(renderer, (sz)*size, (m+1)*size, (sz+1)*size, (m+2)*size, 0, 0, 0, 255);
            SDL_RenderPresent(renderer);
        }
    }
}

void osszes_zaszlo(cella** palya, SDL_Renderer* renderer, adatok datas, icondatas* icon){
    for(int i=0;i<datas.magassag; i++){
        for(int b=0; b<datas.szelesseg;b++){
            if(palya[i][b].ertek==9){
                icon[11].desticon=(SDL_Rect)
                {
                    b*50,(i+1)*50, 50, 50
                };
                SDL_RenderCopy(renderer, icon[11].texture, &icon[11].srcicon, &icon[11].desticon);
            }

        }
    }
    SDL_RenderPresent(renderer);
}

void torolminden(cella** palya, SDL_Window* window, SDL_Renderer* renderer,icondatas* icon){
    free(palya[0]);
    free(palya);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    for(int i=1; i<=11; i++){
        SDL_DestroyTexture(icon[i].texture);
    }
}

void idorajzol(SDL_Renderer* renderer, int* elteltido,adatok datas){
    int size=50;
    TTF_Font* font = TTF_OpenFont("tnr.ttf", 25);
    SDL_Color textcolor = { 255,255,255 };
    char bufferm[20];
    itoa(*elteltido, bufferm, 10);
    SDL_Surface* idosurface = TTF_RenderText_Solid(font,bufferm, textcolor);
    SDL_Rect idorect = {(datas.szelesseg-1)*size, 0, size, size };
    SDL_Texture* idotext = SDL_CreateTextureFromSurface(renderer, idosurface);
    boxRGBA(renderer,(datas.szelesseg-1)*size,0,datas.szelesseg*size,size,0,0,0,255);
    SDL_RenderCopy(renderer, idotext, NULL, &idorect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(idotext);
    SDL_FreeSurface(idosurface);

}

void toplista(SDL_Renderer* renderer,eredmeny* eredmenyek, int cnt)
{
    printf("belep a toplsitaba");
    int windowsize=500;
    TTF_Font* font = TTF_OpenFont("tnr.ttf", 25);
    SDL_Color textcolor = { 255,255,255 };
    for(int i=1; i<=min(EREDMENYEKSZAMA,cnt); i++){
        char bufferm[128+1];
        sprintf(bufferm, "%d. %s %dmp.", i,eredmenyek[i-1].nev ,eredmenyek[i-1].ido);
        SDL_Surface* isurface = TTF_RenderText_Solid(font,bufferm, textcolor);
        SDL_Rect irect = { (windowsize/2)-(isurface->w)/2, i*100, isurface->w, isurface->h };
        SDL_Texture* itext = SDL_CreateTextureFromSurface(renderer, isurface);
        SDL_RenderCopy(renderer, itext, NULL, &irect);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(itext);
        SDL_FreeSurface(isurface);
    }
}
void toplistamukodes(SDL_Window* window, SDL_Renderer* renderer){
    bool quit=false;
    while(quit!=true)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                quit=true;
            }
            break;
        case SDL_QUIT:
            quit=true;
            break;
        }
    }

}

