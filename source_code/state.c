/*
state.c는 queue 처리를 위한 보조 프로그램임
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state.h"

void free_state(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result) {
	free_queue(job_q);
	free_queue(ready_q);
	free_queue(wait_q);
	free_queue(term_q);
	free_process(run_s);
	free_evaluation(result);
}
void save_state(PtrQueue job_q) {
	//FILE *fp;
	//fp = fopen("process_list.dat", "wb");



	/*
	// random process 생성
	for (int i = 0; i < 10; i++) {
	PtrProcess pc = ran_process(i);
	push_queue(init_q, pc);
	}
	// 도착 순으로 정렬
	sort_queue(init_q, ARRIVAL);
	*/
}

// 파일로부터 불러옴
void load_state(PtrQueue init_q) {
	puts("================================================================");
	puts("우선은 랜덤 생성");
	puts("몇 개의 프로세스를 생성하실 건지?");
	int n = 10; // 기본 10개
	scanf("%d", &n);
	// random process 생성
	for (int i = 0; i < n; i++) {
		PtrProcess pc = ran_process(i);
		push_queue(init_q, pc);
	}
	// 도착 순으로 정렬
	sort_queue(init_q, ARRIVAL);

	// 출력
	puts("================================================================");
	puts("pid      CPU burst      IO burst      arrival time      priority");
	PtrNode iter_node = init_q->front;
	while (iter_node) {
		printf("%-9d%-15d%-14d%-18d%-8d\n", iter_node->data->pid, iter_node->data->burst_cpu, iter_node->data->burst_io, iter_node->data->arr_time, iter_node->data->priority);
		iter_node = iter_node->next;
	}
	puts("================================================================");
	/*
	//  priority순으로 정렬
	sort_queue(init_q, PRIORITY);
	sort_queue(init_q, ARRIVAL);
	*/
	/*
	// 출력
	puts("================================================================");
	puts("pid      CPU burst      IO burst      arrival time      priority");
	iter_node = init_q->front;
	while (iter_node) {
		printf("%-9d%-15d%-14d%-18d%-8d\n", iter_node->data->pid, iter_node->data->burst_cpu, iter_node->data->burst_io, iter_node->data->arr_time, iter_node->data->priority);
		iter_node = iter_node->next;
	}
	puts("================================================================");
	*/


	/*
	puts("불러올 프로세스 파일 입력");
	char fname[256];
	gets_s(fname, sizeof(fname));
	FILE *file;

	if (file = fopen(fname, "r")) {
	// 여기에 프로세스 보여주기

	}
	else {
	puts("해당하는 파일이 없습니다!");
	}
	*/
}
