#include "functions.h"

int main (){

	char* option = (char*)malloc(sizeof(char));
	char* difficulty = (char*)malloc(sizeof(char));
	Board* board = (Board*)malloc(sizeof(Board));

	printf("\n------------------------------------\n");
	printf("\n ########## Candy Crush ########## \n");
	printf("\n------------------------------------\n\n");

	//########################### Menú 1: Opciones para crear y cargar un tablero #############################

	printf("Bienvenido...\nIngrese una opción: \n\n");
	printf("1) Crear tablero para jugar \n");
	printf("2) Cargar Tablero para jugar \n\n");	
	printf("Opcion: ");

	scanf("%s",option);


	/*Asegurándome de que sólo 1 y 2 sean opciones válidas.
	Ante alguna equivocación, puede ingresar nuevamente.*/
	while(strcmp(option, "1")!=0 && strcmp(option, "2")!=0){
		printf("Error, ingrese nuevamente: ");
		scanf("%s", option);
	}

	//---------Menú 1 - Opción 1: Crear tablero para jugar.

	if(strcmp(option, "1")==0){

		int rows, columns;
		int condition;

		printf("___________________________________\n");
		printf("\nSeleccione la dificultad: \n\n");
		printf("1) Facil:\n- 3 Tipos de dulces\n- Tablero desde 5x5 hasta 7x7\n- 15 Turnos\n\n");
		printf("2) Medio:\n- 4 Tipos de dulces\n- Tablero desde 8x8 hasta 12x12\n- 15 Turnos\n\n");
		printf("3) Dificil:\n- 5 Tipos de dulces\n- Tablero desde 13x13 hasta 25x25\n- 15 Turnos\n\n");

		printf("Opcion: ");

		scanf("%s", difficulty);


		while(strcmp(difficulty, "1")!=0 && strcmp(difficulty, "2")!=0 && strcmp(difficulty, "3")!=0){
			printf("Error, ingrese nuevamente la opcion: ");
			scanf("%s", difficulty);
		}
		printf("\n___________________________________\n");
		printf("\nIngrese el tamaño del tablero: \n");

		printf("\n- Cantidad de filas: ");
		if(scanf("%i", &rows)!=1){
			printf("Error en la cantidad de filas...\n");
			return 1;
		}

		printf("\n- Cantidad de columnas: ");
		if(scanf("%i", &columns)!=1){
			printf("Error en la cantidad de columnas...\n");
			return 1;
		}


		while(MinMaxBoard(rows, columns, difficulty)==1){
			printf("Error en la cantidad de filas y columnas, por favor ingrese nuevamente...\n");
			printf("Cantidad de filas: ");
			scanf("%d", &rows);
			printf("\nCantidad de columnas: ");
			scanf("%d", &columns);
		}

		printf("\n___________________________________\n");

		condition = 0; /*Esta variable sirve por si al crear el tablero, no encuentra la combinación correcta
					Se re-definan los dulces...*/


		board = createBoard(rows,columns, *crearBolsa(rows, columns, difficulty));
		while(VerificarSiCumpleCondicionDeInicio(board,*crearBolsa(rows, columns, difficulty))!=0){

			condition++;
			VerificarSiCumpleCondicionDeInicio(board,*crearBolsa(rows, columns, difficulty));
			/*Si lleva 500 veces tratando de reordenar los dulces en el tablero, se opta por crear
				otro tablero, así no demora mucho en crearlo*/
			if(condition % 500 == 0){ 
				board= createBoard(rows,columns, *crearBolsa(rows, columns, difficulty));
			}

		}
		print(board);
	}

	//---------Menú 1 - Opción 2: Cargar tablero para jugar.

	else if(strcmp(option, "2")==0){

		char* idString = (char*)malloc(sizeof(char)*10);
		int idNum;

		idNum = 0;
		printf("\n___________________________________\n");
		printf("\nPara cargar un tablero guardado, ingrese el ID\n\n");
		printf("- ID: ");

		scanf("%s",idString);
		idNum = atoi(idString);


		printf("\n___________________________________\n");
		board = loadBoard(idNum);
		printf("\n___________________________________\n");
		print(board);
	}

	free(option);

	/*################# Menú 2: Opciones para comenzar juego, guardar tablero, verificar tablero y salir ##############*/

	option = (char*) malloc(sizeof(char));

	difficulty = getDifficulty(board);
	printf("___________________________________\n\n");

	printf("Que desea realizar?\n\n");
	printf("1) Comenzar el juego\n");
	printf("2) Guardar Tablero\n");
	printf("3) Verificar tablero\n");
	printf("4) Salir\n\n");
	printf("Opcion: ");

	scanf("%s",option);


	/*Asegurándome de que sólo 1 y 2 sean opciones válidas.
	Ante alguna equivocación, puede ingresar nuevamente.*/
	while((strcmp(option, "1")!=0 && strcmp(option, "2")!=0 && strcmp(option, "3")!=0 && strcmp(option, "4")!=0)){  
		printf("Error, ingrese nuevamente: ");					
		scanf("%s", option);
	}
	board->difficulty = difficulty;

	//---------Menú 2 - Opción 1: Comenzar juego.

	if(strcmp(option,"1")==0){
		printf("Asegurese de eliminar todos los dulces '**' ya que si quedan 2 o 1 usted perderá la partida...");
		int *turns = (int*)malloc(sizeof(int));
		int score = 0;
		if(strcmp("1",difficulty)==0){
			*turns = 15;
		}
		else if(strcmp("2",difficulty)==0){
			*turns = 15;
		}
		else{
			*turns = 15;
		}
		while(*turns!=0){
			Coordinates* positions = (Coordinates*)malloc(sizeof(Coordinates));
			printf("\n\nUsted dispone de: %i turnos\n\n",*turns);
			printf("Puntaje: %i\n\n",score);
			printf("Para mover un dulce indique las coordenadas del dulce:\n\n");
			printCoordinates(board);
			printf("Coordenada x Origen: ");
			scanf("%i", &positions->pOri.x);
			printf("Coordenada y Origen: ");
			scanf("%i", &positions->pOri.y);
			printf("\n");
			printf("Coordenada x Destino: ");
			scanf("%i", &positions->pDes.x);
			printf("Coordenada y Destino: ");
			scanf("%i", &positions->pDes.y);
			printf("pOrix: %i, pOriy: %i, pDesx: %i, pDesy: %i\n\n",positions->pOri.x,positions->pOri.y,positions->pDes.x,
			positions->pDes.y);
			score = score + play(board, positions->pOri, positions->pDes, turns/*, code *statusCode*/);
		}
		printf("\nSu puntaje final es: %i\n",score);
	}

	//---------Menú 2 - Opción 2: Guardar tablero.

	else if(strcmp(option,"2")==0){
		int* id = (int*)malloc(sizeof(int));
		saveBoard(board, id);
		printf("___________________________________\n");
	}

	//---------Menú 2 - Opción 3: Verificar tablero.
		
	else if(strcmp(option,"3")==0){
		if(checkBoard(board)==-1){
			printf("Error en el chequeo del tablero...\n");
			exit(0);
		}
		else{
			printf("El tablero se encuentra en perfectas condiciones...\n");
		}	
	}

	//---------Menú 2 - Opción 4: Salir.

	else if(strcmp(option, "4")==0){
		printf("Salir");
		exit(0);
	}
	return 0;
}
