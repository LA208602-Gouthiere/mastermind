#include "../Includes/common.h"
#include "../Includes/mots.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"

// Cette fonction verifie qu'un mot comporte exactement 4 lettres minuscules sans accent
// Paramètres:
// - Le mot à vérifier
// Renvoie:
// - true si le mot est correct, false si le mot n'est pas correct
bool VerifierMot(char *motAVerifier)
{
    // A CODER (cours LPP2)
    return false; // A adapter
}

// Cette fonction initialise la structure avec le dictionnaire
// en l'allouant en memoire et en lisant le dictionnaire à partir d'un fichier
// En cas d'erreur:
// - elle garnit la structure Dico_Message avec l'explication de l'erreur puis renvoie NULL
// - c'est à l'appelant de décider d'afficher le message ou pas
// Paramètres:
// - le nom du fichier
// - l'adresse de la structure Dico_Message
// Renvoie:
// - Une structure Dictionnaire remplie
// - ou NULL s'il y a eu une erreur
struct Dictionnaire *LireDictionnaire(char *nomDeFichier, struct Dico_Message *messageDeRetour)
{
    // A CODER
    // FONCTIONS UTILISEES
    // malloc()
    // EffacerDictionnaire()
    // Cf cours FBD2 pour lire le fichier

    return NULL; // A Adapter
}

// Cette fonction libère la mémoire du dictionnaire passé en Paramètre
// Elle libère d'abord la mémoire des pointeurs internes
// puis libère la mémoire globale du dictionnaire
// A appeler en fin de partie
void EffacerDictionnaire(struct Dictionnaire *dictionnaire)
{   
    // FONCTIONS UTILISEES
    // free()
}

// Cette fonction compare deux mots pour une ligne de jeu
// en comptant les lettres bien placées et les lettres mal pacées
// Parammetres:
// - Solution (mot de reference)
// - Mot placé par le joueur
// - Adresse d'une structure a garnir avec le resultat
// Renvoie:
// - Si la comparaison n'est pas possible, elle renvoie false
// - Si la comparaison est possible, elle garnit la structure ResultatLigne et renvoie true
bool ComparerMots(char *solution, char *motPlace, struct ResultatLigne *resultat)
{
    // Conseil: commencer par décrire l'algorithme en détail, p.ex. en pseudo langage

    // FONCTIONS UTILISEES:
    // cf. cours LPP2 et LPP1 (chaînes de caractères)

    return false; // A adapter
}