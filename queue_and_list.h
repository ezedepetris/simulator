#define _queue_and_list_
#include <stdio.h>
#include <stdlib.h>

typedef struct ev{
  // structure for a single event
  float in;
  float out;
  float services;
  char* name;
}Event;

typedef struct N_Q{// <Queue class="Waiting-server">
  Event info;
  N_Q* next;
}Node;

typedef struct Q { // queue of events waiting for a server
  int lenght;
  Node* node;
}Queue;

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
  return  (q->lenght == 0)? 0 : 1;
}


// End of Method of Queue

typedef struct N_L{
  Event info;
  N_L* next;
}NodeNE;

typedef struct L { // queue of events waiting for a server
  int lenght;
  NodeNE* node; //list of out event
  Event in; //represente the in event
}List;

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
  if (aux != NULL)
    while(aux->next != NULL){
      printf("%f \n",(aux->info).out);
      aux = aux->next;
    }
    printf("%f \n",(aux->info).out);
}

int is_empty_l (List* l){
  return  (l->lenght == 0 && (l->in).in == -1)? 0 : 1;
}
// End of Method of Lsist