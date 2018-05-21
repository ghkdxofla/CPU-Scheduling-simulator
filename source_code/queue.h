#pragma once

// Node 정의
typedef struct Node* PtrNode;
typedef struct Node {
    void* data;
    PtrNode front;
    PtrNode back;
} Node;

typedef struct Queue* PtrQueue;
typedef struct Queue {
  int count;
  PtrQueue front;
  PtrQueue end;
} Queue;

void init_queue(); // queue 생성
void free_queue(PtrQueue queue, void* data); // queue 할당 해제
int pop_queue(PtrQueue queue); // index 반환
void push_queue(PtrQueue queue); // queue에 추가
