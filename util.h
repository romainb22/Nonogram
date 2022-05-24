#ifndef _UTIL_H_
#define _UTIL_H_


int getInt();

void getIndexes(int **myTab, int end);

int count_from_table(int **myTab, int end);

void getPath(char * path);

int getCountFromFile(FILE * myfile);

void getIndexesFromFile(FILE * myfile, int ** tab, int size);

int count_from_gameboard(int **mytab, int n, int m);

#endif
