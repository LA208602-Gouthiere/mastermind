#include "./tests.h"
#include "../Includes/mots.h"

// Test qui lit un dictionnaire sans erreur
// Il verifie que les informations suivantes sont bien lue:
// - Structure Dictionnaire non nulle
// - Nombre de mots correct
// - Verification que les mots de la liste sont bien lus
void TestDictionnaire_OK()
{
    // Créer le test ici
}

// Ajouter d'autres tests, à imaginer

// Execute tous les tests de lecture du dictionnaire
void TestsDictionnaire()
{
    RUN_TEST(TestDictionnaire_OK);
    // Appeler les autres tests ici
}