#include <stdlib.h>
#include <stdio.h>

#include "queue.h"
/*
* file : queue.c
* date : 2018-05-21
* author : Taelim Hwang
* purpose : create, delete and random generate process list.
*/

PtrNode init_node() {
	PtrNode node = (PtrNode)malloc(sizeof(Node));
	node->data = init_process();
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void free_node(PtrNode node) {
	//free_process(node->data);
	free(node);

}


PtrQueue init_queue(){
  PtrQueue queue = (PtrQueue)malloc(sizeof(Queue));
  queue->front = NULL;
  queue->end = NULL;
  queue->count = 0;
  return queue;
} // queue ?ì„±

void free_queue(PtrQueue queue){
  PtrNode node = queue->end;
  while(queue->end){
    node = queue->end;
    queue->end = queue->end->prev;
	free_process(node->data);
	free_node(node);
  }
  free(queue);
} // queue ? ë‹¹ ?´ì œ

PtrQueue copy_queue(PtrQueue queue) {
	PtrQueue copy = init_queue();
	PtrNode queue_front = queue->front;
	while (queue_front) {
		PtrProcess pc = init_process();
		// ê°?ë³µì‚¬ ?œìž‘
		pc->arr_time = queue_front->data->arr_time;
		pc->burst_cpu = queue_front->data->burst_cpu;
		pc->burst_io = queue_front->data->burst_io;
		pc->eval_info = queue_front->data->eval_info;
		pc->pid = queue_front->data->pid;
		pc->priority = queue_front->data->priority;

		// copy????²¨ ?´ëŠ”??
		push_queue(copy, pc);
		queue_front = queue_front->next;
	}
	copy->count = queue->count;
	return copy;
} // queue ë³µì‚¬

PtrProcess pop_queue(PtrQueue queue){
  PtrProcess data;
  if(queue->count > 0){
    data = queue->front->data;
    if(queue->front != queue->end){
      queue->front = queue->front->next;
      queue->front->prev->next = NULL;
	  free_node(queue->front->prev);
      queue->front->prev = NULL;
    }
    else {
      queue->front = NULL;
	  free_node(queue->end);
      queue->end = NULL;
    }
    queue->count--;
    return data;
  }
  else{
    return NULL;
  }
} // data ë°˜í™˜

void push_queue(PtrQueue queue, PtrProcess data){
	PtrNode node = init_node();
  node->data = data;

  if(queue->count == 0){
    queue->front = node;
    queue->end = node;
  }
  else{
    queue->end->next = node;
    node->prev = queue->end;
    queue->end = node;
  }
  queue->count++;
} // queue??ì¶”ê?


void sort_queue(PtrQueue queue, Standard way){
	if (queue->count <= 1) {
		//printf("Don't need to sort\n");
		return;
	}

	PtrNode node = queue->front; // ?•ë ¬???„í•¨
	PtrNode node_next = node; // ë¹„êµë¥??„í•¨
	PtrNode temp_prev = NULL;
	PtrNode temp_next = NULL;
	

	PtrNode node_front = queue->front;
	//PtrNode node_end = queue->end;
	int node_iter = 0;
	int count_end = queue->count - 1;
	while (count_end > 0/*node_end != NULL && node_end != queue->front*/) {
		while (node != NULL && node_iter < count_end/* && node != node_end*/) {
			node_next = node->next;
			// ?„ì°© ?œìœ¼ë¡??•ë ¬
			// ë¬´ì¡°ê±?ì²˜ìŒ?ëŠ” ?„ì°© ?œìœ¼ë¡??•ë ¬???œë‹¤
			if (way == ARRIVAL) {
				if (node->data->arr_time <= node_next->data->arr_time) {
					node = node->next; 
					node_iter++; 
					continue;
				}
			}
			// ì§§ì? ?œê°„?¼ë¡œ ?•ë ¬
			else if (way == SHORTEST) {
				if (node->data->eval_info.remain_cpu <= node_next->data->eval_info.remain_cpu) {
					node = node->next; 
					node_iter++; 
					continue;
				}
			}
			// ?°ì„ ?œìœ„ë¡??•ë ¬
			else if (way == PRIORITY) {
				if (node->data->priority <= node_next->data->priority) {
					node = node->next; 
					node_iter++; 
					continue;
				}
			}
			// pidë¡??•ë ¬
			else if (way == PID) {
				if (node->data->pid <= node_next->data->pid) {
					node = node->next;
					node_iter++; 
					continue;
				}
			}


			if (node == queue->front) {
				queue->front = node_next;
				temp_prev = NULL;
			}
			else {
				temp_prev = node->prev;
				node->prev->next = node_next;
			}
			if (node_next == queue->end) {
				queue->end = node;
				temp_next = NULL;
			}
			else {
				temp_next = node_next->next;
				node_next->next->prev = node;
			}
			/*
			if (node_end == node_next) {
				node_end = node;
			}
			*/
			node_next->next = node;
			node->prev = node_next;



			node->next = temp_next;
			node_next->prev = temp_prev;


			
			//node = node_next->next;
			node_iter++;


		}
		node_iter = 0;
		count_end--;
		//node_end = node_end->prev;
		node = queue->front;
	}
	
	
	
}
