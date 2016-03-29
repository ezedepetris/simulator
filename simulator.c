#include <stdio.h>

float clock;
int number_server;

struct event{
	// structure for a single event
	float in;
	float out;
	float services;
	char* name;
};

struct next_event{
	// structure for a single event
	int in_out; //0 if is a input event; 1 if is an output event
	event next;
};

event pe[10]; // list with events for model an event with her in/out time
event events[10]; //list of initial events

struct queue{ // queue of events waiting for a server
	event my_event;
	struct queue* next;
}

void enqueue (queue q, event e, queue last){
	queue last_item;
	last_item.my_event = e;
	last_item.next = nil;
	last.next = last_item;
}

event desenqueue(queue q){
	if(is_empty(q) != 0)
		return nil;
	else{
		event aux = q.my_event;
		q = q.next;
		return aux;
	}
}

int is_empty(queue q){
	(queue = nil)? return 0 : return 1;
}



void input(event events_aux*){
	// do all thing when arrive an event (move the event to the server or move the event at queue if the server is full)

}

void output(event pe, queue q){
	// less 1 the server list if the queue is empty or put the next event of the queue to the server
	if (is)
	{
		/* code */
	}
}

next_event get_next_event(event pe_aux*){
	/*return minimal time beetwen input event and output event*/)?/*(0,event)*/:/*(1,event) */
	// return the minimal time beetwen input event and output event of pe array
	//(pe_aux[0]>pe_aux[1])? return pe_aux[1] : return pe_aux[0];
	next_event my_record;
	if (pe_aux[0].in > pe_aux[1].out){
		my_record.in_out = 1;
		my_record.next = pe_aux[1];
	}
	else{
		my_record.in_out = 0;
		my_record.next = pe_aux[0];
	}
	return my_record;
}

void update(){
	// update stadistic variables

}

void report(){
	// interprate all stadistic variables and return a visual result

}

void simulate(){
	// initialize all variables
	while(end_simulation() != 1){
		switch next_event do {
			case
		}
	}
}

int end_simulation(){
	(/* condition */)? return 0: return 1;
}

int main(int argc, char const *argv[]){
	simulate()
	return 0;
}
