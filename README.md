# Projet Mastermind

Ce référentiel contient le code source et les fichiers associés au projet Mastermind pour l'UE108.

## Description

Le projet consiste à développer, tester et présenter le jeu "Word Mastermind" en langage C. Le jeu présente une grille de 10 lignes sur 2 colonnes à l’écran, où le joueur doit deviner un mot de 4 lettres en maximum 10 essais. À chaque mot entré, le jeu affiche les lettres bien placées avec un signe '+' et les lettres présentes mais mal placées avec un signe '-'. Le joueur peut quitter la partie en appuyant sur Entrée, et s'il ne trouve pas le mot en 10 essais, la solution est affichée. Le score du joueur est enregistré en fonction du nombre d'essais et est stocké en base de données.

## Collaborateurs

- Professeur Moins (email_professeur_moins@votreuniversite.edu)
- Professeur Alary (email_professeur_alary@votreuniversite.edu)

## Structure du Projet

- `src/` : Contient le code source du projet
- `tests/` : Contient les tests unitaires
- `database/` : Contient le fichier Looping décrivant la structure de la base de données
- `docs/` : Contient la documentation du projet
- `rapport/` : Contient le rapport de projet au format PDF

## Itérations de Développement

- **Itération 1 (date de fin estimée : le 5/4)** : Lectures au clavier et affichage à l’écran
- **Itération 2 (date de fin estimée : le 19/4)** : Lecture et vérification des mots
- **Itération 3 (date de fin estimée : le 3/5)** : Gestion des mouvements
- **Itération 4 (date de fin estimée : le 17/5)** : Interactions avec la base de données

## Livrables

À poster sur ConnectED, le dernier jour de cours du Q2 (voir horaire) :
- Le code source complet et compilable
- L’application fonctionnelle compilée pour la machine virtuelle Linux
- Des tests unitaires fonctionnels compilés pour la machine virtuelle Linux
- Le fichier Looping décrivant la structure de la base de données
- Un rapport de projet au format PDF

## Dépassements

En bonus (uniquement si la version minimale décrite plus haut est fonctionnelle), vous pouvez améliorer cette version minimale. Le développement de ces fonctionnalités permet de gagner plus de points.
