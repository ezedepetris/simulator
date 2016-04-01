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
}Event;


// <List class="List-of-next-event">

typedef struct N_L{
	Event info;
	N_L* next;
}NodeNE;

typedef struct L { // queue of events waiting for a server
	int lenght;
	NodeNE* node; //list of out event
	Event in;	//represente the in event
}List;

// </List>



// <Queue class="Waiting-server">

typedef struct N_Q{
	Event info;
	N_Q* next;
}Node;

typedef struct Q { // queue of events waiting for a server
	int lenght;
	Node* node;
}Queue;

// </Queue>




Event pe[10]; // list with events for model an event with her in/out time
Event events[10]; //list of initial events






// Method of Queue

void enqueue (Queue* q, Event ele){
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

Event dequeue(Queue* q){
	Event aux_info;
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

void show_q (Queue* q){
	Node *aux = q->node;
	if (aux != NULL)
		while(aux->next != NULL){
			// printf("%d\n",aux->info);
			aux = aux->next;
		}
		// printf("%d\n",aux->info);
}

int is_empty_q(Queue* q){
	return	(q->lenght == 0)? 0 : 1;
}


// End of Method od Queue


// Method of Lsist
void insert (List* l, Event ele){
	NodeNE *aux;
	aux = (NodeNE *) malloc(sizeof(NodeNE));
	aux->info = ele;
	if (l->lenght == 0){
		aux->next = NULL;
	}else{
		aux->next =l->node;
	}
	l->node = aux;
	l->lenght++;
}

Event del(List* l){
	Event aux_info;
	NodeNE *aux = l->node;
	NodeNE *destroyed;

	if (l->lenght == 1){
		aux_info = aux->info;
		l->node = NULL;
		l->lenght = 0;
		free(aux);	
	}

	if(l->lenght > 1){
		while(aux->next->next != NULL){
			aux = aux->next;
		}
		destroyed = aux->next;
		aux->next = NULL;
		aux_info = destroyed->info;
		l->lenght--;
		free(destroyed);
		
	}
	return  aux_info;
}

void show_l (List* l){
	NodeNE *aux = l->node;
	if (aux != NULL)
		while(aux->next != NULL){
			// printf("%d\n",aux->info);
			aux = aux->next;
		}
		// printf("%d\n",aux->info);
}

int is_empty_l(List* l){
	return	(l->lenght == 0)? 0 : 1;
}
// End of Method of Lsist

void input (){
	// do all thing when arrive an event (move the event to the server or move the event at queue if the server is full)

}

void output (){
	// less 1 the server list if the queue is empty or put the next event of the queue to the server
	// if ()
	// {
	// 	 code
	// }
}

Event get_next_event(Event* pe_aux){
	/*return minimal time beetwen input event and output event*//*(0,event)*//*(1,event) */
	// return the minimal time beetwen input event and output event of pe array
	//(pe_aux[0]>pe_aux[1])? return pe_aux[1] : return pe_aux[0];
	Event my_record;
	
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
	// initialize Queue
	Queue *queue;
	queue = (Queue*) malloc(sizeof(Queue));
	queue->lenght = 0;

	// initialize List
	List *list;
	list = (List*) malloc(sizeof(List));
	list->lenght = 0;

	// initialize all variables
	
}


int main(int argc, char const *argv[]){
	simulate();
	return 0;
}
