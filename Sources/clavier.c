#include "../Includes/common.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"

/// @brief Lit au clavier et renvoit une chaîne de caractères en l'affichant
/// @return chaine de caractères
char * LireTexte(){

   int carPos;
   char caractere;
   char * texte = (char *)malloc(1);
   
   if(!texte)
      AfficherErreurEtTerminer("Erreur d'allocation mémoire lors de la saisie au clavier", 0);

   // Désactive l'affichage des caractères tapés pour pouvoir le gérer manuellement
   noecho();

   // Ajoute les caractères au string tant que ENTER n'est pas appuyé
   carPos = 0;
   while ((caractere = getch()) != '\n') {

      // Limite aux caractères affichables
      if(caractere >= 32 && caractere <= 126){
         texte[carPos] = caractere;
         carPos++;
         
         // Rajoute de la mémoire pour 1 caractère supplémentaire
         texte = (char *)realloc(texte, carPos + 1);
         if(!texte)
            AfficherErreurEtTerminer("Erreur d'allocation mémoire lors de la saisie au clavier", 0);

         AfficherCharSansRetour(caractere, 1);
      }

      // Vérifie si la touche BACKSPACE est appuyée
      else if (caractere == 127) {
         if (carPos > 0){
            carPos--;
            texte[carPos] = '\0'; // Décale le nulbyte
            addch('\b'); // Déplace le curseur à gauche
            addch(' '); // Efface le caractèree
            addch('\b'); // Déplace le curseur à gauche à nouveau
         }
      }
   }
   texte[carPos] = '\0'; // Ajout du null byte
   
   return texte;
}