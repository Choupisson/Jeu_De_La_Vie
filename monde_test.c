#include "monde_test.h"
//#include "monde.h"



int allTest(){
  if (initEmptyTest() != 0){
    printf("Test failed for function 'initEmpty'\n");
  }
  else {
    printf("Test passed for function 'initEmpty'\n");
  }

  if (getCellTest() != 0){
    printf("Test failed for function 'getCell'\n");
  } 
  else {
    printf("Test passed for function 'getCell'\n");
  }


  if (setCellTest() != 0){
    printf("Test failed for function 'setCell'\n");
  }
  else {
    printf("Test passed for function 'setCell'\n");
  }


  if (evolveTest() != 0){
    printf("Test failed for function 'evolve'\n");
  }
  else {
    printf("Test passed for function 'evolve'\n");
  }


  if (runSimuTest() != 0){
    printf("Test failed for function 'runSimu'\n");
  }
  else {
    printf("Test passed for function 'runSimu'\n");
  }


  if (initialize_world_from_fileTest() != 0){
    printf("Test failed for function 'initialize_world_from_file'\n");
  }
  else {
    printf("Test passed for function 'initialize_world_from_file'\n");
  }


  if (save_world_to_fileTest() != 0){
    printf("Test failed for function 'save_world_to_file'\n");
  }
  else {
    printf("Test passed for function 'save_world_to_file'\n");
  }


  if (initAleatLiveTest() != 0){
    printf("Test failed for function 'initAleatLive'\n");
  }
  else {
    printf("Test passed for function 'initAleatLive'\n");
  }

  printTest();

  printf("\n");
  return 0;
}


int initEmptyTest(){
  monde monde1;
  initEmpty(&monde1, 10, 10);
  for (int i=0; i<10; i++)
  {
    for (int j=0; j<10; j++)
    {
      if (monde1.cellules[i][j] != ' ')
      {
        return -1;
      }
    }
  }
  freeWorld(&monde1);
  initEmpty(&monde1, 3, 25);
  for (int i=0; i<3; i++)
  {
    for (int j=0; j<25; j++)
    {
      if (monde1.cellules[i][j] != ' ')
      {
        return -1;
      }
    }
  }
  freeWorld(&monde1);
  return 0;
}


int getCellTest(){
  monde m1;
  initEmpty(&m1, 8, 16);
  m1.cellules[5][7] = '*';
  for (int i=0; i<m1.lin; i++)
  {
    for (int j=0; j<m1.col; j++)
    {
     if (i == 5 && j == 7){
       if (getCell(&m1,i+1, j+1) != '*'){
         return -1;
       }
     } 
     else 
     {
       if (getCell(&m1,i+1, j+1) != ' '){
         return -1;
       }
     }
    }
  }

  if (getCell(&m1,104,82) != ' ' || getCell(&m1,-57,-8) != ' ' ){
    return -1;
  }
  
  freeWorld(&m1);
  return 0;
}

int setCellTest(){
  monde m1;
  initEmpty(&m1, 17, 5);
  setCell(&m1, -5, -18,'*');
  setCell(&m1, 50, 4,'*');

  for (int i=0; i<m1.lin; i++)
  {
    for (int j=0; j<m1.col; j++){
      if (m1.cellules[i][j] != ' '){
        return -1;
      }
      
    }
  }

  setCell(&m1, 5, 8,'*');
  for (int i=0; i<m1.lin; i++)
  {
    for (int j=0; j<m1.col; j++){
      if (i == 4 && j == 7){
        if (m1.cellules[i][j] != '*'){
          return -1;
        }  
      }
      else {
        if (m1.cellules[i][j] != ' '){
          return -1;
        }
      }
    }
  }

  setCell(&m1, 5, 8,' ');
  for (int i=0; i<m1.lin; i++)
  {
    for (int j=0; j<m1.col; j++){
      if (m1.cellules[i][j] != ' '){
        return -1;
      }
      
    }
  }
  freeWorld(&m1);
  return 0;
}

int evolveTest(){
  monde m1,m2,m3;
  initEmpty(&m1, 10, 10);
  initEmpty(&m2, 10, 10);
  initEmpty(&m3, 10, 10);

  setCell(&m1, 2, 4, '*');
  setCell(&m1, 3, 2, '*');
  setCell(&m1, 3, 4, '*');
  setCell(&m1, 4, 3, '*');
  setCell(&m1, 4, 4, '*');

  setCell(&m3, 2, 3, '*');
  setCell(&m3, 3, 4, '*');
  setCell(&m3, 3, 5, '*');
  setCell(&m3, 4, 3, '*');
  setCell(&m3, 4, 4, '*');


  evolve(&m1, &m2);

  for (int i=0; i<m2.lin; i++)
  {
    for (int j=0; j<m2.col; j++)
    {
      if (m2.cellules[i][j] != m3.cellules[i][j])
      {
        return -1;
      }
    }
  }


  freeWorld(&m1);
  freeWorld(&m2);
  freeWorld(&m3);

  return 0;
}

int runSimuTest(){
  monde m1,m2,m3;
  initEmpty(&m1, 10, 10);
  initEmpty(&m2, 10, 10);
  initEmpty(&m3, 10, 10);

  setCell(&m1, 2, 4, '*');
  setCell(&m1, 3, 2, '*');
  setCell(&m1, 3, 4, '*');
  setCell(&m1, 4, 3, '*');
  setCell(&m1, 4, 4, '*');

  setCell(&m3, 3, 5, '*');
  setCell(&m3, 4, 3, '*');
  setCell(&m3, 4, 5, '*');
  setCell(&m3, 5, 4, '*');
  setCell(&m3, 5, 5, '*');


  runSimu(&m1, &m2, 4);
  
  for (int i=0; i<m2.lin; i++)
  {
    for (int j=0; j<m2.col; j++)
    {
      if (m2.cellules[i][j] != m3.cellules[i][j])
      {
        return -1;
      }
    }
  }


  freeWorld(&m1);
  freeWorld(&m2);
  freeWorld(&m3);
  return 0;
}

int initialize_world_from_fileTest(){
  monde m1,m2;
  initEmpty(&m1, 8, 5);
  if (initialize_world_from_file("fichier_introuvable.txt", &m2) != -1){
    return -1;
  }
  initialize_world_from_file("ex_monde_TEST_1.txt", &m2);
  
  setCell(&m1, 1, 2, '*');
  setCell(&m1, 1, 5, '*');
  setCell(&m1, 2, 3, '*');
  setCell(&m1, 3, 2, '*');
  setCell(&m1, 3, 4, '*');
  setCell(&m1, 4, 3, '*');
  setCell(&m1, 6, 1, '*');
  setCell(&m1, 6, 3, '*');
  setCell(&m1, 7, 3, '*');
  setCell(&m1, 7, 4, '*');
  setCell(&m1, 7, 5, '*');


  for (int i=0; i<m2.lin; i++)
  {
    for (int j=0; j<m2.col; j++)
    {
      if (m2.cellules[i][j] != m2.cellules[i][j])
      {
        return -1;
      }
    }
  }

  freeWorld(&m1);
  freeWorld(&m2);
  return 0;
}

int save_world_to_fileTest(){
  monde m1,m2;
  initialize_world_from_file("ex_monde_TEST_1.txt", &m1);
  save_world_to_file("ex_monde_TEST_2.txt", &m1);
  initialize_world_from_file("ex_monde_TEST_2.txt",&m2);
  
  for (int i=0; i<m2.lin; i++)
  {
    for (int j=0; j<m2.col; j++)
    {
      if (m2.cellules[i][j] != m2.cellules[i][j])
      {
        return 1;
      }
    }
  }

  freeWorld(&m1);
  freeWorld(&m2);
  return 0;
}

int initAleatLiveTest(){
  monde m1;
  for (int p=0; p<100; p++){
    initEmpty(&m1, 8, 5);
    initAleatLive(&m1, p);
    int nombre_vivant_pour_p = ((double)(m1.lin*m1.col)/100)*p;
    //print(&m1);
    //printf("nombre_vivant_pour_p: %i\n",nombre_vivant_pour_p);
    int cpt_vivant =0;
    for (int i=0; i<m1.lin; i++)
    {
      for (int j=0; j<m1.col; j++)
      {
        if (m1.cellules[i][j] == '*')
        {
          //printf("WUIIIIIIII");
          cpt_vivant ++;
        }
      }
    }
    if (cpt_vivant != nombre_vivant_pour_p){
      //printf("%i %i\n",cpt_vivant,nombre_vivant_pour_p);
      return -1;
    }
    freeWorld(&m1);
  }
  
  return 0;
}


void printTest(){
  monde m1 ;
  initEmpty(&m1, 30, 40);

  for (int i=2; i<30 ; i++){
    for (int j=2; j<30; j++){
      setCell(&m1, i, j, '*');
    }
  }


  for (int i=12; i<19 ; i++){
    for (int j=12; j<19; j++){
      setCell(&m1, i, j, ' ');
    }
  }

  setCell(&m1, 5, 5, ' ');
  setCell(&m1, 5, 6, ' ');
  setCell(&m1, 5, 7, ' ');
  setCell(&m1, 6, 6, ' ');
  setCell(&m1, 7, 6, ' ');
  setCell(&m1, 8, 6, ' ');
  setCell(&m1, 9, 6, ' ');

  setCell(&m1, 5, 10, ' ');
  setCell(&m1, 5, 11, ' ');
  setCell(&m1, 5, 12, ' ');
  setCell(&m1, 6, 10, ' ');
  setCell(&m1, 7, 10, ' ');
  setCell(&m1, 7, 11, ' ');
  setCell(&m1, 8, 10, ' ');
  setCell(&m1, 9, 10, ' ');
  setCell(&m1, 9, 11, ' ');
  setCell(&m1, 9, 12, ' ');

  setCell(&m1, 5, 16, ' ');
  setCell(&m1, 5, 17, ' ');
  setCell(&m1, 5, 18, ' ');
  setCell(&m1, 6, 16, ' ');
  setCell(&m1, 7, 16, ' ');
  setCell(&m1, 7, 17, ' ');
  setCell(&m1, 7, 18, ' ');
  setCell(&m1, 8, 18, ' ');
  setCell(&m1, 9, 18, ' ');
  setCell(&m1, 9, 16, ' ');
  setCell(&m1, 9, 17, ' ');


  setCell(&m1, 5, 22, ' ');
  setCell(&m1, 5, 23, ' ');
  setCell(&m1, 5, 24, ' ');
  setCell(&m1, 6, 23, ' ');
  setCell(&m1, 7, 23, ' ');
  setCell(&m1, 8, 23, ' ');
  setCell(&m1, 9, 23, ' ');

  print(&m1);
  freeWorld(&m1);
}