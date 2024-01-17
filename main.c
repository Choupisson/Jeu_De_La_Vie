#include <stdio.h>
#include "monde.h"
#include "monde_test.h"
//#include <unistd.h>




int main(void) {
  //allTest();


  monde m1;
  int choix_user_1 =0;
  while (choix_user_1 != 1){
    printf("Voulez-vous :\n");
    printf("\t1 - Créer un monde\n");
    printf("\t2 - Importer un monde\n");


    printf("Entrez le numéro correspondant à votre choix : ");
    scanf("\n%i",&choix_user_1);

    if (choix_user_1 == 1){
      int nb_ligne = 0;
      int nb_colone = 0;
      printf("Combien de ligne? ");
      scanf("\n%i",&nb_ligne);
      printf("Combien de colone? ");
      scanf("\n%i",&nb_colone);
      initEmpty(&m1, nb_ligne, nb_colone);
      printf("Voulez vous l'initialisé de manière aléatoire ?\n\
        1 - Oui\n\
        2 - Non\n");
      int choix_user_1_2 = 0;
      scanf("\n%i",&choix_user_1_2);
      if (choix_user_1_2 == 1){
        printf("Donnez le pourcentage de cellules qui doivent être vivantes\n");
        int choix_user_1_3 = 0;
        scanf("\n%i",&choix_user_1_3);
        initAleatLive(&m1, choix_user_1_3);
      }

      printf("\nMonde de %i ligne et %i colone créé\n\n",nb_ligne,nb_colone);
      print(&m1);
    }
    else if (choix_user_1 == 2){
      printf("Entrez le nom du fichier\n");
      char nom_fichier[100];
      scanf("\n%s",nom_fichier);
      //printf("\nNom fichier : %s",nom_fichier);
      if (initialize_world_from_file(nom_fichier,&m1) == 0){
        printf("\nMonde initialisé depuis le fichier %s\n",nom_fichier);
        print(&m1);
        break;
      } else {
        printf("\nErreur lors de la lecture du fichier : %s\n",nom_fichier);
      }
    }

  }



  printf("\n");

  int choix_user_2 = 0;
  int print_mode = 1;
  char nom_fichier[100] = " ";

  int choix_user_3 = 0;
  while (choix_user_3 != 3){
    if (choix_user_3 != 1){
      printf("Voulez-vous :\n");
    printf("\t1 - Modifier le monde\n");
    printf("\t2 - Simuler des generations du monde\n");
    printf("\t3 - Quiter le programme\n");

    printf("Entrez le numéro correspondant à votre choix : ");
    scanf("\n%i",&choix_user_3);
    }
    if (choix_user_3 == 1){
      printf("== Mode edition ==\n");
      printf("Entrez la modifications à faire dans le format suivant\n x y '*' ou '_'\n ou entrez -1 pour quitter le mode edition\n");
      int x=0, y=0;
      char etat[100];
      scanf("%i",&x);
      if (x != -1){
        scanf("%i %s",&y,etat);
      }

      if (x ==-1){
        choix_user_3 = 0;
        continue;
      }
      else {
        if (etat[0] == '*'){
          setCell(&m1, x, y, '*');
        }
        else {
          setCell(&m1, x, y, ' ');
        }
        if (print_mode == 2){
          save_world_to_file(nom_fichier,&m1);
        }
        print(&m1);
      }


    }
    else if (choix_user_3 == 2)
    {
      if (choix_user_2 == 0){
        while (choix_user_2 != 1 && choix_user_2 !=2 && choix_user_2 != 3){
          printf("\nLorsque le monde est simulé, voulez-vous :\n");
          printf("\t1 - Voir les résultats en direct\n");
          printf("\t2 - Enregistrer les résultats dans un fichier\n");

          printf("Entrez le numéro correspondant à votre choix : ");
          scanf("\n%i",&choix_user_2);

          if (choix_user_2 == 1){
            break;
          }
          if (choix_user_2 == 2){
            print_mode = 2;
            printf("\nEntre le nom du fichier où enregistrer les résultats\n");
            scanf("\n%s",nom_fichier);
            break;
          }
        }
      }

      int nb_gen = 0;
      printf("Combien de génération ?\n");
      scanf("\n%i",&nb_gen);
      monde m2;
      initEmpty(&m2,m1.lin,m1.col);
      runSimu(&m1, &m2, nb_gen);

      if (print_mode == 1)
      {
        print(&m2);
      }
      else
      {
        save_world_to_file(nom_fichier, &m2);
      }

      freeWorld(&m2);

    }
    else if (choix_user_3 == 3)
    {
      return 0;
    }
  }


  freeWorld(&m1);
  return 0;
}
