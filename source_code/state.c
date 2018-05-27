/*
state.c�� queue ó���� ���� ���� ���α׷���
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
		while(fscanf(file, " %d %d %d %d %d", &pid, &burst_cpu, &burst_io, &arr_time, &priority) != EOF){
			PtrProcess pc = gen_process(pid, burst_cpu, burst_io, arr_time, priority);
			push_queue(init_q, pc);
			if (n % 3 == 0)
				printf("...");
			n++;
		}
		puts("...DONE!!!");
		puts("");
		fclose(file);
		if (init_q->count <= 0) {
			puts("EMPTY FILE!!!");
			return 0;
		}
	}
	else {
		puts("FILE NOT FOUND!!!");
		return 0;
	}

	// ���
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

// process �ҷ���
int save_state(PtrQueue init_q, int n, char select) {
	// ���� ���� �� ������ ����
	while (init_q->front) {
		PtrProcess pc_delete = pop_queue(init_q);
		free_process(pc_delete);
	}
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
		// random process ����
		puts("####  Generate  default  ####");
		puts("1. Default (=100)       [ 1 ]");
		puts("2. Set values    [ 2 OR ANY ]");
		puts("");
		int burst_cpu = 100;
		int burst_io = 100;
		int arr_time = 100;
		int priority = 100;
		char is_deafult = '1';
		scanf(" %c", &is_deafult);
		if (is_deafult != '1') {
			while (1) {
				puts("** Insert range of value **");
				puts("** [ CPU burst >= 1 ] [IO burst >= 0 ] [ arrival time >= 0 ] [ priority >= 1 ] **");
				puts("");
				scanf(" %d %d %d %d", &burst_cpu, &burst_io, &arr_time, &priority);
				if (burst_cpu >= 1 && burst_io >= 0 && arr_time >= 0 && priority >= 1) {
					break;
				}
				else {
					puts("OUT OF RANGE!!!");
					burst_cpu = 100;
					burst_io = 100;
					arr_time = 100;
					priority = 100;
				}
			}
		}
		
		for (int i = 0; i < n; i++) {
			PtrProcess pc = ran_process(i, burst_cpu, burst_io, arr_time, priority);
			push_queue(init_q, pc);
		}
	}
	else {
		puts("WRONG NUMBER!!!");
		return 0;
	}
	// ���� ������ ����, ���� ���� �ð��̸� PID�� ���� ������ ���ĵ�
	sort_queue(init_q, PID);
	sort_queue(init_q, ARRIVAL);

	// ���
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
