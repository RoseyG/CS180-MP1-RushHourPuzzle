#include<stdio.h>
#include<stdlib.h>
#include"header.h"

int zero_h(){
	return 0;
};
int block_h(CarList* car_list){
	Car* current;
	Car* main;
	main = car_list->head;
	current = main->next;
	int cars = 0;
	bool block;
	while(current != NULL){
		block = false;
		if (main->orie == 'v'){ // check car i orientation
			if (current->x_coord < main->x_coord){ // check if car i is behind car A
				current = current->next;
				continue;
			}
			if (current->orie == 'v') // check car i orientation
				for(int y = main->y_coord; y < (main->y_coord + main->car_len); y++)
					if (y >= current->y_coord && y < (current->y_coord + current->car_len))
						block = true;
			else {
				for(int y = current->y_coord; y < (current->y_coord + current->car_len); y++)
					if (y == main->y_coord)
						block = true;
			}
		}
		else{
			if (current->x_coord < (main->x_coord + main->car_len)){ // check if car i is behind car A
				current = current->next;
				continue;
			}
			if (current->orie == 'v') // check car i orientation
				if (main->y_coord >= current->y_coord && main->y_coord < (current->y_coord + current->car_len))
					block = true;
			else
				if (current->y_coord == main->y_coord)
					block = true;
		}
		if(block)
			cars++;
		current = current->next;
	}
	return (cars+1);
};
int adv_h(CarList* state, char** matrix, int size){
	Car* main;
	Car* current;
	CarList* block_list;
	main = state->head;
	current = main->next;
	int block_cars = 0;
	int min_move = 0;
	int a = 0;
	int b = 0;
	bool block, up, down;
	while(current != NULL){
		block = false;
		if (main->orie == 'v'){ // check car i orientation
			if (current->x_coord < main->x_coord){ // check if car i is behind car A
				current = current->next;
				continue;
			}
			if (current->orie == 'v') // check car i orientation
				for(int y = main->y_coord; y < (main->y_coord + main->car_len); y++)
					if (y >= current->y_coord && y < (current->y_coord + current->car_len))
						block = true;
			else
				for(int y = current->y_coord; y < (current->y_coord + current->car_len); y++)
					if (y == main->y_coord)
						block = true;
			if(block){
				up = false;
				down = false;
				if (current->orie == 'v'){
					if (main->y_coord >= current->car_len){
						a = check_up(current, state, size);
						up = true;
					}
					if ((size - main->y_coord - main->car_len) >= current->car_len){
						b = check_down(current, state, size);
						down = true;
					}
				}
				else{
					if (main->y_coord > 0){
						a = check_up(current, state, size);
						up = true;
					}
					if (main->y_coord+main->car_len < size){
						b = check_down(current, state, size);
						down = true;
					}
				}
			}
		}
		else{
			if (current->x_coord < (main->x_coord + main->car_len)){ // check if car i is behind car A
				current = current->next;
				continue;
			}
			if (current->orie == 'v') // check car i orientation
				if (main->y_coord >= current->y_coord && main->y_coord < (current->y_coord + current->car_len))
					block = true;
			else
				if (current->y_coord == main->y_coord)
					block = true;
			if(block){
				up = false;
				down = false;
				if (current->orie == 'v'){
					if (main->y_coord >= current->car_len){
						a = check_up(current, state, size);
						up = true;
					}
					if ((size - main->y_coord) > current->car_len){
						b = check_down(current, state, size);
						down = true;
					}
				}
				else{
					if (main->y_coord > 0){
						a = check_up(current, state, size);
						up = true;
					}
					if (main->y_coord < size-1){
						b = check_down(current, state, size);
						down = true;
					}
				}
				block_cars++;
			}
		}
		if(block){
			int temp_move = 0;
			if(up && down){
				if(a > b)
					temp_move = b;
				else
					temp_move = a;
			}
			else{
				if(up)
					temp_move = a;
				if(down)
					temp_move = b;
			}
			if (temp_move > min_move) // Getting the maximum of all min # of moves
				min_move = temp_move;
		}
		current = current->next;
	}
	if(main->x_coord != 5 || main->y_coord != 2){ // moves plus one or two depending on where the goal car is
		min_move += 1;
		if(main->x_coord != 5 && main->y_coord != 2)
			min_move += 1;
	}
	return (min_move+block_cars);
};
int check_up(Car* current, CarList* state, int size){
	int cars = 0;
	Car* main = state->head;
	Car* temp = main->next;
	while(temp != NULL){
		if(temp->car_ID != current->car_ID){
			if(temp->y_coord < current->y_coord){
				if(current->orie == 'v'){
					if(temp->orie == 'v')
						if(temp->x_coord == current->x_coord){
							cars++;
							break;
						}
					else
						if((current->x_coord >= temp->x_coord)  && (current->x_coord < (temp->x_coord + temp->car_len))){
							cars++;
							break;
						}
				}
				else{
					if(temp->orie == 'v')
						if((temp->x_coord >= current->x_coord)  && (temp->x_coord < (current->x_coord + current->car_len))){
							cars++;
							break;
						}			
					else
						for(int i = 0; i < temp->car_len; i++)
							if((temp->x_coord+i >= current->x_coord)  && (temp->x_coord+i < (current->x_coord + current->car_len))){
								cars++;
								break;
							}
				}
			}
		}
		temp = temp->next;
	}
	return cars;
};
int check_down(Car* current, CarList* state, int size){
	int cars = 0;
	Car* main = state->head;
	Car* temp = main->next;
	while(temp != NULL){
		if(temp->car_ID != current->car_ID){
			if(temp->y_coord > current->y_coord){
				if(current->orie == 'v'){
					if(temp->orie == 'v')
						if(temp->x_coord == current->x_coord){
							cars++;
							break;
						}
					else
						if((current->x_coord >= temp->x_coord)  && (current->x_coord < (temp->x_coord + temp->car_len))){
							cars++;
							break;
						}
				}
				else{
					if(temp->orie == 'v')
						if((temp->x_coord >= current->x_coord)  && (temp->x_coord < (current->x_coord + current->car_len))){
							cars++;
							break;
						}			
					else
						for(int i = 0; i < temp->car_len; i++)
							if((temp->x_coord+i >= current->x_coord)  && (temp->x_coord+i < (current->x_coord + current->car_len))){
								cars++;
								break;
							}
				}
			}
		}
		temp = temp->next;
	}
	return cars;
};