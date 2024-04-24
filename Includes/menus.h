// Fonctions publiques
#include "./common.h"
// Contiennent les structures
#include "./partie.h"
#include "./mots.h"

#ifndef MENUS_H
#define MENUS_H

void AfficherMenuPrincipal(int lin, int col, struct Partie * partie, struct Dictionnaire * dictionnaire);
void AfficherMenuParametres(int lin, int col);
void RunDifficultiesMenu(int lin, int col);
void AfficherMenuCouleurs(int lin, int col);
void AfficherMenuConfirmationSuppressionDB(int lin, int col);

#endif