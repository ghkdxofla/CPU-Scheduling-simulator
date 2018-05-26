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
	
	free(node);

}


PtrQueue init_queue(){
  PtrQueue queue = (PtrQueue)malloc(sizeof(Queue));
  queue->front = NULL;
  queue->end = NULL;
  queue->count = 0;
  return queue;
} // queue 생성

void free_queue(PtrQueue queue){
  PtrNode node = queue->end;
  while(queue->end){
    node = queue->end;
    queue->end = queue->end->prev;
	free_process(node->data);
	free_node(node);
  }
  free(queue);
} // queue 할당 해제

PtrQueue copy_queue(PtrQueue queue) {
	PtrQueue copy = init_queue();
	PtrNode queue_front = queue->front;
	while (queue_front) {
		PtrNode node = init_node();
		// 값 복사 시작
		node->data->arr_time = queue_front->data->arr_time;
		node->data->burst_cpu = queue_front->data->burst_cpu;
		node->data->burst_io = queue_front->data->burst_io;
		node->data->eval_info = queue_front->data->eval_info;
		node->data->pid = queue_front->data->pid;
		node->data->priority = queue_front->data->priority;

		queue_front = queue_front->next;
	}
	copy->count = queue->count;
	return copy;
} // queue 복사

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
} // data 반환

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
} // queue에 추가


void sort_queue(PtrQueue queue, Standard way){
	if (queue->count <= 1) {
		printf("Don't need to sort\n");
		return;
	}

	PtrNode node = queue->front; // 정렬을 위함
	PtrNode node_next = node; // 비교를 위함
	PtrNode temp_prev = NULL;
	PtrNode temp_next = NULL;
	

	PtrNode node_front = queue->front;
	PtrNode node_end = queue->end;
	while (node_end != NULL && node_end != queue->front) {
		while (node != NULL && node != node_end) {
			node_next = node->next;
			// 도착 순으로 정렬
			// 무조건 처음에는 도착 순으로 정렬을 한다
			if (way == ARRIVAL) {
				if (node->data->arr_time <= node_next->data->arr_time) {
					node = node->next; continue;
				}
			}
			// 짧은 시간으로 정렬
			else if (way == SHORTEST) {
				if (node->data->burst_cpu <= node_next->data->burst_cpu) {
					node = node->next; continue;
				}
			}
			// 우선순위로 정렬
			else if (way == PRIORITY) {
				if (node->data->priority <= node_next->data->priority) {
					node = node->next; continue;
				}
			}
			// pid로 정렬
			else if (way == PID) {
				if (node->data->pid <= node_next->data->pid) {
					node = node->next; continue;
				}
			}


			if (node == queue->front) {
				queue->front = node_next;
				node_next->prev = NULL;
			}
			else {
				temp_prev = node->prev;
				node->prev->next = node_next;
			}
			if (node_next == queue->end) {
				queue->end = node;
				node->next = NULL;
			}
			else {
				temp_next = node_next->next;
				node_next->next->prev = node;
			}
			if (node_end == node_next) {
				node_end = node;
			}
			node_next->next = node;
			node->prev = node_next;


			node->next = temp_next;
			node_next->prev = temp_prev;


			
			node = node->next;


		}
		node_end = node_end->prev;
		node = queue->front;
	}
	
	
	
}
