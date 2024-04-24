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
#define NbreMaxDEssais 10 // Attention à ne pas dépasser la hauteur de la console
// #define LongueurMaxNomJoueur 10 // Limité à 10 dans la DB
#define LongueurDesMots 4 // Prévoir un fichier liste_français_n avec des mots de n longueur
#define NbreDeScoresAAfficher 10  // Attention à ne pas dépasser la hauteur de la console
#endif