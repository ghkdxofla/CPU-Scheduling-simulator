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
int load_state(PtrQueue init_q) {
	puts("");
	puts("** Insert file name **");
	puts("");
	char name[256];
	int n = 0;
	scanf(" %s", name);
	strcat(name, ".txt");
	FILE *file = fopen(name, "r");
	if (file != NULL) {
		puts("...FILE PROCESSING...");
		puts("");
		int pid = -1;
		int burst_cpu = -1;
		int burst_io = -1;
		int arr_time = -1;
		int priority = -1;
		
		while(fscanf(file, " %d %d %d %d %d", &pid, &burst_cpu, &burst_io, &arr_time, &priority) == 2){
			PtrProcess pc = gen_process(pid, burst_cpu, burst_io, arr_time, priority);
			push_queue(init_q, pc);
			if (n % 3 == 0)
				printf("...");
			n++;
		}
		puts("...DONE!!!");
		puts("");
		if (init_q->count <= 0) {
			puts("EMPTY FILE!!!");
			return 0;
		}
	}
	else {
		puts("FILE NOT FOUND!!!");
		return 0;
	}

	// 출력
	puts("================================================================");
	puts("pid      CPU burst      IO burst      arrival time      priority");
	PtrNode iter_node = init_q->front;
	while (iter_node) {
		printf("%-9d%-15d%-14d%-18d%-8d\n", iter_node->data->pid, iter_node->data->burst_cpu, iter_node->data->burst_io, iter_node->data->arr_time, iter_node->data->priority);
		iter_node = iter_node->next;
	}
	puts("================================================================");
	printf("================================== %10d processes ========\n", n);
	
	return 1;
}

// process 불러옴
int save_state(PtrQueue init_q, int n, char select) {

	if (select == '1') {
		// manually
		
		for (int i = 0; i < n; i++) {
			puts("** Insert process information **");
			puts("** [ CPU burst ] [IO burst ] [ arrival time ] [ priority ] **");
			puts("");
			int burst_cpu = -1;
			int burst_io = -1;
			int arr_time = -1;
			int priority = -1;
			scanf(" %d %d %d %d", &burst_cpu, &burst_io, &arr_time, &priority);

			PtrProcess pc = gen_process(i, burst_cpu, burst_io, arr_time, priority);
			push_queue(init_q, pc);
		}

	}
	else if (select == '2') {
		// random process 생성
		for (int i = 0; i < n; i++) {
			PtrProcess pc = ran_process(i);
			push_queue(init_q, pc);
		}
	}
	else {
		puts("WRONG NUMBER!!!");
		return 0;
	}
	// 도착 순으로 정렬, 같은 도착 시간이면 PID가 빠른 순으로 정렬됨
	sort_queue(init_q, PID);
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

	printf("================================== %10d processes ========\n", n);
	puts("");
	puts("** Insert file name **");
	puts("");
	char name[256];
	scanf(" %s", name);
	strcat(name, ".txt");
	FILE *file = fopen(name, "w");
	if (file != NULL) {
		iter_node = init_q->front;
		while (iter_node) {
			fprintf(file, "%d %d %d %d %d\n", iter_node->data->pid, iter_node->data->burst_cpu, iter_node->data->burst_io, iter_node->data->arr_time, iter_node->data->priority);
			iter_node = iter_node->next;
		}
		puts("");
		puts("** SAVED!!! **");
		puts("");
		fclose(file);
	}
	else {
		puts("FILE ERROR!!!");
		return 0;
	}
	return 1;
	
}
