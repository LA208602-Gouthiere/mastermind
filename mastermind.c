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
    
    // Initialisation
    srand(time(NULL));
    InitialiserEcran();
    dictionnaire = LireDictionnaire("liste_francais_4.txt", messageDeRetour);
    
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