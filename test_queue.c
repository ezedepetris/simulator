#include <stdio.h>
#include <stdlib.h>

typedef struct N{
	int info;
	N* next;
}Node;

typedef struct Q {
	int lenght;
	Node* node;
}Queue;

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



int main(int argc, char const *argv[]){
	Queue *queue;
	queue = (Queue*) malloc(sizeof(Queue));
	queue->lenght = 0;
	enqueue(queue,1);
	enqueue(queue,2);
	enqueue(queue,3);
	show(queue);
	dequeue(queue);
	dequeue(queue);
	show(queue);
	dequeue(queue);
	printf("esta vacia? %d \n", is_empty(queue));
	return 0;
}