#include "./tests.h"
#include "../Includes/score.h"

// Fonction pour remettre la base de donnees a zero avant un test
// Ceci est appelé dans presque tous les tests de DB mais pas ailleurs
// donc pas d'utilisation de SetUp()
void ViderDBDeTest(){
    // Créer ici le code qui vide la DB de test 
    // pour que tous les tests de DB démarrent avec une DB propre.
}

// Test de connexion a la base de donnees
void test_connexionDB_OK(){
    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    MYSQL * sqlConnection = ConnecterBaseDeDonnees(true, messageDeRetour);
    TEST_ASSERT_NOT_NULL(sqlConnection);
    mysql_close(sqlConnection);
    free(messageDeRetour);
}

// Ajouter d'autres tests, à imaginer

// Execute tous les tests de scores dans la base de donnees
void TestsScores()
{
    RUN_TEST(test_connexionDB_OK);
    // Appeler les autres tests ici
}