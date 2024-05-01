#include "../Includes/common.h"
#include "../Includes/ecran.h"
#include "../Includes/afficherregles.h"

/// @brief Affiche les règles
/// @param lin numéro de ligne à l'origine
/// @param col numéro de colonne à l'origine
/// @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un éventuel code d'erreur
/// @return false si l'affichage a échoué sinon true
bool AfficherRegles(int lin, int col, struct Dico_Message *messageDeRetour){
    
    int touchePressee;
    int noPage = 0;
    char * pages[] = {
        "1. Objectif du jeu :\n"
        "-------------------------------------------------------------------\n"
        "Le joueur doit deviner un mot de 4 lettres choisi au hasard par le jeu\n"
        "en maximum 10 tentatives.\n\n\n"
        "2. Déroulement du jeu :\n------------------------------------------------------------------\n"
        "• Le joueur propose un mot de 4 lettres.\n"
        "• Le jeu fournit des indices sous forme de + et - :\n"
        "    Chaque \"+\" indique qu'une lettre dans la proposition du joueur\n"
        "    se trouve dans la solution et est bien placée.\n"
        "    Chaque \"-\" indique qu'une lettre dans la proposition du joueur\n"
        "    se trouve dans la solution mais n'est pas à la bonne place.\n"
        "• Le joueur utilise ces indices pour affiner ses propositions.",

        "3. Fin du jeu :\n"
        "-------------------------------------------------------------------"
        "• Le joueur gagne s'il parvient à deviner le mot en maximum 10\n"
        "  tentatives.\n"
        "• Le joueur perd s'il épuise toutes ses tentatives sans avoir\n"
        "  deviné le mot.\n\n\n"
        "4. Exemples :\n"
        "-------------------------------------------------------------------"
        "Mot à trouver | Tentative | Résultat\n"
        "     abri     |    coup   |         \n"
        "     abri     |    papa   |  -      \n"
        "     abri     |    vert   |  +      \n"
        "     abri     |    mari   |  ++-    \n"
        "     abri     |    abri   |  ++++   \n",

        "                          × Anecdotes ×\n"
        "-------------------------------------------------------------------"
        "Le jeu est basé sur un jeu papier appelé Bulls and Cows. Une\n"
        "adaptation informatique a été réalisée dans les années 1960 sur le\n"
        "système informatique Titan de l'université de Cambridge, sous le\n"
        "nom de \"MOO\". Cette version a été écrite par Frank King.\n\n"
        "Mordecai Meirowitz, un expert en télécommunications d'Israël, a\n"
        "transformé ce concept en un produit commercial populaire dans les\n"
        "années 1970. C'est la société  Invicta Plastics qui a ensuite\n"
        "commercialisé le produit tel qu'on le connait.\n\n"
        "Donald Knuth, célèbre informaticien, a développé un algorithme de\n"
        "résolution en maximum 5 coup dans le cadre de son livre \""
        "The\nComputer as Master Mind\"."
    };

    // Cache le curseur et les caractères saisis
    curs_set(0);
    noecho();
    
    // Créé une structure fenêtre pour les règles
    WINDOW * bordureFenetre = newwin(20, 71, lin, col); // hauteur (on rajoute 2 pour les bordures), largeur, coord
    WINDOW * fenetre = newwin(16, 67, lin+2, col+2); // hauteur (on rajoute 2 pour les bordures), largeur, coord

    // Vérifie que les fenêtres ont bien été crées
    if(!bordureFenetre || !fenetre){
        strcpy(messageDeRetour->messageErreur, "Erreur lors de la création de la fenêtre des règles");
        messageDeRetour->codeErreur = 0;
        return false;
    }


    wattron(bordureFenetre, COLOR_PAIR(COULEURS_CONTOUR));
    box(bordureFenetre, 0, 0);
    
    mvwprintw(bordureFenetre, 0, 2, "[");
    wattron(bordureFenetre, COLOR_PAIR(COULEURS_MOT));
    wprintw(bordureFenetre, "Règles du jeu");
    wattron(bordureFenetre, COLOR_PAIR(COULEURS_CONTOUR));
    wprintw(bordureFenetre, "]");
    wattroff(bordureFenetre, COLOR_PAIR(COULEURS_CONTOUR));
    mvwprintw(fenetre, 0, 0, "%s", pages[0]);
    wattron(bordureFenetre, COLOR_PAIR(COULEURS_MOT));
    mvwprintw(bordureFenetre, 19, 3, " FLÈCHES pour naviguer ");
    mvwprintw(bordureFenetre, 19, 28, " ENTER pour revenir au menu ");
    mvwprintw(bordureFenetre, 19, 58, " Page 1/3 ");
    wattroff(fenetre, COLOR_PAIR(COULEURS_MOT));
    wrefresh(bordureFenetre);
    wrefresh(fenetre);

    // Permet l'utilisation des flèches du clavier dans la fenêtre
    keypad(fenetre, true);

    // Affiche l'option sélectionnée à chaque fois qu'une flèche est pressée
    do{
        touchePressee = wgetch(fenetre);
        if(touchePressee == KEY_UP || touchePressee == KEY_LEFT){
            if(noPage>0) noPage--;
        } else if (touchePressee == KEY_DOWN || touchePressee == KEY_RIGHT){
            if(noPage<2) noPage++;
        }
        wclear(fenetre);
        mvwprintw(fenetre, 0, 0, "%s", pages[noPage]);
        mvwprintw(bordureFenetre, 19, 58, " Page %d/3 ", noPage+1);
        wrefresh(bordureFenetre);

    } while (touchePressee != '\n'); // Quitte si ENTER est pressé
    
    // Efface et ferme les fenêtres
    wclear(fenetre);
    wclear(bordureFenetre);
    wrefresh(fenetre);
    wrefresh(bordureFenetre);

    // Supprime les fenêtres
    if (delwin(fenetre) == ERR || delwin(bordureFenetre) == ERR){
        strcpy(messageDeRetour->messageErreur, "Erreur lors de la suppression de la fenêtre des règles");
        messageDeRetour->codeErreur = 0;
        return false;
    }

    // Rétabli le curseur et l'affichage des caractères saisis
    curs_set(1);
    echo();

    return true;
}