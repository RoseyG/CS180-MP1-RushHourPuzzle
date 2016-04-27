#ifndef FRINGE
#define FRINGE

typedef struct move Move;
struct move{
	char car_ID;
	char direction;
	int spaces;
};
typedef struct car Car;
struct car{
	char car_ID;
	char orie;
	int car_len;
	int x_coord;
	int y_coord;
	Car* next;
};
typedef struct carList CarList;
struct carList{
	Car *head;
};
void initCar(Car*, char, char, int, int, int);
void freeCarList(CarList*);

typedef struct fringeNode FringeNode;
struct fringeNode{
	FringeNode* parent; 
	FringeNode* next;
	FringeNode* prev;
	CarList* state;
	char** matrix;
	int cost;
	Move action;
	int g_h;
};
typedef struct fringe Fringe;
struct fringe{
	FringeNode *head;
};
void initNode(FringeNode*, FringeNode*, CarList*, int, Move, int, int); // add g_h
void pushNode(FringeNode*, Fringe*);
FringeNode* popNode(FringeNode*, Fringe*);
void freeNode(FringeNode*, int);

int zero_h();
int block_h(CarList*);
int adv_h(CarList*, char**, int);
int check_up(Car*, CarList*, int);
int check_down(Car*, CarList*, int);

void expandNode(FringeNode*, Fringe*, Fringe*, int, int); // add heuristic selector

char** makeMatrix(int, CarList*);
void printMatrix(char**, int);
bool isGoal(Car*, int);
bool compareState(FringeNode*, Fringe*, Fringe*, int);

#endif