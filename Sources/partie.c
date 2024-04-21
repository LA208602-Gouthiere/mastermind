#include "../Includes/common.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"
#include "../Includes/mots.h"
#include "../Includes/partie.h"
#include "../Includes/score.h"

/// @brief Fonction pour créer une partie
/// @param dictionnaire Le dictionnaire contenant tous les mots
/// @return Une structure Partie allouée en memoire, avec un mot choisi au hasard
///         et toute l'information mise à zero pour commencer la partie
struct Partie * CreerPartie(struct Dictionnaire * dictionnaire){
    
    struct Partie * partieEnCours = (struct Partie *)malloc(sizeof(struct Partie));
    
    // Choisit un mot au hasard
    partieEnCours->solution = dictionnaire->listeMots[rand()%(dictionnaire->nbMots - 1)];

    partieEnCours->motsEssayes = NULL;
    partieEnCours->resultatsEssais = (struct ResultatLigne **)malloc(sizeof(struct ResultatLigne *));
    partieEnCours->nomJoueur[0] = '\0';
    partieEnCours->numEssaiCourant = 0;
    partieEnCours->resultat = false;
    
    // AfficherErreurEtTerminer()
    return partieEnCours;
}

/// @brief Fonction pour libérer la memoire liée à une partie
/// @param partieEnCours Pointeur vers la strcuture Partie à libérer de la memoire
void EffacerPartie(struct Partie * partieEnCours){
    free(partieEnCours->motsEssayes);
    free(partieEnCours->resultatsEssais);
    free(partieEnCours);
}

/// @brief Fonction pour afficher une partie en cours
///        Pour chaque mot déjà essayé, on affiche :
///        - Le mot
///        - Le resultat: un + par lettre bien placée et un - par lettre mal placée
/// @param partieEnCours Pointeur vers la structure Partie
/// @param modeDebug Booleen qui indique si on est en mode debug (qui affiche la solution)
void AfficherPartie(struct Partie * partieEnCours, bool modeDebug){
    
    // Cas spécial lorsque tous les essais ont été utilisés et qu'on a 11 tentatives
    int nbCases = partieEnCours->numEssaiCourant;
    if(nbCases > 10)
        nbCases--;

    // On efface tout et on affiche le jeu dans son état actuel
    EffacerEcran();
    
    // Affiche les mots essayés
    AfficherHautDeJeu(modeDebug ? partieEnCours->solution : NULL);
    for (int noMot = 0; noMot < nbCases; noMot++){
        
        AfficherMotDeJeu(partieEnCours->motsEssayes[noMot], partieEnCours->resultatsEssais[noMot]->nbLettreBienPlacees, partieEnCours->resultatsEssais[noMot]->nbLettreMalPlacees);
        if (noMot != 9)
            AfficherSeparateurDeJeu();
    }

    // Affiche les cases restantes
    for (int noCase = nbCases; noCase < 10; noCase++){
        
        AfficherMotDeJeu("    ", 0, 0);
        if (noCase != 9)
            AfficherSeparateurDeJeu();
    }
    AfficherBasDeJeu();
    refresh();
}


/// @brief Jouer une partie
///        Fonctionnement:
///        - Affiche la partie (mots déjà joués)
///        - Demande un nouveau mot de 4 lettres ou ENTER pour abandonner le jeu
///        - Verifier le mot et s'il est correct, calculer le resultat
///          (10 si trouve en 1 coup, 9 en 2 coups... 1 en 10 cours)
///        - Si le mot n'est pas correct, le resultat est 0.
///        A la fin de la partie:
///        - Si gagne ou perdu: on demande le nom du jour et on sauve le résultat
///        - Si abandon: fin de partie, on affiche la solution
/// @param partieEnCours Pointeur vers la structure Partie préablement initialisée avec une nouvelle partie
/// @return false si abandon, true si fin de partie (gagnée ou perdue)
bool JouerPartie(struct Partie *partieEnCours){

    bool debug = false;
    char * motLu;
    struct ResultatLigne * resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));

    partieEnCours->numEssaiCourant = 0;
    do{

        // Saisie
        do{
            AfficherPartie(partieEnCours, debug);
            AfficherTexteIndenteSansRetour("Entrez un mot de 4 lettres (ENTER pour abandonner) : ");
            motLu = LireTexte();

            // Mode debug activé quand * est pressé
            if (strcmp(motLu, "*") == 0){
                if(debug)
                    debug = false;
                else
                    debug = true;
            }

            // Abandon si ENTER pressé (mot vide)
            if (strcmp(motLu, "") == 0){
                free(motLu);
                return false;
            }

        } while (!VerifierMot(motLu));

        // Vérifie mot placé
        if (ComparerMots(partieEnCours->solution, motLu, resultat)){
            
            // Rajoute une zone mémoire pour stocker le mot et le copie
            partieEnCours->motsEssayes = (char **)realloc(partieEnCours->motsEssayes, (partieEnCours->numEssaiCourant+1) * sizeof(char *));
            partieEnCours->motsEssayes[partieEnCours->numEssaiCourant] = (char *)malloc(strlen(motLu) + 1);
            strcpy(partieEnCours->motsEssayes[partieEnCours->numEssaiCourant], motLu);

            // Rajoute une zone mémoire pour stocker le resultat
            partieEnCours->resultatsEssais = (struct ResultatLigne **)realloc(partieEnCours->resultatsEssais, (partieEnCours->numEssaiCourant + 1) * sizeof(struct ResultatLigne *));
            partieEnCours->resultatsEssais[partieEnCours->numEssaiCourant] = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
            partieEnCours->resultatsEssais[partieEnCours->numEssaiCourant]->nbLettreBienPlacees = resultat->nbLettreBienPlacees;
            partieEnCours->resultatsEssais[partieEnCours->numEssaiCourant]->nbLettreMalPlacees = resultat->nbLettreMalPlacees;

            partieEnCours->numEssaiCourant++;
            // Lors d'une victoire ou d'une défaite
            if (resultat->nbLettreBienPlacees == 4 || partieEnCours->numEssaiCourant == 10){
                
                // Saisie du pseudo
                do {
                    AfficherPartie(partieEnCours, debug);
                    if(resultat->nbLettreBienPlacees == 4){
                        AfficherTexteIndenteSansRetour("Bravo ! Entrez votre pseudo (max 10 caractères) : ");
                    } else {
                        partieEnCours->numEssaiCourant++;
                        AfficherTexteIndenteSansRetour("Dommage... Le mot était \"");
                        AfficherTexteSansRetour(partieEnCours->solution);
                        AfficherTexteSansRetour("\"");
                        RetourALaLigne();
                        AfficherTexteIndenteSansRetour("Entrez votre pseudo (max 10 caractères) : ");
                    }
                    
                    motLu = LireTexte();
                } while (strlen(motLu) > 10 || strlen(motLu) <= 0); // Pseudo doit étre en 1 et 10 caractères
                strcpy(partieEnCours->nomJoueur, motLu);
                
                // Vérifie sauvegarde du score
                if (!SauverScore(false, motLu, partieEnCours->numEssaiCourant, messageDeRetour)){
                    AfficherErreurEtTerminer(messageDeRetour->messageErreur, messageDeRetour->codeErreur);
                }
                free(motLu);
                free(messageDeRetour);
                return true;
            }
        }

    } while (true);

    free(motLu);
    return true;
}

/// @brief Fonction pour afficher les meilleurs scores
///        Le nombre de scores est une constante du code, on peut la modifier et recompiler
///        La fonction @c LireMeilleursScores() est appellée pour obtenir les meilleurs scores
///        Son résultat est un tableau alloué en mémoire, qu'il faut libérer a la fin
void AfficherMeilleursScores(){
    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    struct Points * tabScores;

    // Vérifie si le tableau des score est NULL
    if(!(tabScores = LireMeilleursScores(false, 10, messageDeRetour)))
        AfficherErreurEtTerminer(messageDeRetour->messageErreur, messageDeRetour->codeErreur);
    
    EffacerEcran();
    RetourALaLigne();
    AfficherTexteDansCadre(" Meilleurs Scores ");
    RetourALaLigne();
    RetourALaLigne();

    // Parcourt le tableau des scores pour les afficher ligne par ligne
    for (int noJoueur = 0; noJoueur < 10; noJoueur++){
        // Si le score existe
        if(tabScores[noJoueur].score != -1){
            AfficherTexteIndenteSansRetour(tabScores[noJoueur].name);
            AfficherTexteSansRetour(" : ");
            AfficherNombreSansRetour(tabScores[noJoueur].score);
            RetourALaLigne();
        }
    }

    RetourALaLigne();
    AfficherTexteIndenteSansRetour("Enfoncez ENTER pour continuer ");
    LireTexte();
    free(messageDeRetour);
    free(tabScores);
}