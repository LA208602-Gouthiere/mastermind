#include "../Includes/common.h"
#include "./tests.h"

int main()
{
    UNITY_BEGIN();

    // Lance tous les tests en une seule fois
    TestsVerificationDUnMot();
    TestsDictionnaire();
    TestsComparaisonDeMots();
    TestsScores();

    UNITY_END();

    printf("Enfoncez une touche");
    getchar();

    return EXIT_SUCCESS;
}