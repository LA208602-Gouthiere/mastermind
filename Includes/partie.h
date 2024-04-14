// Fonctions publiques
#include "./common.h"
#include "./mots.h"

#ifndef _DICO_PARTIE
#define _DICO_PARTIE

/*
    La stucture contient tout le jeu en cours:
    - solution à trouver
    - liste des mots essayés
    - résultats des essais
    - nom du joureur
    - numéro de l'essai en cours
    - résultat: victoire (true) ou abandon (false)
*/ 

struct Partie {
    char * solution;
    char ** motsEssayes;
    struct ResultatLigne ** resultatsEssais;
    char nomJoueur[11];
    int numEssaiCourant;
    bool resultat;
};
#endif

struct Partie *CreerPartie(struct Dictionnaire *dictionnaire);
void EffacerPartie(struct Partie *partieEnCours);
bool JouerPartie(struct Partie *partieEnCours);
void AfficherPartie(struct Partie *partieEnCours, bool modeDebug);
void AfficherMeilleursScores();