#include <stdio.h>
#include <stdlib.h>

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


// Method of Lsist
void insert (List* l, Event ele, int in_out){
	/*
		in_out == 0 (is an in event)
		in_out == 1 (is an out event)
	*/
	if (in_out == 0){
		printf("HASTA ACA FUNCIONO 00000\n");
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

			if (ele.out < (walker->info).out){
				aux->next = walker;
				l->node = aux;
			}else{

				while(ele.out > (walker->info).out && walker->next != NULL){
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

	if((l->in).in < (aux->info).out)
		aux_info = l->in;
	else{
		aux_info = aux->info;
		l->node = (l->node)->next;
		free(aux);
	}
	return  aux_info;
}

void show_l (List* l){
	NodeNE *aux = l->node;
	if (aux != NULL)
		while(aux->next != NULL){
			printf("%f \n",(aux->info).out);
			aux = aux->next;
		}
		printf("%f \n",(aux->info).out);
}

int is_empty_l (List* l){
	return	(l->lenght == 0)? 0 : 1;
}
// End of Method of Lsist


int main(int argc, char const *argv[]){
	printf("HASTA ACA FUNCIONO\n");
	// initialize List
	List *list;
	list = (List*) malloc(sizeof(List));
	list->lenght = 0;

	Event a;

	a.in = 1;
	a.out = 3;
	a.services = 12;
	insert(list,a,1);
	
	//Event a;
	a.in = 1;
	a.out = 2;
	a.services = 12;
	insert(list,a,1);

	a.in = 1;
	a.out = 4;
	a.services = 12;
	insert(list,a,1);


	a.in = 1;
	a.out = 1;
	a.services = 12;
	insert(list,a,1);


	a.in = 1;
	a.out = 5;
	a.services = 12;
	insert(list,a,1);

	a.in = 1;
	a.out = 534;
	a.services = 12;
	insert(list,a,10);
	show_l(list);
	printf("Antes de eliminar\n");
	del(list);
	printf("Despues de eliminar\n");
	del(list);
	printf("Despues de eliminar\n");

	show_l(list);

	
	return 0;
}