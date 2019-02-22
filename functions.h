#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "constants.h"

Board *createBoard(int N, int M, Params params/*, code *statusCode*/);
int VerificarSiCumpleCondicionDeInicio(Board* board, Params params);
int MinMaxBoard(int M, int N, char* difficulty);
int max(int num1, int num2);
Params *crearBolsa(int N, int M, char* difficulty);
void print(Board* board/*, code *statusCode*/);
void printCoordinates(Board* board/*, code *statusCode*/);
char *UnirTresString(char* string1, char* string2, char* string3);
char *getDifficulty(Board* b);
char *leerArchivoPorlinea(FILE* archivo, int linea);
void saveBoard(Board *b, int *id/*, code *statusCode*/);
Board *loadBoard(int id/*, Code *statusCode*/);
int checkBoard(Board *board/*, code *statusCode*/);
Position *checkCandies(Board * board/*, code *statusCode*/);
int play(Board *board, Position pOri, Position pDes, int *turns/*, code *statusCode*/);
