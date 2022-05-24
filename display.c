#ifndef _DISPLAY_C_
#define _DISPLAY_C_

#include<stdlib.h>
#include<stdio.h>

#include "display.h"


void display_message(char * str){
  printf("%s\n",str);
  return;
}

void display_gameboard(int ** myTab, int col, int row){
  int i,j;
  printf("\n\n");
  for(i=0;i<col;i++){
    for(j=0;j<row;j++){
      switch(myTab[i][j]){
        case 1:
          printf("\033[0;34m");
          printf("O");
          break;
        case 0:
          printf(" ");
          break;
        case -1:
          printf("\033[1;31m");
          printf("X");
          break;
        default:
          break;
      }
    }
    printf("\n");
  }
  printf("\033[0m");
  printf("\n\n");
  return;
}

#endif
