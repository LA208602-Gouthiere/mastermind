#include "../Includes/common.h"
#include "../Includes/mots.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"


/// @brief Cette fonction verifie qu'un mot comporte exactement 4 lettres minuscules sans accent
/// @param motAVerifier le mot à vérifier
/// @return true si le mot est correct, false si le mot n'est pas correct
bool VerifierMot(char *motAVerifier){

    if(strlen(motAVerifier) != LongueurDesMots){
        return false;
    }

    for (int carPos = 0; carPos < LongueurDesMots; carPos++){
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
    FILE * fichier;
    char bufferMot[100];
    
    // Vérifie allocation
    dictionnaire = (struct Dictionnaire *)malloc(sizeof(struct Dictionnaire));
    if (!dictionnaire) {
        sprintf(messageDeRetour->messageErreur, "Erreur d'allocation de mémoire pour le dictionnaire");
        messageDeRetour->codeErreur = 0;
        return NULL;
    }

    // Vérifie ouverture du fichier
    fichier = fopen(nomDeFichier, "r");
    if (!fichier){ 
        sprintf(messageDeRetour->messageErreur, "Erreur lors de l'ouverture du fichier %s", nomDeFichier);
        messageDeRetour->codeErreur = errno;
        return NULL;
    }

    // Lecture du fichier
    dictionnaire->listeMots = NULL;
    dictionnaire->nbMots = 0;
    while (fscanf(fichier, "%99s", bufferMot) == 1) { // %99s permet d'éviter un débordement de tampon

        if (VerifierMot(bufferMot)){

            // Rajoute une zone mémoire pour stocker un pointeur vers un mot de plus
            dictionnaire->listeMots = (char **)realloc(dictionnaire->listeMots, (dictionnaire->nbMots+1) * sizeof(char *));

            // Vérifie allocation
            if (!dictionnaire->listeMots) {
                sprintf(messageDeRetour->messageErreur, "Erreur de réallocation mémoire pour la liste de mots");
                messageDeRetour->codeErreur = 0;
                EffacerDictionnaire(dictionnaire);
                fclose(fichier);
                return NULL;
            }

            // Rajoute une zone mémoire pour stocker le mot et le copie
            dictionnaire->listeMots[dictionnaire->nbMots] = (char *)malloc(strlen(bufferMot) + 1);
            // Vérifie allocation
            if (!dictionnaire->listeMots[dictionnaire->nbMots]) {
                sprintf(messageDeRetour->messageErreur, "Erreur d'allocation de mémoire pour les mots du dictionnaire");
                messageDeRetour->codeErreur = 0;
                return NULL;
            }
            strcpy(dictionnaire->listeMots[dictionnaire->nbMots], bufferMot);

            dictionnaire->nbMots++;

        } else {
            // Remplit le message d'erreur, vide le dictionnaire et quitte la boucle
            sprintf(messageDeRetour->messageErreur, "Le mot à la ligne %d du fichier %s est invalide", dictionnaire->nbMots+1, nomDeFichier);
            EffacerDictionnaire(dictionnaire);
            messageDeRetour->codeErreur = 0;
            fclose(fichier);
            return NULL;
        }
    }
    
    // Vérifie que le nombre de mots scannés n'est pas nul
    if (dictionnaire->nbMots == 0){
        sprintf(messageDeRetour->messageErreur, "Erreur, le fichier %s est vide", nomDeFichier);
        messageDeRetour->codeErreur = 0;
        EffacerDictionnaire(dictionnaire);
        fclose(fichier);
        return NULL;
    }  

    // Fermeture du fichier
    if (fclose(fichier)){
        sprintf(messageDeRetour->messageErreur, "Erreur lors de la fermeture du fichier %s", nomDeFichier);
        messageDeRetour->codeErreur = errno;
        return NULL;
    }

    return dictionnaire;
}

/// @brief Appelée en fin de partie pour libérer la mémoire du dictionnaire passé en paramètre.
///        Libère d'abord la mémoire des pointeurs internes puis libère la mémoire globale
/// @param dictionnaire le dictionnaire de mots
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

    int occurrencesSolution[26] = {0};
    int occurrencesMotPlace[26] = {0};

    resultat->nbLettreBienPlacees = 0;
    resultat->nbLettreMalPlacees = 0;

    // Compte les occurrences de chaque lettre dans solution et motPlace
    for (int carPos = 0; carPos < LongueurDesMots; carPos++){

        // Si même lettre
        if(motPlace[carPos] == solution[carPos]) {
            resultat->nbLettreBienPlacees++;
        } else {
            // Incrémente le compteur de la lettre dans les tableaux d'occurrences
            occurrencesSolution[solution[carPos] - 'a']++;
            occurrencesMotPlace[motPlace[carPos] - 'a']++;
        }
    }

    // Compte les lettres mal placées
    for (int carPos = 0; carPos < 26; carPos++){
        if(occurrencesMotPlace[carPos] != 0 && occurrencesSolution[carPos] != 0)
            // Prend la plus petite valeur
            // Ex: abri et dada, 1 fois a et 2 fois a, on incrémente de 1
            //     car il y a 1 lettres en commun mais mal placées
            if (occurrencesMotPlace[carPos] < occurrencesSolution[carPos])
                resultat->nbLettreMalPlacees+=occurrencesMotPlace[carPos];
            else
                resultat->nbLettreMalPlacees+=occurrencesSolution[carPos];

    }
    return true;
}