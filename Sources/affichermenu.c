#include "../Includes/common.h"
#include "../Includes/ecran.h"
#include "../Includes/affichermenu.h"

/// @brief Affiche un menu navigable avec les flèches du clavier et la touche ENTER.
/// @param lin numéro de ligne à l'origine
/// @param col numéro de colonne à l'origine
/// @param titre titre du menu, "" si aucun
/// @param listeChoix liste des choix du menu
/// @param nbChoix le nombre de choix
/// @param choixSurligne le choix qui est surligné initialement, commence à 0
/// @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un éventuel code d'erreur
/// @return un nombre correspondant à l'option choisie, retourne -1 en cas d'erreur
int AfficherMenu(int lin, int col, char *titre, char **listeChoix, int nbChoix, int choixSurligne, struct Dico_Message *messageDeRetour){
    
    WINDOW * fenetreMenu;
    
    // Vérifie que le choix initial est possible
    if (choixSurligne < 0 || choixSurligne >= nbChoix){
        strcpy(messageDeRetour->messageErreur, "Erreur le choix initial du menu est impossible");
        messageDeRetour->codeErreur = 0;
        return -1;
    }

    // Créé une fenêtre pour le menu (hauteur+2 pour les bordures, largeur, coordonnées)
    if(!(fenetreMenu = newwin(nbChoix+2, 58, lin, col))){
        strcpy(messageDeRetour->messageErreur, "Erreur lors de la création de la fenêtre du menu");
        messageDeRetour->codeErreur = 0;
        return -1;
    }

    // Trace une bordure sur le contour de la fenêtre
    wattron(fenetreMenu, COLOR_PAIR(COULEURS_CONTOUR));
    box(fenetreMenu, 0, 0);
    mvwprintw(fenetreMenu, 0, 2, "[");
    wattron(fenetreMenu, COLOR_PAIR(COULEURS_MOT));
    wprintw(fenetreMenu, "%s", titre);
    wattron(fenetreMenu, COLOR_PAIR(COULEURS_CONTOUR));
    wprintw(fenetreMenu, "]");
    wattron(fenetreMenu, COLOR_PAIR(COULEURS_MOT));
    mvwprintw(fenetreMenu, nbChoix+1, 30, " ENTER pour sélectionner ");
    mvwprintw(fenetreMenu, nbChoix+1, 3, " FLÈCHES pour naviguer ");
    wattroff(fenetreMenu, COLOR_PAIR(COULEURS_MOT));
    wrefresh(fenetreMenu);

    // Permet l'utilisation des flèches du clavier
    keypad(fenetreMenu, true);

    // Cache le curseur et les caractères saisis
    curs_set(0);
    noecho();

    // Boucle du menu, réaffiche le menu à chaque fois qu'une nouvelle option est sélectionnée
    // quitte la boucle lorsqu'une option est sélectionnée
    int toucheAppuyee;
    bool estDansMenu = true;

    while (estDansMenu) {

        // Parcourt chaque choix du menu et les affiche
        for (int posChoix = 0; posChoix < nbChoix; posChoix++) {

            // Surligne le choix si c'est celui sélectionné
            if (posChoix == choixSurligne){
                mvwaddch(fenetreMenu, posChoix+1, 1, ACS_DIAMOND);
                wattron(fenetreMenu, A_REVERSE); // Inverse les couleurs de l'avant et arrière plans
            } else {
                mvwprintw(fenetreMenu, posChoix+1, 1, "  ");
            }

            // Affiche l'option dans la fenêtre
            mvwprintw(fenetreMenu, posChoix+1, 3, "%s", listeChoix[posChoix]);
            wattroff(fenetreMenu, A_REVERSE); // Rétablit les couleurs si elles ont été inversées
        }
        // Scan l'input clavier et incrémente ou décrémente selon que la flèche du haut ou bas soit appuyée
        toucheAppuyee = wgetch(fenetreMenu);
        switch (toucheAppuyee){
            case KEY_UP:
                if(choixSurligne>0) choixSurligne--;
                break;

            case KEY_DOWN:
                if(choixSurligne<nbChoix-1) choixSurligne++;
                break;
            
            case 10:
                estDansMenu = false; // Quitte la boucle si une option est sélectionnée avec ENTER
                break;

            default:
                break;
        }   
    }

    // Efface et rafraîchi la fenêtre
    wclear(fenetreMenu);
    wrefresh(fenetreMenu);

    // Supprime la fenêtre pour libérer la mémoire
    if(delwin(fenetreMenu) == ERR){
        strcpy(messageDeRetour->messageErreur, "Erreur lors de la suppression de la fenêtre du menu");
        messageDeRetour->codeErreur = 0;
        return -1;
    }

    // Rétablit le curseur
    curs_set(1);
    echo();

    return choixSurligne;
}