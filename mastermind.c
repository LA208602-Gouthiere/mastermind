#include "./Includes/common.h"
#include "./Includes/clavier.h"
#include "./Includes/score.h"
#include "./Includes/ecran.h"
#include "./Includes/mots.h"
#include "./Includes/partie.h"

int main(){

    struct Partie * partie;
    struct Dictionnaire * dictionnaire;
    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    bool finPartie;
 
    InitialiserEcran();
    dictionnaire = LireDictionnaire("liste_francais_4.txt", messageDeRetour);
    // Vérifie si le dictionnaire est bien remplis et lance la partie
    if(dictionnaire) {

        do {
            partie = CreerPartie(dictionnaire);
            finPartie = JouerPartie(partie);
            EffacerPartie(partie);

        } while(finPartie); // Lance une nouvelle partie si la précédente est terminée et qu'elle n'a pas été abandonnée

        EffacerDictionnaire(dictionnaire);
        free(messageDeRetour);
        
    // Sinon affiche l'erreur et ferme le programme
    } else {
        AfficherErreurEtTerminer(messageDeRetour->messageErreur, messageDeRetour->codeErreur);
    }

    TerminerEcran();

    // AfficherMeilleursScores()
    
    return EXIT_SUCCESS;
}