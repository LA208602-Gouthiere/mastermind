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


// Fonction lire l'identifiant unique du joueur dans la base de donnees
// Si le joueur n'est pas déjà present, il est ajoute puis la fonction
// se rapelle en recursif pour obtenir l'identifiant autoincremente dans la base de donnees
// Paramètres:
// - Pointeur vers la structure de connexion MYSQL
// - Le nom du joueur
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie
// - L'identifiant unique du joueur dans la base de donnees
int LireIDJoueur(MYSQL *sqlConnection, char *nomJoueur, struct Dico_Message *messageDeRetour)
{
    MYSQL_RES *sqlResult;
    MYSQL_ROW sqlRow;

    // FONCTIONS APPELLEES:
    // ExecuterInstructionSQL();
    // Autres fonctions: voir le cours FBD2

    // Verification du nom du joueur: pas NULL et max 50 caracteres

    return 0; // A Adapter
}

// Fonction pour sauver un score dans la base de donnees
// Le score se calcule comme etant (nombre maximum d'essais + 1 - nombre d'essais)
// Paramètres:
// - Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas (et donc: de production)
// - Le nom du joueur
// - Le nombre d'essai.
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie
// - Un booleen qui indique si le sauvetage s'est fait ou pas
bool SauverScore(bool baseDeTest, char *nomJoueur, int nombreDEssais, struct Dico_Message *messageDeRetour)
{
    // FONCTIONS APPELLEES:
    // ConnecterBaseDeDonnees();
    // LireIDJoueur();
    // ExecuterInstructionSQL();
    // Autres fonctions: voir le cours FBD2

    return false; // A adapter
}

// Fonction pour les meilleurs scores dans la base de donnees
// Paramètres:
// - Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas (et donc: de production)
// - Le nombre de scores maximum à lire
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie
// - Un pointeur vers le nombre demandé de Points (pointeur vers un tableau)
//   ou bien NULL en cas d'erreur
struct Points *LireMeilleursScores(bool baseDeTest, int nombreDeScore, struct Dico_Message *messageDeRetour)
{
    // FONCTIONS APPELLEES:
    // ConnecterBaseDeDonnees();
    // ExecuterInstructionSQL();
    // malloc
    // Autres fonctions: voir le cours FBD2

    return NULL; // A adapter
}