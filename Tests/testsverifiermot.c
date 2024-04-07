#include "./tests.h"
#include "../Includes/mots.h"

    
// Test qui vérifie des mots de bonne longueur avec uniquement des minuscules
// Cas testés:
void TestMot_OK(){
    TEST_ASSERT_TRUE(VerifierMot("aaaa"));
    TEST_ASSERT_TRUE(VerifierMot("zzzz"));
    TEST_ASSERT_TRUE(VerifierMot("azer"));
}

void TestMot_MauvaiseLongueur(){
    TEST_ASSERT_FALSE(VerifierMot("aze"));
    TEST_ASSERT_FALSE(VerifierMot("azert"));
}

void TestMot_AvecMajuscule(){
    TEST_ASSERT_FALSE(VerifierMot("AAAA"));
    TEST_ASSERT_FALSE(VerifierMot("ZZZZ"));
}

void TestMot_AvecCaractereSpecial(){
    TEST_ASSERT_FALSE(VerifierMot("aze "));
    TEST_ASSERT_FALSE(VerifierMot("azér"));
    TEST_ASSERT_FALSE(VerifierMot("/zer"));
}

void TestsVerificationDUnMot()
{
    RUN_TEST(TestMot_OK);
    RUN_TEST(TestMot_MauvaiseLongueur);
    RUN_TEST(TestMot_AvecMajuscule);
    RUN_TEST(TestMot_AvecCaractereSpecial);
}