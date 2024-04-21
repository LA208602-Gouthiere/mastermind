#include "./tests.h"
#include "../Includes/score.h"

/// @brief Fonction pour remettre la base de données à zéro avant un test
/// Ceci est appelé dans presque tous les tests de DB mais pas ailleurs
/// donc pas d'utilisation de SetUp()
void ViderDBDeTest(){
    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    MYSQL * sqlConnection;

    // Connexion
    if (!(sqlConnection = ConnecterBaseDeDonnees(true, messageDeRetour))){
        fprintf(stderr, "Erreur lors de la connexion à la base de données: %s\n", messageDeRetour->messageErreur);
        free(messageDeRetour);
        return;
    }

    // Requête pour supprimer la DB de test
    if (ExecuterInstructionSQL(sqlConnection, "DROP DATABASE IF EXISTS la208602_test", messageDeRetour)){
        fprintf(stderr, "Erreur lors de la suppression des données: %s\n", messageDeRetour->messageErreur);
        mysql_close(sqlConnection);
        free(messageDeRetour);
        return;
    }

    mysql_close(sqlConnection);
    free(messageDeRetour);
}

// Test requête invalide
void test_requeteInvalide(){
    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    MYSQL * sqlConnection = ConnecterBaseDeDonnees(true, messageDeRetour);
    bool resultat;

    resultat = ExecuterInstructionSQL(sqlConnection, "requête invalide", messageDeRetour);
    TEST_ASSERT_TRUE(resultat);

    mysql_close(sqlConnection);
    free(messageDeRetour);
}

// Test de connexion à la base de données
void test_connexionDB_OK(){
    ViderDBDeTest();

    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    MYSQL * sqlConnection = ConnecterBaseDeDonnees(true, messageDeRetour);

    TEST_ASSERT_NOT_NULL(sqlConnection);

    mysql_close(sqlConnection);
    free(messageDeRetour);
}


// Tests ajout d'un joueur à la base de donnees
void test_ajoutJoueurs_OK(){
    ViderDBDeTest();

    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    MYSQL * sqlConnection = ConnecterBaseDeDonnees(true, messageDeRetour);
    
    int id;
    id = LireIDJoueur(sqlConnection, "joueur1", messageDeRetour);
    TEST_ASSERT_EQUAL_INT(1, id);
    id = LireIDJoueur(sqlConnection, "joueur2", messageDeRetour);
    TEST_ASSERT_EQUAL_INT(2, id);
    id = LireIDJoueur(sqlConnection, "joueur3", messageDeRetour);
    TEST_ASSERT_EQUAL_INT(3, id);
    id = LireIDJoueur(sqlConnection, "joueur1", messageDeRetour);
    TEST_ASSERT_EQUAL_INT(1, id);

    mysql_close(sqlConnection);
    free(messageDeRetour);
}

void test_ajoutJoueurs_longueur(){
    ViderDBDeTest();

    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    MYSQL * sqlConnection = ConnecterBaseDeDonnees(true, messageDeRetour);
    
    int id;
    id = LireIDJoueur(sqlConnection, "", messageDeRetour);
    TEST_ASSERT_EQUAL_INT(-1, id);
    id = LireIDJoueur(sqlConnection, " ", messageDeRetour);
    TEST_ASSERT_EQUAL_INT(-1, id);
    id = LireIDJoueur(sqlConnection, "          ", messageDeRetour);
    TEST_ASSERT_EQUAL_INT(-1, id);
    id = LireIDJoueur(sqlConnection, "0123456789A", messageDeRetour);
    TEST_ASSERT_EQUAL_INT(-1, id);

    mysql_close(sqlConnection);
    free(messageDeRetour);
}

// Tests sauvegarde des scores
void test_sauverScore_OK(){
    ViderDBDeTest();

    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    bool resultat;
    
    resultat = SauverScore(true, "joueur1", 9, messageDeRetour);
    TEST_ASSERT_TRUE(resultat);
    resultat = SauverScore(true, "joueur2", 4, messageDeRetour);
    TEST_ASSERT_TRUE(resultat);

    free(messageDeRetour);
}

void test_sauverScore_longueur(){
    ViderDBDeTest();

    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    bool resultat;
    
    resultat = SauverScore(true, "   ", 9, messageDeRetour);
    TEST_ASSERT_FALSE(resultat);
    resultat = SauverScore(true, "joueur123456789", 4, messageDeRetour);
    TEST_ASSERT_FALSE(resultat);
    resultat = SauverScore(true, "", 9, messageDeRetour);
    TEST_ASSERT_FALSE(resultat);

    free(messageDeRetour);
}

// Tests obtention des meilleurs scores
void test_meilleursScores_OK(){
    ViderDBDeTest();

    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    struct Points * tabScores;
    
    SauverScore(true, "joueur1", 1, messageDeRetour);
    SauverScore(true, "joueur2", 2, messageDeRetour);
    SauverScore(true, "joueur3", 3, messageDeRetour);
    SauverScore(true, "joueur4", 4, messageDeRetour);
    SauverScore(true, "joueur5", 5, messageDeRetour);
    SauverScore(true, "joueur5", 8, messageDeRetour); // Le score moins bon n'est pas sensé remplacer l'ancien

    tabScores = LireMeilleursScores(true, 10, messageDeRetour);
    TEST_ASSERT_EQUAL_STRING("joueur1", tabScores[0].name);
    TEST_ASSERT_EQUAL_INT(10, tabScores[0].score);
    TEST_ASSERT_EQUAL_STRING("joueur5", tabScores[4].name);
    TEST_ASSERT_EQUAL_INT(6, tabScores[4].score);

    free(messageDeRetour);
    free(tabScores);
}

// Execute tous les tests de scores dans la base de donnees
void TestsScores()
{
    RUN_TEST(test_requeteInvalide);
    RUN_TEST(test_connexionDB_OK);
    RUN_TEST(test_ajoutJoueurs_OK);
    RUN_TEST(test_ajoutJoueurs_longueur);
    RUN_TEST(test_sauverScore_OK);
    RUN_TEST(test_sauverScore_longueur);
    RUN_TEST(test_meilleursScores_OK);
}