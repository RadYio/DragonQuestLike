/**
*\file jeu.c
*\brief gestion du jeu
*\author Anna Beranger
*\date 17/02/2022
*/

#include "../lib/jeu.h"
/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, images_t *textures, monde_t * monde, TTF_Font * police){

    detruire_monde(&monde);

    clean_images(textures, police);

    clean_sdl(renderer,window);
}

/*
La fonction charger_combat sert à actualiser l'état du jeu afin de mettre le jeu en version "combat"

#define COMBAT 57

void fction(joueur_t * joueur, monstre_t * monstre, images_t texture){

	char nom_monstre[10];

	apply_texture(textures->arene_combat, renderer, (taille_fenetre[0]/2) - 500, (taille_fenetre[1]/2) - 375); //voir si les coordonnées sont bonnes
	apply_texture(textures->joueur,...);
	//apply_texture la bonne image de monstre -->
	//récupération de l'information via la zone et la salle du joueur
	switch(monde->joueur->zone){
		case 0:
			switch(monde->joueur->salle){
				case (0||1||2):
					//texture du monstre de base de la zone et de la salle
					break;
				case 3:
					//texture du boss de la zone et de la salle
					break;
			}
		case 1:
			switch(monde->joueur->salle){
				case (0||1||2):
					//texture du monstre de base de la zone et de la salle
					break;
				case 3:
					//texture du boss de la zone et de la salle
					break;
			}
		case 2:
			switch(monde->joueur->salle){
				case (0||1||2):
					//texture du monstre de base de la zone et de la salle
					break;
				case 3:
					//texture du boss de la zone et de la salle
					break;
			}
	}

	//Après avoir fait l'affichage de l'arène du joueur et du monstre engagé dans le combat on affiche les pts de vie du monstre en haut et les pts de vie du joueur en bas

	char pv_j[4];
	char pv_m[4];

	snprintf(pv_j, 4, "%d", (monde->joueur->combattant->pvCour));
	snprintf(pv_m, 4, "%d", (monstre->combattant->pvCour));

	--->on doit afficher les pts de vie transformés en string avec un sprintf et un apply_text
	sprintf(opt, pv_j);
	apply_text();

	sprintf(opt, pv_m);
	apply_text();

	//Après les pv du j et du m on affiche un menu avec les options du joueur: attaque ou fuite

	//J'ai besoin d'une case avec attaque à l'intérieur et une case avec fuite à l'intérieur
	apply_texture(textures->attaque,...);
	sprintf(opt, "Attaque");
	apply_text(...);

	apply_texture(textures->fuite,...);
	sprintf(opt, "Fuite");
	apply_text(...);


	//J'ai ensuite besoin que lorsque je clique sur la case, l'action soit réalisée



}

*/
void changement_salle(joueur_t * j, int changement_salle){
	j->salle = (j->salle) + changement_salle;

	switch(j->salle){
		case 0:
      //Si le personnage revient à gauche, on le met tout à droite de la salle sans changer sa hauteur
			j->combattant->x = SCREEN_WIDTH - j->combattant->x - 20 - LARGEUR_PERSONNAGE;
			break;
		case 1:
      //S'il arrive de la gauche, on ne change pas sa hauteur et on le met tout à gauche
			j->combattant->x = 20;
			break;
		case 2:
      //S'il arrive d'en haut on le met tout en haut sans changer son placement latéral
			j->combattant->y = HAUTEUR_PERSONNAGE + 20;
			break;
		case 3:
      //S'il va vers la gauche même cas que pour le cas 0
			j->combattant->x = SCREEN_WIDTH - j->combattant->x - 20 - LARGEUR_PERSONNAGE;
			break;

	}
}

void changement_zone(joueur_t * j){
	(j->zone)++;
	j->salle = 0;

	j->combattant->x = (SCREEN_WIDTH/2) - (LARGEUR_PERSONNAGE/2);
	j->combattant->y = HAUTEUR_PERSONNAGE + 30;
}

int collision_combattant_ecran(combattant_t * combattant, monde_t * monde){


    if(combattant->type == JOUEUR){

        if( (monde->joueur->salle == 0)  && (combattant->x  + LARGEUR_PERSONNAGE >= SCREEN_WIDTH) ){
          changement_salle(monde->joueur, +1);
    		  return(PAS_COLLISION);
    	  }

        if( (monde->joueur->salle == 1)  && (combattant->x <= 0) ){
          changement_salle(monde->joueur, -1);
    		  return(PAS_COLLISION);
    	  }

    	  if( (monde->joueur->salle == 1) && (combattant->x >= ENTREE_GAUCHE_ZONE_SUIVANTE) && (combattant->x + LARGEUR_PERSONNAGE <= ENTREE_DROITE_ZONE_SUIVANTE) && (combattant->y + HAUTEUR_PERSONNAGE >= SCREEN_HEIGHT - 100) ){
    		  changement_zone(monde->joueur);
    		  return(PAS_COLLISION);
    	  }

        switch(monde->joueur->salle){
          case 0:
            if((combattant->y == ENTREE_HAUT_SALLE_1) && (combattant->y + HAUTEUR_PERSONNAGE <= ENTREE_BAS_SALLE_1) && (combattant->x + LARGEUR_PERSONNAGE >= SCREEN_WIDTH)){
              changement_salle(monde->joueur, +1);
    		      return(PAS_COLLISION);
            }
            break;
          case 1:
            if((combattant->y >= ENTREE_HAUT_SALLE_1) && (combattant->y + HAUTEUR_PERSONNAGE <= ENTREE_BAS_SALLE_1) && (combattant->x <= 0)){
              changement_salle(monde->joueur, -1);
    		      return(PAS_COLLISION);
    	      }

    	      if((combattant->x >= ENTREE_GAUCHE_ZONE_SUIVANTE) && (combattant->x + LARGEUR_PERSONNAGE <= ENTREE_DROITE_ZONE_SUIVANTE) && (combattant->y + HAUTEUR_PERSONNAGE >= SCREEN_HEIGHT - 100)){
    		      changement_zone(monde->joueur);
    		      return(PAS_COLLISION);
    	      }
            break;
          case 2:
            if((combattant->x >= ENTREE_GAUCHE_ZONE_SUIVANTE) && (combattant->x + LARGEUR_PERSONNAGE <= ENTREE_DROITE_ZONE_SUIVANTE) && (combattant->y <= 100.0)){
              changement_salle(monde->joueur, -1);
    		      return(PAS_COLLISION);
    	      }

    	      if((combattant->y == ENTREE_HAUT_SALLE_1) && (combattant->y + HAUTEUR_PERSONNAGE <= ENTREE_BAS_SALLE_1) && (combattant->x >= 0.0)){
              changement_salle(monde->joueur, +1);
    		      return(PAS_COLLISION);
            }
            break;
          case 3:
            if((combattant->y == ENTREE_HAUT_SALLE_1) && (combattant->y + HAUTEUR_PERSONNAGE <= ENTREE_BAS_SALLE_1) && (combattant->x + LARGEUR_PERSONNAGE>= SCREEN_WIDTH)){
              changement_salle(monde->joueur, -1);
    		      return(PAS_COLLISION);
    	      }

    	      if((combattant->y == ENTREE_GAUCHE_ZONE_SUIVANTE) && (combattant->y + HAUTEUR_PERSONNAGE <= ENTREE_DROITE_ZONE_SUIVANTE) && (combattant->y + HAUTEUR_PERSONNAGE >= SCREEN_HEIGHT - 100)){
              changement_zone(monde->joueur);
    		      return(PAS_COLLISION);
            }
            break;
        }

    }

    switch(monde->joueur->salle){
      case 0:
        if(combattant->x  < 100.0){

          return(COLLISION);
        }
        if(combattant->y < 100.0){

          return(COLLISION);
        }
        if(combattant->x + LARGEUR_PERSONNAGE  > SCREEN_WIDTH ){

            return(COLLISION);
        }
        if(combattant->y + HAUTEUR_PERSONNAGE > SCREEN_HEIGHT - 100){

            return(COLLISION);
        }
        break;
      case 1:
        if(combattant->x  < 0.0){

          return(COLLISION);
        }
        if(combattant->y < 100.0){

          return(COLLISION);
        }
        if(combattant->x + LARGEUR_PERSONNAGE  > SCREEN_WIDTH - 100.0){

            return(COLLISION);
        }
        if(combattant->y + HAUTEUR_PERSONNAGE > SCREEN_HEIGHT - 100){

            return(COLLISION);
        }
        break;
      case 2:
        if(combattant->x  < 0.0){

          return(COLLISION);
        }
        if(combattant->y < 100.0){

          return(COLLISION);
        }
        if(combattant->x + LARGEUR_PERSONNAGE  > SCREEN_WIDTH - 100){

            return(COLLISION);
        }
        if(combattant->y + HAUTEUR_PERSONNAGE > SCREEN_HEIGHT - 100){

            return(COLLISION);
        }
        break;
      case 3:
        if(combattant->x  < 100.0){

          return(COLLISION);
        }
        if(combattant->y < 100.0){

          return(COLLISION);
        }
        if(combattant->x + LARGEUR_PERSONNAGE  > SCREEN_WIDTH ){

            return(COLLISION);
        }
        if(combattant->y + HAUTEUR_PERSONNAGE > SCREEN_HEIGHT - 100){

            return(COLLISION);
        }
        break;
    }

    return(PAS_COLLISION);
}

int collision_joueur_monstre(combattant_t * joueur, combattant_t * monstre/*monde_t * monde */){

    if( (joueur->x + LARGEUR_PERSONNAGE >= monstre->x) && (joueur->x + LARGEUR_PERSONNAGE <= monstre->x + LARGEUR_PERSONNAGE) && (joueur->y + HAUTEUR_PERSONNAGE >= monstre->y) && (joueur->y + HAUTEUR_PERSONNAGE <= monstre->y + HAUTEUR_PERSONNAGE) ){

        /*
        charger_combat(monde);
        return(PAS_COLLISION);
        */
        return(COLLISION);
    }
    if( (joueur->x + LARGEUR_PERSONNAGE >= monstre->x) && (joueur->x + LARGEUR_PERSONNAGE <= monstre->x + LARGEUR_PERSONNAGE) && (joueur->y  >= monstre->y) && (joueur->y <= monstre->y + HAUTEUR_PERSONNAGE) ){

        return(COLLISION);
        /*
        charger_combat(monde);
        return(PAS_COLLISION);
        */
    }
    if( (joueur->x >= monstre->x) && (joueur->x <= monstre->x + LARGEUR_PERSONNAGE) && (joueur->y >= monstre->y) && (joueur->y <= monstre->y + HAUTEUR_PERSONNAGE) ){

        return(COLLISION);
        /*
        charger_combat(monde);
        return(PAS_COLLISION);
        */
    }
    if( (joueur->x >= monstre->x) && (joueur->x <= monstre->x + LARGEUR_PERSONNAGE) && (joueur->y + HAUTEUR_PERSONNAGE >= monstre->y) && (joueur->y + HAUTEUR_PERSONNAGE <= monstre->y + HAUTEUR_PERSONNAGE) ){

        return(COLLISION);
        /*
        charger_combat(monde);
        return(PAS_COLLISION);
        */
    }
    return(PAS_COLLISION);
}


int collision_combattant_pnj(combattant_t * combattant, nonCombattant_t * pnj){

  if((combattant->x + LARGEUR_PERSONNAGE >= pnj->x) && (combattant->x + LARGEUR_PERSONNAGE <= pnj->x + LARGEUR_PERSONNAGE) && (combattant->y + HAUTEUR_PERSONNAGE >= pnj->y) && (combattant->y + HAUTEUR_PERSONNAGE <= pnj->y + HAUTEUR_PERSONNAGE)){

    return(COLLISION);
  }

  if((combattant->x + LARGEUR_PERSONNAGE >= pnj->x) && (combattant->x + LARGEUR_PERSONNAGE <= pnj->x + LARGEUR_PERSONNAGE) && (combattant->y  >= pnj->y) && (combattant->y <= pnj->y + HAUTEUR_PERSONNAGE) ){

    return(COLLISION);
  }

  if((combattant->x >= pnj->x) && (combattant->x <= pnj->x + LARGEUR_PERSONNAGE) && (combattant->y >= pnj->y) && (combattant->y <= pnj->y + HAUTEUR_PERSONNAGE)){

    return(COLLISION);
  }

  if( (combattant->x >= pnj->x) && (combattant->x <= pnj->x + LARGEUR_PERSONNAGE) && (combattant->y + HAUTEUR_PERSONNAGE >= pnj->y) && (combattant->y + HAUTEUR_PERSONNAGE <= pnj->y + HAUTEUR_PERSONNAGE) ){

    return(COLLISION);
  }

  return(PAS_COLLISION);
}

int collision_combattant_coffre(combattant_t * combattant, nonCombattant_t * coffre){


  if( (combattant->x + LARGEUR_PERSONNAGE >= coffre->x) && (combattant->x + LARGEUR_PERSONNAGE <= coffre->x + LARGEUR_COFFRE) && (combattant->y + HAUTEUR_PERSONNAGE >= coffre->y) && (combattant->y + HAUTEUR_PERSONNAGE <= coffre->y + HAUTEUR_COFFRE) ){

    return(COLLISION);
  }
  if( (combattant->x + LARGEUR_PERSONNAGE >= coffre->x) && (combattant->x + LARGEUR_PERSONNAGE <= coffre->x + LARGEUR_COFFRE) && (combattant->y  >= coffre->y) && (combattant->y <= coffre->y + HAUTEUR_COFFRE) ){

    return(COLLISION);
  }
  if( (combattant->x >= coffre->x) && (combattant->x <= coffre->x + LARGEUR_COFFRE) && (combattant->y >= coffre->y) && (combattant->y <= coffre->y + HAUTEUR_COFFRE) ){

    return(COLLISION);
  }
  if( (combattant->x >= coffre->x) && (combattant->x <= coffre->x + LARGEUR_COFFRE) && (combattant->y + HAUTEUR_PERSONNAGE >= coffre->y) && (combattant->y + HAUTEUR_PERSONNAGE <= coffre->y + HAUTEUR_COFFRE) ){

    return(COLLISION);
  }

  return(PAS_COLLISION);

}

int collision_combattant(combattant_t * combattant, int indice_monstre, monde_t * monde/*, int indice_salle, int indice_zone*/){
    int i;

    if(collision_combattant_ecran(combattant, monde)){
      return(COLLISION);
    }

    if(combattant->type == JOUEUR){
      for(i = 0; i < NB_MONSTRES_SALLE; i++){
        if(collision_joueur_monstre(combattant,monde->zones[monde->joueur->zone]->salles[monde->joueur->salle]->monstres[i]->combattant)){
            return(COLLISION);
        }
      }
    }

    if(combattant->type == MONSTRE){
      for(i = 0; i < NB_MONSTRES_SALLE; i++){
        if(indice_monstre != i){
          /*if(collision_monstre(combattant, salle->monstres[i]->combattant)){
            return(COLLISION);
          }*/
        }
      }
      if(collision_joueur_monstre(monde->joueur->combattant, combattant)){
        return(COLLISION);
      }
    }

    for(i = 0; i < NB_PERSO_SALLE; i++){
      if(collision_combattant_pnj(combattant,monde->zones[monde->joueur->zone]->salles[monde->joueur->salle]->perso[i])){
        return(COLLISION);
      }
    }

    if(collision_combattant_coffre(combattant, monde->zones[monde->joueur->zone]->salles[monde->joueur->salle]->coffre)){
      return(COLLISION);
    }

    return(PAS_COLLISION);
}



int deplacement_droit(combattant_t * entitee, int indice_monstre, monde_t * monde){
    entitee->x = (entitee->x)+entitee->vitesse;
    if(collision_combattant(entitee, indice_monstre, monde)){

        a_gauche(entitee);
        return(1);
    }else{
      return(0);
    }
}

int deplacement_gauche(combattant_t * entitee, int indice_monstre, monde_t * monde){
    entitee->x = (entitee->x)-entitee->vitesse;
    if(collision_combattant(entitee, indice_monstre, monde)){

        a_droite(entitee);
        return(1);
    }else{
      return(0);
    }
}

int deplacement_haut(combattant_t * entitee, int indice_monstre, monde_t * monde){
    entitee->y = (entitee->y)-entitee->vitesse;
    if(collision_combattant(entitee, indice_monstre, monde)){

        en_bas(entitee);
        return(1);
    }else{
      return(0);
    }
}

int deplacement_bas(combattant_t * entitee, int indice_monstre, monde_t * monde){
    entitee->y = (entitee->y)+entitee->vitesse;
    if(collision_combattant(entitee, indice_monstre, monde)){

        en_haut(entitee);
        return(1);
    }else{
      return(0);
    }
}

int distancejoueurmonstre(joueur_t * joueur,monstre_t * monstre){// renvoie la distance entre deux combattants.
  int distance;
  int xa=joueur->combattant->x;
  int ya=joueur->combattant->y;
  int xb=monstre->combattant->x;
  int yb=monstre->combattant->y;
  distance=sqrt(pow(xb-xa,2)+pow(yb-ya,2));
  return distance;
}

void deplacement_monstre(monstre_t * monstre,monde_t * m){
  int valColision=0;
  int direction;
  int distance;
  int dist_min=10;// A METRE JEU.H
  int dist_max=50;// A METRE JEU.H
  int nb_direction=4; //A METRE JEU.H
  int distance_agro=400; //A METRE JEU.H
  if(distancejoueurmonstre(m->joueur,monstre)>distance_agro && monstre->etat==1){
    monstre->etat=0;
    monstre->dir=-1;
  }
  if(distancejoueurmonstre(m->joueur,monstre)<distance_agro && monstre->etat==0){
    monstre->etat=1;
  }
  //printf("%d",monstre->etat);
  if(monstre->etat==0){ // Etat du monde dans lequel il se déplace de manière aléatoire
    if(monstre->dir==-1){
      direction=rand()%nb_direction;
      do{distance=rand()%dist_max;}while(distance<dist_min||distance>dist_max);
      monstre->dir=direction;
      monstre->dist=distance;
      monstre->x=monstre->combattant->x;
      monstre->y=monstre->combattant->y;
    }
    if(monstre->dir==0 && (monstre->combattant->x)>(monstre->x-monstre->dist)){ // Si le monstre va à gauche
      valColision = deplacement_gauche(monstre->combattant, 0, m);
      if(valColision){
        monstre->dir=-1;
      }
      if((monstre->combattant->x)<=(monstre->x-monstre->dist)){
        do{direction=rand()%nb_direction;}while(direction==1);
        do{distance=rand()%dist_max;}while(distance<dist_min||distance>dist_max);
        monstre->x=monstre->combattant->x;
        monstre->dir=direction;
      }
    }
    if(monstre->dir==1 && (monstre->combattant->x)<(monstre->x+monstre->dist)){ // Si le monstre va à droite
      valColision = deplacement_droit(monstre->combattant, 0, m);
      if(valColision){
        monstre->dir=-1;
      }
      if((monstre->combattant->x)>=(monstre->x+monstre->dist)){
        do{direction=rand()%nb_direction;}while(direction==0);
        do{distance=rand()%dist_max;}while(distance<dist_min||distance>dist_max);
        monstre->x=monstre->combattant->x;
        monstre->dir=direction;

      }
    }
    if(monstre->dir==2 && (monstre->combattant->y)>(monstre->y-monstre->dist)){ // Si le monstre va en haut
      valColision = deplacement_haut(monstre->combattant, 0, m);
      if(valColision){
        monstre->dir=-1;
      }
      if((monstre->combattant->y)<=(monstre->y-monstre->dist)){
        do{direction=rand()%nb_direction;}while(direction==3);
        do{distance=rand()%dist_max;}while(distance<dist_min||distance>dist_max);
        monstre->y=monstre->combattant->y;
        monstre->dir=direction;
      }
    }
    if(monstre->dir==3 && (monstre->combattant->y)<(monstre->y+monstre->dist)){ // Si le monstre va en bas
      valColision = deplacement_bas(monstre->combattant, 0, m);
      if(valColision){
        monstre->dir=-1;
      }
      if((monstre->combattant->y)>=(monstre->y+monstre->dist)){
        do{direction=rand()%nb_direction;}while(direction==2);
        do{distance=rand()%dist_max;}while(distance<dist_min||distance>dist_max);
        monstre->y=monstre->combattant->y;
        monstre->dir=direction;
      }
    }
  }
  if(monstre->etat==1){// Etat du monstre dans lequel il fonce vers le joueur
    if(m->joueur->combattant->x < monstre->combattant->x){
      valColision = deplacement_gauche(monstre->combattant, 0,m);
    }
    if(m->joueur->combattant->x > monstre->combattant->x){
      valColision = deplacement_droit(monstre->combattant, 0,m);
    }
    if(m->joueur->combattant->y < monstre->combattant->y){
      valColision = deplacement_haut(monstre->combattant, 0,m);
    }
    if(m->joueur->combattant->y > monstre->combattant->y){
      valColision = deplacement_bas(monstre->combattant, 0,m);
    }
  }
}

void affichage_nonCombattants(SDL_Renderer *renderer, images_t *textures, salle_t* salle){
    if(salle->num_salle == 0)
        for(int i = 0; i < NB_PERSO_SALLE ; i++){
            nonCombattant_position(renderer, textures, salle->perso[i]);
        }
}

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */
void rafraichir(SDL_Renderer *renderer, monde_t * monde, images_t *textures,int * next_tick,int *next_tick_monstre, TTF_Font* police){

    int time_sec=(SDL_GetTicks()/10);

    //on vide le renderer
    SDL_RenderClear(renderer);


    if(monde->etat_jeu == 0 || monde->etat_jeu == 4){

      fond(renderer, textures, monde->etat_jeu, 0,0);

      affichage_menu(renderer, monde, police);

    }
    else{
      fond(renderer, textures, monde->etat_jeu, monde->joueur->zone, monde->joueur->salle);
    }
    if(monde->etat_jeu == 3){
      affichage_inventaire(renderer, monde, textures, police);
    }


    if(monde->etat_jeu == 1){

      joueur_position(renderer, textures, monde->joueur);

      affichage_nonCombattants(renderer,textures,monde->zones[monde->joueur->zone]->salles[monde->joueur->salle]);

      for(int i = 0; i < NB_MONSTRES_SALLE ; i++){
        int suivaleatoir;
        monstre_position(renderer, textures, monde->zones[monde->joueur->zone]->salles[monde->joueur->salle]->monstres[i]);
        if(time_sec>(*next_tick_monstre)){
          if(monde->zones[monde->joueur->zone]->salles[monde->joueur->salle]->monstres[i]->combattant->vitesse==1){
            monde->zones[monde->joueur->zone]->salles[monde->joueur->salle]->monstres[i]->combattant->vitesse=0;
          }else{
            monde->zones[monde->joueur->zone]->salles[monde->joueur->salle]->monstres[i]->combattant->vitesse=1;
          }
          do{
            suivaleatoir=rand()%500;
          }while(suivaleatoir<200||suivaleatoir>500);
          (*next_tick_monstre)+=suivaleatoir;
        }

        if(time_sec>(*next_tick)){
          (*next_tick)+=1;
          deplacement_monstre(monde->zones[monde->joueur->zone]->salles[monde->joueur->salle]->monstres[i], monde);
        }

      }

    }

    //On actualise l'affichage
    SDL_RenderPresent(renderer);

}

void sauvegarde(monde_t* monde){
    FILE * fichier;
    if(monde->partie == 1){
        fichier = fopen("./rsrc/txt/partie1.txt","w");
        fprintf(fichier, "%d\n%d", monde->joueur->combattant->niveau, monde->joueur->zone);
        fclose(fichier);
    }
    if(monde->partie == 2){
      fichier = fopen("./rsrc/txt/partie2.txt","w");
      fprintf(fichier, "%d\n%d", monde->joueur->combattant->niveau, monde->joueur->zone);
      fclose(fichier);
    }

}

/**
 * \brief gestion des évènements avant le rafraichissement
 * \param event contient les événements
 * \param monde les données du monde
 */

void evenements(SDL_Event* event, monde_t * monde){
  const Uint8* keystates = SDL_GetKeyboardState(NULL);


    while(SDL_PollEvent( event )) {
        if(event->type != SDL_KEYDOWN)
           continue;

        if(monde->etat_jeu == 0){
            evenements_menu(event, monde);
        }
        if(monde->etat_jeu == 4){
            choix_partie(event,monde);
            printf("menu partie\n");
        }
        /*!< Jeu en cours */
        if(monde->etat_jeu == 1){
            if(event->key.keysym.sym == SDLK_LEFT) {
                deplacement_gauche(monde->joueur->combattant, 0, monde);
            }
            if(event->key.keysym.sym == SDLK_RIGHT){
                deplacement_droit(monde->joueur->combattant, 0, monde);
            }
            if(event->key.keysym.sym == SDLK_UP){
                deplacement_haut(monde->joueur->combattant, 0, monde);
            }
            if(event->key.keysym.sym == SDLK_DOWN){
                deplacement_bas(monde->joueur->combattant, 0, monde);
            }
            if(event->key.keysym.sym == SDLK_i){// Si en jeu il ouvre l'inventaire
                monde->etat_jeu=3;
                event->key.keysym.sym =0;

            }
        }
        // Si dans l'inventaire le joueur le ferme.
        if(monde->etat_jeu==3){// si dans inventaire
          evenements_inventaire(event, monde);
          if(event->key.keysym.sym == SDLK_i){
            monde->etat_jeu=1;
          }
        }

        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            sauvegarde(monde);
            //On indique la fin du jeu
            monde->etat_jeu = -1;
            printf("fin du jeu");
        }
        if(keystates[SDL_SCANCODE_ESCAPE] ){
            sauvegarde(monde);
            monde->etat_jeu = -1;
            printf("fin du jeu");
        }
    }

    SDL_PumpEvents();
}
