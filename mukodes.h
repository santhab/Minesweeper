#ifndef mukodes_h
#define mukodes_h

    jatekallas jatek(cella** palya,SDL_Renderer* renderer, SDL_Window* window, adatok datas, icondatas* icon,int* elteltido);

    bool gameover(void);

    void jobbklikk(cella** palya,int m, int sz,SDL_Renderer* renderer, icondatas* icon);

    void torolminden(cella** palya, SDL_Window* window, SDL_Renderer* renderer,icondatas* icon);
#endif // mukodes_h
