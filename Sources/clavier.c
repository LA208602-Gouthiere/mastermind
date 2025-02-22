#include "../Includes/common.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"

/// @brief Lit au clavier et renvoie une chaîne de caractères en l'affichant.
/// @return une chaine de caractères
char * LireTexte(){

   int carPos;
   char caractere;
   char * texte = (char *)malloc(11);
   
   if(!texte)
      AfficherErreurEtTerminer("Erreur d'allocation mémoire lors de la saisie au clavier", 0);

   // Désactive l'affichage des caractères tapés pour pouvoir le gérer manuellement
   noecho();

   // Ajoute les caractères au string tant que ENTER n'est pas appuyé
   attron(COLOR_PAIR(COULEURS_MOT));
   carPos = 0;
   while ((caractere = getch()) != '\n') {

      // Limite aux caractères affichables et à 10 caractères
      if(caractere >= 32 && caractere <= 126 && carPos < 10){
         texte[carPos] = caractere;
         carPos++;
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

      // Ignore les touches spéciales
      else if (caractere == '\033') {
         getch(); getch();
      }
   }
   attroff(COLOR_PAIR(COULEURS_MOT));

   // Ajout du null byte
   texte[carPos] = '\0';
   
   return texte;
}