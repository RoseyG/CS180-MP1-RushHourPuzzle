#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"header.h"

int main(void){
	int size = 0;	// size of matrix
	int row;	// x-coords
	int col;	// y-coords
	char orie;	// car orientation
	char car_ID = 'A';	// car ID
	int len;	// car length
	char** matrix;	// matrix
	bool found = false;
	int h_num = 0;  // heuristic selector
	int max_nodes = 0;
	int tree_depth = 0;
	clock_t run_time = 0;
	clock_t begin, end;


	CarList* initial_state = (CarList*)malloc(sizeof(CarList));
	initial_state->head = (Car*)malloc(sizeof(Car));
	Car* current_car = initial_state->head;
	FILE* in_file = fopen("in.txt","r");	//File reading
	fscanf(in_file,"%d",&size);
	fscanf(in_file,"%d %d %c %d", &row, &col, &orie, &len);
	initCar(initial_state->head, car_ID, orie, len, row, col); // assign car ID (single character, first car is A and so on)
	car_ID++;
	while(!feof(in_file)){
		fscanf(in_file,"%d %d %c %d", &row, &col, &orie, &len);
		Car* new_car = (Car*)malloc(sizeof(Car)); // make new car
		initCar(new_car, car_ID, orie, len, row, col); // assign car ID (single character, first car is A and so on)
		current_car->next = new_car; // add car to list
		current_car = current_car->next;
		car_ID++;
	}
	fclose(in_file);
	while( h_num < 1 || h_num > 3){
		printf("Enter which heuristic you wat to use:\n");
		printf("[1] Zero Heuristic\n");
		printf("[2] Blocking Heuristic\n");
		printf("[3] Advance Heuristic\n");
		scanf("%d", &h_num);
	}

	Fringe* unex_queue = (Fringe*)malloc(sizeof(Fringe));
	unex_queue->head = NULL;
	Fringe* ex_queue = (Fringe*)malloc(sizeof(Fringe));
	ex_queue->head = NULL;
	FringeNode* new_node = (FringeNode*)malloc(sizeof(FringeNode));
	FringeNode* goal_node;	// Store goal node here
	Move new_move; // dummy move
	initNode(new_node, NULL, initial_state, -1, new_move, size, h_num); // INITIAL NODE
	pushNode(new_node, unex_queue);
	FringeNode* current_node = new_node;

	begin = clock();
	while(unex_queue->head != NULL){
		current_node = popNode(unex_queue->head, unex_queue);
		if(isGoal(current_node->state->head, size)){
			found = true;
			goal_node = current_node;
			break;
		}
		max_nodes++;
		expandNode(current_node, unex_queue, ex_queue, size, h_num);
		pushNode(current_node, ex_queue);
		if(current_node->cost+1 > tree_depth)
			tree_depth = current_node->cost+1;
	}
	end = clock();
	run_time = end-begin;

	FILE* out_file = fopen("out.txt", "w");
	if(h_num == 1)
		fprintf(out_file,"ZERO H\n");
	if(h_num == 2)
		fprintf(out_file,"BLOCKING H\n");
	if(h_num == 3)
		fprintf(out_file,"ADVANCE H\n");
	if(!found){
		printf("Solution not found!\n");
		fprintf(out_file, "%d\n", -1);
	}
	else{
		FringeNode* temp_node = goal_node;
		int action_ctr = 0;
		while(temp_node->parent != NULL){
			action_ctr++;
			temp_node = temp_node->parent;
		}
		Move move_list[action_ctr];
		char** matrix_list[action_ctr+1];
		temp_node = goal_node;
		for(int i = action_ctr; i > 0; i--){
			move_list[i-1] = temp_node->action;
			matrix_list[i] = temp_node->matrix;
			temp_node = temp_node->parent;
		}
		matrix_list[0] = temp_node->matrix;

		current_car = initial_state->head;
		printf("Initial State:\n");
		printMatrix(matrix_list[0], size);
		fprintf(out_file,"Cost: %d \n", action_ctr);
		for(int i = 0; i < action_ctr; i++){
			fprintf(out_file,"%c %c %d\n", move_list[i].car_ID, move_list[i].direction, move_list[i].spaces);
			printf("%c %c %d\n", move_list[i].car_ID, move_list[i].direction, move_list[i].spaces);
			printMatrix(matrix_list[i+1], size);
		}

	}
	fprintf(out_file,"Max number of nodes expanded: %d \n", max_nodes);
	fprintf(out_file,"Depth of search tree: %d \n", tree_depth);
	fprintf(out_file,"Running time: %d \n", run_time);
	printf("Max number of nodes expanded: %d \n", max_nodes);
	printf("Depth of search tree: %d \n", tree_depth);
	printf("Running time: %d \n", run_time);
	fclose(out_file);	

	freeCarList(initial_state);
	freeNode(current_node, size);
	free(unex_queue);
	free(ex_queue);
	return 0;
}