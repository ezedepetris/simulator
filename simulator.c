#include <stdio.h>
#include <stdlib.h>
#include "queue_and_list.h"

float timer;
int number_server;

Event pe[10]; // list with events for model an event with her in/out time
Event array_events[10]; //list of initial events


void input (Queue* queue, Event e, List* list,float timer){
	// do all thing when arrive an event (move the event to the server or move the event at queue if the server is full)
	if (number_server == 0){
		enqueue(queue, e);
	}
	else{
		number_server--;
		e.out = timer + e.services;
		insert(list, e, 1);
	}
}

void output (Queue* queue, List* list,float timer){
	// less 1 the server list if the queue is empty or put the next event of the queue to the server
	if (is_empty_q(queue) == 1){
		Event e;
		e = dequeue(queue);
		e.out = timer + e.services;
		insert(list, e, 1);
	}
	else{
		number_server++;
	}
}

void update(){
	// update stadistic variables

}

void report(){
	// interprate all stadistic variables and return a visual result

}

int end_simulation(Queue* q, List* l){
	return (is_empty_q(q)==0 &&  is_empty_l(l)==0)? 0: 1;
}

void simulate(float timer){
	// initialize Queue
	Queue *queue;
	queue = (Queue*) malloc(sizeof(Queue));
	queue->lenght = 0;

	// initialize List
	List *list;
	list = (List*) malloc(sizeof(List));
	list->lenght = 0;
	Event a;
	a.in = -1;
	list->in = a;

	// initialize all variables
	number_server = 1;
	int i = 0;
	Event e = array_events[i];
	insert(list, e, 0);

	while(end_simulation(queue, list) != 0){//not end simulation
		show_l(list);
		e = del(list);
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");

		if (e.out == -1){
			// printf("Clock = %f      Soy un evento de Entrada\n", timer );
			timer = timer + e.in;
			input(queue, e, list,timer);
			i++;
			insert(list, array_events[i], 0);
		}
		else{
			// printf("Clock = %f      Soy un evento de Salida\n", timer );
			timer = e.out;
			output(queue, list,timer);
		}
	}
}


int main(int argc, char const *argv[]){
	Event test;

	test.in = 1;
	test.out = -1;
	test.services = 2.5;
	array_events[0] = test;

	test.in = 2;
	test.out = -1;
	test.services = 3;
	array_events[1] = test;

	test.in = 4;
	test.out = -1;
	test.services = 2.3;
	array_events[2] = test;

	test.in = 5;
	test.out = -1;
	test.services = 1.8;
	array_events[3] = test;

	test.in = 7;
	test.out = -1;
	test.services = 1;
	array_events[4] = test;

	test.in = 8.5;
	test.out = -1;
	test.services = 4;
	array_events[5] = test;

	// test.in = 7;
	// test.out = -1;
	// test.services = 5.4;
	// array_events[6] = test;

	// test.in = 8;
	// test.out = -1;
	// test.services = 3;
	// array_events[7] = test;

	// test.in = 9;
	// test.out = -1;
	// test.services = 9;
	// array_events[8] = test;

	// test.in = 10;
	// test.out = -1;
	// test.services = 1;
	// array_events[9] = test;


	timer = 0;
	simulate(timer);
	return 0;
}
