/**
  * \file entitee.h
  * \brief header des entitées
  * \author Anna Béranger, Arthur Fabre, Alex Choux
*/
#ifndef ENTITEE_H
#define ENTITEE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define TAILLE_INVENTAIRE 0
#define NB_EQUIPEMENT 0

#define JOUEUR 1
#define MONSTRE 0



/**
  * \struct combattant_t
  * \brief représentation d'une entitee combattante
*/
typedef struct{
  int pvMax; /**< nombre de point de vie max */
  int pvCour; /**< nombre de point de vie actuelle*/
  int attaque; /**< valeur de ses points d'attaques */
  int vitesse;
  float x; /**< possition sur l'axe des abscisses */
  float y; /**< position sur l'axe des ordonnées */
  int niveau; /**< niveau du combattant */
  int type; /**< type du combattant: monstre ou joueur*/
} combattant_t;

/**
  * \struct objet_t
  * \brief représentation d'un objet
*/
typedef struct{
  int id; /**< id de l'objet */
  int attaque_sup; /**< attaque de l'objet */
  int vie_sup; /**< vie de l'objet */
  char* nom; /**< nom de l'objet */
  char* description; /**< description de l'objet */
} objet_t;

/**
  * \struct joueur_t
  * \brief représentation du joueur
*/
typedef struct{
  combattant_t* combattant; /**< points de vie et position */
  int ** inventaire; /**< id des objets en possession du joueur */
  int ** objet_equipe; /**< id des objets équipés par le joueur */
  int zone;
  int salle;
  int mana;
  int defense;
  int agilite;
}joueur_t;

/**
  * \struct monstre_t
  * \brief représentation d'un monstre
*/
typedef struct{
  combattant_t* combattant; /**< points de vie et position */
  int type; /**< correspond à son type 0=normal 1=boss */
  int x;
  int y;
  int dir;
  int dist;
  int etat;
} monstre_t;

/**
  * \struct nonCombattant_t
  * \brief représentation d'une entitee non combattante
*/
typedef struct{
  int id; /**< id des entités coffre: 0, pnj n°1: 1, pnj n°2: 2 */
  float x; /**< possition sur l'axe des abscisses */
  float y; /**< position sur l'axe des ordonnées */
  int visite; /**< 1: le joueur a déjà intéragi avec l'entité */
} nonCombattant_t;

/**
  * \fn void a_gauche(combattant_t*)
  * \param entitee entitée à déplacer.
  * \brief déplacement d'une entitée à gauche selon un PAS.
*/
void a_gauche(combattant_t* entitee);

void a_droite(combattant_t* entitee);

void en_bas(combattant_t* entitee);

void en_haut(combattant_t* entitee);

joueur_t * creer_joueur();

monstre_t * creer_monstre();

nonCombattant_t * creer_nonCombattant();

void init_joueur(joueur_t * joueur,int niveau, int zone);

void init_monstre(monstre_t * monster, int pvMax, int pvCour, int attaque, int vitesse, int niveau,int type);

void init_nonCombattant(nonCombattant_t* nonCombattant, int id, float x, float y,int visite);

void detruire_joueur(joueur_t ** player);

void detruire_monstre(monstre_t ** monster);

void detruire_nonCombattant(nonCombattant_t ** nonCombat);

objet_t * creer_objet();

void objet_initialiser(objet_t * objet,int id,int attaque_sup,int vie_sup,char*nom,char*description);

void detruire_objet(objet_t**objet);
#endif
