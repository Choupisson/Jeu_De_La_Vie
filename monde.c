#include "monde.h"

/**
 * Initialise le monde m avec lin ligne et col colonnes, alloue une matrix de dimension lin x col en mémoire, et remplit chaque case avec une cellule morte.
 * @param m l'adresse d'un monde
 * @param lin un nombre entier de ligne
 * @param col un nombre entier de colonne
*/
void initEmpty( monde * m, int lin, int col){
  m->lin = lin;
  m->col = col;

  m->cellules = (char**) malloc(lin * sizeof(char*));
  for (int i=0; i<lin ; i++){
    m->cellules[i] = (char*) malloc(col * sizeof(char));
    for (int j=0; j<col; j++){
      m->cellules[i][j] = ' ';
    }
  }
}

/**
 * Affiche le contenue de chaque cellule du monde m.
 * Une cellule morte est représentée par ' ', une cellule vivante par '*', et les cellules sont séparées par des barres verticales |
 * @param m l'adresse d'un monde
*/
void print(monde * m){
  //printf("\033[5;0H");
  //Pour chaque ligne du monde
  for(int i=0; i<m->lin; i++){
    //Pour chaque colone du monde
    for(int j=0; j<m->col; j++){
      //on affiche '|' suivit du contenue de la cellule à cette ligne et cette colone
      printf("|%c",m->cellules[i][j]);
    }
    // puis on rajoute '|' et un saut de ligne
    printf("|\n");
  }
  printf("\n");
}

/**
 * Retourne l'état de la cellule située à la ligne l et la colonne c. 
 * Si la cellule n'est pas dans le monde, l'etat retourné est toujours ' '. 
 * @param m l'adresse d'un monde
 * @param l un numero entier de ligne
 * @param c un numero entier de colonne
 * @return Un caractère representant l'etat de la cellule, ' ' ou '*'
*/
char getCell(monde * m, int l, int c){
  if (0<l && l<m->lin+1 && 0<c && c<m->col+1){
    // Si la cellule visé existe dans le monde,
    // retourne son état.
    return m->cellules[l-1][c-1];
  }
  else {
    // Sinon, retourne ' ' pour cellule morte.
    return ' ';

  }
}

/**
 * Modifie l'état de la cellule située à la ligne l et la colonne c.
 * Si state est '*', la cellule devient vivante, sinon elle meurt. 
 * Si la cellule n'est pas dans le monde, ne fait rien.
 * @param m l'adresse d'un monde
 * @param l un numero de ligne entier
 * @param c un numero de colonne entier
 * @param state un caractère
*/
void setCell(monde * m, int l, int c, char state){
  if (0<l && l<m->lin+1 && 0<c && c<m->col+1){
    // Si la cellule visée existe dans le monde
    if (state == '*'){
      // Si l'etat de state correspond à vivant, change l'etat de la cellule à vivant
      m->cellules[l-1][c-1] = '*';
    }
    else {
      // Sinon change l'etat de la cellule à mort.
      m->cellules[l-1][c-1] = ' ';
    }
    
  }
}

/**
 * Applique les règles du Jeu de la vie au monde 'avant' et enregistre les résultats dans le monde 'apres'. Les deux adresses ne doivent pas correspondre au même monde.
 * @param avant l'adresse d'un monde
 * @param apres l'adresse d'un monde
*/
void evolve( monde * avant, monde * apres){
  int cell_all_dead_in_last_line = 0; //bool
  int cell_all_dead_in_curent_line = 1; //bool
  //pour chaque cellule du monde
  for (int i=0; i<avant->lin; i++){
    for (int j=0; j<avant->col; j++){
      //on compte le nombre de cellule dans le voisinage a l'aide d'un compteur
      int compteur_cell_autour = 0;
      if (avant->cellules[i][j] == '*'){
        cell_all_dead_in_curent_line = 0;
        
        //si la cellule au centre est vivante, on retire 1 au compteur de base pour ne pas compter la cellule elle même
        compteur_cell_autour = -1;
      }
      for (int i2=i-1+cell_all_dead_in_last_line; i2<i+2; i2++){
        for (int j2=j-1; j2<j+2; j2++){
          if ( getCell(avant, i2+1, j2+1) == '*' ){
            compteur_cell_autour ++;
          }
        }
      }
      
      if (compteur_cell_autour ==3){
        //si la cellule est entourée de 3 cellules vivantes, elle vit (ou revit)
        apres->cellules[i][j] = '*';
      }
      else if (compteur_cell_autour==2 ){ 
        //sinon si elle est entourée de 2 cellules vivantes, elle reste dans le même état
        apres->cellules[i][j] = avant->cellules[i][j];
      }
      else {
        //dans tous les autres cas elle meurt (ou reste morte);
        apres->cellules[i][j] = ' ';
      }
    }

    /* les bools si dessous permettent de ne pas avoir à regarder l'état des cellules au dessus de la cellule actuelle quand la ligne précedente ne contenait aucune cellule vivante */
    cell_all_dead_in_last_line = cell_all_dead_in_curent_line;
    cell_all_dead_in_curent_line = 1;
  }
}

/**
 * Applique les règles du Jeu de la vie nbGen fois au monde 'avant' et enregistre les résultats dans le monde 'apres'. 
 * Les deux adresses ne doivent pas correspondre au même monde.
 * @param avant l'adresse d'un monde
 * @param apres l'adresse d'un monde
 * @param nbGen un nombre entier de génération
*/
void runSimu( monde * avant, monde * apres, int nbGen){
  if (nbGen <0){
    //si le nombre de generation est inferieur à 0, on ne fait rien
    return;
  }
  else if (nbGen == 0){
    //si le nombre de generation est 0, on copie avant dans apres
    for (int i=0; i<avant->lin; i++){
      for (int j=0; j<avant->col; j++){
        apres->cellules[i][j] = avant->cellules[i][j];
      }
    }
    return;
  }
  else if (nbGen == 1){
    //si le nombre de generation est 1, on utilise la fonction evolve une fois
    evolve(avant, apres);
    return;
  }

  //sinon, on utilise nGen fois la fonction evolve sur deux monde que l'on interchange
  monde * swap = NULL;  
  monde * apres_2 = apres;
  monde *temp = malloc(sizeof(monde));
  initEmpty(temp,avant->lin,avant->col);
  evolve(avant,temp);
  for (int i=1;i<nbGen;i++){
    evolve(temp, apres_2);
    swap = temp;
    temp = apres_2;
    apres_2 = swap;
  }
  if (nbGen %2 == 1) {
    /* Si le nombre de generation est impaire, apres n'est pas la dernière table à avoir évoluée , il faut donc mettre le contenue de temp dans apres */
    freeWorld(apres); // on suprime le contenue des cellules de apres
    apres->cellules = temp->cellules; //on remplace le pointeur vers les cellules de apres par celui vers les cellules de temp
    free(temp);
    
  }
  else 
  {
    /* Sinon, apres est la dernières table à avoir évolué, il ne reste donc qu'à supprimer le monde temporaire. Lorsque le nombre de generation est impaire, c'est apres_2 qui pointe vers le monde temporaire à ce moment du programme. On supprime donc le monde tmeporaire via apres_2*/
    freeWorld(apres_2);
    free(apres_2);
  }
  
}

/**
 * Initialise un monde m passé en paramètre à partir du contenue du fichier nommé filename.
 * Le nom de fichier doit contenir l'extension.
 * Le fichier doit contenir les dimensions du monde sur la première ligne, séparées par 'x'.
 * @param filename le nom d'un fichier sous forme d'une chaine de caractère
 * @param m l'adresse d'un monde
 * @return -1 si le fichier n'a pas pu être ouvert, 0 sinon
*/
int initialize_world_from_file(char * filename, monde *m){
  FILE * fichier = NULL;
  
  char * testLigneVide = NULL ;
  fichier = fopen(filename,"r") ;
  if( fichier != NULL ) {
    char * ligne = malloc(500 * sizeof(char)); //buffer de lecture

    //on recupere le format de la grille sur la premiere ligne 
    //Récupération de la ligne
    testLigneVide = fgets( ligne, 500, fichier ) ;
    m->lin = atoi(ligne); //on recupere le premiers nombre de la ligne
  
     //Récupération de la colonne
    testLigneVide = fgets( ligne, 500, fichier ) ;
    m->col = atoi( ligne) ;
    
    //on initialise un monde à la bonne taille
    initEmpty(m,m->lin, m->col);
    //puis on lit m->lin lignes du fichier
    int i = 0, j = 0;
    while( testLigneVide != NULL && i<m->lin)
    {
      testLigneVide = fgets( ligne,500, fichier ) ;
      j = 0;
      // on lit ensuite un caractère sur deux pour éviter les | du format
      while ((ligne[j*2+1] == ' ' || ligne[j*2+1] == '*') && j<m->col && ligne[j*2]!='\0')
      {
        m->cellules[i][j] = ligne[j*2+1] ; // on recupie l'état lu dans la cellule
        j++;
      }
      // si la ligne était trop courte, on change le reste des cellules de la ligne en cellules mortes.
      if (j < m->col)
      {
        for (; j<m->col; j++)
        {
          m->cellules[i][j] = ' ';
        }
      }
      i++ ;
    }
    free(ligne);

    //Si il n'y avait pas assez de ligne, on change le reste des cellules en cellules mortes
    if (i<m->lin)
    {
      for (; i<m->lin; i++){
        for (int j = 0; j<m->col; j++){
            m->cellules[i][j] = ' '; 
        }
      }
    }
    fclose( fichier ) ;
  }
  else {
    //erreur de lecture
    return -1;
  }

  return 0;
}

/**
 * Recopie du monde pointé par m dans le fichier nommé filename.
 * Le nom de fichier doit contenir l'extension.
 * La première ligne contient les dimensions du monde, séparées par 'x'.
 * @param filename le nom d'un fichier sous forme d'une chaine de caractère
 * @param m l'adresse d'un monde
 * @return -1 si le fichier n'a pas pu être ouvert, -2 si le format est incorrecte, 0 sinon
*/
int save_world_to_file(char * filename, monde * m){

  FILE * fichier = NULL;
  char ligne[500] ="" ;
  char * testLigneVide = NULL ;
  fichier = fopen(filename,"w+") ;
  if( fichier != NULL )
  {
    //On écrit le format du monde sur la première ligne
    fprintf(fichier,"%ix%i\n",m->lin,m->col);
    //Puis on recopie l'état de chaque cellule dans le fichier, séparé par des |
    for (int i=0; i<m->lin; i++){
      for (int j=0; j<m->col; j++){
        fprintf(fichier,"|%c",m->cellules[i][j]);
      }
      fprintf(fichier,"|\n");
    }
    fclose( fichier ) ;
  }
  else 
  {
    //Erreur de lecteur
    return -1;
  }

  return 0;
}

/**
 * Change l'etat de p % des cellules d' monde vide m en 'vivant'.
 * Le monde passé en paramètre doit deja être initialisé.
 * @param m l'adresse d'un monde
 * @param p un nombre entier
*/
void initAleatLive(monde* m, int p){
  srand( time(NULL) ) ;
  int nombre_vivant_pour_p;
  if (p >= 100){
    nombre_vivant_pour_p = m->lin * m->col;
  }
  else {
    nombre_vivant_pour_p = ((double)(m->lin*m->col)/100)*p; //on calcule le nombre de cellules qui doivent etre vivantes en fonction du pourcentage donné et du nombre de cellules
  }
  
  for (int k=0; k<nombre_vivant_pour_p; k++){ //pour chaque cellule qui doit etre vivante
    // On calcule des coordonées aleatoires dans la matrice
    int i = rand()% m->lin;
    int j = rand()% m->col;
    // Tant que les coordonées contiennent une cellule deja vivante, on recalcule des coordonées aléatoires 
    while (m->cellules[i][j] != ' ')
    {
      i = rand()% m->lin;
      j = rand()% m->col;
    }
    // Puis on rends la cellule à ces coordonées vivante 
    m->cellules[i][j] = '*';
  }

}

/**
 * Libère la mémoire utilisée par le monde à l'adresse m.
 * @param m l'adresse d'un monde
*/
void freeWorld(monde * m){
  for (int i=0; i<m->lin; i++){
    free(m->cellules[i]); // on libère chaque sous tableau
  }
  free(m->cellules); // puis on libère le tableau principale
}