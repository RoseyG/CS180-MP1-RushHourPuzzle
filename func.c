#include<stdio.h>
#include<stdlib.h>
#include"header.h"

void initCar(Car* new_car, char new_ID, char new_orie, int new_len, int new_x, int new_y){
	new_car->car_ID = new_ID;
	new_car->orie = new_orie;
	new_car->car_len = new_len;
	new_car->x_coord = new_x;
	new_car->y_coord = new_y;
	new_car->next = NULL;
};
void freeCarList(CarList* car_list){
	Car* current = car_list->head;
	Car* temp;
	while(current != NULL){
		temp = current;
		current = current->next;
		free(temp);
	}
	free(car_list);
};
void initNode(FringeNode* new_node, FringeNode* new_parent, CarList* temp_state, int parent_cost, Move new_action, int size, int h_num){
	CarList* new_state = (CarList*)malloc(sizeof(CarList));
	new_state->head = (Car*)malloc(sizeof(Car));
	Car* temp_car = temp_state->head;
	initCar(new_state->head, temp_car->car_ID, temp_car->orie, temp_car->car_len, temp_car->x_coord, temp_car->y_coord);
	Car* current_car = new_state->head;
	while(temp_car->next != NULL){
		Car* new_car = (Car*)malloc(sizeof(Car)); // make new car
		temp_car = temp_car->next;
		initCar(new_car, temp_car->car_ID, temp_car->orie, temp_car->car_len, temp_car->x_coord, temp_car->y_coord);
		current_car->next = new_car; // add car to list
		current_car = current_car->next;
	}
	new_node->state = new_state;
	new_node->matrix = makeMatrix(size, new_state);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->parent = new_parent;
	new_node->cost = parent_cost + 1;
	new_node->action = new_action;
	if(h_num == 1)
		new_node->g_h = new_node->cost + zero_h();
	else if(h_num == 2)
		new_node->g_h = new_node->cost + block_h(new_state);
	else
		new_node->g_h = new_node->cost + adv_h(new_state, new_node->matrix, size);
};
void pushNode(FringeNode* new_node, Fringe* queue){
	FringeNode* current;
	FringeNode* temp;
	current = queue->head;
	if(current == NULL){
		queue->head = new_node;
		new_node->next = NULL;
	}
	else{
		while(current != NULL){
			if (new_node->g_h > current->g_h){
				if(current->next == NULL){
					new_node->prev = current;
					current->next = new_node;
					new_node->next = NULL;
					break;
				}
				else
					current = current->next;
	   		}
			else{
				if(current->prev == NULL){
					new_node->next = current;
					current->prev = new_node;
					queue->head = new_node;
					break;
				}
				else{
					temp = current->prev;
					current->prev = new_node;
					temp->next = new_node;
					new_node->prev = temp;
					new_node->next = current;
					break;
				}
			}
		}
	}
}
FringeNode* popNode(FringeNode* node, Fringe* queue){
	FringeNode* temp;
	if(node->prev == NULL){
		temp = node->next;
		queue->head = temp;
		if(temp != NULL)
			temp->prev = NULL;
	}
	else{
		temp = node->prev;
		if(node->next == NULL){
			temp->next = NULL;	
		}
		else{
			temp->next = node->next;
			temp = node->next;
			temp->prev = node->prev;
		}

	}
	return node;
};
void freeNode(FringeNode* node, int size){
	freeCarList(node->state);
	for(int y = 0; y < size; y++)
		free(node->matrix[y]);
	free(node->matrix);
	free(node);
};
char** makeMatrix(int size, CarList* car_list){
	Car* current = car_list->head;
	int x_coord;
	int y_coord;
	int len;
	char** matrix = new char*[size];
	for(int y = 0; y< size; y++){
		matrix[y] = new char[size];
		for(int x = 0; x<size; x++){
			matrix[y][x] = '.';
		}
	}
	while(current != NULL){
		x_coord = current->x_coord;
		y_coord = current->y_coord;
		len = current->car_len;
		if(current->orie == 'v'){
			matrix[y_coord][x_coord] = '^';
			for(int i = 1; i<len-1;i++){
				matrix[y_coord+i][x_coord] = '|';
			}
			matrix[y_coord+len-1][x_coord] = 'v';
		}
		else{
			matrix[y_coord][x_coord] = '<';
			for(int i = 1; i<len-1;i++){
				matrix[y_coord][x_coord+i] = '-';
			}
			matrix[y_coord][x_coord+len-1] = '>';
		}
		current = current->next;
	}
	return matrix;
};
void printMatrix(char** matrix, int size){
	for(int y = 0; y<size; y++){
		for(int x = 0; x<size; x++){
			if ((y == 2) && (x == size-1)){
					printf("%c|", matrix[y][x]);
			}
			else
			printf("%c ", matrix[y][x]);
		}
		printf("\n");
	}
};
bool isGoal(Car* main, int size){
	bool is_goal = false;
	if(main->orie == 'v'){
		if((main->x_coord == size-1) && (main->y_coord == 2))
			is_goal = true;
	}
	else{
		if((main->x_coord == (size-main->car_len)) && (main->y_coord == 2))
			is_goal = true;
	}
	return is_goal;
};
bool compareState(FringeNode* new_node, Fringe* queue, Fringe* unex_queue, int size){
	bool is_same;
	FringeNode* current_node = queue->head;
	while(current_node != NULL){
		is_same = true;
		Car* current_car = current_node->state->head;
		Car* new_car = new_node->state->head;
		while(current_car != NULL){
			if(current_car->x_coord != new_car->x_coord){
				is_same = false;
				break;
			}
			if(current_car->y_coord != new_car->y_coord){
				is_same = false;
				break;
			}
			current_car = current_car->next;
			new_car = new_car->next;
		}
		if(is_same){
			Car* temp_state;
			if(new_node->g_h < current_node->g_h){	// KEEP NEW NODE
				popNode(current_node, queue);
				pushNode(new_node, unex_queue);
				freeNode(current_node, size);
			}
			else // KEEP OLD NODE
				freeNode(new_node, size);
			break;
		}
		else
			current_node = current_node->next;
	}
	return is_same;
};