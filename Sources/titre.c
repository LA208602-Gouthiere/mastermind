#include <unistd.h>
#include "../Includes/common.h"
#include "../Includes/ecran.h"
#include "../Includes/titre.h"

#define FLOPPY_ANIM_SPEED 60000 // en microsecondes
#define TITLE_ANIM_SPEED 5000

/// @brief Affiche le splashscreen
/// @param lin numéro de ligne à l'origine
/// @param col numéro de colonne à l'origine
void AfficherIntro(int lin, int col){

    // Cache le curseur et les caractères saisis
    curs_set(0);
    noecho();

    // Animation disquette
    for (int translation = 0; translation < 37; translation++) {
        clear();
        AfficherLecteurDisquetteBas(lin-1, col+4);

        // Disquette en bleu
        attron(COLOR_PAIR(1));
        AfficherDisquette(lin+21-translation, col+14);
        attroff(COLOR_PAIR(1));

        AfficherLecteurDisquetteHaut(lin-4, col+4);
        usleep(FLOPPY_ANIM_SPEED);
        refresh();
    }
    usleep(1000);
    clear();
    AfficherLecteurDisquetteBas(lin-1, col+4);

    // Disquette en bleu
    attron(COLOR_PAIR(COULEURS_CONTOUR));
    AfficherDisquette(lin-15, col+15);
    attroff(COLOR_PAIR(COULEURS_CONTOUR));

    AfficherLecteurDisquetteHaut(lin-4, col+4);
    refresh();
    usleep(1000);

    // Affichage du titre
    clear();
    refresh();
    
    AfficherTitre(lin, col, true);

    // Rétabli le curseur
    curs_set(1);
    echo();
}

/// @brief Affiche le dessin ascii d'une disquette
/// @param lin numéro de la ligne
/// @param col numéro de la colonne
void AfficherDisquette(int lin, int col){
    mvprintw(lin,   col," __________________________");
    mvprintw(lin+1, col,"|     |          ___    |  \\");
    mvprintw(lin+2, col,"| /\\  |         |   |   |   \\");
    mvprintw(lin+3, col,"| ||  |         |___|   |    \\");
    mvprintw(lin+4, col,"|     |_________________|    |\\");
    mvprintw(lin+5, col,"|                            ||");
    mvprintw(lin+6, col,"|                            ||");
    mvprintw(lin+7, col,"|                            ||");
    mvprintw(lin+8, col,"|    ____________________    ||");
    mvprintw(lin+9, col,"|   |                    |   ||");
    mvprintw(lin+10,col,"|   |  -----HELHa------  |   ||");
    mvprintw(lin+11,col,"|   |  ---Mastermind---  |   ||");
    mvprintw(lin+12,col,"|   |  ----NG--2024----  |   ||");
    mvprintw(lin+13,col,"|___|____________________|___||");
    mvprintw(lin+14,col,"\\___\\____________________\\___\\|");
}

/// @brief Affiche le dessin ascii du haut du lecteur de disquette
/// @param lin numéro de la ligne
/// @param col numéro de la colonne
void AfficherLecteurDisquetteHaut(int lin, int col){
    mvprintw(lin,   col,"|___________________________________________|     |");
    mvprintw(lin+1, col,"\\                                           \\     |");
    mvprintw(lin+2, col," \\    ___________\\-----------\\____________   \\    |");
}

/// @brief Affiche le dessin ascii du bas du lecteur de disquette
/// @param lin numéro de la ligne
/// @param col numéro de la colonne
void AfficherLecteurDisquetteBas(int lin, int col){
    mvprintw(lin,   col,"  \\   \\                                   \\   \\   |");
    mvprintw(lin+1, col,"   \\   \\____________            ___________\\   \\  |");
    mvprintw(lin+2, col,"    \\               \\-----------\\               \\ |");
    mvprintw(lin+3, col,"     \\___________________________________________\\|");
}

/// @brief Affiche le dessin ascii du titre qui peut être animé ou non.
/// @param lin numéro de la ligne
/// @param col numéro de la colonne
/// @param animation true si l'animation doit avoir lieu sinon false
void AfficherTitre(int lin, int col, bool animation) {
    
    char * title[] = {
        " __     __           _                      _           _ ",
        "|  \\   /  |         | |                    (_)         | |",
        "|   \\ /   | __ _ ___| |_ ___ _ __ _ __ ___  _ _ __   __| |",
        "| |\\ V /| |/ _` / __| __/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` |",
        "| | \\_/ | | (_| \\__ \\ ||  __/ |  | | | | | | | | | | (_| |",
        "|_|     |_|\\__,_|___/\\__\\___|_|  |_| |_| |_|_|_| |_|\\__,_|",
        "----------------------------------------------------------",
        "                 Nicolas Gouthiere - 2024                 "
    };
    const int nbLines = 8;
    const int lineLength = 58;
    const int nbChars = nbLines*lineLength;
    struct Dico_Message *messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));

    // Vérifie l'allocation
    if (!(messageDeRetour)) {
        AfficherErreurEtTerminer("Erreur d'allocation mémoire lors de l'affichage du titre", 0);
    }

    // Si l'animation doit être jouée
    attron(COLOR_PAIR(COULEURS_MOT));
    if (animation){

        // Créer un tableau pour les positions des caractères et vérifie s'il est bien rempli
        int *charPositions;
        if (!(charPositions = TableauNombresAleasUniques(0, nbChars-1, messageDeRetour))){
            AfficherErreurEtTerminer(messageDeRetour->messageErreur, messageDeRetour->codeErreur);
        }

        // Afficher chaque caractère à une position aléatoire
        int pos;
        int linPos;
        int colPos;
        for (int currentChar = 0; currentChar < nbChars; currentChar++) {

            // Détermine la position de la ligne et de la colonne du caractère courant
            pos = charPositions[currentChar];
            linPos = pos / lineLength;
            colPos = pos % lineLength;

            mvaddch(lin + linPos, col + colPos, title[linPos][colPos]);
            refresh();
            usleep(TITLE_ANIM_SPEED);
        }

    } else {
        // Affiche chaque ligne du titre
        for (int noLigne = 0; noLigne < nbLines; noLigne++){
            mvprintw(lin + noLigne, col, "%s", title[noLigne]);
        }
        refresh();
    }
    attroff(COLOR_PAIR(COULEURS_MOT));

    // Vide le dictionnaire d'erreur
    free(messageDeRetour);
}

/// @brief Génère un tableau avec des nombres aléatoires uniques entre 2 bornes comprises
/// @param min borne inférieure
/// @param max borne supérieure
/// @return un pointeur vers un tableau de nombres aléatoires uniques, retourne NULL en cas d'erreur
int * TableauNombresAleasUniques(int min, int max, struct Dico_Message *messageDeRetour){
    int taille;
    int * tableau;

    // Vérifie les bornes
    if (min > max) {
        strcpy(messageDeRetour->messageErreur, "Erreur: min doit être inférieur ou égal à max");
        messageDeRetour->codeErreur = 0;
        return NULL;
    }

    // Calcule la taille du tableau
    taille = max - min + 1;

    // Alloue de la mémoire pour le tableau
    if (!(tableau = (int *) malloc(taille * sizeof(int)))) {
        printf("Erreur d'allocation de mémoire\n");
        return NULL;
    }

    // Générer des nombres aléatoires uniques
    for (int i = 0; i < taille; ++i) {
        bool unique;
        int nombre;

        do {
            unique = true;
            nombre = rand() % (max - min + 1) + min;

            // Vérifier si le nombre est déjà dans le tableau
            for (int j = 0; j < i; ++j) {
                if (tableau[j] == nombre) {
                    unique = false;
                    break;
                }
            }
        } while (!unique);

        tableau[i] = nombre;
    }

    return tableau;
}