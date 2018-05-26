#pragma once

#include "process.h"

typedef enum Standard { ARRIVAL, SHORTEST, PRIORITY, PID } Standard;

// Node 정의
typedef struct Node* PtrNode;
typedef struct Node {
	PtrProcess data;
	PtrNode next;
	PtrNode prev;
} Node;

typedef struct Queue* PtrQueue;
typedef struct Queue {
	int count;
	PtrNode front;
	PtrNode end;
} Queue;

PtrNode init_node(); // node 생성
void free_node(PtrNode node); //node 해제

PtrQueue init_queue(); // queue 생성
void free_queue(PtrQueue queue); // queue 할당 해제
PtrQueue copy_queue(PtrQueue queue); // queue 복사
PtrProcess pop_queue(PtrQueue queue); // index 반환
void push_queue(PtrQueue queue, PtrProcess data); // queue에 추가
void sort_queue(PtrQueue queue, Standard way); // queue sort
