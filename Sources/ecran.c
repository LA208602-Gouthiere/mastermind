#include "../Includes/common.h"
#include "../Includes/ecran.h"

// ***************************************//
// FONCTIONS DECLAREES DANS LE FICHIER .h //
// ***************************************//

// Initialise la console ncurses
void InitialiserEcran()
{
    // A CODER, cf. cours LPP2 ncurses
}

// Terminer la console ncurses
void TerminerEcran()
{
    // A CODER, cf. cours LPP2 ncurses
}

// Efface l'ecran de la console ncurses
void EffacerEcran()
{
    // A CODER, cf. cours LPP2 ncurses
}

// Va a la ligne dans la console ncurses
void RetourALaLigne()
{
    // A CODER, cf. cours LPP2 ncurses
}

// Affiche dans la console ncurses un texte avec indentation
// a partir de la position courante
// sans retour a la ligne
// Paramètres:
// - la chaine de caracteres a afficher (pointeur)
void AfficherTexteIndenteSansRetour(char *texteAAfficher)
{
    // A CODER, cf. cours LPP2 ncurses
}

// Affiche une chaine de caracteres a la position courante dans la console ncurses
// sans retour a la ligne
// Paramètres:
// - la chaine de caracteres a afficher (pointeur)
void AfficherTexteSansRetour(char *texteAAfficher)
{
    // A CODER, cf. cours LPP2 ncurses
}

// Affiche un caractere a la position courante dans la console ncurses
// sans retour a la ligne
// Paramètres:
// - le caractere a afficher
// - le nombre de fois qu'il faut le repeter
void AfficherCharSansRetour(unsigned char caractereAAfficher, int repetition)
{
    // A CODER, cf. cours LPP2 ncurses
}

// Affiche un nombre entier a la position courante dans la console ncurses
// sans retour a la ligne
// Paramètres:
// - le nombre a afficher
void AfficherNombreSansRetour(int nombreAAfficher)
{
    // A CODER, cf. cours LPP2 ncurses
}

// Affiche un caractere special a la position courante dans la console ncurses
// sans retour a la ligne
// Cette fonction permet notamment de dessiner des bordures/contours
// Liste des codes: https://invisible-island.net/ncurses/man/curs_addch.3x.html
// Paramètres:
// - le caractere a traduire en code special
// - le nombre de fois qu'il faut le repeter
void AfficherCharSpecialSansRetour(unsigned char caractereAAfficher, int repetition)
{
    // A CODER, cf. cours LPP2 ncurses
}

// Affiche dans la console ncurses un texte dans un cadre indente d'une tabulation
// Paramètres:
// - la chaine de caracteres a afficher dans le cadre (pointeur)
void AfficherTexteDansCadre(char *texteAAfficher)
{
    // A CODER, cf. labo4 LPP2 ncurses
}

// Cette fonction efface l'ecran, affiche "Erreur" dans un cadre
// affiche un message et un code d'erreur sous le cadre,
// attend 5 secondes puis termine l'application
// Paramètres:
// - Le texte d'erreur
// - Le code d'erreur eventuel
void AfficherErreurEtTerminer(char *texteDErreur, int codeDErreur)
{
    // FONCTIONS UTILISEES:
    // EffacerEcran()
    // AfficherTexteDansCadre
    // AfficherTexteSansRetour()
    // AfficherNombreSansRetour(codeDErreur)
    // RetourALaLigne()
    // sleep()
    // TerminerEcran()
    // exit(à)
}

// Affiche le haut du cadre de jeu (bordure supérieure)
// Paramètres:
// - Le mot à afficher, ou NULL si rien ne doit etre affiché
void AfficherHautDeJeu(char *motAAfficher)
{
    // Cf. LPP2 Labo 5, à compléter
}

// Affiche un separateur entre deux mots du jeu
void AfficherSeparateurDeJeu()
{
    // Cf. LPP2 Labo 5, à compléter
}

// Affiche un mot du jeu et son resultat
// - Un '+' par lettre bien placée
// - Un '-' par lettre mal placée
// - Des espaces pour compléter
void AfficherMotDeJeu(char *motAAfficher, int nbreLettresBienplacées, int nbreLettresMalplacées)
{
    // Cf. LPP2 Labo 5, à compléter
}

// Affiche la bordure inférieure du jeu
void AfficherBasDeJeu()
{
    // Cf. LPP2 Labo 5, à compléter
}
