//
// Created by BruceWayne on 2018. 11. 09..
//

#include <stdlib.h>
#include <stdio.h>


#include "palya.h"


cella **palyafoglal(adatok datas) {
    int height=datas.magassag;
    int width=datas.szelesseg;
    cella **palya;
    palya = (cella **) malloc(height * sizeof(cella *));
    palya[0] = (cella *) malloc(height * width * sizeof(cella));
    for (int y = 1; y < height; y++) {
        palya[y] = palya[0] + y * width;
    }
    return palya;
}

void palyainicializalo(cella **palya, adatok datas, int ertek) {
    int magassag=datas.magassag;
    int szelesseg=datas.szelesseg;
    for (int m = 0; m < magassag; m++) {
        for (int sz = 0; sz < szelesseg; sz++) {
            palya[m][sz].allapot = ertek;
            palya[m][sz].flagged = ertek;
        }
    }
}

int tartalmaz_akna(cella **palya, int magassag, int szelesseg) {
    if (palya[magassag][szelesseg].ertek == 9)
        return 1;
    return 0;
}

void aknaszoro(cella **palya, adatok datas) {
    int magassag=datas.magassag;
    int szelesseg=datas.szelesseg;
    int akna_db=datas.aknakszama;
    int db = 0;
    int m, sz;
    while (db < akna_db) {
        m = rand() % magassag;
        sz = rand() % szelesseg;
        if (tartalmaz_akna(palya, m, sz) != 1) {
            palya[m][sz].ertek = 9;
            db += 1;
        }
    }
}

int kornyezoaknak(cella **palya, int m, int sz, int magassag, int szelesseg) {
    int db = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            //saját maga-e?
            if (dy == 0 && dx == 0)
                continue;

            if (0 <= m + dy && m + dy < magassag && 0 <= sz + dx && sz + dx < szelesseg) {
                if (palya[m + dy][sz + dx].ertek == 9) {
                    db += 1;
                }
            }
        }
    }
    return db;
}

void palyakitolto(cella **palya, adatok datas) {
    int magassag=datas.magassag;
    int szelesseg=datas.szelesseg;
    for (int m = 0; m < magassag; m++) {
        for (int sz = 0; sz < szelesseg; sz++) {
            if (palya[m][sz].ertek != 9) {
                palya[m][sz].ertek = kornyezoaknak(palya, m, sz, magassag, szelesseg);
            }
        }
    }
}

int cellaallapot(cella **palya, int magassag, int szelesseg) {
    if (palya[magassag][szelesseg].allapot)
        return 1;
    return 0;
}

int vaneures(cella **palya, int m, int sz, int magassag, int szelesseg) {
    int db = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dy != 0 || dx != 0) {
                if (0 <= m + dy && m + dy < magassag && 0 <= sz + dx && sz + dx < szelesseg) {
                    if (palya[m + dy][sz + dx].ertek == 0) {
                        db += 1;
                    }
                }
            }
        }
    }
    if (db != 0) {
        return 1;
    }
    return 0;
}



void felderit(cella **palya, int m, int sz, int magassag, int szelesseg) {
    if (vaneures(palya, m, sz, magassag, szelesseg) != 1) {
        return;
    } else {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dy != 0 || dx != 0) {
                    if (0 <= m + dy && m + dy < magassag && 0 <= sz + dx && sz + dx < szelesseg) {
                        if (palya[m + dy][sz + dx].ertek != 9) {
                            felfed(palya, m + dy, sz + dx, magassag, szelesseg);
                        }
                    }
                }
            }
        }
    }
};

bool felfed(cella **palya, int m, int sz, int magassag, int szelesseg) {
    if(palya[m][sz].flagged!=1){
        if (palya[m][sz].allapot == 0) {
        palya[m][sz].allapot = 1;
        if (tartalmaz_akna(palya, m, sz)) {
            return true;
        }
        if (palya[m][sz].ertek == 0) {
            felderit(palya, m, sz, magassag, szelesseg);
        }
    }
    }

    return false;
}


bool nyerte(cella **palya, adatok datas) {
    int db = 0;
    int osszes = datas.magassag * datas.szelesseg - datas.aknakszama;
    for (int m = 0; m < datas.magassag; m++) {
        for (int sz = 0; sz < datas.szelesseg; sz++) {
            if (cellaallapot(palya, m, sz))
                db += 1;
        }
    }
    if (osszes == db)
        return true;
    return false;
}


