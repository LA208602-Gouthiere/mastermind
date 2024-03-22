#include <time.h>
#include <unistd.h>
#include <ncurses.h>

// Definition des caractères de bordures pour les cadres autour des mots
#ifndef _ECRAN_CONST
static const int NombreDeTabulationAGauche = 3;

// Definition d'aliases pour les codes de couleurs (dépassement)
#define COULEURS_CONTOUR 1
#define COULEURS_MOT 2
#define COULEURS_BIENPLACE 3
#define COULEURS_QUESTION 3
#define COULEURS_MALPLACE 4
#define COULEURS_ERREUR 4
#endif

// Déclaration des fonctions du module
//void ChoisirModeEcran(bool couleur);
void InitialiserEcran();
void TerminerEcran();
void EffacerEcran();
void RetourALaLigne();
void AfficherTexteIndenteSansRetour(char *texteAAfficher);
void AfficherTexteSansRetour(char *texteAAfficher);
void AfficherCharSansRetour(unsigned char caractereAAfficher, int repetition);
void AfficherNombreSansRetour(int nombreAAfficher);
void AfficherCharSpecialSansRetour(unsigned char caractereAAfficher, int repetition);
void AfficherTexteDansCadre(char *texteAAfficher);
void AfficherErreurEtTerminer(char *texteDErreur, int codeDErreur);
void AfficherHautDeJeu();
void AfficherSeparateurDeJeu();
void AfficherMotDeJeu(char *motAAfficher, int nbreLettresBienplacées, int nbreLettresMalplacées);
void AfficherBasDeJeu();