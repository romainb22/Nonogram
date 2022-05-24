#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_


#include "display.h"
#include "util.h"

typedef struct Nonogram{
  int rowCount;
  int colCount;
  int totalCells;
  int** rowIndex;
  int** colIndex;
  int** gameBoard;
}Nonogram;

Nonogram * create_nonogram();

Nonogram * read_nonogram();

void solver(Nonogram * myNonoGram);

void display_Nonogram(Nonogram * mynono);

#endif
