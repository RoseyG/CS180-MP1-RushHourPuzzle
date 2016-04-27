#include<stdio.h>
#include<stdlib.h>
#include"header.h"

void expandNode(FringeNode* current, Fringe* unex_queue, Fringe* ex_queue, int size, int h_num){
	Car* car = current->state->head;
	char** matrix = makeMatrix(size, current->state);
	Move new_move;
	bool is_free = false;
	int temp;
	int ctr;
	int len;
	int x;
	int y;
	while(car != NULL){
		len = car->car_len;

		y = car->y_coord;
		ctr = 0;
		is_free = true;
		if(car->orie == 'v')
			while(y > 0){
				y--;
				if(matrix[y][car->x_coord] != '.')
					break;
				ctr++;
			}
		else
			while(y > 0){
				y--;
				for(int i = 0; i < len; i++)
					if(matrix[y][car->x_coord+i] != '.'){
						is_free = false;
						break;
					}
				if(!is_free)
					break;
				ctr++;
			}
		y = car->y_coord - ctr;
		if(ctr > 0){
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

		x = car->x_coord;
		ctr = 0;
		is_free = true;
		if(car->orie == 'v'){
			while(x < (size-1)){
				x++;
				for(int i=0; i < len; i++)
					if(matrix[car->y_coord+i][x] != '.'){
						is_free = false;
						break;
					}
				if(!is_free)
					break;
				ctr++;
			}

		}
		else{
			while((x+(len-1)) < (size-1)){
				x++;
				if(matrix[car->y_coord][x+(len-1)] != '.')
					break;
				ctr++;
			}
		}
		x = car->x_coord + ctr;
		if(ctr > 0){
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


		y = car->y_coord;
		ctr = 0;
		is_free = true;
		if(car->orie == 'v')
			while((y+(len-1)) < (size-1)){
				y++;
				if(matrix[y+(len-1)][car->x_coord] != '.')
					break;
				ctr++;
			}
		else
			while(y < (size-1)){
				y++;
				for(int i=0; i< len; i++)
					if(matrix[y][car->x_coord+i] != '.'){
						is_free = false;
						break;
					}
				if(!is_free)
					break;
				ctr++;
			}
		y = car->y_coord + ctr;
		if(ctr > 0){
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


		x = car->x_coord;
		ctr = 0;
		is_free = true;
		if(car->orie == 'v')
			while(x > 0){
				x--;
				for(int i=0; i < len; i++)
					if(matrix[car->y_coord+i][x] != '.'){
						is_free = false;
						break;
					}
				if(!is_free)
					break;
				ctr++;
			}
		else
			while(x > 0){
				x--;
				if(matrix[car->y_coord][x] != '.')
					break;
				ctr++;
			}
		x = car->x_coord - ctr;
		if(ctr > 0){
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

		car = car->next;
	}
};