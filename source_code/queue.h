#pragma once

#include "process.h"

typedef enum Standard { ARRIVAL, SHORTEST, PRIORITY, PID } Standard;

// Node ����
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

PtrNode init_node(); // node ����
void free_node(PtrNode node); //node ����

PtrQueue init_queue(); // queue ����
void free_queue(PtrQueue queue); // queue �Ҵ� ����
PtrQueue copy_queue(PtrQueue queue); // queue ����
PtrProcess pop_queue(PtrQueue queue); // index ��ȯ
void push_queue(PtrQueue queue, PtrProcess data); // queue�� �߰�
void sort_queue(PtrQueue queue, Standard way); // queue sort
