#include "../Includes/common.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"
#include "../Includes/mots.h"
#include "../Includes/partie.h"
#include "../Includes/score.h"

// Fonction pour créer une partie
// Paramètre:
// - Le dictionnaire contenant tous les mots
// Renvoie
// - Une structure Partie allouée en memoire, avec un mot choisi au hasard
//   et toute l'information mise à zero pour commencer la partie
struct Partie *CreerPartie(struct Dictionnaire *dictionnaire)
{
    struct Partie *partieEnCours;

    // FONCTIONS UTILISEES
    // malloc()
    // AfficherErreurEtTerminer()
    // srand()

    return partieEnCours;
}

// Fonction pour libérer la memoire liee a une partie
// Paramètre:
// - Pointeur vers la strcuture Partie a libérer de la memoire
void EffacerPartie(struct Partie *partieEnCours)
{
    // FONCTIONS UTILISEES
    // free()
}

// Fonction pour afficher une partie en cours
// Pour chaque mot déjà essayé, on affiche
// - Le mot
// - Le resultat: un + par lettre bien placée et un - par lettre mal placée
// Paramètre:
// - Pointeur vers la structure Partie
// - Booleen qui indique si on est en mode debug (qui affiche la solution)
void AfficherPartie(struct Partie *partieEnCours, bool modeDebug)
{
    // On efface tout et on affiche le jeu dans son état actuel

    // FONCTIONS UTILISEES
    // EffacerEcran();
    // AfficherHautDeJeu();
    // AfficherMotDeJeu();
    // AfficherSeparateurDeJeu();
    // AfficherBasDeJeu();
}

// Fonction pour jouer une partie
// Paramètre:
// - Pointeur vers la structure Partie préablement initialisée avec une nouvelle partie
// Renvoie:
// - false si abandon, true si fin de partie (gagnée ou perdue)
// Fonctionnement:
// - Affiche la partie (mots déjà joués)
// - Demande un nouveau mot de 4 lettres ou ENTER pour abandonner le jeu
// - Verifier le mot et s'il est correct, calculer le resultat
//   (10 si trouve en 1 coup, 9 en 2 coups... 1 en 10 cours)
// - Si le mot n'est pas correct, le resultat est 0.
// A la fin de la partie:
// - Si gagne ou perdu: on demande le nom du jour et on sauve le résultat
// - Si abandon: fin de partie, on affiche la solution
bool JouerPartie(struct Partie *partieEnCours)
{
    // Conseil: commencer par décrire l'algorithme en détail, p.ex. en pseudo langage

    // FONCTIONS UTILISEES:
    // AfficherPartie()
    // AfficherTexteIndenteSansRetour()
    // LireTexte()
    // VerifierMot()
    // ComparerMots()
    // SauverScore()
    // free()

    return false; // A adapter
}

// Fonction pour afficher les meilleurs scores
// Le nombre de scores est une constante du code, on peut la modifier et recompiler
// La fonction LireMeilleursScores() est appellée pour obtenir les meilleurs scores
// Son résultat est un tableau alloué en mémoire, qu'il faut libérer a la fin
void AfficherMeilleursScores()
{
    // FONCTIONS UTILISEES:
    // LireMeilleursScores()
    // AfficherErreurEtTerminer()
    // EffacerEcran()
    // AfficherTexteDansCadre()
    // AfficherTexteIndenteSansRetour()
    // AfficherTexteSansRetour()
    // AfficherNombreSansRetour()
    // RetourALaLigne()
    // LireTexte();
    // free()
}