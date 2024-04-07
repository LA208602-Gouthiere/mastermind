#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

#ifndef _DICO_COMMON
#define _DICO_COMMON

// Structure pour stocker un message d'erreur à renvoyer
// et toute autre information utile qui l'accompagne
struct Dico_Message {
    char messageErreur[200];
    int codeErreur;
};

// Constantes du jeu
#define NbreMaxDEssais 10
#define LongueurMaxNomJoueur 10
#define LongueurDesMots 4
#define NbreDeScoresAAfficher 10
#endif