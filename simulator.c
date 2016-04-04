#include <stdio.h>
#include <stdlib.h>


float timer;
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
Event array_events[10]; //list of initial events






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


// End of Method of Queue


// Method of Lsist
void insert (List* l, Event ele, int in_out){
	/*
		in_out == 0 (is an in-put event)
		in_out == 1 (is an out-put event)
	*/
	if (in_out == 0){
		l->in = ele;
	}


	if (in_out == 1){
		NodeNE *aux;
		aux = (NodeNE *) malloc(sizeof(NodeNE));
		aux->info = ele;

		NodeNE *walker;
		walker = l->node;

		if (l->lenght == 0){
			aux->next = NULL;
			l->node = aux;
		}else{
			int flag = 0;

			if (ele.out < (walker->info).out){
				aux->next = walker;
				l->node = aux;
				flag--;
			}

			if(ele.out > (walker->info).out && flag == 0){
				if(walker->next == NULL){
					walker->next = aux;
					aux->next = NULL;
					flag--;
				}

				if((walker->next)->info.out > ele.out){
					aux->next = walker->next;
					walker->next = aux;
					flag--;
				}

			}
			if(flag == 0){
				while(ele.out > (walker->info).out && walker->next != NULL ){
					walker = walker->next;
				}

				aux->next = walker->next;
				walker->next = aux;
			}
		}
		l->lenght++;
	}
}

Event del (List* l){
	Event aux_info;

	NodeNE *aux = l->node;

	NodeNE *destroyed;

	if(l->lenght == 0){
		aux_info = l->in;
		(l->in).in = -1;
		return aux_info;

	}

	if((l->in).in == -1){
		aux_info = aux->info;
		l->node = (l->node)->next;
		l->lenght--;
		free(aux);
		return  aux_info;
	}

	if((l->in).in < (aux->info).out && (l->in).in > 0){
		aux_info = l->in;
		(l->in).in = -1;
	}else{
		aux_info = aux->info;
		l->node = (l->node)->next;
		l->lenght--;
		free(aux);
	}
	return  aux_info;
}

void show_l (List* l){
	NodeNE *aux = l->node;
	if(l->lenght == 0){
		printf("Evento de entrada timer: %f\n", (l->in).in);
	}else{
		while(aux != NULL){
			printf("Evento de salida timer: %f\n", (aux->info).out);
			aux = aux->next;
		}
	}
}

int is_empty_l (List* l){
	return	(l->lenght == 0 && (l->in).in == -1)? 0 : 1;
}
// End of Method of Lsist

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
	number_server = 3;
	int i = 0;
	Event e = array_events[i];
	insert(list, e, 0);

	while(end_simulation(queue, list) != 0){//not end simulation
		e = del(list);
		show_l(list);
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
	test.services = 2;
	array_events[0] = test;
	
	test.in = 2;
	test.out = -1;
	test.services = 3.4;
	array_events[1] = test;
	
	test.in = 3;
	test.out = -1;
	test.services = 1;
	array_events[2] = test;
	
	test.in = 4;
	test.out = -1;
	test.services = 2.5;
	array_events[3] = test;
	
	test.in = 5;
	test.out = -1;
	test.services = 2;
	array_events[4] = test;
	
	test.in = 6;
	test.out = -1;
	test.services = 6;
	array_events[5] = test;
	
	test.in = 7;
	test.out = -1;
	test.services = 5.4;
	array_events[6] = test;
	
	test.in = 8;
	test.out = -1;
	test.services = 3;
	array_events[7] = test;
	
	test.in = 9;
	test.out = -1;
	test.services = 9;
	array_events[8] = test;
	
	test.in = 10;
	test.out = -1;
	test.services = 1;
	array_events[9] = test;


	timer = 0;
	simulate(timer);
	return 0;
}
