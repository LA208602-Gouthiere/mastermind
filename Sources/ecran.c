#include "../Includes/common.h"
#include "../Includes/ecran.h"

// ***************************************//
// FONCTIONS DECLAREES DANS LE FICHIER .h //
// ***************************************//


/// @brief Initialise la console ncurses
void InitialiserEcran(){
    initscr();
}

/// @brief Terminer la console ncurses
void TerminerEcran(){
    endwin();
}

// Efface l'écran de la console ncurses
void EffacerEcran(){
    clear();
}

/// @brief Va à la ligne dans la console ncurses
void RetourALaLigne() {
    addch('\n');
}

/// @brief Affiche dans la console ncurses un texte avec indentation à partir de la position courante sans retour à la ligne
/// @param texteAAfficher chaine de caracteres à afficher (pointeur)
void AfficherTexteIndenteSansRetour(char *texteAAfficher){
    printw("\t%s", texteAAfficher);
}

/// @brief Affiche une chaine de caracteres à la position courante dans la console ncurses sans retour à la ligne
/// @param texteAAfficher chaine de caracteres à afficher (pointeur)
void AfficherTexteSansRetour(char *texteAAfficher){
    printw("%s", texteAAfficher);
}

/// @brief Affiche une chaine de caracteres à la position courante dans la console ncurses sans retour à la ligne
/// @param texteAAfficher chaine de caracteres à afficher (pointeur)
void AfficherMotEspaceSansRetour(char *texteAAfficher){
    printw("%s", texteAAfficher);
}

/// @brief Affiche un caractere à la position courante dans la console ncurses sans retour à la ligne
/// @param caractereAAfficher le caractère à afficher
/// @param repetition le nombre de fois qu'il faut le répéter
void AfficherCharSansRetour(unsigned char caractereAAfficher, int repetition){
    for (int carPos = 0; carPos < repetition; carPos++){
        addch(caractereAAfficher);
    } 
}

/// @brief Affiche un nombre entier à la position courante dans la console ncurses sans retour à la ligne
/// @param nombreAAfficher le nombre à afficher
void AfficherNombreSansRetour(int nombreAAfficher){
    printw("%d", nombreAAfficher);
}

/// @brief Affiche un caractère spécial à la position courante dans la console ncurses sans retour à la ligne
///        Cette fonction permet notamment de dessiner des bordures/contours
/// @param caractereAAfficher le caractere a traduire en code special
/// @param repetition le nombre de fois qu'il faut le répeter
void AfficherCharSpecialSansRetour(unsigned char caractereAAfficher, int repetition){
    for (int carPos = 0; carPos < repetition; carPos++){
        addch(NCURSES_ACS(caractereAAfficher));
    }
}

/// @brief Affiche dans la console ncurses un texte dans un cadre indente d'une tabulation
/// @param texteAAfficher la chaine de caracteres à afficher dans le cadre (pointeur)
void AfficherTexteDansCadre(char * texteAAfficher){
    
    int lenText = strlen(texteAAfficher);

    // Haut du cadre
    AfficherCharSansRetour('\t', 1);
    AfficherCharSpecialSansRetour(ACS_ULCORNER, 1);
    AfficherCharSpecialSansRetour(ACS_HLINE, lenText);
    AfficherCharSpecialSansRetour(ACS_URCORNER, 1);

    // Milieu et texte
    RetourALaLigne();
    AfficherCharSansRetour('\t', 1);
    AfficherCharSpecialSansRetour(ACS_VLINE, 1);
    printw("%s", texteAAfficher);
    AfficherCharSpecialSansRetour(ACS_VLINE, 1);

    // Bas du cadre
    RetourALaLigne();
    AfficherCharSansRetour('\t', 1);
    AfficherCharSpecialSansRetour(ACS_LLCORNER, 1);
    AfficherCharSpecialSansRetour(ACS_HLINE, lenText);
    AfficherCharSpecialSansRetour(ACS_LRCORNER, 1);

}

/// @brief Efface l'écran, affiche "Erreur" dans un cadre, affiche un message et un code d'erreur sous le cadre,
///        attend 5 secondes puis termine l'application
/// @param texteDErreur Le texte d'erreur
/// @param codeDErreur Le code d'erreur eventuel
void AfficherErreurEtTerminer(char *texteDErreur, int codeDErreur){
    EffacerEcran();
    AfficherTexteDansCadre("Erreur");
    RetourALaLigne();
    AfficherTexteIndenteSansRetour(texteDErreur);
    RetourALaLigne();
    AfficherTexteIndenteSansRetour("Code d'erreur : ");
    AfficherNombreSansRetour(codeDErreur);
    refresh();
    sleep(5);
    TerminerEcran();
    exit(EXIT_FAILURE);
}

/// @brief Affiche le haut du cadre de jeu (bordure supérieure)
/// @param motAAfficher Mot à afficher, ou NULL si rien ne doit etre affiché
void AfficherHautDeJeu(char * motAAfficher){

    AfficherCharSansRetour('\t', 3);
    AfficherCharSpecialSansRetour(ACS_ULCORNER, 1);
    if (motAAfficher){

        // Affiche mot avec espaces
        AfficherCharSansRetour(' ', 1);
        for (int carPos = 0; carPos < 4; carPos++){
            AfficherCharSansRetour(motAAfficher[carPos], 1);
            AfficherCharSansRetour(' ', 1);
        }

    } else {
        AfficherCharSpecialSansRetour(ACS_HLINE, 9);
    }
    AfficherCharSpecialSansRetour(ACS_TTEE, 1);
    AfficherCharSpecialSansRetour(ACS_HLINE, 4);
    AfficherCharSpecialSansRetour(ACS_URCORNER, 1);
    RetourALaLigne();
}

/// @brief Affiche un mot du jeu et son resultat
/// @param motAAfficher 
/// @param nbreLettresBienplacées Un '+' par lettre bien placée
/// @param nbreLettresMalplacées Un '-' par lettre mal placée
void AfficherMotDeJeu(char *motAAfficher, int nbreLettresBienplacées, int nbreLettresMalplacées)
{
    AfficherCharSansRetour('\t', 3);
    AfficherCharSpecialSansRetour(ACS_VLINE, 1);

    // Affiche mot avec espaces
    AfficherCharSansRetour(' ', 1);
    for (int carPos = 0; carPos < 4; carPos++){
        AfficherCharSansRetour(motAAfficher[carPos], 1);
        AfficherCharSansRetour(' ', 1);
    }

    // Affiche symboles
    AfficherCharSpecialSansRetour(ACS_VLINE, 1);
    AfficherCharSansRetour('+', nbreLettresBienplacées);
    AfficherCharSansRetour('-', nbreLettresMalplacées);
    AfficherCharSansRetour(' ', 4 - nbreLettresBienplacées - nbreLettresMalplacées); // Complète avec des espaces
    AfficherCharSpecialSansRetour(ACS_VLINE, 1);
    RetourALaLigne();
}

/// @brief Affiche un separateur entre deux mots du jeu
void AfficherSeparateurDeJeu(){

    AfficherCharSansRetour('\t', 3);
    AfficherCharSpecialSansRetour(ACS_LTEE, 1);
    AfficherCharSpecialSansRetour(ACS_HLINE, 9);
    AfficherCharSpecialSansRetour(ACS_PLUS, 1);
    AfficherCharSpecialSansRetour(ACS_HLINE, 4);
    AfficherCharSpecialSansRetour(ACS_RTEE, 1);
    RetourALaLigne();
}

// Affiche la bordure inférieure du jeu
void AfficherBasDeJeu()
{
    AfficherCharSansRetour('\t', 3);
    AfficherCharSpecialSansRetour(ACS_LLCORNER, 1);
    AfficherCharSpecialSansRetour(ACS_HLINE, 9);
    AfficherCharSpecialSansRetour(ACS_BTEE, 1);
    AfficherCharSpecialSansRetour(ACS_HLINE, 4);
    AfficherCharSpecialSansRetour(ACS_LRCORNER, 1);
    RetourALaLigne();
}
