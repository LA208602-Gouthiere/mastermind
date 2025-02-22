#include "./tests.h"
#include "../Includes/mots.h"

// === Tests qui vérifient des mots identiques ===
void TestComparerMots_Identiques1() {
    struct ResultatLigne * resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    TEST_ASSERT_NOT_NULL(resultat);
    TEST_ASSERT_TRUE(ComparerMots("abri", "abri", resultat));
    TEST_ASSERT_EQUAL_INT(4, resultat->nbLettresBienPlacees);
    TEST_ASSERT_EQUAL_INT(0, resultat->nbLettresMalPlacees);
    free(resultat);
}

void TestComparerMots_Identiques2() {
    struct ResultatLigne * resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    TEST_ASSERT_NOT_NULL(resultat);
    TEST_ASSERT_TRUE(ComparerMots("aaaa", "aaaa", resultat));
    TEST_ASSERT_EQUAL_INT(4, resultat->nbLettresBienPlacees);
    TEST_ASSERT_EQUAL_INT(0, resultat->nbLettresMalPlacees);
    free(resultat);
}

void TestComparerMots_Identiques3() {
    struct ResultatLigne * resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    TEST_ASSERT_NOT_NULL(resultat);
    TEST_ASSERT_TRUE(ComparerMots("zzzz", "zzzz", resultat));
    TEST_ASSERT_EQUAL_INT(4, resultat->nbLettresBienPlacees);
    TEST_ASSERT_EQUAL_INT(0, resultat->nbLettresMalPlacees);
    free(resultat);
}

// === Tests qui vérifient des mots différents ===
void TestComparerMots_Differents1() {
    struct ResultatLigne * resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    TEST_ASSERT_NOT_NULL(resultat);
    TEST_ASSERT_TRUE(ComparerMots("abri", "coup", resultat));
    TEST_ASSERT_EQUAL_INT(0, resultat->nbLettresBienPlacees);
    TEST_ASSERT_EQUAL_INT(0, resultat->nbLettresMalPlacees);
    free(resultat);
}

void TestComparerMots_Differents2() {
    struct ResultatLigne * resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    TEST_ASSERT_NOT_NULL(resultat);
    TEST_ASSERT_TRUE(ComparerMots("papa", "apap", resultat));
    TEST_ASSERT_EQUAL_INT(0, resultat->nbLettresBienPlacees);
    TEST_ASSERT_EQUAL_INT(4, resultat->nbLettresMalPlacees);
    free(resultat);
}

void TestComparerMots_Differents3() {
    struct ResultatLigne * resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    TEST_ASSERT_NOT_NULL(resultat);
    TEST_ASSERT_TRUE(ComparerMots("abri", "dada", resultat));
    TEST_ASSERT_EQUAL_INT(0, resultat->nbLettresBienPlacees);
    TEST_ASSERT_EQUAL_INT(1, resultat->nbLettresMalPlacees);
    free(resultat);
}

void TestComparerMots_Differents4() {
    struct ResultatLigne * resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    TEST_ASSERT_NOT_NULL(resultat);
    TEST_ASSERT_TRUE(ComparerMots("dada", "abri", resultat));
    TEST_ASSERT_EQUAL_INT(0, resultat->nbLettresBienPlacees);
    TEST_ASSERT_EQUAL_INT(1, resultat->nbLettresMalPlacees);
    free(resultat);
}

void TestComparerMots_Differents5() {
    struct ResultatLigne * resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    TEST_ASSERT_NOT_NULL(resultat);
    TEST_ASSERT_TRUE(ComparerMots("aaaz", "zaaa", resultat));
    TEST_ASSERT_EQUAL_INT(2, resultat->nbLettresBienPlacees);
    TEST_ASSERT_EQUAL_INT(2, resultat->nbLettresMalPlacees);
    free(resultat);
}

void TestComparerMots_Impossible1() {
    struct ResultatLigne * resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    TEST_ASSERT_NOT_NULL(resultat);
    TEST_ASSERT_FALSE(ComparerMots("abri", "abris", resultat));
    free(resultat);
}

void TestComparerMots_Impossible2() {
    struct ResultatLigne * resultat = (struct ResultatLigne*)malloc(sizeof(struct ResultatLigne));
    TEST_ASSERT_NOT_NULL(resultat);
    TEST_ASSERT_FALSE(ComparerMots("abri", "", resultat));
    free(resultat);
}

// Execute tous les tests de comparaison de mots
void TestsComparaisonDeMots(){
    RUN_TEST(TestComparerMots_Identiques1);
    RUN_TEST(TestComparerMots_Identiques2);
    RUN_TEST(TestComparerMots_Identiques3);
    RUN_TEST(TestComparerMots_Differents1);
    RUN_TEST(TestComparerMots_Differents2);
    RUN_TEST(TestComparerMots_Differents3);
    RUN_TEST(TestComparerMots_Differents4);
    RUN_TEST(TestComparerMots_Differents5);
    RUN_TEST(TestComparerMots_Impossible1);
    RUN_TEST(TestComparerMots_Impossible2);
}