#include <stdio.h>
#include <stdlib.h>


float clock;
int number_server;

typedef struct ev{
	// structure for a single event
	float in;
	float out;
	float services;
	char* name;
}event;


// <List class="List-of-next-event">

typedef struct next_ev{ // structure for a single event
	int in_out; //0 if is a input event; 1 if is an output event
	event next;
}next_event;

typedef struct N{
	next_event info;
	N* next;
}NodeNE;

typedef struct L { // queue of events waiting for a server
	int lenght;
	NodeNE* node;
}List;

// </List>



// <Queue class="Waiting-server">

typedef struct N{
	event info;
	N* next;
}Node;

typedef struct Q { // queue of events waiting for a server
	int lenght;
	Node* node;
}Queue;

// </Queue>




event pe[10]; // list with events for model an event with her in/out time
event events[10]; //list of initial events

// int is_empty(queue* q){
// 	return (q == NULL) ? 0: 1;
// }

// void enqueue (queue* q, event e, queue* last){
// 	queue *last_item;
// 	last_item = (queue *) malloc(sizeof(queue));
// 	last_item -> my_event = e;
// 	last_item -> next = NULL;
// 	last -> next = last_item;
// }

// event desenqueue(queue* q){
// 	event aux = q -> my_event;
// 	q = q -> next;
// 	return aux;
// }





// Method of Queue

void enqueue (Queue* q, int ele){
	Node *aux;
	aux = (Node *) malloc(sizeof(Node));
	aux->info = ele;
	if (q->lenght == 0){
		aux->next = NULL;
	}else{
		aux->next =q->node;
	}
	q->node = aux;
	q->lenght++;
}

int dequeue(Queue* q){
	int aux_info;
	Node *aux = q->node;
	Node *destroyed;

	if (q->lenght == 1){
		aux_info = aux->info;
		q->node = NULL;
		q->lenght = 0;
		free(aux);	
	}

	if(q->lenght > 1){
		while(aux->next->next != NULL){
			aux = aux->next;
		}
		destroyed = aux->next;
		aux->next = NULL;
		aux_info = destroyed->info;
		q->lenght--;
		free(destroyed);
		
	}
	return  aux_info;
}

void show (Queue* q){
	Node *aux = q->node;
	if (aux != NULL)
		while(aux->next != NULL){
			printf("%d\n",aux->info);
			aux = aux->next;
		}
		printf("%d\n",aux->info);
}

int is_empty(Queue* q){
	return	(q->lenght == 0)? 0 : 1;
}


// End of Method od Queue


// Method of Lsist

// End of Method of Lsist

void input(event* events_aux){
	// do all thing when arrive an event (move the event to the server or move the event at queue if the server is full)

}

void output(event pe, queue q){
	// less 1 the server list if the queue is empty or put the next event of the queue to the server
	// if ()
	// {
	// 	 code
	// }
}

next_event get_next_event(event* pe_aux){
	/*return minimal time beetwen input event and output event*//*(0,event)*//*(1,event) */
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

int end_simulation(){
	return (1==2)? 0: 1;
}

void simulate(){
	// initialize all variables
	next_event aux = get_next_event(pe);
	int value =  aux.in_out;
	while(end_simulation() != 1){
		switch (value){
			case 0 :
				break;
			case 1 :
				break;

		}
	}
}


int main(int argc, char const *argv[]){
	simulate();
	return 0;
}
