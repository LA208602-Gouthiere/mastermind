/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *       Titre: Word Mastermind                                            *
 *      Auteur: Nicolas Gouthiere                                          *
 *       Année: 2024                                                       *
 * Description: Le jeu Word Mastermind développé en C pour l'UE108 (Prin-  *
 *              cipes et langages de programmation 2). Ce projet contient  *
 *              les fonctions pour l'affichage, la logique du jeu, la ge-  *
 *              stion de la base de données et les tests associés.         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "./Includes/common.h"
#include "./Includes/clavier.h"
#include "./Includes/score.h"
#include "./Includes/ecran.h"
#include "./Includes/mots.h"
#include "./Includes/partie.h"
#include "./Includes/menus.h"
#include "./Includes/titre.h"

int main(){

    struct Partie * partie;
    struct Dictionnaire * dictionnaire;
    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    char nomFichier[30];
    
    // Vérifie l'allocation
    if (!(messageDeRetour)) {
        AfficherErreurEtTerminer("Erreur d'allocation mémoire", 0);
    }
    
    // Initialisation
    srand(time(NULL));
    InitialiserEcran();

    // Lecture du dictionnaire
    sprintf(nomFichier, "liste_francais_%d.txt", LongueurDesMots);
    dictionnaire = LireDictionnaire(nomFichier, messageDeRetour);
    
    // Vérifie si le dictionnaire est bien remplis et lance la partie
    if(dictionnaire) {

        // Affichage du menu
        AfficherIntro(4, 11);
        AfficherMenuPrincipal(14, 11, partie, dictionnaire);

        // Vide le dictionnaire à la fin du programme
        EffacerDictionnaire(dictionnaire);
        free(messageDeRetour);
        
    // Sinon affiche l'erreur et ferme le programme
    } else {
        AfficherErreurEtTerminer(messageDeRetour->messageErreur, messageDeRetour->codeErreur);
    }

    TerminerEcran();
    return EXIT_SUCCESS;
}