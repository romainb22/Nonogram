#ifndef _STRUCTURE_C_
#define _STRUCTURE_C_
#include<stdlib.h>
#include<stdio.h>
#include <MLV/MLV_all.h>

#include "structure.h"
#include "display.h"
#include "util.h"
#define WINDOW_LENGHT 800
#define WINDOW_HEIGHT 600

Nonogram * create_nonogram(){
  Nonogram * myNonoGram = (Nonogram *) calloc(1,sizeof(Nonogram));
  int totalCells, rowCount, rowIndexTotal=0, colCount, colIndexTotal=-1, i,j;
  display_message("\nVeuillez rentrer le nombre de lignes :");
  rowCount = getInt();
  display_message("\nVeuillez rentrer le nombre de colonnes :");
  colCount = getInt();
  //printf("row=%d,col=%d\n",rowCount,colCount);
  myNonoGram->rowIndex = (int **) calloc(rowCount,sizeof(int)*rowCount);
  myNonoGram->colIndex = (int **) calloc(colCount,sizeof(int)*colCount);
  while(rowIndexTotal != colIndexTotal){
    display_message("\nVeuillez rentrer l'index des lignes :");
    getIndexes(myNonoGram->rowIndex, rowCount);
    display_message("\nVeuillez rentrer l'index des colonnes :");
    getIndexes(myNonoGram->colIndex, colCount);
    rowIndexTotal = count_from_table(myNonoGram->rowIndex, rowCount);
    colIndexTotal = count_from_table(myNonoGram->colIndex, colCount);
    if(colIndexTotal != rowIndexTotal){
      display_message("Le nombre de cellules à colorier est incorrect.");
      printf("\n%d != %d\n", colIndexTotal, rowIndexTotal);
    }
  }
  totalCells = colIndexTotal;
  myNonoGram->totalCells = totalCells;
  myNonoGram->colCount = colCount;
  myNonoGram->rowCount = rowCount;
  myNonoGram->gameBoard = malloc(sizeof(int*)*colCount);
  for(i=0;i<colCount;i++){
    myNonoGram->gameBoard[i] = malloc(sizeof(int)*rowCount);
  }
  for(i=0;i<colCount;i++){
    for(j=0;j<rowCount;j++){
      myNonoGram->gameBoard[i][j] = 0;
    }
  }
  return myNonoGram;
}

Nonogram * read_nonogram(){
  Nonogram * myNonoGram = (Nonogram *) calloc(1, sizeof(Nonogram));
  int totalCells, rowCount=0, rowIndexTotal=0, colCount=0, colIndexTotal=-1, i ,j;
  char * path = (char *) malloc(sizeof(char));
  FILE * myFile;
  getPath(path);
  myFile = fopen(path,"r");
  myNonoGram->rowCount = getCountFromFile(myFile);
  myNonoGram->colCount = getCountFromFile(myFile);
  myNonoGram->rowIndex = (int **) calloc(1,sizeof(int *)*rowCount);
  myNonoGram->colIndex = (int **) calloc(1,sizeof(int *)*colCount);
  while(rowIndexTotal != colIndexTotal){
    getIndexesFromFile(myFile, myNonoGram->rowIndex, myNonoGram->rowCount);
    getIndexesFromFile(myFile, myNonoGram->colIndex, myNonoGram->colCount);
    rowIndexTotal = count_from_table(myNonoGram->rowIndex,rowCount);
    colIndexTotal = count_from_table(myNonoGram->colIndex,colCount);
    if(colIndexTotal != rowIndexTotal){
      display_message("cellCountUnmatch\n");
    }
  }
  totalCells = colIndexTotal;
  myNonoGram->totalCells = totalCells;
  myNonoGram->colCount = colCount;
  myNonoGram->rowCount = rowCount;
  myNonoGram->gameBoard = (int **) malloc(sizeof(int *));
  for(i=0;i<colCount;i++){
    for(j=0;j<rowCount;i++){
      myNonoGram->gameBoard[i][j]=0;
    }
  }
  return myNonoGram;
}

void solver(Nonogram * myNonoGram){
  int i,j;
  // Cas des lignes et des colonnes complètes sans compter les cases vides
  for(i=0;i<myNonoGram->colCount;i++){
    if(myNonoGram->colIndex[i][1]==myNonoGram->rowCount){
      for(j=0;j<myNonoGram->rowCount;j++){
        myNonoGram->gameBoard[i][j]=1;
      }
    }
  }
  for(i=0;i<myNonoGram->rowCount;i++){
    if(myNonoGram->rowIndex[i][1]==myNonoGram->colCount){
      for(j=0;j<myNonoGram->colCount;j++){
        myNonoGram->gameBoard[j][i]=1;
      }
    }
  }
  // Cas des lignes et des colonnes complètes en comptant les cases vides
  for(i=0;i<myNonoGram->colCount;i++){
    int res=0;
    for(j=0;j<myNonoGram->colIndex[i][0];j++){
      res+=myNonoGram->colIndex[i][j];
      res++;
    }
    res--;
    // Ici, on regarde si la somme des index + les cases vides évidentes est égale aux dimensions
    // (par ex:, pour une dimension de 10, les index 3 2 3 sont valide (3+1+2+1+3=10))
    if(res==myNonoGram->colCount){
      int l=0;
      // reparcourir la colonne pour colorier
      for(j=1;j<=myNonoGram->colIndex[i][0];j++){
        for(int k=0;k<myNonoGram->colIndex[i][j];k++){
          myNonoGram->gameBoard[i][l]=1;
          l++;
        }
        if(l<myNonoGram->colCount){
          myNonoGram->gameBoard[i][l]=-1;
          l++;
        }
      }
    }
  }
  for(i=0;i<myNonoGram->rowCount;i++){
    int res=0;
    for(j=0;j<myNonoGram->rowIndex[i][0];j++){
      res+=myNonoGram->rowIndex[i][j];
      res++;
    }
    res--;
    // Ici, on regarde si la somme des index + les cases vides évidentes est égale aux dimensions
    // (par ex:, pour une dimension de 10, les index 3 2 3 sont valide (3+1+2+1+3=10))
    if(res==myNonoGram->rowCount){
      int l=0;
      // reparcourir la colonne pour colorier
      for(j=1;j<=myNonoGram->rowIndex[i][0];j++){
        for(int k=0;k<myNonoGram->rowIndex[i][j];k++){
          myNonoGram->gameBoard[l][i]=1;
          l++;
        }
        if(l<myNonoGram->rowCount){
          myNonoGram->gameBoard[l][i]=-1;
          l++;
        }
      }
    }
  }
  // On va remplir les groupes qui sont en bordure, en rajoutant la case vide à la fin du groupe
  for(i=0;i<myNonoGram->colCount;i++){
    int full=0,res=0;
    /*On le fait seulement si la ligne n'est pas pleine */
    for(j=0;j<myNonoGram->colCount;j++){
      res+=abs(myNonoGram->gameBoard[i][j]);
    }
    if(res==myNonoGram->colCount){
      full++;
    }
    if(!full){
      for(j=1;j<myNonoGram->rowIndex[i][1];j++){
        if(myNonoGram->gameBoard[0][i]==1){
          myNonoGram->gameBoard[j][i]=1;
          display_Nonogram(myNonoGram);
          usleep(5000);
        }
      }
      if(j<myNonoGram->colCount && myNonoGram->gameBoard[0][i]==1){
        myNonoGram->gameBoard[j][i]=-1;
        display_Nonogram(myNonoGram);
        usleep(5000);
      }
      // Il faut refaire dans le sens inverse maintenant
      for(j=myNonoGram->rowCount-1;j>=myNonoGram->rowIndex[i][myNonoGram->rowIndex[i][0]-1];j--){
        if(myNonoGram->gameBoard[myNonoGram->rowCount-1][i]==1){
          myNonoGram->gameBoard[j][i]=1;
          display_Nonogram(myNonoGram);
          usleep(5000);
        }
      }
    }
    if(j<myNonoGram->colCount && myNonoGram->gameBoard[myNonoGram->rowCount-1][i]==1){
      myNonoGram->gameBoard[j][i]=-1;
      display_Nonogram(myNonoGram);
      usleep(5000);
    }
  }
  for(i=0;i<myNonoGram->rowCount;i++){
    int full=0,res=0;
    for(j=0;j<myNonoGram->colCount;j++){
      res+=abs(myNonoGram->gameBoard[j][i]);
    }
    if(res==myNonoGram->rowCount){
      full++;
    }
    if(!full){
      for(j=1;j<myNonoGram->colIndex[i][1];j++){
        if(myNonoGram->gameBoard[i][0]==1){
          myNonoGram->gameBoard[i][j]=1;
          display_Nonogram(myNonoGram);
          usleep(5000);
        }
      }
      if(j<myNonoGram->rowCount && myNonoGram->gameBoard[i][0]==1){
        myNonoGram->gameBoard[i][j]=-1;
        display_Nonogram(myNonoGram);
        usleep(5000);
      }
      for(j=myNonoGram->colCount-1;j>=myNonoGram->colIndex[i][myNonoGram->colIndex[i][0]-1];j--){
        if(myNonoGram->gameBoard[i][myNonoGram->colCount-1]==1){
          myNonoGram->gameBoard[i][j]=1;
          display_Nonogram(myNonoGram);
          usleep(5000);
        }
      }
      if(j<myNonoGram->colCount && myNonoGram->gameBoard[i][myNonoGram->rowCount-1]==1){
        myNonoGram->gameBoard[i][j]=-1;
        display_Nonogram(myNonoGram);
        usleep(5000);
      }
    }
  }
  return;
}


void display_Nonogram(Nonogram * mynono){
  int i,j;
  MLV_clear_window(MLV_COLOR_BLACK);

  MLV_actualise_window();
  for(i=0;i<mynono->colCount;i++){
    for(j=0;j<mynono->rowCount;j++){
      if(mynono->gameBoard[i][j]==1){
        MLV_draw_filled_rectangle((100+((WINDOW_LENGHT-200)/mynono->colCount)*i),
          (100+((WINDOW_HEIGHT-200)/mynono->rowCount)*j),
          (WINDOW_LENGHT-200)/mynono->colCount,
          ((WINDOW_HEIGHT-200)/mynono->rowCount),MLV_rgba(0,0,89,MLV_ALPHA_OPAQUE)); /* ici, on calcule la taille d'un carré en fonction
          de la taille de la fenêtre et du nombre de carrés choisi en appelant le programme */
      }
      if(mynono->gameBoard[i][j]==-1){
        MLV_draw_filled_rectangle((100+((WINDOW_LENGHT-200)/mynono->colCount)*i),
          (100+((WINDOW_HEIGHT-200)/mynono->rowCount)*j),
          (WINDOW_LENGHT-200)/mynono->colCount,
          ((WINDOW_HEIGHT-200)/mynono->rowCount),MLV_COLOR_RED); /* ici, on calcule la taille d'un carré en fonction
          de la taille de la fenêtre et du nombre de carrés choisi en appelant le programme */
      }
      MLV_draw_rectangle((100+((WINDOW_LENGHT-200)/mynono->colCount)*i),
        (100+((WINDOW_HEIGHT-200)/mynono->rowCount)*j),
        (WINDOW_LENGHT-200)/mynono->colCount,
        ((WINDOW_HEIGHT-200)/mynono->rowCount),MLV_COLOR_WHITE);
      usleep(1000);
    }
  }
  MLV_actualise_window();
  usleep(1000000);
  return;
}


#endif
