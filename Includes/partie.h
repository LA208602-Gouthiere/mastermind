// Fonctions publiques
#include "./common.h"
#include "./mots.h"

#ifndef _DICO_PARTIE
#define _DICO_PARTIE
struct Partie
{
    // A COMPLETER (Cf. LPP2 structures)
    // La stucture contient tout le jeu en cours:
    // - solution à trouver
    // - liste des mots essayés
    // - résultats des essais
    // - nom du joureur
    // - numéro de l'essai en cours
    // - résultat: victoire ou abandon
};
#endif

struct Partie *CreerPartie(struct Dictionnaire *dictionnaire);
void EffacerPartie(struct Partie *partieEnCours);
bool JouerPartie(struct Partie *partieEnCours);
void AfficherPartie(struct Partie *partieEnCours, bool modeDebug);
void AfficherMeilleursScores();