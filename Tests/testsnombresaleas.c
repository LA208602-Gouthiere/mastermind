#include "./tests.h"
#include "../Includes/titre.h"

// Test qui vérifie que chaque nombre n'est présent qu'une seule fois
void TestNombresAleas_Unicite() {
    int * tabNbAleas;
    int occurences;
    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    TEST_ASSERT_NOT_NULL(messageDeRetour);

    tabNbAleas = TableauNombresAleasUniques(0, 10, messageDeRetour);
    TEST_ASSERT_NOT_NULL(tabNbAleas);

    // Test si chaque nombre est présent 1 seule fois
    for (int nombre = 0; nombre <= 10; nombre++){
        occurences = 0;
        for (int index = 0; index <= 10; index++){
            if(nombre == tabNbAleas[index]){
                occurences++;
            }
        }
        TEST_ASSERT_EQUAL_INT(1, occurences);
    }

    tabNbAleas = TableauNombresAleasUniques(-20, -5, messageDeRetour);
    TEST_ASSERT_NOT_NULL(tabNbAleas);

    // Test si chaque nombre est présent 1 seule fois
    for (int nombre = -20; nombre <= -5; nombre++){
        occurences = 0;
        for (int index = 0; index <= 15; index++){
            if(nombre == tabNbAleas[index]){
                occurences++;
            }
        }
        TEST_ASSERT_EQUAL_INT(1, occurences);
    }

    free(messageDeRetour);
}

// Test qui vérifie si on peut mettre des bornes invalides
void TestNombresAleas_BornesInvalides() {
    int * tabNbAleas;
    struct Dico_Message * messageDeRetour = (struct Dico_Message *)malloc(sizeof(struct Dico_Message));
    TEST_ASSERT_NOT_NULL(messageDeRetour);

    tabNbAleas = TableauNombresAleasUniques(10, 0, messageDeRetour);
    TEST_ASSERT_NULL(tabNbAleas);

    tabNbAleas = TableauNombresAleasUniques(-1, -2, messageDeRetour);
    TEST_ASSERT_NULL(tabNbAleas);

    free(messageDeRetour);
}

// Execute tous les tests de comparaison de mots
void TestsNombresAleas(){
    RUN_TEST(TestNombresAleas_Unicite);
    RUN_TEST(TestNombresAleas_BornesInvalides);
}