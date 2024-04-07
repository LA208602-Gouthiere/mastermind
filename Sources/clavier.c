#include "../Includes/common.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"

/// @brief Lit au clavier et renvoit une chaîne de caractères en l'affichant
/// @return chaine de caractères
char * LireTexte()
{
   char caractere;
   char * texte = (char *)malloc(1);
   checkAllocation(texte);

   // Ajoute les caractères au string tant que ENTER n'est pas appuyé
   int carPos = 0;
   while ((caractere = getch()) != '\n') {
      texte[carPos] = caractere;
      carPos++;
      texte = (char *)realloc(texte, carPos + 1); // Rajoute de la mémoire pour 1 caractère supplémentaire
      checkAllocation(texte);
   }
   texte[carPos] = '\0'; // Ajout du null byte
   
   return texte;
}

/// @brief Vérifie si l'allocation mémoire est réussie sinon quitte le programme
/// @param pointeur Pointeur à vérfier
void checkAllocation(void * pointeur){
   if (!pointeur)
      AfficherErreurEtTerminer("Erreur d'allocation mémoire", 0);
}