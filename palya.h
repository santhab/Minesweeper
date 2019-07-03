
//
// Created by BruceWayne on 2018. 11. 09..
//
#ifndef palya_h
#define palya_h

#include <stdbool.h>

typedef struct adatok{
    int magassag;
    int szelesseg;
    int aknakszama;
    bool mehet;
}adatok;

typedef struct cella {
    int ertek;
    int allapot; //0 ha lefedett, 1 ha feltárt
    int flagged; //0 ha nem, 1 ha igen
} cella;


//ez a fuggvény foglal dinamikusan egy 2d-s tömböt, FONTOS: A hívónak fel kell szabadítania.
cella** palyafoglal(adatok datas);

//ez a függvény állítja be a cellákat alapértelmezetten valamilyen allapotúra, (0 lefedett, 1 felfedett)
void palyainicializalo(cella **palya, adatok datas, int ertek);

//a függvény visszaadja a paraméterként meghatározott celláról hogy tartalmaz-e aknát,
// ha tartalmaz 1, ha nem akkor 0-al tér vissza
int tartalmaz_akna(cella **palya, int magassag, int szelesseg);

/*A függvény paraméterként kapott számú aknát szór el a pályán véletlenszerûen*/
void aknaszoro(cella **palya, adatok datas);

//ez a függvény megmondja egy konkrét celláról, hogy a környezetében mennyi akna van
//meg kell adni hogy konkrétan melyik cella környezetét vizsgáljuk(m,sz)
//és hogy mekkora a pálya méretei(magassag, szelesseg
int kornyezoaknak(cella **palya, int m, int sz, int magassag, int szelesseg);

//ezzel a függvénnyel töltjük fel a nem aknás cellákat a megfelelõ egész számokkal,
//amelyek azt jelzik, hogy a környezetükben mennyi akna van
void palyakitolto(cella **palya,adatok datas);

//ez a függvény visszadja hogy a cella felfedett-e vagy sem
int cellaallapot(cella **palya, int magassag, int szelesseg);

//megmondja egy konkrét celláról hogy a környezetében van-e üres cella
//ha van üres, akkor 1-et ad, ha nincs akkor 0-t
int vaneures(cella **palya, int m, int sz, int magassag, int szelesseg);


//ennek a függvénynek adjuk meg paraméterül, hogy pontosan melyik cellát akarjuk felfedni,(m,sz)
//meg kell adni a pálya méreteit is neki az általa hívott függvények miatt(magasság, szélesség)
bool felfed(cella **palya, int m, int sz, int magassag, int szelesseg);

//ez a függvény felderít egy üres cella (m,sz) környezetében lévõ többi üres cellákat is
//paraméterként meg kell kapja a pálya magasságát és szélességét is,
// mert az általa hívott segédfüggvényeknek szüksége lesz rá
void felderit(cella **palya, int m,int sz, int magassag, int szelesseg);


bool nyerte(cella **palya, adatok datas);




#endif //palya_h
