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
        fprintf(stderr, "%s\n", messageDeRetour->messageErreur);
        return true;
    }
    return false;
}

/// @brief Fonction pour se connecter à la base de données en la créant si elle n'existe pas
/// @param baseDeTest Booléen qui indique si c'est la base de donnees pour les tests unitaires ou pas (et donc: de production)
/// @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un éventuel code d'erreur
/// @return Pointeur vers la structure MYSQL de la connexion
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
    if (!mysql_real_connect(sqlConnection, "127.0.0.1", "root", NULL, NULL, 3306, NULL, 0)){
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

    // Crée la base de données si elle n'existe pas
    requete = (char *)malloc(strlen("CREATE DATABASE IF NOT EXISTS %s") + strlen(db) +1);
    sprintf(requete, "CREATE DATABASE IF NOT EXISTS %s", db);
    if (ExecuterInstructionSQL(sqlConnection, requete, messageDeRetour))
        return NULL;

    // Définit la DB à utiliser
    requete = (char *)malloc(strlen("USE %s") + strlen(db) +1);
    sprintf(requete, "USE %s", db);
    if (ExecuterInstructionSQL(sqlConnection, requete, messageDeRetour))
        return NULL;

    // Crée la table joueurs si elle n'existe pas
    if (ExecuterInstructionSQL(sqlConnection, "CREATE TABLE IF NOT EXISTS joueurs(id_joueur INT AUTO_INCREMENT, nom_joueur VARCHAR(10), score_joueur INT, PRIMARY KEY(id_joueur))", messageDeRetour))
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

    // Verification du nom du joueur
    if(strlen(nomJoueur) > 10 || strlen(nomJoueur) <= 0 ){
        return -1;
    }

    // Génère la requête
    char * selectJoueur = "SELECT id_joueur FROM joueurs WHERE nom_joueur='%s'";
    requete = (char *)malloc(strlen(selectJoueur) + strlen(nomJoueur) +1);
    sprintf(requete, selectJoueur, nomJoueur);

    ExecuterInstructionSQL(sqlConnection, requete, messageDeRetour);

    // Stocke le résultat
    if(!(sqlResult = mysql_store_result(sqlConnection))){
        strcpy(messageDeRetour->messageErreur, mysql_error(sqlConnection));
        messageDeRetour->codeErreur = mysql_errno(sqlConnection);
        return -1;
    }
    
    if (sqlRow = mysql_fetch_row(sqlResult)) {// Si le joueur existe déjà, récupérer l'ID
        id_joueur = atoi(sqlRow[0]);
        mysql_free_result(sqlResult);
        return id_joueur;
    }

    // Si le joueur n'existe pas, l'ajouter et récupérer l'ID auto-incrémenté
    sprintf(requete, "INSERT INTO joueurs (nom_joueur, score_joueur) VALUES ('%s', 0)", nomJoueur);
    ExecuterInstructionSQL(sqlConnection, requete, messageDeRetour);

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
    
    MYSQL * sqlConnection = ConnecterBaseDeDonnees(baseDeTest, messageDeRetour);
    int id_joueur;
    int score;
    
    if(!sqlConnection){
        return false;
    }
    
    if((id_joueur = LireIDJoueur(sqlConnection, nomJoueur, messageDeRetour)) == -1){
        return false;
    }

    // Génère la requête
    score = 11 - nombreDEssais;
    char * selectJoueur = "UPDATE joueurs SET score_joueur=%d WHERE id_joueur=%d";
    char * requete = (char *)malloc(strlen(selectJoueur) + 20); // + 20 pour les valeurs
    sprintf(requete, selectJoueur, score, id_joueur);

    ExecuterInstructionSQL(sqlConnection, requete, messageDeRetour);

    mysql_close(sqlConnection);
    free(requete);
    return true;
}


/// @brief Fonction pour lire les meilleurs scores dans la base de données
/// @param baseDeTest Booleen qui indique si c'est la base de données pour les tests unitaires ou pas (et donc: de production)
/// @param nombreDeScore Le nombre de scores maximum à lire
/// @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un éventuel code d'erreur
/// @return Un pointeur vers le nombre demandé de points (pointeur vers un tableau)
///         ou bien NULL en cas d'erreur
struct Points * LireMeilleursScores(bool baseDeTest, int nombreDeScore, struct Dico_Message *messageDeRetour){
    // FONCTIONS APPELLEES:
    // ConnecterBaseDeDonnees();
    // ExecuterInstructionSQL();
    // malloc
    // Autres fonctions: voir le cours FBD2

    return NULL; // A adapter
}