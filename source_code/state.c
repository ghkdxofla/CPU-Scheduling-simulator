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
void save_state(PtrQueue job_q) {
	//FILE *fp;
	//fp = fopen("process_list.dat", "wb");



	/*
	// random process ����
	for (int i = 0; i < 10; i++) {
	PtrProcess pc = ran_process(i);
	push_queue(init_q, pc);
	}
	// ���� ������ ����
	sort_queue(init_q, ARRIVAL);
	*/
}

// ���Ϸκ��� �ҷ���
void load_state(PtrQueue init_q) {
	puts("================================================================");
	puts("�켱�� ���� ����");
	puts("�� ���� ���μ����� �����Ͻ� ����?");
	int n = 10; // �⺻ 10��
	scanf("%d", &n);
	// random process ����
	for (int i = 0; i < n; i++) {
		PtrProcess pc = ran_process(i);
		push_queue(init_q, pc);
	}
	// ���� ������ ����
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
	/*
	//  priority������ ����
	sort_queue(init_q, PRIORITY);
	sort_queue(init_q, ARRIVAL);
	*/
	/*
	// ���
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
	puts("�ҷ��� ���μ��� ���� �Է�");
	char fname[256];
	gets_s(fname, sizeof(fname));
	FILE *file;

	if (file = fopen(fname, "r")) {
	// ���⿡ ���μ��� �����ֱ�

	}
	else {
	puts("�ش��ϴ� ������ �����ϴ�!");
	}
	*/
}
