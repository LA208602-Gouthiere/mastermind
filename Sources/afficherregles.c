#include "../Includes/ecran.h"
#include "../Includes/afficherregles.h"

/// @brief Affiche les règles
/// @param lin numéro de ligne à l'origine
/// @param col numéro de colonne à l'origine
void AfficherRegles(int lin, int col){
    
    // Cache le curseur et les caractères saisis
    curs_set(0);
    noecho();

    int touchePressee;
    int noPage = 0;
    char * pages[] = {
        "1. Objectif du jeu :\n-------------------------------------------------------------------\nLe joueur doit deviner un mot de 4 lettres choisi au hasard par le jeu en maximum 10 tentatives.\n\n\n2. Déroulement du jeu :\n------------------------------------------------------------------\n• Le joueur propose un mot de 4 lettres.\n• Le jeu fournit des indices sous forme de + et - :\n    Chaque \"+\" indique qu'une lettre dans la proposition du joueur\n    se trouve dans la solution et est bien placée.\n    Chaque \"-\" indique qu'une lettre dans la proposition du joueur\n    se trouve dans la solution mais n'est pas à la bonne place.\n• Le joueur utilise ces indices pour affiner ses propositions.\n  suivantes.",

        "3. Fin du jeu :\n-------------------------------------------------------------------• Le joueur gagne s'il parvient à deviner le mot en maximum 10\n  tentatives.\n• Le joueur perd s'il épuise toutes ses tentatives sans avoir\n  deviné le mot.\n\n\n4. Exemples :\n-------------------------------------------------------------------Mot à trouver | Tentative | Résultat\n     abri     |    coup   |         \n     abri     |    papa   |  -     \n     abri     |    vert   |  +     \n     abri     |    mari   |  ++-   \n     abri     |    abri   |  ++++  \n",

        "                          × Fun facts ×\n-------------------------------------------------------------------Le jeu est basé sur un jeu papier appelé Bulls and Cows. Une\nadaptation informatique a été réalisée dans les années 1960 sur le\nsystème informatique Titan de l'université de Cambridge, sous le\nnom de \"MOO\". Cette version a été écrite par Frank King.\n\nMordecai Meirowitz, un expert en télécommunications d'Israël, a\ntransformé ce concept en un produit commercial populaire dans les\nannées 1970. C'est la société  Invicta Plastics qui a ensuite\ncommercialisé le produit tel qu'on le connait.\n\nDonald Knuth, célèbre informaticien, a développé un algorithme de\nrésolution en maximum 5 coup dans le cadre de son livre \"The\nComputer as Master Mind\"."
    };
    
    // Créé une fenêtre pour les règles
    WINDOW * bordureFenetre = newwin(20, 71, lin, col); // hauteur (on rajoute 2 pour les bordures), largeur, coord
    WINDOW * fenetre = newwin(16, 67, lin+2, col+2); // hauteur (on rajoute 2 pour les bordures), largeur, coord
    box(bordureFenetre, 0, 0);

    mvwprintw(bordureFenetre, 0, 2, "[Règles du jeu]");
    mvwprintw(fenetre, 0, 0, "%s", pages[0]);
    mvwprintw(bordureFenetre, 19, 3, " FLÈCHES pour naviguer ");
    mvwprintw(bordureFenetre, 19, 28, " ENTER pour revenir au menu ");
    mvwprintw(bordureFenetre, 19, 58, " Page 1/3 ");
    wrefresh(bordureFenetre);
    wrefresh(fenetre);

    // Permet l'utilisation des flèches du clavier
    keypad(fenetre, true);

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

    } while (touchePressee != 10); // Quitte si appuis sur ENTER
    
    wclear(fenetre);
    wclear(bordureFenetre);
    wrefresh(fenetre);
    wrefresh(bordureFenetre);
    delwin(fenetre);
    delwin(bordureFenetre);

    // Rafraîchit les autres fenêtres en dessous pour afficher leur contenu
    touchwin(stdscr);
    refresh();

    // Rétabli le curseur
    curs_set(1);
    echo();
}