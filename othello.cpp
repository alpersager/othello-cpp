/*
 * othello.cpp
 *
 *  Created on: 17 May 2025
 *      Author: alper
 */

/**
 * Praktikum Informatik 1 MMXXV
 *
 * @file othello.cpp
 * Implementierung des Spiels Othello
 */

#include <iostream>
#include <cctype>
#include "config.h"
#include "test.h"
#include "othelloKI.h"

// Initialisierung des Spielfelds: 0 = leer, 1 = Spieler 1, 2 = Spieler 2
void initialisiereSpielfeld(int spielfeld[GROESSE_Y][GROESSE_X]) {
    for (int y = 0; y < GROESSE_Y; ++y)
        for (int x = 0; x < GROESSE_X; ++x)
            spielfeld[y][x] = 0;
    // Startaufstellung
    spielfeld[GROESSE_Y/2 - 1][GROESSE_X/2 - 1] = 1;
    spielfeld[GROESSE_Y/2    ][GROESSE_X/2    ] = 1;
    spielfeld[GROESSE_Y/2 - 1][GROESSE_X/2    ] = 2;
    spielfeld[GROESSE_Y/2    ][GROESSE_X/2 - 1] = 2;
}

// Ausgabe des Spielfelds
void zeigeSpielfeld(const int spielfeld[GROESSE_Y][GROESSE_X]) {
    std::cout << "   | ";
    for (int i = 0; i < GROESSE_X; ++i)
        std::cout << char('A' + i) << " | ";
    std::cout << "\n";

    for (int y = 0; y < GROESSE_Y; ++y) {
        for (int i = 0; i < GROESSE_X; ++i) std::cout << "---+";
        std::cout << "---+\n";
        std::cout << ' ' << (y + 1) << " |";
        for (int x = 0; x < GROESSE_X; ++x) {
            int f = spielfeld[y][x];
            if (f == 0)      std::cout << "   ";
            else if (f == 1) std::cout << " X ";
            else             std::cout << " O ";
            std::cout << "|";
        }
        std::cout << "\n";
    }
}

// Bestimme Gewinner (0 = unentschieden, 1 oder 2)
int gewinner(const int spielfeld[GROESSE_Y][GROESSE_X]) {
    int c1 = 0, c2 = 0;
    for (int y = 0; y < GROESSE_Y; ++y)
        for (int x = 0; x < GROESSE_X; ++x) {
            if (spielfeld[y][x] == 1) ++c1;
            else if (spielfeld[y][x] == 2) ++c2;
        }
    if (c1 > c2) return 1;
    if (c2 > c1) return 2;
    return 0;
}

// Position im Feld?
bool aufSpielfeld(const int posX, const int posY) {
    return posX >= 0 && posX < GROESSE_X
        && posY >= 0 && posY < GROESSE_Y;
}

// Pruefe, ob Zug gueltig ist
bool zugGueltig(const int spielfeld[GROESSE_Y][GROESSE_X],
                const int spieler,
                const int posX,
                const int posY) {
    if (!aufSpielfeld(posX, posY) || spielfeld[posY][posX] != 0)
        return false;
    int opp = (spieler == 1 ? 2 : 1);
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            int x = posX + dx, y = posY + dy;
            bool foundOpp = false;
            while (aufSpielfeld(x, y) && spielfeld[y][x] == opp) {
                x += dx; y += dy; foundOpp = true;
            }
            if (foundOpp && aufSpielfeld(x, y) && spielfeld[y][x] == spieler)
                return true;
        }
    }
    return false;
}

// Fuehre Zug aus und drehe Steine um
void zugAusfuehren(int spielfeld[GROESSE_Y][GROESSE_X],
                   const int spieler,
                   const int posX,
                   const int posY) {
    int opp = (spieler == 1 ? 2 : 1);
    spielfeld[posY][posX] = spieler;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            int x = posX + dx, y = posY + dy;
            bool foundOpp = false;
            while (aufSpielfeld(x, y) && spielfeld[y][x] == opp) {
                x += dx; y += dy; foundOpp = true;
            }
            if (foundOpp && aufSpielfeld(x, y) && spielfeld[y][x] == spieler) {
                int fx = posX + dx, fy = posY + dy;
                while (fx != x || fy != y) {
                    spielfeld[fy][fx] = spieler;
                    fx += dx; fy += dy;
                }
            }
        }
    }
}

// Zaehle moegliche Zuege
int moeglicheZuege(const int spielfeld[GROESSE_Y][GROESSE_X],
                   const int spieler) {
    int cnt = 0;
    for (int y = 0; y < GROESSE_Y; ++y)
        for (int x = 0; x < GROESSE_X; ++x)
            if (zugGueltig(spielfeld, spieler, x, y)) ++cnt;
    return cnt;
}

// Menschlicher Zug ueber Konsole
bool menschlicherZug(int spielfeld[GROESSE_Y][GROESSE_X],
                     const int spieler) {
    if (moeglicheZuege(spielfeld, spieler) == 0) return false;
    int posX, posY; char c;
    do {
        std::cout << "Dein Zug (z.B. A1): "; std::cin >> c >> posY;
        posX = std::toupper(c) - 'A'; posY -= 1;
    } while (!zugGueltig(spielfeld, spieler, posX, posY));
    zugAusfuehren(spielfeld, spieler, posX, posY);
    return true;
}

// Hauptspielschleife
void spielen(const int spielerTyp[2]) {
    int spielfeld[GROESSE_Y][GROESSE_X];
    initialisiereSpielfeld(spielfeld);
    int cur = 1;
    while (moeglicheZuege(spielfeld,1) > 0 || moeglicheZuege(spielfeld,2) > 0) {
        zeigeSpielfeld(spielfeld);
        // moved variable entfernt, direkter Aufruf:
        if (spielerTyp[cur-1] == MENSCH)
            menschlicherZug(spielfeld, cur);
        else
            computerZug(spielfeld, cur);
        cur = (cur == 1 ? 2 : 1);
    }
    zeigeSpielfeld(spielfeld);
    int w = gewinner(spielfeld);
    if (w == 0)      std::cout << "Unentschieden!\n";
    else if (w == 1) std::cout << "Spieler X gewinnt!\n";
    else             std::cout << "Spieler O gewinnt!\n";
}

int main() {
    if (TEST == 1) {
        bool ok = ganzenTestAusfuehren();
        std::cout << (ok
            ? "ALLE TESTS BESTANDEN!\n"
            : "MINDESTENS EIN TEST FEHLGESCHLAGEN!\n");
        if (!ok) return 1;
    }
    int spielerTyp[2] = { COMPUTER, COMPUTER };
    spielen(spielerTyp);

    return 0;
}


