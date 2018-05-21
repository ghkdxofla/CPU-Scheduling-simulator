#include <stdlib.h>
#include <stdio.h>

#include "process.h"
#include "queue.h"

/*
* file : queue.c
* date : 2018-05-21
* author : Taelim Hwang
* purpose : create, delete and random generate process list.
*/


void init_queue(); // queue 생성
void free_queue(PtrQueue queue, void* data); // queue 할당 해제
int pop_queue(PtrQueue queue); // index 반환
void push_queue(PtrQueue queue); // queue에 추가
