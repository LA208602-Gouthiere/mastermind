#include <mysql.h>
#include "./common.h"

#ifndef _DICO_SCORE
#define _DICO_SCORE

/// @brief Structure contenant le nom du joueur et son score.
struct Points {
    char nom[11];
    int score;
};

static const char *ServerDB = "127.0.0.1";
#endif

bool ExecuterInstructionSQL(MYSQL *sqlConnection, char *instructionSQL, struct Dico_Message *messageDeRetour);
MYSQL *ConnecterBaseDeDonnees(bool DBDeTest, struct Dico_Message *messageDeRetour);
int LireIDJoueur(MYSQL *sqlConnection, char *nomJoueur, struct Dico_Message *messageDeRetour);
bool SauverScore(bool baseDeTest, char *nomJoueur, int nombreDEssais, struct Dico_Message *messageDeRetour);
bool SupprimerScores(bool baseDeTest, struct Dico_Message *messageDeRetour);
struct Points *LireMeilleursScores(bool baseDeTest, int nombreDeScore,  struct Dico_Message *messageDeRetour);
