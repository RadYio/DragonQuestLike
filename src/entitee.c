/**
  * \file entitee.c
  * \brief Contient les fonctions liées aux entitées
  * \author Anna Béranger, Arthur Fabre, Alex Choux
*/
#include  "../lib/entitee.h"

/**
  * \fn void a_gauche(combattant_t*)
  * \param entitee entitée à déplacer.
  * \brief déplacement d'une entitée à gauche selon un pas.
*/
void a_gauche(combattant_t * entitee){
    entitee->x = (entitee->x)-entitee->vitesse;
}
/**
  * \fn void a_droite(combattant_t*)
  * \param entitee entitée à déplacer.
  * \brief déplacement d'une entitée à droite selon un pas.
*/
void a_droite(combattant_t* entitee){
    entitee->x = (entitee->x)+entitee->vitesse;
}
/**
  * \fn void en_bas(combattant_t*)
  * \param entitee entitée à déplacer.
  * \brief déplacement d'une entitée en bas selon un pas.
*/
void en_bas(combattant_t* entitee){
    entitee->y = (entitee->y)+entitee->vitesse;
}
/**
  * \fn void en_haut(combattant_t*)
  * \param entitee entitée à déplacer.
  * \brief déplacement d'une entitée en haut selon un pas.
*/
void en_haut(combattant_t* entitee){
    entitee->y = (entitee->y)-entitee->vitesse;
}


/**
  * \fn joueur_t * creer_joueur()
  * \brief La fonction créer le joueur.
*/
joueur_t * creer_joueur(){
    joueur_t * player;
    player = malloc(sizeof(joueur_t));
    player->combattant= malloc(sizeof(combattant_t));

    player->inventaire= malloc(sizeof(int)*TAILLE_INVENTAIRE);

    player->objet_equipe=malloc(sizeof(int)*NB_EQUIPEMENT);

    return player;
}

/**
  * \fn monstre_t * creer_monstre()
  * \brief La fonction créer le joueur.
*/
monstre_t * creer_monstre(){
  monstre_t * monster;
  monster=malloc(sizeof(monstre_t));
  monster->combattant= malloc(sizeof(combattant_t));
  return monster;
}

/**
  * \fn nonCombattant_t * creer_nonCombattant()
  * \brief La fonction créer une entitée non combattante.
*/

nonCombattant_t * creer_nonCombattant(){
  nonCombattant_t * nonCombat;
  nonCombat = malloc(sizeof(nonCombattant_t));
  return(nonCombat);
}

/**
  * \fn void detruire_joueur(joueur_t ** player)
  * \brief La fonction détruire le joueur.
*/
void detruire_joueur(joueur_t ** player){
  int i;
  free((*player)->combattant);
  (*player)->combattant=NULL;
  for(i=0;i<TAILLE_INVENTAIRE;i++){
    free((*player)->inventaire[i]);
    (*player)->inventaire[i]=NULL;
  }
  free((*player)->inventaire);
  (*player)->inventaire=NULL;
  for(i=0;i<NB_EQUIPEMENT;i++){
    free((*player)->objet_equipe[i]);
    (*player)->objet_equipe[i]=NULL;
  }
  free((*player)->objet_equipe);
  (*player)->objet_equipe=NULL;
  free(*(player));
  (*player)=NULL;
}
/**
  * \fn void detruire_monstre(monstre_t ** player)
  * \brief La fonction détruire le monstre.
*/
void detruire_monstre(monstre_t ** monster){
  free((*monster)->combattant);
  (*monster)->combattant=NULL;
  free(*monster);
  (*monster)=NULL;

}
/**
  * \fn void detruire_nonCombattant(nonCombattant_t ** nonCombat)
  * \brief La fonction détruire un nonCombattant.
*/
void detruire_nonCombattant(nonCombattant_t ** nonCombat){
  free(*nonCombat);
  (*nonCombat)=NULL;
}

/**
  * \fn void init_joueur(joueur_t* joueur, int pvMax, int pvCour, int attaque, int vitesse, int x, int y)
  * \param joueur entitée à initialiser.
  * \param pvMax entitée à initialiser.
  * \param pvCour entitée à initialiser.
  * \param attaque entitée à initialiser.
  * \param vitesse entitée à initialiser.
  * \param x entitée à initialiser.
  * \param y entitée à initialiser.
  * \brief Initialisation du joueur avec des parametres.
*/
void init_joueur(joueur_t * joueur,int niveau, int zone){
  joueur->combattant->pvMax=100;
  joueur->combattant->pvCour=100;
  joueur->combattant->attaque=10;
  joueur->combattant->vitesse=20;
  joueur->combattant->x= 1000/10;
  joueur->combattant->y= 1000/10;
  joueur->combattant->niveau=niveau;
  joueur->combattant->type = 1;
  joueur->zone = zone;
  joueur->salle = 0;
  joueur->objet_equipe[0]=1;
  joueur->objet_equipe[0]=2;
}

/**
  * \fn void init_monstre(monstre_t * monster, int pvMax, int pvCour, int attaque, int vitesse, float x, float y,int niveau)
  * \param monstre entitée à initialiser.
  * \param pvMax entitée à initialiser.
  * \param pvCour entitée à initialiser.
  * \param attaque entitée à initialiser.
  * \param vitesse entitée à initialiser.
  * \param x entitée à initialiser.
  * \param y entitée à initialiser.
  * \brief Initialisation du monstre avec des parametres.
*/
void init_monstre(monstre_t * monster, int pvMax, int pvCour, int attaque, int vitesse,int niveau,int type){
  monster->combattant->pvMax=pvMax;
  monster->combattant->pvCour=pvCour;
  monster->combattant->attaque=attaque;
  monster->combattant->vitesse=vitesse;
  monster->combattant->x=500;
  monster->combattant->y=250;
  monster->combattant->niveau=niveau;
  monster->type=type;
  monster->x=500;
  monster->y=250;
  monster->dir=-1;
  monster->dist=-1;
  monster->combattant->type = 0;
  monster->etat = 0;
}


/**
  * \fn void init_nonCombattant(nonCombattant_t * nonCombat, int id, float x, float y,int visite)
  * \param nonCombat entitée à initialiser.
  * \param x entitée à initialiser.
  * \param y entitée à initialiser.
  * \param visite entitée à initialiser.
  * \brief Initialisation du nonCombattant avec des parametres.
*/
void init_nonCombattant(nonCombattant_t * nonCombat, int id, float x, float y,int visite){
  nonCombat->id=id;
  nonCombat->x=x;
  nonCombat->y=y;
  nonCombat->visite=visite;
}


objet_t * creer_objet(){
  objet_t * objet;
  objet= malloc(sizeof(objet_t));
  objet->nom = malloc(sizeof(char));
  objet->description = malloc(sizeof(char));
  return(objet);
}
void objet_initialiser(objet_t * objet,int id,int attaque_sup,int vie_sup,char*nom,char*description){
  objet->id=id;
  objet->attaque_sup=attaque_sup;
  objet->vie_sup=vie_sup;
  objet->nom=nom;
  objet->description=description;
}

void detruire_objet(objet_t**objet){
  free((*objet)->nom);
  (*objet)->nom=NULL;
  free((*objet)->description);
  (*objet)->description=NULL;
  free(*objet);
  (*objet)=NULL;

}
