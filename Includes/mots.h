#ifndef _DICO_CONST
#define _DICO_CONST


/// @brief Structure pour stocker le dictionnaire des mots.
///        Elle contient un tableau dynamique de mots et le compteur du nombre de mots.
struct Dictionnaire {
    char ** listeMots;
    int nbMots;
};


/// @brief Structure pour le résultat d'une ligne contenant le nombre de lettres bien
///        placées et le nombre de lettres mal placées.
struct ResultatLigne {
    int nbLettresBienPlacees;
    int nbLettresMalPlacees;
};
#endif

// Déclaration des fonctions du module
bool VerifierMot(char *motAVerifier);
struct Dictionnaire *LireDictionnaire(char *nomDeFichier, struct Dico_Message *messageDeRetour);
void EffacerDictionnaire(struct Dictionnaire *dictionnaire);
bool ComparerMots(char *solution, char *motPlace, struct ResultatLigne *resultat);