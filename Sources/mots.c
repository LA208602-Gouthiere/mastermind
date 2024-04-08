#include "../Includes/common.h"
#include "../Includes/mots.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"


/// @brief Cette fonction verifie qu'un mot comporte exactement 4 lettres minuscules sans accent
/// @param motAVerifier le mot à vérifier
/// @return true si le mot est correct, false si le mot n'est pas correct
bool VerifierMot(char *motAVerifier){

    if(strlen(motAVerifier) != 4){
        return false;
    }

    for (int carPos = 0; carPos < 4; carPos++){
        if(motAVerifier[carPos] < 'a' || motAVerifier[carPos] > 'z')
            return false;
    }
    
    return true;
}


/// @brief Initialise la structure avec le dictionnaire
///        en l'allouant en memoire et en lisant le dictionnaire à partir d'un fichier.
///        En cas d'erreur garnit la structure Dico_Message avec l'explication de l'erreur puis renvoie NULL.
///        C'est à l'appelant de décider d'afficher le message ou pas.
/// @param nomDeFichier le nom du fichier
/// @param messageDeRetour l'adresse de la structure Dico_Message
/// @return Une structure Dictionnaire remplie ou NULL en cas d'erreur
struct Dictionnaire * LireDictionnaire(char *nomDeFichier, struct Dico_Message * messageDeRetour) {

    struct Dictionnaire * dictionnaire;
    char * bufferMot;
    int nbMots = 0;
    FILE * fichier = fopen(nomDeFichier, "r");

    if (!fichier){ // Vérifie ouverture du fichier
        sprintf(messageDeRetour->messageErreur, "Erreur lors de l'ouverture du fichier %s", nomDeFichier);
        messageDeRetour->codeErreur = errno;
        return NULL;
    }

    dictionnaire = (struct Dictionnaire *)malloc(sizeof(struct Dictionnaire));
    dictionnaire->listeMots = NULL;
    bufferMot = (char *) malloc(1000);
    while (fscanf(fichier, "%s", bufferMot) == 1) {

        if (VerifierMot(bufferMot)){

            // Rajoute une zone mémoire pour stocker un pointeur vers un mot de plus
            dictionnaire->listeMots = (char **)realloc(dictionnaire->listeMots, (nbMots+1) * sizeof(char *));

            // Rajoute une zone mémoire pour stocker le mot
            dictionnaire->listeMots[nbMots] = (char *)malloc(strlen(bufferMot) + 1);

            // Copie le mot dans la zone
            strcpy(dictionnaire->listeMots[nbMots], bufferMot);
            nbMots++;

        } else {

            // Vide le dictionnaire, remplit le message d'erreur et quitte la boucle
            free(bufferMot);
            EffacerDictionnaire(dictionnaire);
            sprintf(messageDeRetour->messageErreur, "Le mot à la ligne %d du fichier %s est invalide", nbMots+1, nomDeFichier);
            messageDeRetour->codeErreur = 0;
            return NULL;
        }
    }
    dictionnaire->nbMots = nbMots;
    free(bufferMot);

    if (fclose(fichier)){ // Fermeture du fichier
        EffacerDictionnaire(dictionnaire);
        sprintf(messageDeRetour->messageErreur, "Erreur lors de la fermeture du fichier %s", nomDeFichier);
        messageDeRetour->codeErreur = errno;
        return NULL;
    }

    return dictionnaire;
}

/// @brief Appelée en fin de partie pour libérer la mémoire du dictionnaire passé en paramètre.
///        Libère d'abord la mémoire des pointeurs internes puis libère la mémoire globale
/// @param dictionnaire le ductionnaire de mots
void EffacerDictionnaire(struct Dictionnaire * dictionnaire){   
    
    // Parcourt le tableau des mots pour libérer chaque espace mémoire
    for (int wordPos = 0; wordPos < dictionnaire->nbMots; wordPos++) {
        free(dictionnaire->listeMots[wordPos]);
    }
    free(dictionnaire->listeMots); // Libère tableau de mots
    free(dictionnaire);
}

/// @brief Compare deux mots pour une ligne de jeu en comptant les lettres bien placées et les lettres mal placées
///        Garnit la structure ResultatLigne si comparaison possible
/// @param solution mot de référence
/// @param motPlace mot placé par le joueur
/// @param resultat adresse d'une structure à garnir avec le résultat
/// @return false si comparaison impossible sinon true
bool ComparerMots(char *solution, char *motPlace, struct ResultatLigne *resultat){

    if (!VerifierMot(motPlace))
        return false;

    int occurencesSolution[26] = {0};
    int occurencesMotPlace[26] = {0};

    resultat->nbLettreBienPlacees = 0;
    resultat->nbLettreMalPlacees = 0;

    // Compte les occurrences de chaque lettre dans solution et motPlace
    for (int carPos = 0; carPos < 4; carPos++){

        // Si même lettre
        if(motPlace[carPos] == solution[carPos]) {
            resultat->nbLettreBienPlacees++;
        } else {
            // Incrémente le compteur de la lettre dans les tableaux d'occurences
            occurencesSolution[solution[carPos] - 'a']++;
            occurencesMotPlace[motPlace[carPos] - 'a']++;
        }
    }

    // Compte les lettres mal placées
    for (int carPos = 0; carPos < 26; carPos++){

        // Ex: abri et dada, 1 fois a et 2 fois a, on incrémente de 2
        //     car il y a 2 lettres présentes mais mal placées
        // Ex: dada et abri, 2 fois a et 1 fois a, on incrémente de 1
        //     car il y a 1 lettre présente mais mal placée
        if(occurencesMotPlace[carPos] != 0 && occurencesSolution[carPos] != 0)
            resultat->nbLettreMalPlacees+=occurencesMotPlace[carPos];

    }
    return true;
}