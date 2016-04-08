#include <stdio.h>
#include <stdlib.h>
#include "queue_and_list.h"
#include "lcgrand.h"


int opt; // option to select the input distribution
float timer;
float limited_time; // this variable refine the timer, it's for run the simulator just an specyfic time
int number_server;
int free_server;

Event array_events[1]; //list of initial events

//time of the last event
float time_event = 0;

//stadistics
float avg_time_server = 0;
float avg_time_queue = 0;
float avg_number_server = 0;
float avg_number_queue = 0;
float avg_timer_commerce = 0;
float avg_number_commerce = 0;

void update(float number_queue, float number_server, float time_queue, float time_server, float commerce){
	// update stadistic variables
	avg_number_queue += number_queue;
	avg_number_server += number_server;
	avg_time_queue += time_queue;
	avg_time_server += time_server;
	avg_number_commerce += commerce;
}

void input (Queue* queue, Event e, List* list,float timer){
	// do all thing when arrive an event (move the event to the server or move the event at queue if the server is full)
	if (free_server == 0){
		float queue_aux = (timer + time_event) * queue->lenght;
		float server_aux = (timer - time_event) * (number_server - free_server);
		float commerce_aux = (timer - time_event) * (queue->lenght+(number_server - free_server));
		enqueue(queue, e);
		update(queue_aux,server_aux,queue->lenght,0,commerce_aux);
	}
	else{
		float server_aux = (timer - time_event) * (number_server - free_server);
		float commerce_aux = (timer - time_event) * (queue->lenght+(number_server - free_server));
		free_server--;
		e.out = timer + e.services;
		insert(list, e, 1);
		update(0,server_aux,queue->lenght,e.services,commerce_aux);
	}
}

void output (Queue* queue, List* list,float timer){
	// less 1 the server list if the queue is empty or put the next event of the queue to the server
	if (is_empty_q(queue) == 1){
		float queue_aux = (timer + time_event) * queue->lenght;
		float server_aux = (timer - time_event) * (number_server - free_server);
		float commerce_aux = (timer - time_event) * (queue->lenght+(number_server - free_server));
		Event e;
		e = dequeue(queue);
		update(queue_aux,server_aux,queue->lenght,0,commerce_aux);
		e.out = timer + e.services;
		insert(list, e, 1);
	}
	else{
		float commerce_aux = (timer - time_event) * (queue->lenght+(number_server - free_server));
		float server_aux = (timer - time_event) * (number_server - free_server);
		free_server++;
		update(0,server_aux,queue->lenght,0,commerce_aux);
	}
}

void report(int cant){
	// interprate all stadistic variables and return a visual result
	avg_time_queue = avg_time_queue / cant;
	avg_number_queue = avg_number_queue / timer;
	avg_number_server = avg_number_server / (timer * number_server);
	avg_time_server = avg_time_server / cant;
	avg_timer_commerce = avg_time_server + avg_time_queue;
	avg_number_commerce = avg_number_commerce / timer;
	printf("Utilizacion de la maquina lavadora de autos %f\n", avg_number_server);
	printf("Tiempo promedio que un cliente pasa en el comercio %f\n", avg_timer_commerce);
	printf("Tiempo promedio de un cliente en la cola %f\n", avg_time_queue);
	printf("Numero promedio de clientes en el comercio %f\n", avg_number_commerce);
	printf("Numero promedio de clientes en la cola %f\n", avg_number_queue);
}

float laundry_distribution(){
	float value,x;
	/*
		here we are going to call the fuction of lcgrand and
		return in X the probability beetwen 0 and 1 and we choise 
		the correct option for that probability and, return that value
		x = lcgrand( (<an_int>) maybe an_int could be the seed
	*/
		x = lcgrand(1);

	if(0 <= x && x <= 0.05)
		value = 5;
	if(0.05 < x && x<= 0.1)
		value = 10;
	if(0.1< x && x <= 0.2)
		value = 15;
	if(0.2< x && x <= 0.3)
		value = 20;
	if(0.3< x && x <= 0.6)
		value = 25;
	if(0.6< x && x <= 0.8)
		value = 30;
	if(0.8< x && x <=0.95)
		value = 35;
	if(0.95< x && x <= 1)
		value = 40;
	
	return value;
}
float laundry_distribution_services(){
	float value,x;
	/*
		here we are going to call the fuction of lcgrand and
		return in X the probability beetwen 0 and 1 and we choise 
		the correct option for that probability and, return that value
		x = lcgrand( (<an_int>) maybe an_int could be the seed
	*/
		x = lcgrand(4);

	if(0 <= x && x <= 0.15)
		value = 10;
	if(0.05 < x && x<= 0.25)
		value = 20;
	if(0.1< x && x <= 0.4)
		value = 30;
	if(0.2< x && x <= 0.2)
		value = 40;
	
	return value;
}

float input_distribution(){
	float value;
	switch (opt){

		case 1:

			break;

		case 2:
			value = laundry_distribution();
			break;

		case 3:

			break;
	}
	return value;
}

float services_distribution(){
	float value;
	switch (opt){

		case 1:

			break;

		case 2:
			value = laundry_distribution_services();
			break;

		case 3:

			break;
	}
	return value;
}


int end_simulation(Queue* q, List* l){
	return (is_empty_q(q)==0 &&  is_empty_l(l)==0)? 0: 1;
}

void simulate(float last_arrive){
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
	Event e = array_events[0];
	insert(list, e, 0);

	while(end_simulation(queue, list) != 0 && timer< limited_time){//not end simulation
		Event aux;

		show_l(list);
		e = del(list);
		if (e.out == -1){
			timer = e.in;
			input(queue, e, list,timer);
			i++;
			/*
				here we create an event when we need one
			*/
			aux.in = last_arrive + input_distribution(); // this calculate the inter arrives
			last_arrive = aux.in;
			aux.out = -1;
			aux.services = services_distribution(); // here we need another distribution for the services
			insert(list, aux, 0);
		}
		else{
			if (list->in.in != -1)
				timer = e.out;
			output(queue, list,timer);
		}
	}
	report(i);
}


int main(int argc, char const *argv[]){
	printf("Ingrese la cantidad de servidores con los que quiere correr la simulacion\n");
	scanf("%d", &number_server);
	free_server = number_server;

	printf("Ingrese el tiempo en segundos que quiere que la simulacion se ejecute\n");
	scanf("%f", &limited_time);

	printf("Ingrese la distribucion elegida\n1: Exponencial\n2: El Lavadero\n3: Poisson\n");
	scanf("%d", &opt);

	float arrive = input_distribution();

	Event first;

	first.in = arrive;
	first.out = -1;
	first.services = services_distribution();// here we need another distribution for the time service of the event

	array_events[0] = first;

	timer = 0;
	simulate(arrive);
	return 0;
}
