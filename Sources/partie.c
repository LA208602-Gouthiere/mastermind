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
    
    // Vérifie l'allocation
    if(!partieEnCours){
        AfficherErreurEtTerminer("Erreur d'allocation mémoire lors de la création de la partie", 0);
    }
    
    // Choisit un mot au hasard
    partieEnCours->solution = dictionnaire->listeMots[rand()%(dictionnaire->nbMots - 1)];

    partieEnCours->motsEssayes = NULL;
    partieEnCours->resultatsEssais = (struct ResultatLigne **)malloc(sizeof(struct ResultatLigne *));
    // Vérifie l'allocation
    if(!partieEnCours->resultatsEssais){
        AfficherErreurEtTerminer("Erreur d'allocation mémoire lors de la création de la partie", 0);
    }
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
    
    // Pour les cases vide
    char motVide[20];
    memset(motVide, ' ', LongueurDesMots);

    // Cas spécial lorsque tous les essais ont été utilisés et qu'on a 11 tentatives
    int nbCases = partieEnCours->numEssaiCourant;
    if(nbCases > NbreMaxDEssais)
        nbCases--;

    // On efface tout et on affiche le jeu dans son état actuel
    EffacerEcran();
    
    // Affiche les mots essayés
    AfficherHautDeJeu(modeDebug ? partieEnCours->solution : NULL);
    for (int noMot = 0; noMot < nbCases; noMot++){
        
        AfficherMotDeJeu(partieEnCours->motsEssayes[noMot], partieEnCours->resultatsEssais[noMot]->nbLettreBienPlacees, partieEnCours->resultatsEssais[noMot]->nbLettreMalPlacees);
        if (noMot != NbreMaxDEssais-1)
            AfficherSeparateurDeJeu();
    }

    // Affiche les cases restantes
    for (int noCase = nbCases; noCase < NbreMaxDEssais; noCase++){
        

        AfficherMotDeJeu(motVide, 0, 0);
        if (noCase != NbreMaxDEssais-1)
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
///        À la fin de la partie:
///        - Si gagne ou perdu: on demande le nom du jour et on sauve le résultat
///        - Si abandon: fin de partie, on affiche la solution
/// @param partieEnCours Pointeur vers la structure Partie préablement initialisée avec une nouvelle partie
/// @return false si abandon, true si fin de partie (gagnée ou perdue)
bool JouerPartie(struct Partie *partieEnCours){

    bool debug = false;
    char * motLu;
    int longueurMotLu;
    struct ResultatLigne * resultat;
    struct Dico_Message * messageDeRetour;
    static char inviteSaisie[60];

    resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));

    // Vérifie l'allocation
    if(!resultat || !messageDeRetour){
        AfficherErreurEtTerminer("Erreur d'allocation mémoire pendant la partie", 0);
    }

    // Formate l'invite de saisie
    sprintf(inviteSaisie, "Entrez un mot de %d lettres (ENTER pour abandonner) : ", LongueurDesMots);

    partieEnCours->numEssaiCourant = 0;
    do{

        // Saisie
        do{
            AfficherPartie(partieEnCours, debug);
            attron(COLOR_PAIR(COULEURS_QUESTION));
            AfficherTexteIndenteSansRetour(inviteSaisie);
            attroff(COLOR_PAIR(COULEURS_QUESTION));
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
            
            // Agrandit la zone mémoire pour la liste de mots
            partieEnCours->motsEssayes = (char **)realloc(partieEnCours->motsEssayes, (partieEnCours->numEssaiCourant+1) * sizeof(char *));
            // Agrandit la zone mémoire pour la liste de structures de résultats
            partieEnCours->resultatsEssais = (struct ResultatLigne **)realloc(partieEnCours->resultatsEssais, (partieEnCours->numEssaiCourant + 1) * sizeof(struct ResultatLigne *));
            // Vérifie les allocations mémoire
            if (!partieEnCours->motsEssayes || !partieEnCours->resultatsEssais){
                AfficherErreurEtTerminer("Erreur d'allocation mémoire pendant la partie", 0);
            }

            // Rajoute une zone mémoire pour stocker le mot
            partieEnCours->motsEssayes[partieEnCours->numEssaiCourant] = (char *)malloc(strlen(motLu) + 1);
            // Rajoute une zone mémoire pour stocker une structure de resultat
            partieEnCours->resultatsEssais[partieEnCours->numEssaiCourant] = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
            // Vérifie les allocations mémoire
            if (!partieEnCours->motsEssayes || !partieEnCours->resultatsEssais){
                AfficherErreurEtTerminer("Erreur d'allocation mémoire pendant la partie", 0);
            }

            // Copie le mot et le résultat de la comparaison
            strcpy(partieEnCours->motsEssayes[partieEnCours->numEssaiCourant], motLu);
            partieEnCours->resultatsEssais[partieEnCours->numEssaiCourant]->nbLettreBienPlacees = resultat->nbLettreBienPlacees;
            partieEnCours->resultatsEssais[partieEnCours->numEssaiCourant]->nbLettreMalPlacees = resultat->nbLettreMalPlacees;

            partieEnCours->numEssaiCourant++;
            // Lors d'une victoire ou d'une défaite
            if (resultat->nbLettreBienPlacees == LongueurDesMots || partieEnCours->numEssaiCourant == NbreMaxDEssais){
                
                // Compte le dernier essai en plus si perdu
                if(resultat->nbLettreBienPlacees != LongueurDesMots)
                    partieEnCours->numEssaiCourant++;

                // Saisie du pseudo
                do {
                    AfficherPartie(partieEnCours, debug);
                    attron(COLOR_PAIR(COULEURS_QUESTION));
                    if(resultat->nbLettreBienPlacees == LongueurDesMots){
                        AfficherTexteIndenteSansRetour("Bravo ! Entrez votre pseudo (max 10 caractères) : ");
                    } else {
                        AfficherTexteIndenteSansRetour("Dommage... Le mot était \"");
                        AfficherTexteSansRetour(partieEnCours->solution);
                        AfficherTexteSansRetour("\"");
                        RetourALaLigne();
                        AfficherTexteIndenteSansRetour("Entrez votre pseudo (max 10 caractères) : ");
                    }
                    attroff(COLOR_PAIR(COULEURS_QUESTION));
                    
                    motLu = LireTexte();
                    longueurMotLu = strlen(motLu);

                  // Pseudo doit être en 1 et 10 caractères et ne peut être composé uniquement d'espaces
                } while ( (longueurMotLu > 10) || (longueurMotLu <= 0) || (strspn(motLu, " ") == longueurMotLu));
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
    struct Points * tabScores;
    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    // Vérifie l'allocation
    if(!messageDeRetour){
        AfficherErreurEtTerminer("Erreur d'allocation mémoire lors de l'affichage des scores", 0);
    }

    // Vérifie si le tableau des score est NULL
    if(!(tabScores = LireMeilleursScores(false, NbreDeScoresAAfficher, messageDeRetour)))
        AfficherErreurEtTerminer(messageDeRetour->messageErreur, messageDeRetour->codeErreur);
    
    EffacerEcran();
    RetourALaLigne();
    AfficherTexteDansCadre(" Meilleurs Scores ");
    RetourALaLigne();
    RetourALaLigne();

    // Parcourt le tableau des scores pour les afficher ligne par ligne
    for (int noJoueur = 0; noJoueur < NbreDeScoresAAfficher; noJoueur++){
        // Si le score existe
        if(tabScores[noJoueur].score != -1){
            AfficherTexteIndenteSansRetour(tabScores[noJoueur].name);
            AfficherTexteSansRetour(" : ");
            AfficherNombreSansRetour(tabScores[noJoueur].score);
            RetourALaLigne();
        }
    }

    RetourALaLigne();
    attron(COLOR_PAIR(COULEURS_QUESTION));
    AfficherTexteIndenteSansRetour("Enfoncez ENTER pour continuer ");
    attroff(COLOR_PAIR(COULEURS_QUESTION));
    LireTexte();
    free(messageDeRetour);
    free(tabScores);
}