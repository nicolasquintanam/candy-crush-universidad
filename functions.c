#include "functions.h"

Board* createBoard(int N, int M, Params params/*, code *statusCode*/){

	Board* board = (Board*)malloc(sizeof(Board));
	int cd1, cd2, cd3, cd4, cd5, cd6;   // Cantidad de dulces por cada tipo.
	int cantidadTiposDulcesPorDificultad;  // Cantidad de tipos de dulces por dificultad
	char*** boardMatrix = (char***)malloc(sizeof(char*)*N*10);  // Matriz para crear el tablero
	int i, j;
	int NumRandom = 0;  // Variable que tomará valor random
	int f; //NO ME ACUERDO PARA QUE ERA ESTA VARIABLE ------------------------------------

	board->rows = N;
	board->columns = M;

	cd1 = params.cantidadC1;
	cd2 = params.cantidadC2;
	cd3 = params.cantidadC3;
	cd4 = params.cantidadC4;
	cd5 = params.cantidadC5;
	cd6 = params.cantidadC6;

	if(strcmp(params.difficulty, "1")==0){
		cantidadTiposDulcesPorDificultad = 4;
	}
	else if(strcmp(params.difficulty, "2")==0){
		cantidadTiposDulcesPorDificultad = 5;
	}
	else if(strcmp(params.difficulty, "3")==0){
		cantidadTiposDulcesPorDificultad = 6;
	}
	else{
		printf("ERROR");
	}

	srand(time(NULL));

	for (i = 0; i < N; i++){

		boardMatrix[i] = (char**)malloc(sizeof(char)*M*10);

		for (j = 0; j < M; j++){

			f=100;

			while(f==100){
				NumRandom = rand();
				if(NumRandom % cantidadTiposDulcesPorDificultad == 0 && cd1 != 0){
					boardMatrix[i][j] = params.sweet1->sweet;
					cd1 = cd1 - 1;
					f=0;
				}
				else if(NumRandom % cantidadTiposDulcesPorDificultad == 1 && cd2 != 0){
					boardMatrix[i][j] = params.sweet2->sweet;
					cd2 = cd2 - 1;
					f=0;
				}
				else if(NumRandom % cantidadTiposDulcesPorDificultad == 2 && cd3 != 0){
					boardMatrix[i][j] = params.sweet3->sweet;
					cd3 = cd3 - 1;
					f=0;
				}
				else if(NumRandom % cantidadTiposDulcesPorDificultad == 3 && cd4 != 0){
					boardMatrix[i][j] = params.sweet4->sweet;
					cd4 = cd4 - 1;
					f=0;
				}
				else if(NumRandom % cantidadTiposDulcesPorDificultad == 4 && cd5 != 0){
					boardMatrix[i][j] = params.sweet5->sweet;
					cd5 = cd5 - 1;
					f=0;
				}
				else if(NumRandom % cantidadTiposDulcesPorDificultad == 5 && cd6 != 0){
					boardMatrix[i][j] = params.sweet6->sweet;
					cd6 = cd6 - 1;
					f=0;
				}
			}
		}
	}

	board->matrix = boardMatrix;
	return board;
}

int VerificarSiCumpleCondicionDeInicio(Board* board, Params params){

	char*** boardMatrix = (char***) board->matrix;  //Matriz para tablero
	int i, j, k, l;
	int h = 0;
	int cantidadTiposDulcesPorDificultad = 0;
	char* aux = (char*)malloc(sizeof(char));
	char* aux2 = (char*)malloc(sizeof(char));
	char* aux3 = (char*)malloc(sizeof(char));
	char* aux4 = (char*)malloc(sizeof(char));

	srand(time(NULL));

	if(strcmp(params.difficulty, "1")==0){
		cantidadTiposDulcesPorDificultad = 4;
	}
	else if(strcmp(params.difficulty, "2")==0){
		cantidadTiposDulcesPorDificultad = 5;
	}
	else if(strcmp(params.difficulty, "3")==0){
		cantidadTiposDulcesPorDificultad = 6;
	}
	else{
		printf("ERROR");
	}

	for (i = 0; i < board->rows; i++){

		for(j=0; j < board->columns; j++){

			if(i < board->rows-2){

				if(boardMatrix[i][j] == boardMatrix[i+1][j] && boardMatrix[i][j] == boardMatrix[i+2][j]){
					aux = boardMatrix[i][j];
					k = rand();
					aux2 = boardMatrix[k % cantidadTiposDulcesPorDificultad][k % cantidadTiposDulcesPorDificultad];
					boardMatrix[k % cantidadTiposDulcesPorDificultad][k % cantidadTiposDulcesPorDificultad] = aux;
					boardMatrix[i][j] = aux2;
					h = h + 1;
				}			
			}
			if(j < board->columns-2){
				if(boardMatrix[i][j] == boardMatrix[i][j+1] && boardMatrix[i][j] == boardMatrix[i][j+2]){
					l = rand();
					aux4 = boardMatrix[l % cantidadTiposDulcesPorDificultad][l % cantidadTiposDulcesPorDificultad];
					aux3 = boardMatrix[i][j];
					boardMatrix[i][j] = aux4;
					boardMatrix[l % cantidadTiposDulcesPorDificultad][l % cantidadTiposDulcesPorDificultad] = aux3;	
					h = h + 1;
				}
				
			}

		}
	}

	if(h == 0){
		return 0;
	}
	else{
		return 1;
	}
}

int MinMaxBoard(int M, int N, char* difficulty){

	if(strcmp(difficulty, "1") == 0){
		if( (N > 7 || N < 5) || (M > 7 || M < 5) ){
			return 1;
		}
	}
	if(strcmp(difficulty, "2") == 0){
		if( (N > 12 || N < 8) || (M > 12 || M < 8) ){
			return 1;
		}
	}
	if(strcmp(difficulty, "3") == 0){
		if( (N > 25 || N < 13) || (M > 25 || M < 13) ){
			return 1;
		}
	}
	return 0;
}

int max(int num1, int num2){
	if(num1>num2){
		return num1;
	}
	else{
		return num2;
	}
}

Params* crearBolsa(int N, int M, char* difficulty){

	Params* bolsaDulces = (Params*)malloc(sizeof(Params));
	bolsaDulces->sweet1 = (Candy*)malloc(sizeof(Candy));
	bolsaDulces->sweet2 = (Candy*)malloc(sizeof(Candy));
	bolsaDulces->sweet3 = (Candy*)malloc(sizeof(Candy));
	bolsaDulces->sweet4 = (Candy*)malloc(sizeof(Candy));
	bolsaDulces->sweet5 = (Candy*)malloc(sizeof(Candy));
	bolsaDulces->sweet6 = (Candy*)malloc(sizeof(Candy));

	bolsaDulces->difficulty = difficulty;

	if(strcmp(difficulty, "1") == 0){
		if(max(N,M)%2==0){
			bolsaDulces->cantidadC1 = (((N*M)/3)+(N*M)%3) - max(N,M);
			bolsaDulces->cantidadC2 = ((N*M)/3);
			bolsaDulces->cantidadC3 = ((N*M)/3);
			bolsaDulces->cantidadC4 = max(N,M);
			bolsaDulces->cantidadC5 = 0;
			bolsaDulces->cantidadC6 = 0;
			bolsaDulces->turns = 15;
		}
		else{
			bolsaDulces->cantidadC1 = (((N*M)/3)+(N*M)%3) - (max(N,M)+1);
			bolsaDulces->cantidadC2 = ((N*M)/3);
			bolsaDulces->cantidadC3 = ((N*M)/3);
			bolsaDulces->cantidadC4 = (max(N,M)+1);
			bolsaDulces->cantidadC5 = 0;
			bolsaDulces->cantidadC6 = 0;
			bolsaDulces->turns = 15;
		}
		
	}

	else if(strcmp(difficulty, "2") == 0){
		if(max(N,M)%2==0){
			bolsaDulces->cantidadC1 = (((N*M)/4)+(N*M)%4) - max(N,M);
			bolsaDulces->cantidadC2 = ((N*M)/4);
			bolsaDulces->cantidadC3 = ((N*M)/4);
			bolsaDulces->cantidadC4 = ((N*M)/4);
			bolsaDulces->cantidadC5 = max(N,M);
			bolsaDulces->cantidadC6 = 0;
			bolsaDulces->turns = 15;
		}
		else{
			bolsaDulces->cantidadC1 = (((N*M)/4)+(N*M)%4) - (max(N,M)+1);
			bolsaDulces->cantidadC2 = ((N*M)/4);
			bolsaDulces->cantidadC3 = ((N*M)/4);
			bolsaDulces->cantidadC4 = ((N*M)/4);
			bolsaDulces->cantidadC5 = max(N,M)+1;
			bolsaDulces->cantidadC6 = 0;
			bolsaDulces->turns = 15;
		}
		
	}

	else if(strcmp(difficulty, "3") == 0){
		if(max(N,M)%2==0){
			bolsaDulces->cantidadC1 = (((N*M)/5)+(N*M)%5)- max(N,M);
			bolsaDulces->cantidadC2 = ((N*M)/5);
			bolsaDulces->cantidadC3 = ((N*M)/5);
			bolsaDulces->cantidadC4 = ((N*M)/5);
			bolsaDulces->cantidadC5 = ((N*M)/5);
			bolsaDulces->cantidadC6 = max(N,M);
			bolsaDulces->turns = 15;
		}
		else{
			bolsaDulces->cantidadC1 = (((N*M)/5)+(N*M)%5) - (max(N,M)+1);
			bolsaDulces->cantidadC2 = ((N*M)/5);
			bolsaDulces->cantidadC3 = ((N*M)/5);
			bolsaDulces->cantidadC4 = ((N*M)/5);
			bolsaDulces->cantidadC5 = ((N*M)/5);
			bolsaDulces->cantidadC6 = max(N,M)+1;
			bolsaDulces->turns = 15;
		}
		
	}

	else{
		printf("ERRORRR\n");
		exit(0);
	}

	bolsaDulces->sweet1->sweet = SWEET_1;
	bolsaDulces->sweet2->sweet = SWEET_2;
	bolsaDulces->sweet3->sweet = SWEET_3;
	bolsaDulces->sweet4->sweet = SWEET_4;
	bolsaDulces->sweet5->sweet = SWEET_5;
	bolsaDulces->sweet6->sweet = SWEET_6;


	return bolsaDulces;
}

void print(Board* board/*, code *statusCode*/){
	
	int i, j;

	printf("\nTABLERO: \n\n");

	for (i = 0; i < board->rows; i++){
		for (j = 0; j < board->columns; j++){
			printf (" %s ",board->matrix[i][j]);
		}
		printf("\n\n");
	}
}

void printCoordinates(Board* board/*, code *statusCode*/){
	int i, j;
	printf("\nTABLERO: \n\n");
	for (i = 0; i < board->rows; i++){
		if(i > 9){
				printf("x=%i |",i);
			}
			else{
				printf("x=%i  |",i);
			}
		
		for (j = 0; j < board->columns; j++){
			printf (" %s ",board->matrix[i][j]);
		}
		if(i==board->rows-1){
			printf("\n");
		}
		else{
			printf("\n     |\n");
			
		}
		

	}
	printf("     ");
	for (j = 0; j < board->columns; j++){
		printf("____");
	}
	printf("\n     ");
	for (j = 0; j < board->columns; j++){
		printf(" y=%i",j);
	}
	printf("\n\n");
}

char* UnirTresString(char* string1, char* string2, char* string3){
	char* completeString = (char*)malloc(sizeof(char)*10);
	int lenString1 = strlen(string1);
	int lenString2 = strlen(string2);
	int lenString3 = strlen(string3);
	int i,j, k;
	for(i = 0; i < lenString1; i++){
		completeString[i] = string1[i];
	}
	for(j = 0; j < lenString2; j++){
		completeString[i] = string2[j];
		i++;
	}
	for(k = 0; k < lenString3; k++){
		completeString[i] = string3[k];
		i++;
	}
	return completeString;
}

char* getDifficulty(Board* b){
	char* difficulty = (char*) malloc(sizeof(char));
	if(b->rows <= 7){
		difficulty = "1";
	}
	else if(b->rows > 7 && b->rows <= 12){
		difficulty = "2";
	}
	else{
		difficulty = "3";
	}

	return difficulty;
}

char* leerArchivoPorlinea(FILE* file, int linea){
	char* lectura = (char*)malloc(sizeof(char)*50);
	int i;
	for (i = 0; i < linea; i++){
		fscanf(file, " %[^\n]",lectura);
	}
	return lectura;
}

void saveBoard(Board *b, int *id/*, code *statusCode*/){
	FILE* file = NULL;
	int num = 0;
	char* aux1 = (char*) malloc(sizeof(char)*10);
	char* aux2 = (char*) malloc(sizeof(char)*10);
	char* aux3 = (char*) malloc(sizeof(char)*10);
	char* aux4 = (char*) malloc(sizeof(char)*10);
	aux1 = "Tablero ";
	aux2 = ".txt";
	sprintf(aux3, "%i", num);
	aux4 = UnirTresString(aux1,aux3,aux2);
	file = fopen(aux4, "r");
	while(file!=NULL){
		num = num+1;
		fclose(file);
		sprintf(aux3, "%i", num);
		aux4 = UnirTresString(aux1,aux3,aux2);
		file = fopen(aux4, "r");
		fclose(file);
	}
	*id = num;
	aux1 = (char*) malloc(sizeof(char)*10);
	aux2 = (char*) malloc(sizeof(char)*10);
	aux3 = (char*) malloc(sizeof(char)*10);
	aux4 = (char*) malloc(sizeof(char)*10);
	char* rows = (char*) malloc(sizeof(char)*10);
	char* columns = (char*) malloc(sizeof(char)*10);
	int i,j;
	char* fechayhora = (char*)malloc(sizeof(char)*10);
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	strftime(fechayhora,128,"%d/%m/%y %H:%M:%S",tlocal);
	sprintf(aux3, "%i", *id);
	aux1 = "Tablero ";
	aux2 = ".txt";
	aux4 = UnirTresString(aux1,aux3,aux2);
	file = fopen(aux4, "w");
	sprintf(rows, "%i", b->rows);
	sprintf(columns, "%i", b->columns);
	fprintf(file, "%s", "Tablero guardado\n\nID:\n");
	fprintf(file, "%s\n\n", aux3);
	fprintf(file, "%s", "Fecha y Hora:\n");
	fprintf(file, "%s\n\n", fechayhora);
	fprintf(file, "%s\n", "Dimensiones tablero:");
	fprintf(file, "%sx%s\n\n",rows, columns);

	fprintf(file, "%s", "TABLERO: \n\n");
	for (i = 0; i < b->rows; i++){
		for (j = 0; j < b->columns; j++){
			fprintf (file, " %s ",b->matrix[i][j]);
		}
		fprintf(file, "%s","\n\n");
	}
	fprintf(file, "%s", "\n");
	printf("___________________________________\n\n");
	printf("Archivo creado correctamente...\nNombre: %s\n",aux4);
	fclose(file);
}

Board* loadBoard(int id/*, Code *statusCode*/){
	Board* b = (Board*)malloc(sizeof(Board));
	FILE* file = NULL;
	int i,j;
	char* aux1 = (char*) malloc(sizeof(char)*10);
	char* aux2 = (char*) malloc(sizeof(char)*10);
	char* aux3 = (char*) malloc(sizeof(char)*10);
	char* aux4 = (char*) malloc(sizeof(char)*10);
	char* aux5 = (char*) malloc(sizeof(char)*10);
	char* aux6 = (char*) malloc(sizeof(char)*10);
	char* aux7 = (char*) malloc(sizeof(char)*10);

	char* rows = (char*) malloc(sizeof(char)*10);
	char* columns = (char*) malloc(sizeof(char)*10);
	aux1 = "Tablero ";
	aux2 = ".txt";
	sprintf(aux3, "%i", id);
	aux4 = UnirTresString(aux1,aux3,aux2);
	file=fopen(aux4,"r");
	if(file==NULL){
		printf("Error\n");
		exit(1);
	}
	else{
		printf("\nSe abrio correctamente el archivo...\n");
	}
	aux5=leerArchivoPorlinea(file,7);
	rewind(file);
	strncpy(rows,aux5,(strlen(aux5)-1)/2);
	for(i = strlen(rows)+1, j=0 ; i < strlen(aux5) ; i++,j++){
		columns[j] = aux5[i];
	}
	b->rows=atoi(rows);
	b->columns=atoi(columns);
	printf("filas: %i, columnas: %i\n\n",b->rows,b->columns);
	char*** t = (char***)malloc(sizeof(char*)*(b->rows)*100);
	for (i = 0; i < b->rows; i++){
		j=0;
		t[i] = (char**)malloc(sizeof(char)*(b->columns)*10);
		aux6=leerArchivoPorlinea(file,9+i);
		rewind(file);
		aux7 = strtok (aux6," ");
		while (aux7 != NULL && j<(b->columns)){
			t[i][j] = aux7;
			aux7 = strtok(NULL, " ");
			j++;
		}
	}
	b->matrix=t;



	fclose(file);
	return b;
}

int checkBoard(Board *board/*, code *statusCode*/){

	// Verificando que en el tablero no hayan filas o columnas mayores a 25 y menores a 5.

	if(board->rows < 5 || board->rows > 25){
		printf("Error, filas con menor a 5 o mayor a 25\n");
		return -1;

	}
	
	if(board->columns < 5 || board->columns > 25){
		printf("Error, columnas con menor a 5 o mayor a 25\n");
		return -1;
	}

	// Verificando que la cantidad de filas y columnas sea acorde a la dificultad
	
	if(strcmp(board->difficulty,"1")==0){
		if(board->rows > 7){
			printf("Error, filas distinto a dificultad\n");
			return -1;
		}
		if(board->columns > 7){
			printf("Error, columnas distintas a dificultad\n");
			return -1;
		}
	}
	else if(strcmp(board->difficulty,"2")==0){
		if(board->rows < 8 && board->rows > 12){
			printf("Error, filas distinto a dificultad\n");
			return -1;
		}
		if(board->columns < 8 && board->columns > 12){
			printf("Error, columnas distintas a dificultad\n");
			return -1;
		}
	}
	else if(strcmp(board->difficulty,"3")==0){
		if(board->rows < 13 && board->rows > 25){
			printf("Error, filas distinto a dificultad\n");
			return -1;
		}
		if(board->columns < 13 && board->columns > 25){
			printf("Error, columnas distintas a dificultad\n");
			return -1;
		}
	}
	else{
		printf("Error dificultad\n");
		return -1;
	}
	int cantidadC1,cantidadC2,cantidadC3,cantidadC4,cantidadC5, cantidadC6;
	cantidadC1=cantidadC2=cantidadC3=cantidadC4=cantidadC5=cantidadC6=0;


	int i,j;
	for (i = 0; i < board->rows; i++){
		for (j = 0; j < board->columns; j++){
			if(strcmp(SWEET_1,board->matrix[i][j])==0){
				cantidadC1++;
			}
			else if(strcmp(SWEET_2,board->matrix[i][j])==0){
				cantidadC2++;
			}
			else if(strcmp(SWEET_3,board->matrix[i][j])==0){
				cantidadC3++;
			}
			else if(strcmp(SWEET_4,board->matrix[i][j])==0){
				cantidadC4++;
			}
			else if(strcmp(SWEET_5,board->matrix[i][j])==0){
				cantidadC5++;
			}
			else if(strcmp(SWEET_6,board->matrix[i][j])==0){
				cantidadC6++;
			}
		}
	}
	if(cantidadC1+cantidadC2+cantidadC3+cantidadC4+cantidadC5+cantidadC6 != board->rows * board->columns){
		printf("Error en la cantidad de dulces\n");
		return -1;
	}
	
	if(strcmp(board->difficulty,"1")==0){
		
		if(cantidadC1 == 0){
			return -1;
		}
		else if(cantidadC2 == 0){
			return -1;	
		}
		else if(cantidadC3 == 0){
			return -1;
		}
		else if(cantidadC4 == 0){
			return -1;
		}
		else if(cantidadC5 > 0){
			return -1;
		}
		else if(cantidadC6 > 0){
			return -1;
		}

	}

	else if(strcmp(board->difficulty,"2")==0){
		if(cantidadC1 == 0){
			return -1;
		}
		else if(cantidadC2 == 0){
			return -1;	
		}
		else if(cantidadC3 == 0){
			return -1;
		}
		else if(cantidadC4 == 0){
			return -1;
		}
		else if(cantidadC5 == 0){
			return -1;
		}
		else if(cantidadC6 > 0){
			return -1;
		}
	}
	else if(strcmp(board->difficulty,"3")==0){
		if(cantidadC1 == 0){
			return -1;
		}
		else if(cantidadC2 == 0){
			return -1;	
		}
		else if(cantidadC3 == 0){
			return -1;
		}
		else if(cantidadC4 == 0){
			return -1;
		}
		else if(cantidadC5 == 0){
			return -1;
		}
		else if(cantidadC6 == 0){
			return -1;
		}
	}
	return 0;
}

Position *checkCandies(Board * board/*, code *statusCode*/){
	Position* position = (Position*)malloc(sizeof(Position)*20);
	int i,j,k, repetitions;
	for (i = 0; i < board->rows; i++){
		for (j = 0; j < board->columns; j++){
			k=0;
			if(i<=(board->rows-3)){
				if(strcmp(board->matrix[i][j],board->matrix[i+1][j])==0 && strcmp(board->matrix[i][j],
					board->matrix[i+2][j])==0) {

						if(strcmp(board->matrix[i][j],SWEET_4)==0){
									int l;
									for (l = 0; l < board->columns; l++){
										position[l].x = l;
										position[l].y = j;
										position[0].z = board->columns;
									}
									return position;
								}
						repetitions = 0;
						if(i == board->rows-3){
							repetitions = 3;	
							position[0].x = i;
							position[0].y = j;
							position[0].z = repetitions;
							position[1].x = i+1;
							position[1].y = j;
							position[2].x = i+2;
							position[2].y = j;
							return position;		
					}
					else{
						for (k = 0; k < board->rows-1; k++){
							if(strcmp(board->matrix[i][j],board->matrix[i+k][j])==0){
								position[k].x = i+k;
								position[k].y = j;
								position[0].z = k+1;
								if(i+k==board->rows-1){
									return position;
								}
							}
							else{
								return position;
							}
						}
					}
						
				}
					
			}
			if(j<=(board->columns-3)){
				if(strcmp(board->matrix[i][j],board->matrix[i][j+1])==0 && strcmp(board->matrix[i][j+1],
					board->matrix[i][j+2])==0){

					if(strcmp(board->matrix[i][j],SWEET_4)==0){
									int l;
									for (l = 0; l < board->rows; l++){
										position[l].x = i;
										position[l].y = l;
										position[0].z = board->rows;
									}
									return position;
								}

						repetitions = 0;
						if(j== board->columns-3){
							repetitions = 3;
							position[0].x = i;
							position[0].y = j;
							position[0].z = repetitions;
							position[1].x = i;
							position[1].y = j+1;
							position[2].x = i;
							position[2].y = j+2;
							return position;
					}
					else{
						for (k = 0; k < board->columns-1; k++){
							if(strcmp(board->matrix[i][j],board->matrix[i][j+k])==0){
								if(strcmp(board->matrix[i][j],SWEET_4)==0){
									int l;
									for (l = 0; l < board->columns-1; l++){
										
									}
								}
								position[k].x = i;
								position[k].y = j+k;
								position[0].z = k+1;
								if(j+k==board->columns-1){
									return position;
								}
							}
							else{
								return position;
							}
						
						}
					}
						
				}
			}

		}
	}
	return NULL;
}

int play(Board *board, Position pOri, Position pDes, int *turns/*, code *statusCode*/){

	int score = 0;
	Position* position = (Position*)malloc(sizeof(Position)*10);
	char* aux = (char*)malloc(sizeof(char));
	char* aux2 = (char*)malloc(sizeof(char));
	if(pOri.x >= board->rows || pOri.x < 0 || pOri.y >=board->columns || pOri.y < 0 || pDes.x >= board->rows || 
		pDes.x < 0 || pDes.y >=board->columns || pDes.y < 0 ){
			printf("Error\n");
			exit(0);
	} 
	aux = board->matrix[pOri.x][pOri.y];
	aux2 = board->matrix[pDes.x][pDes.y];
	board->matrix[pOri.x][pOri.y] = aux2;
	board->matrix[pDes.x][pDes.y] = aux;

	if(!((pOri.x == pDes.x && (pOri.y == pDes.y+1 || pOri.y == pDes.y-1))  || ((pOri.y == pDes.y && (pOri.x==pDes.x+1 || 
		pOri.x == pDes.x-1))))){
			printf("No se puede...\n");
			exit(0);
	}
	int largo =0;
	
	int m;
	m = 0;
	position = checkCandies(board);
	srand(time(NULL));
	while(position!=NULL){
		largo = position[0].z;
		printCoordinates(board);
		for (m = 0; m < largo; m++){
			board->matrix[position[m].x][position[m].y] = "xx";
		}
		printf("DULCES ELIMINADOS: \n");
		printCoordinates(board);
		for (m = 0; m < largo; m++){
			if(strcmp(board->difficulty,"1")==0){
				if(rand()%3==0){
					board->matrix[position[m].x][position[m].y] = SWEET_1;
				}
				else if(rand()%5==0){
					board->matrix[position[m].x][position[m].y] = SWEET_2;	
				}
				else{
					board->matrix[position[m].x][position[m].y] = SWEET_3;
				}
			}
			else if(strcmp(board->difficulty,"2")==0){
				if(rand()%3==0){
					board->matrix[position[m].x][position[m].y] = SWEET_1;
				}
				else if(rand()%5==0){
					board->matrix[position[m].x][position[m].y] = SWEET_2;	
				}
				else if(rand()%7==0){
					board->matrix[position[m].x][position[m].y] = SWEET_3;
				}
				else{
					board->matrix[position[m].x][position[m].y] = SWEET_5;
				}
			}
			else{
				if(rand()%3==0){
					board->matrix[position[m].x][position[m].y] = SWEET_1;
				}
				else if(rand()%5==0){
					board->matrix[position[m].x][position[m].y] = SWEET_2;	
				}
				else if(rand()%7==0){
					board->matrix[position[m].x][position[m].y] = SWEET_3;
				}
				else if(rand()%11==0){
					board->matrix[position[m].x][position[m].y] = SWEET_5;
				}
				else{
					board->matrix[position[m].x][position[m].y] = SWEET_6;	
				}
			}
			int mmm;
			for (mmm = 0; mmm < 2000; mmm++)
			{
				//hciendo tiempo para que no se repitan los random, ya que estos dependen de la hora
			}

		}
		if(largo==3){
			score = score + 10;
			printf("Puntaje otorgado: 10\n");
		}
		else if(largo==4){
			score = score + 20;
			printf("Puntaje otorgado: 20\n");
		}
		else{
			score = score + largo*10;
			printf("Puntaje otorgado: %i", largo*10);
		}

		position = checkCandies(board);



	}


	int cantidadDulcesMagico = 0;
			int n,h;
			for (n = 0; n < board->rows; n++){
				for (h = 0; h < board->columns; h++){
					if(strcmp(board->matrix[n][h],"**")==0){
						cantidadDulcesMagico++;
					}
				}
			}
			if(cantidadDulcesMagico==2 || cantidadDulcesMagico ==1){
				*turns = 0;
				printf("No se pueden eliminar más los dulces magicos, por lo tanto pierde la partida...\n");
			}
			else{
				*turns = *turns -1;
			}
	
	return score;
}



