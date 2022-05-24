#ifndef _MAIN_C_
#define _MAIN_C_

#include<stdlib.h>
#include<stdio.h>
#include <MLV/MLV_all.h>
#include"structure.h"
#include"display.h"

#define WINDOW_LENGHT 800
#define WINDOW_HEIGHT 600

int main(int argc, char ** argv){
  Nonogram * myNonoGram;
  MLV_create_window("Nonogram ", "- Affichage", WINDOW_LENGHT, WINDOW_HEIGHT);
  if(argc != 2){
    printf("Usage = %s [-c/-r]\n",argv[0]);
    exit(EXIT_FAILURE);
  }
  if(argv[1][1]=='c'){
    myNonoGram = create_nonogram();
  }
  else{
    myNonoGram = read_nonogram();
  }
  //while(count_from_gameboard(myNonoGram->gameBoard, myNonoGram->colCount, myNonoGram->rowCount)!=count_from_table(myNonoGram->colIndex, myNonoGram->colCount)){
  for(int i=0;i<2;i++){
    solver(myNonoGram);
    //display_gameboard(myNonoGram->gameBoard, myNonoGram->colCount, myNonoGram->rowCount);
    display_Nonogram(myNonoGram);
  }
  sleep(30);
  exit(EXIT_SUCCESS);
}

#endif
