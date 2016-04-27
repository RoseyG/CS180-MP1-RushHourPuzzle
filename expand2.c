#include<stdio.h>
#include<stdlib.h>
#include"header.h"

void expandNode(FringeNode* current, Fringe* unex_queue, Fringe* ex_queue, int size, int h_num){
	Car* car = current->state->head;
	char** matrix = makeMatrix(size, current->state);
	int temp;
	Move new_move;
	bool is_free;
	int ctr;
	int len;
	int x;
	int y;
	while(car != NULL){
		len = car->car_len;
		if(car->orie == 'v'){
			y = car->y_coord;
			ctr = 0;
			while(y > 0){
				ctr++;
				y--;
				if(matrix[y][car->x_coord] == '.'){
					temp = car->y_coord;
					car->y_coord = y;
					FringeNode* new_node = (FringeNode*)malloc(sizeof(FringeNode));
					new_move.car_ID = car->car_ID;
					new_move.direction = 'U';
					new_move.spaces = ctr;
					initNode(new_node, current, current->state, current->cost, new_move, size, h_num);
					if(!compareState(new_node, ex_queue, unex_queue, size))
						if(!compareState(new_node, unex_queue, unex_queue, size))
							pushNode(new_node, unex_queue);
					car->y_coord = temp;
				}
				else
					break;
			}
			x = car->x_coord;
			ctr = 0;
			while(x < (size-1)){
				ctr++;
				x++;
				is_free = true;
				for(int i=0; i < len; i++)
					if(matrix[car->y_coord+i][x] != '.')
						is_free = false;
				if(is_free){
					temp = car->x_coord;
					car->x_coord = x;
					FringeNode* new_node = (FringeNode*)malloc(sizeof(FringeNode));
					new_move.car_ID = car->car_ID;
					new_move.direction = 'R';
					new_move.spaces = ctr;
					initNode(new_node, current, current->state, current->cost, new_move, size, h_num);
					if(!compareState(new_node, ex_queue, unex_queue, size))
						if(!compareState(new_node, unex_queue, unex_queue, size))
							pushNode(new_node, unex_queue);
					car->x_coord = temp;					
				}
				else
					break;
			}
			y = car->y_coord;
			ctr = 0;
			while((y+(len-1)) < (size-1)){
				ctr++;
				y++;
				if(matrix[y+(len-1)][car->x_coord] == '.'){
					temp = car->y_coord;
					car->y_coord = y;
					FringeNode* new_node = (FringeNode*)malloc(sizeof(FringeNode));
					new_move.car_ID = car->car_ID;
					new_move.direction = 'D';
					new_move.spaces = ctr;
					initNode(new_node, current, current->state, current->cost, new_move, size, h_num);
					if(!compareState(new_node, ex_queue, unex_queue, size)){
						if(!compareState(new_node, unex_queue, unex_queue, size))
							pushNode(new_node, unex_queue);
					}
					car->y_coord = temp;
				}
				else
					break;
			}
			x = car->x_coord;
			ctr = 0;
			while(x > 0){
				ctr++;
				x--;
				is_free = true;
				for(int i=0; i < len; i++)
					if(matrix[car->y_coord+i][x] != '.')
						is_free = false;
				if(is_free){
					temp = car->x_coord;
					car->x_coord = x;
					FringeNode* new_node = (FringeNode*)malloc(sizeof(FringeNode));
					new_move.car_ID = car->car_ID;
					new_move.direction = 'L';
					new_move.spaces = ctr;
					initNode(new_node, current, current->state, current->cost, new_move, size, h_num);
					if(!compareState(new_node, ex_queue, unex_queue, size))
						if(!compareState(new_node, unex_queue, unex_queue, size))
							pushNode(new_node, unex_queue);
					car->x_coord = temp;					
				}
				else
					break;
			}
		}
		else{
			y = car->y_coord;
			ctr = 0;
			while(y > 0){
				ctr++;
				y--;
				is_free = true;
				for(int i = 0; i < len; i++)
					if(matrix[y][car->x_coord+i] != '.')
						is_free = false;
				if(is_free){
					temp = car->y_coord;
					car->y_coord = y;
					FringeNode* new_node = (FringeNode*)malloc(sizeof(FringeNode));
					new_move.car_ID = car->car_ID;
					new_move.direction = 'U';
					new_move.spaces = ctr;
					initNode(new_node, current, current->state, current->cost, new_move, size, h_num);
					if(!compareState(new_node, ex_queue, unex_queue, size))
						if(!compareState(new_node, unex_queue, unex_queue, size))
							pushNode(new_node, unex_queue);
					car->y_coord = temp;					
				}
				else
					break;
			}	 
			x = car->x_coord;
			ctr = 0;
			while((x+(len-1)) < (size-1)){
				ctr++;
				x++;
				if(matrix[car->y_coord][x+(len-1)] == '.'){
					temp = car->x_coord;
					car->x_coord = x;
					FringeNode* new_node = (FringeNode*)malloc(sizeof(FringeNode));
					new_move.car_ID = car->car_ID;
					new_move.direction = 'R';
					new_move.spaces = ctr;
					initNode(new_node, current, current->state, current->cost, new_move, size, h_num);
					if(!compareState(new_node, ex_queue, unex_queue, size))
						if(!compareState(new_node, unex_queue, unex_queue, size))
							pushNode(new_node, unex_queue);
					car->x_coord = temp;
				}
				else
					break;
			}
			y = car->y_coord;
			ctr = 0;
			while(y < (size-1)){
				ctr++;
				y++;
				is_free = true;
				for(int i=0; i< len; i++)
					if(matrix[y][car->x_coord+i] != '.')
						is_free = false;
				if(is_free){
					temp = car->y_coord;
					car->y_coord = y;
					FringeNode* new_node = (FringeNode*)malloc(sizeof(FringeNode));
					new_move.car_ID = car->car_ID;
					new_move.direction = 'D';
					new_move.spaces = ctr;
					initNode(new_node, current, current->state, current->cost, new_move, size, h_num);
					if(!compareState(new_node, ex_queue, unex_queue, size))
						if(!compareState(new_node, unex_queue, unex_queue, size))
							pushNode(new_node, unex_queue);
					car->y_coord = temp;					
				}
				else
					break;
			}
			x = car->x_coord;
			ctr = 0;
			while(x > 0){
				ctr++;
				x--;
				if(matrix[car->y_coord][x] == '.'){
					temp = car->x_coord;
					car->x_coord = x;
					FringeNode* new_node = (FringeNode*)malloc(sizeof(FringeNode));
					new_move.car_ID = car->car_ID;
					new_move.direction = 'L';
					new_move.spaces = ctr;
					initNode(new_node, current, current->state, current->cost, new_move, size, h_num);
					if(!compareState(new_node, ex_queue, unex_queue, size))
						if(!compareState(new_node, unex_queue, unex_queue, size))
							pushNode(new_node, unex_queue);
					car->x_coord = temp;
				}
				else
					break;
			}

		}
		car = car->next;
	}
};