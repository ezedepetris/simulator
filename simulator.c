#include <stdio.h>
#include <stdlib.h>
#include "queue_and_list.h"

float timer;
int number_server = 1;
int free_server = number_server;

Event pe[10]; // list with events for model an event with her in/out time
Event array_events[10]; //list of initial events

//stadistics
float avg_time_server = 0;
float avg_time_queue = 0;
float avg_number_server = 0;
float avg_number_queue = 0;

void update(float number_queue, float number_server, float time_queue, float time_server){
	// update stadistic variables
	avg_number_queue = avg_number_queue + number_queue;
	avg_number_server = avg_number_server + number_server;
	avg_time_queue = avg_time_queue + time_queue;
	avg_time_server = avg_time_server + time_server;
}

void input (Queue* queue, Event e, List* list,float timer){
	// do all thing when arrive an event (move the event to the server or move the event at queue if the server is full)
	if (free_server == 0){
		e.queue_time = timer;
		enqueue(queue, e);
		update(queue->lenght,number_server,0,0);
	}
	else{
		free_server--;
		e.out = timer + e.services;
		insert(list, e, 1);
		update(0,number_server - free_server,0,e.services);
	}
}

void output (Queue* queue, List* list,float timer){
	// less 1 the server list if the queue is empty or put the next event of the queue to the server
	if (is_empty_q(queue) == 1){
		Event e;
		e = dequeue(queue);
		e.queue_time = timer - e.queue_time;
		update(queue->lenght,0,0,0);
		e.out = timer + e.services;
		insert(list, e, 1);
	}
	else{
		free_server++;
		update(0,number_server - free_server,0,0);
	}
}

void report(){
	// interprate all stadistic variables and return a visual result
	avg_number_queue = avg_number_queue / 6;
	avg_number_server = avg_number_server / 6;
	avg_time_server = avg_time_server / 6;
	printf("Numero promedio eventos en cola %f\n", avg_number_queue);
	printf("Numero promedio eventos en el servidor %f\n", avg_number_server);
	printf("Tiempo promedio en cola %f\n", avg_time_queue);
	printf("Tiempo promedio en servidor %f\n", avg_time_server);
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
	int i = 0;
	Event e = array_events[i];
	insert(list, e, 0);

	while(end_simulation(queue, list) != 0){//not end simulation
		//show_l(list);
		e = del(list);
		printf("\n");

		if (e.out == -1){
			timer = e.in;
			input(queue, e, list,timer);
			i++;
			insert(list, array_events[i], 0);
		}
		else{
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

	timer = 0;
	simulate(timer);
	report();
	return 0;
}
