#include "./tests.h"
#include "../Includes/mots.h"

struct Dico_Message * messageDeRetour;
struct Dictionnaire * dictionnaire;

// Fonction exécutée avant chaque test
void setUp(void) {
    messageDeRetour = (struct Dico_Message*)malloc(sizeof(struct Dico_Message));
}

// Fonction exécutée après chaque test
void tearDown(void) {
    free(messageDeRetour);
    if (dictionnaire != NULL) {
        EffacerDictionnaire(dictionnaire);
        dictionnaire = NULL;
    }
}

// Test qui lit un dictionnaire sans erreur
// Il verifie que les informations suivantes sont bien lue:
// - Structure Dictionnaire non nulle
// - Nombre de mots correct
// - Verification que les mots de la liste sont bien lus
void TestDictionnaire_OK(){
    dictionnaire = LireDictionnaire("FichiersMots/liste_correcte.txt", messageDeRetour);
    
    TEST_ASSERT_NOT_NULL(dictionnaire);
    TEST_ASSERT_EQUAL_INT(416, dictionnaire->nbMots);

    // Vérifie si le premier et dernier mots sont bient sotckés
    TEST_ASSERT_EQUAL_STRING("abri", dictionnaire->listeMots[0]);
    TEST_ASSERT_EQUAL_STRING("zone", dictionnaire->listeMots[415]);
}


// Tests qui lisent des dictionnaires avec erreur (mots avec accents, trop longs, avec majuscule, avec chiffres)
// et vérifie qu'il est bien NULL
void TestDictionnaire_accents(){
    dictionnaire = LireDictionnaire("FichiersMots/liste_accents.txt", messageDeRetour);
    TEST_ASSERT_NULL(dictionnaire);
}

void TestDictionnaire_longueurs(){
    dictionnaire = LireDictionnaire("FichiersMots/liste_longueurs.txt", messageDeRetour);
    TEST_ASSERT_NULL(dictionnaire);
}

void TestDictionnaire_majuscules(){
    dictionnaire = LireDictionnaire("FichiersMots/liste_majuscules.txt", messageDeRetour);
    TEST_ASSERT_NULL(dictionnaire);
}

void TestDictionnaire_chiffres(){
    dictionnaire = LireDictionnaire("FichiersMots/liste_chiffres.txt", messageDeRetour);
    TEST_ASSERT_NULL(dictionnaire);
}

void TestsDictionnaire(){
    RUN_TEST(TestDictionnaire_OK);
    RUN_TEST(TestDictionnaire_accents);
    RUN_TEST(TestDictionnaire_longueurs);
    RUN_TEST(TestDictionnaire_majuscules);
    RUN_TEST(TestDictionnaire_chiffres);
}