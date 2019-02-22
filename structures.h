typedef struct {
	int rows;
	int columns;
	char*** matrix;
	char* difficulty;
} Board;

typedef struct {

} Game;

typedef struct {
	char* sweet;
} Candy;

typedef struct {
	Candy* sweet1;
	Candy* sweet2;
	Candy* sweet3;
	Candy* sweet4;
	Candy* sweet5;
	Candy* sweet6;
	int cantidadC1;
	int cantidadC2;
	int cantidadC3;
	int cantidadC4;
	int cantidadC5;
	int cantidadC6;
	char* difficulty;
	int turns;
} Params;

typedef struct {
	int x,y,z;
} Position;

typedef struct {
	Position pOri;
	Position pDes;
} Coordinates;

typedef enum code {OK, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERM, IMPOSSIBLE_VALID_BOARD} Code;