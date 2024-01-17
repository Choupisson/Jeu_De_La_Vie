#ifndef MONDE_H
#define MONDE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
  int lin, col;
  char **cellules;
} monde ;


/**
 * Initialise le monde m avec lin ligne et col colonnes, alloue une matrix de dimension lin x col en mémoire, et remplit chaque case avec une cellule morte.
 * @param m l'adresse d'un monde
 * @param lin un nombre entier de ligne
 * @param col un nombre entier de colonne
*/
void initEmpty( monde * m, int lin, int col); 


/**
 * Affiche le contenue de chaque cellule du monde m.
 * Une cellule morte est représentée par ' ', une cellule vivante par '*', et les cellules sont séparées par des barres verticales |
 * @param m l'adresse d'un monde
*/
void print(monde * m);


/**
 * Retourne l'état de la cellule située à la ligne l et la colonne c. 
 * Si la cellule n'est pas dans le monde, l'etat retourné est toujours ' '. 
 * @param m l'adresse d'un monde
 * @param l un numero entier de ligne
 * @param c un numero entier de colonne
 * @return Un caractère representant l'etat de la cellule, ' ' ou '*'
*/
char getCell(monde * m, int l, int c);


/**
 * Modifie l'état de la cellule située à la ligne l et la colonne c.
 * Si state est '*', la cellule devient vivante, sinon elle meurt. 
 * Si la cellule n'est pas dans le monde, ne fait rien.
 * @param m l'adresse d'un monde
 * @param l un numero de ligne entier
 * @param c un numero de colonne entier
 * @param state un caractère
*/
void setCell(monde * m, int l, int c, char state);


/**
 * Applique les règles du Jeu de la vie au monde 'avant' et enregistre les résultats dans le monde 'apres'. Les deux adresses ne doivent pas correspondre au même monde.
 * @param avant l'adresse d'un monde
 * @param apres l'adresse d'un monde
*/
void evolve( monde * avant, monde * apres);


/**
 * Applique les règles du Jeu de la vie nbGen fois au monde 'avant' et enregistre les résultats dans le monde 'apres'. 
 * Les deux adresses ne doivent pas correspondre au même monde.
 * @param avant l'adresse d'un monde
 * @param apres l'adresse d'un monde
 * @param nbGen un nombre entier de génération
*/
void runSimu( monde * avant, monde * apres, int nbGen);


/**
 * Initialise un monde m passé en paramètre à partir du contenue du fichier nommé filename.
 * Le nom de fichier doit contenir l'extension.
 * Le fichier doit contenir les dimensions du monde sur la première ligne, séparées par 'x'.
 * @param filename le nom d'un fichier sous forme d'une chaine de caractère
 * @param m l'adresse d'un monde
 * @return -1 si le fichier n'a pas pu être ouvert, 0 sinon
*/
int initialize_world_from_file(char * filename, monde *m);


/**
 * Recopie du monde pointé par m dans le fichier nommé filename.
 * Le nom de fichier doit contenir l'extension.
 * La première ligne contient les dimensions du monde, séparées par 'x'.
 * @param filename le nom d'un fichier sous forme d'une chaine de caractère
 * @param m l'adresse d'un monde
 * @return -1 si le fichier n'a pas pu être ouvert, -2 si le format est incorrecte, 0 sinon
*/
int save_world_to_file(char * filename, monde * m);


/**
 * Change l'etat de p % des cellules d' monde vide m en 'vivant'.
 * Le monde passé en paramètre doit deja être initialisé.
 * @param m l'adresse d'un monde
 * @param p un nombre entier
*/
void initAleatLive(monde* m, int p); 


/**
 * Libère la mémoire utilisée par le monde à l'adresse m.
 * @param m l'adresse d'un monde
*/
void freeWorld(monde * m);


#endif