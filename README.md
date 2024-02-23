# Jeu de Roulette Russe en C avec SDL et MySQL

Ce projet est un jeu de roulette russe développé en langage C utilisant la bibliothèque SDL pour l'interface graphique et MySQL pour la gestion des scores.

## Prérequis

Avant de pouvoir compiler et exécuter ce jeu, assurez-vous d'avoir les éléments suivants installés sur votre système :

- Un compilateur C compatible avec le standard C99 (par exemple, GCC)
- La bibliothèque SDL (Simple DirectMedia Layer) et ses dépendances
- Un serveur MySQL et les bibliothèques de développement MySQL pour la gestion des utilisateurs

## Compilation

Pour compiler le jeu, un makefile à été réalisé afin de faciliter l'installation pour le joueur, il faudra juste exécuter la commande suivante

```bash
make
```

Assurez-vous que les bibliothèques SDL sont correctement configurées et accessibles depuis votre environnement de compilation.

## Configuration de la base de données

Ce jeu utilise une base de données MySQL pour enregistrer les noms des joueurs. Assurez-vous d'avoir configuré votre base de données et d'avoir modifié les informations de connexion appropriées dans le fichier `register.c`.

## Exécution

Une fois compilé avec succès, vous pouvez exécuter le jeu en utilisant la commande suivante :

```bash
./prog
```

## Fonctionnalités

- Interface graphique intuitive développée avec la bibliothèque SDL.
- Jeu de roulette russe.
- Système de gestion des noms d'utilisateurs utilisant une base de données MySQL.

## Auteur

Ce jeu a été développé par Mehdi Benchrif, Lucas Defaud et Ahmed Satouri.
