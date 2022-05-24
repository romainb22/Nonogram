#ifndef _UTIL_C_
#define _UTIL_C_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "util.h"

/*Test*/

int getInt(){
  int myInt;
  if(scanf("%d", &myInt)!=1){
    printf("Lecture erronée !\n");
    return -1;
  };
  while(getchar() != '\n'){
    ;
  }
  return myInt;
}

void getIndexes(int **myTab, int end){
  int i,j,count=0;
  for(i=0;i<end;i++){
    printf("\nVeuillez rentrer le nombre d'index (%d/%d):\n",i+1,end);
    if(scanf("%d", &count)!=1){
      printf("Lecture erronée !\n");
    }
    while(getchar() != '\n'){
      ;
    }
    //printf("Vous avez rentré %d\n", count);
    myTab[i] = malloc(sizeof(int)*count+1);
    if(myTab == NULL){
      printf("Erreur d'allocation\n");
      return;
    }
    myTab[i][0] = count;
    //printf("myTab[%d][0] = %d\n", i, myTab[i][0]);
    for(j=1;j<=count;j++){
      //printf("i= %d, j=%d\n",i,j);
      printf("Index (%d/%d):\n",j,count);
      if(scanf("%d", &myTab[i][j])!=1){
        printf("Lecture erronée !\n");
      }
      while(getchar() != '\n'){
        ;
      }
      //printf("Vous avez rentré %d\n", myTab[i][j]);
    }
  }
}

int count_from_table(int **myTab, int end){
  int i,j,res=0;
  for(i=0;i<end;i++){
    //printf("myTab[%d][0] = %d\n", i, myTab[i][0]);
    for(j=1;j<=myTab[i][0];j++){
      //printf("myTab[%d][%d] = %d\n", i, j, myTab[i][j]);
      //printf("res = %d\n", res);
      res+=myTab[i][j];
    }
  }
  return res;
}

int count_from_gameboard(int **mytab, int n, int m){
  int i,j,res=0;
  for(i=0;i<n;i++){
    for(j=0;j<m;j++){
      if(mytab[i][j]==1){
        res++;
      }
    }
  }
  return res;
}

void getPath(char * path){
  int done=1;
  while(done){
    printf("\nVeuillez rentrer le chemin du fichier:\n");
    if(scanf("%s",path)!=1){
      done=0;
      printf("\nLecture Eronnée, veuillez recommencer.\n");
    }
    while(getchar() != '\n'){
      ;
    }
    done=0;
  }
  return;
}

int getCountFromFile(FILE * myfile){
  int res;
  char * str,c;
  str = malloc(sizeof(char)*500);
  if(!str){
    printf("Erreur d'allocation\n");
    return -1;
  }
  if(fscanf(myfile,"%[^\n]",str)!=1){
    printf("Erreur de lecture\n");
    return 0;
  }
  c = fgetc(myfile);
  while(c!='\n'){
    c = fgetc(myfile);
  }
  res = atoi(str);
  return res;
}

void getIndexesFromFile(FILE * myfile, int ** tab, int size){
  int i,j;
  char * str, * token;
  str = malloc(sizeof(char)*500);
  if(!str){
    printf("Erreur d'allocation\n");
    return;
  }
  for(i=0;i<size;i++){
    if(fscanf(myfile,"%[^\n]",str)!=1){
      printf("Erreur de lecture getIndexes %s\n",str);
      return;
    }
    token=strtok(str," ");
    tab[i] = calloc(sizeof(int)*atoi(token),1);
    for(j=1;j<tab[i][0];j++){
      token=strtok(NULL," ");
      tab[i][j]=atoi(token);
      //printf("%d\n",tab[i][j]);
    }
  }
  /*c = fgetc(myfile);
  while(c!='\n' && c!=EOF){
    c = fgetc(myfile);
  }*/
  return;
}

#endif
