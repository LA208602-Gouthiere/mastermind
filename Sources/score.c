#include "../Includes/common.h"
#include "../Includes/score.h"


/// @brief Fonction pour exécuter une instruction SQL
///        En cas d'erreur, affiche la cause à la console, mais continue toujours
/// @param sqlConnection Pointeur vers la structure de connexion MYSQL
/// @param instructionSQL Chaine de caractères avec l'instruction à exécuter
/// @param messageDeRetour Structure pour écrire un message et un code en cas d'erreur
/// @return booléen qui indique le résultat : false en cas de succès, true en cas d'erreur
bool ExecuterInstructionSQL(MYSQL *sqlConnection, char *instructionSQL, struct Dico_Message *messageDeRetour){
    if (mysql_query(sqlConnection, instructionSQL)){
        strcpy(messageDeRetour->messageErreur, mysql_error(sqlConnection));
        messageDeRetour->codeErreur = mysql_errno(sqlConnection);
        return true;
    }
    return false;
}

/// @brief Fonction pour se connecter à la base de données en la créant si elle n'existe pas
/// @param baseDeTest Booléen qui indique si c'est la base de donnees pour les tests unitaires ou pas (et donc: de production)
/// @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un éventuel code d'erreur
/// @return Pointeur vers la structure MYSQL de la connexion, NULL en cas d'erreur
MYSQL *ConnecterBaseDeDonnees(bool baseDeTest, struct Dico_Message *messageDeRetour){
    
    MYSQL * sqlConnection;
    char * db;
    char * requete;

    // Initialisation de la structure
    if(!(sqlConnection = mysql_init(NULL))){
        // Si erreur lors de l'initialisation
        strcpy(messageDeRetour->messageErreur, mysql_error(sqlConnection));
        messageDeRetour->codeErreur = mysql_errno(sqlConnection);
        return NULL;
    }

    // Connexion à MySQL
    if (!mysql_real_connect(sqlConnection, ServerDB, "root", NULL, NULL, 3306, NULL, 0)){
        // Si erreur lors de la connexion
        strcpy(messageDeRetour->messageErreur, mysql_error(sqlConnection));
        messageDeRetour->codeErreur = mysql_errno(sqlConnection);
        return NULL;
    }

    // Sélection de la base de données
    if(baseDeTest)
        db = "la208602_test";
    else
        db = "la208602";

    //=== Crée la base de données si elle n'existe pas ===//
    requete = (char *)malloc(strlen("CREATE DATABASE IF NOT EXISTS %s") + strlen(db) +1);

    // Vérifie l'allocation mémoire
    if(!requete){
        sprintf(messageDeRetour->messageErreur, "Erreur d'allocation mémoire lors de la connexion à la base de données");
        messageDeRetour->codeErreur = 0;
        return NULL;
    }
    sprintf(requete, "CREATE DATABASE IF NOT EXISTS %s", db);

    // Exécute et vérifie la requête
    if(ExecuterInstructionSQL(sqlConnection, requete, messageDeRetour)){
        return NULL;
    }

    //=== Définit la DB à utiliser ===//
    requete = (char *)realloc(requete, strlen("USE %s") + strlen(db) +1);

    // Vérifie l'allocation mémoire
    if(!requete){
        sprintf(messageDeRetour->messageErreur, "Erreur d'allocation mémoire lors de la connexion à la base de données");
        messageDeRetour->codeErreur = 0;
        return NULL;
    }
    sprintf(requete, "USE %s", db);
    if(ExecuterInstructionSQL(sqlConnection, requete, messageDeRetour))
        return NULL;

    //=== Crée la table joueurs si elle n'existe pas ===//
    if (ExecuterInstructionSQL(sqlConnection, "CREATE TABLE IF NOT EXISTS joueurs(id_joueur INT AUTO_INCREMENT, nom_joueur VARCHAR(10), score_joueur INT, PRIMARY KEY(id_joueur), UNIQUE(nom_joueur))", messageDeRetour))
        return NULL;

    free(requete);
    return sqlConnection;
}


/// @brief Fonction pour lire l'identifiant unique du joueur dans la base de données. 
///        Si le joueur n'est pas déjà présent, il est ajouté puis la fonction
///        se rappelle en récursif pour obtenir l'identifiant autoincrementé dans la base de données
/// @param sqlConnection Pointeur vers la structure de connexion MYSQL
/// @param nomJoueur Le nom du joueur
/// @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un éventuel code d'erreur
/// @return L'identifiant unique du joueur dans la base de données, retourne -1 en cas d'erreur
int LireIDJoueur(MYSQL *sqlConnection, char *nomJoueur, struct Dico_Message *messageDeRetour){
    
    MYSQL_RES *sqlResult;
    MYSQL_ROW sqlRow;
    char * requete;
    int id_joueur;
    int longueurNomJoueur;

    // Verification du nom du joueur (doit être en 1 et 10 caractères et ne peut être composé uniquement d'espaces)
    longueurNomJoueur = strlen(nomJoueur);
    if((longueurNomJoueur > 10) || (longueurNomJoueur <= 0) || (strspn(nomJoueur, " ") == longueurNomJoueur)){
        strcpy(messageDeRetour->messageErreur, "Le pseudo est invalide");
        messageDeRetour->codeErreur = 0;
        return -1;
    }

    // Génère la requête
    char * selectJoueur = "SELECT id_joueur FROM joueurs WHERE nom_joueur=TRIM('%s')"; // Trim permet de tronquer les espaces en trop
    requete = (char *)malloc(strlen(selectJoueur) + strlen(nomJoueur) +1);

    // Vérifie l'allocation mémoire
    if (!requete){
        sprintf(messageDeRetour->messageErreur, "Erreur d'allocation de mémoire pour le pseudo");
        messageDeRetour->codeErreur = 0;
        return -1;
    }
    sprintf(requete, selectJoueur, nomJoueur);

    // Exécute la requête
    if (ExecuterInstructionSQL(sqlConnection, requete, messageDeRetour)){
        return -1;
    }

    // Stocke le résultat
    if(!(sqlResult = mysql_store_result(sqlConnection))){
        strcpy(messageDeRetour->messageErreur, mysql_error(sqlConnection));
        messageDeRetour->codeErreur = mysql_errno(sqlConnection);
        return -1;
    }
    
    // Si le joueur existe déjà, récupérer l'ID
    if (sqlRow = mysql_fetch_row(sqlResult)) {
        id_joueur = atoi(sqlRow[0]);
        mysql_free_result(sqlResult);
        return id_joueur;
    }

    // Si le joueur n'existe pas, l'ajouter et récupérer l'ID auto-incrémenté
    
    // Génère la requête
    char * insertJoueur = "INSERT INTO joueurs (nom_joueur, score_joueur) VALUES (TRIM('%s'), 0)";
    requete = (char *)realloc(requete, strlen(insertJoueur) + strlen(nomJoueur) +1);

    // Vérifie l'allocation mémoire
    if (!requete){
        sprintf(messageDeRetour->messageErreur, "Erreur d'allocation de mémoire pour le pseudo");
        messageDeRetour->codeErreur = 0;
        return -1;
    }
    sprintf(requete, insertJoueur, nomJoueur);

    // Exécute la requête
    if (ExecuterInstructionSQL(sqlConnection, requete, messageDeRetour)){
        return -1;
    }

    free(requete);
    // Rappel récursif pour obtenir l'ID du nouveau joueur
    return LireIDJoueur(sqlConnection, nomJoueur, messageDeRetour);
}


/// @brief Fonction pour sauver un score dans la base de données
///        Le score se calcule comme étant (nombre maximum d'essais + 1 - nombre d'essais)
/// @param baseDeTest Booleen qui indique si c'est la base de données pour les tests unitaires ou pas (et donc: de production)
/// @param nomJoueur Le nom du joueur
/// @param nombreDEssais Le nombre d'essais.
/// @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un éventuel code d'erreur
/// @return Un booléen qui indique si la sauvegarde s'est faite ou pas
bool SauverScore(bool baseDeTest, char *nomJoueur, int nombreDEssais, struct Dico_Message * messageDeRetour){
    
    MYSQL * sqlConnection;
    int id_joueur;
    int score;
    
    // Vérifie la connexion à la DB
    if(!(sqlConnection = ConnecterBaseDeDonnees(baseDeTest, messageDeRetour))){
        return false;
    }
    
    // Vérifie la lecture de l'identifiant joueur
    if((id_joueur = LireIDJoueur(sqlConnection, nomJoueur, messageDeRetour)) == -1){
        mysql_close(sqlConnection);
        return false;
    }

    // Génère la requête
    score = 11 - nombreDEssais;
    // Ne remplace le score dans la table que s'il est inférieur au nouveau score
    char * selectJoueur = "UPDATE joueurs SET score_joueur=%d WHERE id_joueur=TRIM('%d') AND score_joueur < %d";
    char * requete = (char *)malloc(strlen(selectJoueur) + 20); // + 20 pour les valeurs
    
    // Vérifie l'allocation mémoire
    if (!requete){
        mysql_close(sqlConnection);
        sprintf(messageDeRetour->messageErreur, "Erreur d'allocation de mémoire pour lors de la sauvegarde du score");
        messageDeRetour->codeErreur = 0;
        return false;
    }
    sprintf(requete, selectJoueur, score, id_joueur, score);

    // Vérifie le résultat de la requête
    if (ExecuterInstructionSQL(sqlConnection, requete, messageDeRetour)){
        mysql_close(sqlConnection);
        free(requete);
        return false;
    }

    mysql_close(sqlConnection);
    free(requete);
    return true;
}

/// @brief Fonction pour vider la table des scores
/// @param baseDeTest Booleen qui indique si c'est la base de données pour les tests unitaires ou pas (et donc: de production)
/// @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un éventuel code d'erreur
/// @return Un booléen qui indique si la suppression s'est faite ou pas
bool SupprimerScores(bool baseDeTest, struct Dico_Message *messageDeRetour){
    
    MYSQL * sqlConnection;
    
    if(!(sqlConnection = ConnecterBaseDeDonnees(baseDeTest, messageDeRetour))){
        return false;
    }

    // Vérifie le résultat de la requête
    if (ExecuterInstructionSQL(sqlConnection, "DELETE FROM joueurs;", messageDeRetour)){
        mysql_close(sqlConnection);
        return false;
    }

    mysql_close(sqlConnection);
    return true;
}

/// @brief Fonction pour lire les meilleurs scores dans la base de données
/// @param baseDeTest Booleen qui indique si c'est la base de données pour les tests unitaires ou pas (et donc: de production)
/// @param nombreDeScore Le nombre de scores maximum à lire
/// @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un éventuel code d'erreur
/// @return Un pointeur vers le nombre demandé de points (pointeur vers un tableau)
///         ou bien NULL en cas d'erreur
struct Points * LireMeilleursScores(bool baseDeTest, int nombreDeScore, struct Dico_Message *messageDeRetour){
    
    MYSQL * sqlConnection;
    MYSQL_RES *sqlResult;
    MYSQL_ROW sqlRow;
    struct Points * tabScores;
    
    // Vérifie connexion
    if(!(sqlConnection = ConnecterBaseDeDonnees(baseDeTest, messageDeRetour))){
        return NULL;
    }
    
    // Récupère les n meilleurs joueurs
    char * selectJoueurs = "SELECT * FROM joueurs ORDER BY score_joueur DESC LIMIT %d";
    char * requete = (char *)malloc(strlen(selectJoueurs) + 10);

    // Vérifie l'allocation mémoire
    if (!requete){
        mysql_close(sqlConnection);
        sprintf(messageDeRetour->messageErreur, "Erreur d'allocation de mémoire pour lors de la sauvegarde du score");
        messageDeRetour->codeErreur = 0;
        return false;
    }
    sprintf(requete, selectJoueurs, nombreDeScore);

    // Exécute l'instruction
    if (ExecuterInstructionSQL(sqlConnection, requete, messageDeRetour)){
        mysql_close(sqlConnection);
        return NULL;
    }
    free(requete);

    // Stocke le résultat
    if(!(sqlResult = mysql_store_result(sqlConnection))){
        strcpy(messageDeRetour->messageErreur, mysql_error(sqlConnection));
        messageDeRetour->codeErreur = mysql_errno(sqlConnection);
        return NULL;
    }
    
    // Définit une zone mémoire pour le tableau de structures Points
    tabScores = (struct Points *)malloc(nombreDeScore * sizeof(struct Points));
    
    // Vérifie l'allocation mémoire
    if (!tabScores){
        mysql_free_result(sqlResult);
        mysql_close(sqlConnection);
        sprintf(messageDeRetour->messageErreur, "Erreur d'allocation de mémoire pour lors de la sauvegarde du score");
        messageDeRetour->codeErreur = 0;
        return false;
    }

    // Remplit le tableau de scores
    for (int noJoueur = 0; noJoueur < nombreDeScore; noJoueur++){
        
        if(sqlRow = mysql_fetch_row(sqlResult)){ // Si il reste des scores dans la DB
            tabScores[noJoueur].score = atoi(sqlRow[2]);
            strcpy(tabScores[noJoueur].nom, sqlRow[1]);
        } else { // Sinon pointeur NULL
            tabScores[noJoueur].score = -1;
            strcpy(tabScores[noJoueur].nom, "");
        }
    }
    
    mysql_free_result(sqlResult);
    mysql_close(sqlConnection);
    return tabScores;
}