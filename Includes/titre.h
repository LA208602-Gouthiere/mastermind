#ifndef TITRE_H
#define TITRE_H

void AfficherIntro(int lin, int col);
void AfficherDisquette(int lin, int col);
void AfficherLecteurDisquetteHaut(int lin, int col);
void AfficherLecteurDisquetteBas(int lin, int col);
void AfficherTitre(int lin, int col, bool animation);
int * TableauNombresAleasUniques(int min, int max, struct Dico_Message *messageDeRetour);

#endif