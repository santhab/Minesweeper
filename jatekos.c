#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "jatekos.h"
#define min(a,b) (((a)<(b))?(a):(b))

void mentes(SDL_Renderer* renderer,adatok datas, int elteltido,eredmeny* eredmenyek, FILE* fp)
{
    int size=50;
    TTF_Font* font = TTF_OpenFont("tnr.ttf", 25);
    SDL_Color feher = {255, 255, 255}, fekete = { 0, 0, 0 };
    char szoveg[100];
    SDL_Rect r = { (datas.szelesseg*size)/2-200, (datas.magassag*size)/2-20, 400, 40 };
    input_text(szoveg, 100,r,fekete, feher, font, renderer);
    fprintf(fp, "%s,%dx%d,%d,%d\n",szoveg,datas.magassag,datas.szelesseg,datas.aknakszama,elteltido);
    fclose(fp);

}

/*void toplista(SDL_Renderer* renderer,eredmeny* eredmenyek, int cnt)
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
}*/
void beolvas(eredmeny* tomb, FILE* fp, int* cnt)
{

    eredmeny e;
    char sor[128+1];
    while(fgets(sor, 128, fp) != NULL)
    {
        sscanf(sor,"%[^,],%dx%d,%d,%d\n",e.nev,&e.magas,&e.szeles,&e.aknakszama,&e.ido);
        double pontszam=pontszamito(e);
        int index=0;
        if(*cnt==0)
        {
            tomb[0]=e;
        }
        else
        {
            for(int i=0; i<min(*cnt,EREDMENYEKSZAMA); i++)
            {
                if (pontszamito(tomb[i]) > pontszam)
                {
                    index++;
                }
            }
            if (index<EREDMENYEKSZAMA)
            {
                beszur(tomb,e,index);
            }
        }
        (*cnt)++;

    }
}


void beszur(eredmeny* tomb, eredmeny e, int index)
{
    for(int i=EREDMENYEKSZAMA-1; i>index; i--){
        tomb[i]=tomb[i-1];
    }
    tomb[index]=e;
}

double pontszamito(eredmeny e)
{
    return (double)e.aknakszama/(e.magas*e.szeles*(e.ido+1))*10000;
}

bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer)
{
    /* Ez tartalmazza az aktualis szerkesztest */
    char composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    composition[0] = '\0';
    /* Ezt a kirajzolas kozben hasznaljuk */
    char textandcomposition[hossz + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];
    /* Max hasznalhato szelesseg */
    int maxw = teglalap.w - 2;
    int maxh = teglalap.h - 2;

    dest[0] = '\0';

    bool enter = false;
    bool kilep = false;

    SDL_StartTextInput();
    while (!kilep && !enter)
    {
        /* doboz kirajzolasa */
        boxRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, hatter.r, hatter.g, hatter.b, 255);
        rectangleRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, szoveg.r, szoveg.g, szoveg.b, 255);
        /* szoveg kirajzolasa */
        int w;
        strcpy(textandcomposition, dest);
        strcat(textandcomposition, composition);
        if (textandcomposition[0] != '\0')
        {
            SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, textandcomposition, szoveg);
            SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
            SDL_Rect cel = { teglalap.x, teglalap.y, felirat->w < maxw ? felirat->w : maxw, felirat->h < maxh ? felirat->h : maxh };
            SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
            SDL_FreeSurface(felirat);
            SDL_DestroyTexture(felirat_t);
            w = cel.w;
        }
        else
        {
            w = 0;
        }
        /* kurzor kirajzolasa */
        if (w < maxw)
        {
            vlineRGBA(renderer, teglalap.x + w + 2, teglalap.y + 2, teglalap.y + teglalap.h - 3, szoveg.r, szoveg.g, szoveg.b, 192);
        }
        /* megjeleniti a képernyon az eddig rajzoltakat */
        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        /* Kulonleges karakter */
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_BACKSPACE)
            {
                int textlen = strlen(dest);
                do
                {
                    if (textlen == 0)
                    {
                        break;
                    }
                    if ((dest[textlen-1] & 0x80) == 0x00)
                    {
                        /* Egy bajt */
                        dest[textlen-1] = 0x00;
                        break;
                    }
                    if ((dest[textlen-1] & 0xC0) == 0x80)
                    {
                        /* Bajt, egy tobb-bajtos szekvenciabol */
                        dest[textlen-1] = 0x00;
                        textlen--;
                    }
                    if ((dest[textlen-1] & 0xC0) == 0xC0)
                    {
                        /* Egy tobb-bajtos szekvencia elso bajtja */
                        dest[textlen-1] = 0x00;
                        break;
                    }
                }
                while(true);
            }
            if (event.key.keysym.sym == SDLK_RETURN)
            {
                enter = true;
            }
            break;

        /* A feldolgozott szoveg bemenete */
        case SDL_TEXTINPUT:
            if (strlen(dest) + strlen(event.text.text) < hossz)
            {
                strcat(dest, event.text.text);
            }

            /* Az eddigi szerkesztes torolheto */
            composition[0] = '\0';
            break;

        /* Szoveg szerkesztese */
        case SDL_TEXTEDITING:
            strcpy(composition, event.edit.text);
            break;

        case SDL_QUIT:
            /* visszatesszuk a sorba ezt az eventet, mert
             * sok mindent nem tudunk vele kezdeni */
            SDL_PushEvent(&event);
            kilep = true;
            break;
        }
    }

    /* igaz jelzi a helyes beolvasast; = ha enter miatt allt meg a ciklus */
    SDL_StopTextInput();
    return enter;
}



