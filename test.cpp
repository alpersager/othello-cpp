/*
 * test.cpp
 *
 *  Created on: 17 May 2025
 *      Author: alper
 */
/**
 * Praktikum Informatik 1 MMXXV
 *
 * @file test.cpp
 *
 * Stellt Funktionen zum Testen der Spielfunktionen zur Verfuegung
 */

#include <iostream>
#include "config.h"
#include "test.h"

extern void zeigeSpielfeld(const int spielfeld[GROESSE_Y][GROESSE_X]);
extern int gewinner(const int spielfeld[GROESSE_Y][GROESSE_X]);
extern bool aufSpielfeld(const int posX, const int posY);
extern bool zugGueltig(const int spielfeld[GROESSE_Y][GROESSE_X],
                       const int player,
                       const int posX,
                       const int posY);
extern void zugAusfuehren(int spielfeld[GROESSE_Y][GROESSE_X],
                          const int player,
                          const int posX,
                          const int posY);
extern int moeglicheZuege(const int spielfeld[GROESSE_Y][GROESSE_X],
                          const int player);

/**
 * @brief Funktion zum Testen der gewinner() Funktion.
 */
bool gewinnerTest(const int eingabefeld[GROESSE_Y][GROESSE_X],
                  const int richtig,
                  const int testNummer)
{
    std::cout << "Fuehre Test " << testNummer + 1
              << " fuer 'gewinner()' aus ..." << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;

    int ergebnis = gewinner(eingabefeld);
    if (ergebnis == richtig) {
        std::cout << "Test " << testNummer + 1
                  << " bestanden!" << std::endl << std::endl;
        return true;
    } else {
        std::cout << "Test " << testNummer + 1
                  << " fehlgeschlagen" << std::endl << std::endl;
        if (AUSFUEHRLICH == 1) {
            zeigeSpielfeld(eingabefeld);
            std::cout << "Berechnetes Ergebnis: " << ergebnis
                      << std::endl
                      << "Richtiges Ergebnis: " << richtig
                      << std::endl << std::endl;
        }
        return false;
    }
}

/**
 * @brief Funktion zum Testen der aufSpielfeld() Funktion.
 */
bool aufSpielfeldTest(const int posX,
                      const int posY,
                      const bool richtig,
                      const int testNummer)
{
    std::cout << "Fuehre Test " << testNummer + 1
              << " fuer 'aufSpielfeld()' aus ..." << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;

    bool ergebnis = aufSpielfeld(posX, posY);
    if (ergebnis == richtig) {
        std::cout << "Test " << testNummer + 1
                  << " bestanden!" << std::endl << std::endl;
        return true;
    } else {
        std::cout << "Test " << testNummer + 1
                  << " fehlgeschlagen" << std::endl << std::endl;
        return false;
    }
}

/**
 * @brief Funktion zum Testen der zugGueltig() Funktion.
 */
bool zugGueltigTest(const int eingabeFeld[GROESSE_Y][GROESSE_X],
                    const int spieler,
                    const int posX,
                    const int posY,
                    const bool richtig,
                    const int testNummer)
{
    std::cout << "Fuehre Test " << testNummer + 1
              << " fuer 'zugGueltig()' aus ..." << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;

    bool ergebnis = zugGueltig(eingabeFeld, spieler, posX, posY);
    if (ergebnis == richtig) {
        std::cout << "Test " << testNummer + 1
                  << " bestanden!" << std::endl << std::endl;
        return true;
    } else {
        std::cout << "Test " << testNummer + 1
                  << " fehlgeschlagen" << std::endl << std::endl;
        if (AUSFUEHRLICH == 1) {
            zeigeSpielfeld(eingabeFeld);
            std::cout << "Position: (" << posX
                      << "," << posY << ")" << std::endl << std::endl;
        }
        return false;
    }
}

/**
 * @brief Funktion zum Testen der zugAusfuehren() Funktion.
 */
bool zugAusfuehrenTest(int eingabeFeld[GROESSE_Y][GROESSE_X],
                       const int ergebnisFeld[GROESSE_Y][GROESSE_X],
                       const int spieler,
                       const int posX,
                       const int posY,
                       const int testNummer)
{
    std::cout << "Fuehre Test " << testNummer + 1
              << " fuer 'zugAusfuehren()' aus ..." << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;

    // Arbeitskopie anlegen
    int feld[GROESSE_Y][GROESSE_X];
    for (int y = 0; y < GROESSE_Y; ++y)
        for (int x = 0; x < GROESSE_X; ++x)
            feld[y][x] = eingabeFeld[y][x];

    // Testzug ausfuehren
    zugAusfuehren(feld, spieler, posX, posY);

    // Ergebniss vergleichen
    bool gleich = true;
    for (int y = 0; y < GROESSE_Y; ++y) {
        for (int x = 0; x < GROESSE_X; ++x) {
            if (feld[y][x] != ergebnisFeld[y][x]) {
                gleich = false;
                break;
            }
        }
        if (!gleich) break;
    }

    if (gleich) {
        std::cout << "Test " << testNummer + 1
                  << " bestanden!" << std::endl << std::endl;
        return true;
    } else {
        std::cout << "Test " << testNummer + 1
                  << " fehlgeschlagen" << std::endl << std::endl;
        if (AUSFUEHRLICH == 1) {
            std::cout << "Eingabe-Feld:" << std::endl;
            zeigeSpielfeld(eingabeFeld);
            std::cout << "Ergebnis-Feld:" << std::endl;
            zeigeSpielfeld(ergebnisFeld);
        }
        return false;
    }
}

/**
 * @brief Funktion zum Testen der moeglicheZuege() Funktion.
 */
bool moeglicheZuegeTest(const int eingabeFeld[GROESSE_Y][GROESSE_X],
                        const int spieler,
                        const int richtig,
                        const int testNummer)
{
    std::cout << "Fuehre Test " << testNummer + 1
              << " fuer 'moeglicheZuege()' aus ..." << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;

    int ergebnis = moeglicheZuege(eingabeFeld, spieler);
    if (ergebnis == richtig) {
        std::cout << "Test " << testNummer + 1
                  << " bestanden!" << std::endl << std::endl;
        return true;
    } else {
        std::cout << "Test " << testNummer + 1
                  << " fehlgeschlagen" << std::endl << std::endl;
        if (AUSFUEHRLICH == 1) {
            zeigeSpielfeld(eingabeFeld);
            std::cout << "Berechnetes Ergebnis: " << ergebnis
                      << " (korrekt: " << richtig << ")"
                      << std::endl << std::endl;
        }
        return false;
    }
}

/**
 * @brief Funktion, die alle Tests ausfuehrt.
 */
bool ganzenTestAusfuehren()
{
    bool gesamtErgebnis = true;

    // ---------- TESTE GEWINNER ---------- //
    {
        int eingabeFeld[3][8][8] = {
            {
                {1,2,1,2,1,2,1,2},
                {1,2,1,2,1,2,1,2},
                {1,2,1,2,1,2,1,2},
                {1,2,1,2,1,2,1,2},
                {1,2,1,2,1,2,1,2},
                {1,2,1,2,1,2,1,2},
                {1,2,1,2,1,2,1,2},
                {1,2,1,2,1,2,1,2}
            },
            {
                {1,1,2,1,1,2,1,1},
                {2,1,1,2,1,1,2,1},
                {1,2,1,1,2,1,1,2},
                {1,1,2,1,1,2,1,1},
                {2,1,1,2,1,1,2,1},
                {1,2,1,1,2,1,1,2},
                {1,1,2,1,1,2,1,1},
                {2,1,1,2,1,1,2,1}
            },
            {
                {1,2,2,1,2,2,1,2},
                {2,1,2,2,1,2,2,1},
                {2,2,1,2,2,1,2,2},
                {1,2,2,1,2,2,1,2},
                {2,1,2,2,1,2,2,1},
                {2,2,1,2,2,1,2,2},
                {1,2,2,1,2,2,1,2},
                {2,1,2,2,1,2,2,1}
            }
        };
        int korrektesErgebnis[3] = {0, 1, 2};

        for (int i = 0; i < 3; ++i) {
            if (!gewinnerTest(eingabeFeld[i],

                              korrektesErgebnis[i],
                              i))
                gesamtErgebnis = false;
        }
        std::cout << "Ende des Tests fuer 'gewinner()'"
                  << std::endl << std::endl;
    }

    // ---------- TESTE POSITION IM FELD ---------- //
    {
        int position[6][2] = {
            {2,3}, {0,8}, {-1,7},
            {2,-1}, {8,5}, {-1,8}
        };
        bool korrektesErgebnis[6] = {
            true, false, false,
            false, false, false
        };

        for (int i = 0; i < 6; ++i) {
            if (!aufSpielfeldTest(position[i][0],
                                  position[i][1],
                                  korrektesErgebnis[i],
                                  i))
                gesamtErgebnis = false;
        }
        std::cout << "Ende des Tests fuer 'aufSpielfeld()'"
                  << std::endl << std::endl;
    }

    // ---------- TESTE ZUG GUELTIG ---------- //
    {
        int eingabeFeld[7][8][8] = {
            {
                {1,0,2,0,0,1,1,1},
                {0,0,2,0,0,0,0,1},
                {0,0,0,0,0,1,2,2},
                {2,2,0,2,0,0,0,0},
                {0,0,0,0,0,2,2,0},
                {0,0,0,2,1,1,0,2},
                {1,0,0,1,0,0,0,0},
                {0,0,0,0,0,1,0,1}
            },
            {
                {1,0,2,0,0,1,1,1},
                {0,0,2,0,0,1,0,0},
                {0,0,2,0,0,2,1,1},
                {0,0,0,2,0,0,0,0},
                {0,0,0,0,0,2,2,0},
                {0,0,0,2,1,1,0,2},
                {1,0,0,1,0,0,0,0},
                {0,0,0,0,0,1,0,1}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,1,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,2,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,1,0,0,2,0,0,0},
                {0,0,0,0,0,0,1,0},
                {2,0,1,2,0,2,0,0},
                {0,2,0,2,2,2,2,2},
                {0,0,0,0,0,0,0,1},
                {1,0,0,0,0,2,2,2},
                {0,2,0,0,0,0,0,0},
                {0,1,0,1,1,1,0,0}
            },
            {
                {2,1,0,0,2,1,1,1},
                {0,2,0,0,0,0,0,0},
                {1,0,0,2,0,0,0,1},
                {0,1,1,1,0,1,0,0},
                {1,0,0,1,1,0,0,2},
                {0,0,0,0,0,0,0,1},
                {1,1,0,0,0,0,2,0},
                {1,1,2,0,0,2,2,1}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,0,0,1,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {1,2,2,2,2,2,2,2},
                {1,2,1,1,2,2,2,2},
                {1,1,1,2,2,2,2,2},
                {1,1,1,2,2,2,2,2},
                {1,1,1,1,2,2,2,2},
                {1,1,1,0,2,2,2,2},
                {1,0,0,0,2,0,0,2},
                {0,0,0,0,0,0,0,0}
            }
        };
        int spieler[7] = {1, 2, 2, 1, 2, 1, 1};
        int position[7][2] = {
            {2,3}, {0,3}, {4,3}, {3,4},
            {3,5}, {3,4}, {5,7}
        };
        bool korrektesErgebnis[7] = {
            false, false, false, true,
            true, false, false
        };

        for (int i = 0; i < 7; ++i) {
            if (!zugGueltigTest(eingabeFeld[i],
                                spieler[i],
                                position[i][0],
                                position[i][1],
                                korrektesErgebnis[i],
                                i))
                gesamtErgebnis = false;
        }
        std::cout << "Ende des Tests fuer 'zugGueltig()'"
                  << std::endl << std::endl;
    }

    // ---------- TESTE ZUG AUSFUEHREN ---------- //
    {
        int eingabeFeld[10][8][8] = {
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,1,2,2},
                {2,2,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,2,1,1},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,1,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,2,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,0},
                {0,0,0,2,0,2,0,0},
                {0,0,0,2,2,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,2,0,0,0,0},
                {0,0,0,1,0,1,0,0},
                {0,0,0,1,1,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,0,0,1,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,1,0,0,1,0},
                {0,0,0,2,0,2,0,0},
                {0,0,0,2,2,0,0,0},
                {0,1,2,0,2,2,1,0},
                {0,0,0,2,2,0,0,0},
                {0,0,0,1,0,1,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,2,0,0},
                {0,0,0,0,1,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,0,1,1,1,1,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,1,0,0,0,0,0,0},
                {0,1,0,0,0,0,2,1},
                {1,0,1,1,2,0,0,0},
                {0,0,1,0,0,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,1,0,1},
                {0,0,0,0,0,1,1,0},
                {0,0,0,0,0,1,0,0},
                {0,0,0,0,1,1,0,0},
                {0,0,0,1,0,1,0,0},
                {0,0,2,0,0,2,0,0},
                {0,1,0,0,0,1,0,0},
                {0,0,0,0,0,0,0,0}
            }
        };
        int ergebnisFeld[10][8][8] = {
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,1,2,2},
                {2,2,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,2,1,1},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,1,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,2,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,0},
                {0,0,0,2,0,1,0,0},
                {0,0,0,2,1,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,0,2,1,0,0,0},
                {0,0,0,2,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,0,1,1,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,1,0,0,1,0},
                {0,0,0,1,0,1,0,0},
                {0,0,0,1,1,0,0,0},
                {0,1,1,1,1,1,1,0},
                {0,0,0,1,1,0,0,0},
                {0,0,0,1,0,1,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,2,0,0},
                {0,0,0,0,2,0,0,0},
                {0,0,0,2,0,0,0,0},
                {0,0,2,1,1,1,1,0},
                {0,0,2,0,0,0,0,0},
                {0,0,2,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,1,0,0,0,0,0,0},
                {0,1,0,0,0,0,2,1},
                {1,2,2,2,2,0,0,0},
                {0,0,1,0,0,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,1,0,1},
                {0,0,0,0,0,1,1,0},
                {0,0,0,0,0,1,0,0},
                {0,0,0,0,1,1,0,0},
                {0,0,0,1,0,1,0,0},
                {0,0,2,0,0,2,0,0},
                {0,1,0,0,0,1,0,0},
                {0,0,0,0,0,0,0,0}
            }
        };
        int spielerZug[10] = {0,0,0,1,2,0,1,2,2,1};
        int positionZug[10][2] = {
            {0,0},{0,0},{0,0},{3,4},{3,5},
            {0,0},{3,4},{2,4},{1,4},{5,2}
        };

        for (int i = 0; i < 10; ++i) {
            if (!zugAusfuehrenTest(eingabeFeld[i],
                                   ergebnisFeld[i],
                                   spielerZug[i],
                                   positionZug[i][0],
                                   positionZug[i][1],
                                   i))
                gesamtErgebnis = false;
        }
        std::cout << "Ende des Tests fuer 'zugAusfuehren()'"
                  << std::endl << std::endl;
    }

    // ---------- TESTE MOEGLICHE ZUEGE ---------- //
    {
        int eingabeFeld[2][8][8] = {
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,1,2,0,0,0},
                {0,0,0,1,2,1,0,0},
                {0,0,0,2,1,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            },
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,2,1,0,0,0},
                {0,0,0,2,1,1,0,0},
                {0,0,0,2,1,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}
            }
        };
        int spielerMz[2] = {1, 1};
        int korrektesMz[2] = {4, 5};

        for (int i = 0; i < 2; ++i) {
            if (!moeglicheZuegeTest(eingabeFeld[i],
                                    spielerMz[i],
                                    korrektesMz[i],
                                    i))
                gesamtErgebnis = false;
        }
        std::cout << "Ende des Tests fuer 'moeglicheZuege()'"
                  << std::endl << std::endl;
    }

    return gesamtErgebnis;
}
