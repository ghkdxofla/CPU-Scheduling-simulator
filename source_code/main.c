#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algorithm.h"

// simulate and evaluate function
void simulate(int algorithm, PtrQueue init_q) {
	// ���� init_q�� job_q�� ����
	PtrQueue job_q = copy_queue(init_q);
	PtrQueue ready_q = init_queue();
	PtrQueue wait_q = init_queue();
	PtrQueue term_q = init_queue();
	PtrProcess run_s = NULL;
	PtrEvalTotal result = init_evaluation(); // ���� ����� ����
	
	int quant = 3; // rr�� time quantum
	// ����
	puts("================================================");
	puts("================================================");
	switch (algorithm) {
	case 0:
		fcfs(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 1:
		//prem_sjf(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 2:
		//nprem_sjf(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 3:
		//prem_priority(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 4:
		//nprem_priority(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 5:
		//rr(quant, run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 6:
		//hrrn(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 7:
		//mlq(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	default:
		puts("�ش��ϴ� �˰����� �����ϴ�!");
		break;
	}
	// �˰��� �� ���
	gets();
	puts("================================================");
	puts("================================================");
}

// �� ������ init_q�� �� �Ҵ����� �ؾ� �Ѵ�

int main(int argc, char* argv[]) {
	// seed �ʱ�ȭ - �̰� ���ο� �� �� ��ߵȴ�
	srand((unsigned)time(NULL));
	// init queue �ʱ�ȭ
	PtrQueue init_q = init_queue();
	
	// random process ����
	for (int i = 0; i < 10; i++) {
		PtrProcess pc = ran_process(i);
		push_queue(init_q, pc);
	}
	
	// ���� ������ ����
	sort_queue(init_q, ARRIVAL);

	// simulate
	simulate(0, init_q);

	// ������ init_q �Ҵ� ����
	free_queue(init_q);
	return 0;
}
