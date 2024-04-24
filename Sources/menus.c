#include "../Includes/menus.h"
#include "../Includes/ecran.h"
#include "../Includes/affichermenu.h"
#include "../Includes/afficherregles.h"
#include "../Includes/titre.h"
#include "../Includes/score.h"

/// @brief Affiche le menu principal
/// @param lin numéro de ligne à l'origine
/// @param col numéro de colonne à l'origine
void AfficherMenuPrincipal(int lin, int col, struct Partie * partie, struct Dictionnaire * dictionnaire){
    
    bool finPartie;
    int choix;
    char * listeChoix[5] = {"Jouer", "Classement", "Règles", "Paramètres", "Quitter"};
    struct Dico_Message *messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    
    do {
        // Affiche le titre au dessus du menu
        EffacerEcran();
        refresh();
        AfficherTitre(lin - 10, col, false);

        // Vérifie l'affichage du menu
        choix = AfficherMenu(lin, col, "Menu principal", listeChoix, 5, messageDeRetour);
        if (choix == -1){
            AfficherErreurEtTerminer(messageDeRetour->messageErreur, messageDeRetour->codeErreur);
        }
        
        // Exécute l'action liée au choix
        switch (choix){
            case 0: // Lancement de la partie
                do {
                    partie = CreerPartie(dictionnaire);
                    finPartie = JouerPartie(partie);
                    EffacerPartie(partie);
                    AfficherMeilleursScores();
                } while(finPartie); // Lance une nouvelle partie si la précédente est terminée et qu'elle n'a pas été abandonnée
                break;

            case 1:
                AfficherMeilleursScores();
                break;
            case 2:
                AfficherRegles(lin-12, col-6);
                break;
            case 3:
                AfficherMenuParametres(lin, col);
                break;
        }
    } while (choix != 4); // Continue à afficher le menu principal tant que "Quitter" n'est pas sélectionné

    // Vide le dico d'erreur
    free(messageDeRetour);
}

/// @brief Affiche le menu paramètres
/// @param lin numéro de ligne à l'origine
/// @param col numéro de colonne à l'origine
void AfficherMenuParametres(int lin, int col){

    int choix;
    char * settingsMenuChoices[3] = {"Changer les couleurs", "Réinitialiser le classement", "Retour"};
    struct Dico_Message *messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));

    do {
        // Vérifie l'affichage du menu
        choix = AfficherMenu(lin, col, "Paramètres", settingsMenuChoices, 3, messageDeRetour);
        if (choix == -1){
            AfficherErreurEtTerminer(messageDeRetour->messageErreur, messageDeRetour->codeErreur);
        }
        
        switch (choix){
            case 0:
                AfficherMenuCouleurs(lin, col);
                break;
            case 1:
                AfficherMenuConfirmationSuppressionDB(lin, col);
                break;
        }
    } while (choix != 2); // Continue à afficher le menu paramètres tant que "Quitter" n'est pas sélectionné

    // Vide le dico d'erreur
    free(messageDeRetour);
}

/// @brief Affiche le menu des couleurs
/// @param lin numéro de ligne à l'origine
/// @param col numéro de colonne à l'origine
void AfficherMenuCouleurs(int lin, int col){
    int choix;
    char * listeChoix[3] = {"Monochrome", "Couleurs", "Retour"};
    struct Dico_Message *messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));

    do {
        // Vérifie l'affichage du menu
        choix = AfficherMenu(lin, col, "Affichage des couleurs", listeChoix, 3, messageDeRetour);
        if (choix == -1){
            AfficherErreurEtTerminer(messageDeRetour->messageErreur, messageDeRetour->codeErreur);
        }
        
        switch (choix){
            case 0:
                ChoisirModeEcran(false);
                break;
            case 1:
                ChoisirModeEcran(true);
                break;
        }
    } while (choix != 2); // Continue à afficher le menu couleurs tant que "Quitter" n'est pas sélectionné

    // Vide le dico d'erreur
    free(messageDeRetour);
}

/// @brief Affiche le menu de confirmation de la suppression de la DB
/// @param lin numéro de ligne à l'origine
/// @param col numéro de colonne à l'origine
void AfficherMenuConfirmationSuppressionDB(int lin, int col){
    int choix;
    char * listeChoix[2] = {"Oui", "Non"};
    struct Dico_Message *messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));

    // Vérifie l'affichage du menu
    choix = AfficherMenu(lin, col, "Êtes-vous sûr de supprimer les scores ?", listeChoix, 2, messageDeRetour);
    if (choix == -1){
        AfficherErreurEtTerminer(messageDeRetour->messageErreur, messageDeRetour->codeErreur);
    }
    
    // Supprime les score si Oui est sélectionné
    if (choix == 0){
        if (!SupprimerScores(false, messageDeRetour))
            AfficherErreurEtTerminer(messageDeRetour->messageErreur, messageDeRetour->codeErreur);
    }

    // Vide le dico d'erreur
    free(messageDeRetour);
}