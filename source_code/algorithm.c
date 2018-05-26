#include <stdio.h>
#include <stdlib.h>

#include "algorithm.h"

// cpu scheduling algorithm

void fcfs(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result) {
	int count_process = job_q->count; // ���� ���θ� �Ǵ��ϱ� ����
	int time = 0; // ����
	int idle_time = 0; // run state�� ����ִ� �ð�
	while (time >= 0) {
		// job queue�� ���� ��� return
		// job queue���� ready queue�� �Ѿ(arrive)
		if (job_q->count > 0) {
			if (job_q->front->data->arr_time == time) {
				push_queue(ready_q, pop_queue(job_q));
				// ������ process
				if (result->time_start = -1) {
					result->time_start = time;
					idle_time = 0;
				}
			}
			else 
				continue;
			
		}		

		// ready queue���� run state�� ����
		// run state�� ����ų�(NULL), �۾� ���� ��(CPU burst ��)

		// run state�� �����, ready queue�� ���� ���

		if (run_s == NULL){
			// ready queue�� �������, wait queue���� ���°� �ʿ��� ���
			if(!ready_q->front && wait_q->front->data->eval_info.remain_io == 0)
				push_queue(ready_q, pop_queue(wait_q));
			if (ready_q->front) 
				run_s = pop_queue(ready_q);
			else {
				run_s = NULL;
				time++;
				idle_time++; // cpu�� �ƹ��͵� ���ϴ� �ð�
				continue;
			}
		}

		// run_s�� �����ΰ� ���� ���

		if (run_s != NULL) {
			// �۾��� �������������� Ȯ��
			if (run_s->eval_info.remain_cpu == 0) {
				// ���μ��� ó��
				run_s->eval_info.time_end = time; // ���� ó��
				run_s->eval_info.time_turn = run_s->eval_info.time_wait + run_s->burst_cpu; // turnaround ó��
				push_queue(term_q, run_s);
				// ready queue���� ���� �ִ´�
				if (ready_q->front)
					run_s = pop_queue(ready_q);
				else {
					run_s = NULL;
					time++;
					idle_time++;
					continue;
				}

			}
			// I/O �߻� ��
			if (run_s->burst_io > 0 && run_s->burst_cpu - run_s->eval_info.remain_cpu == 1) {
				run_s->eval_info.time_pause = time;
				push_queue(wait_q, run_s);
				// ready queue���� ���� �ִ´�
				if (ready_q->front)
					run_s = pop_queue(ready_q);
				else {
					run_s = NULL;
					time++;
					idle_time++;
					continue;
				} 
			}
			// ó�� ���� ���
			// response time ����
			if (run_s->eval_info.time_res == -1) {
				run_s->eval_info.time_res = time - run_s->arr_time; // ��� �ð� - ���� �ð� => ���� �ð�
				run_s->eval_info.time_wait = run_s->eval_info.time_res;
				run_s->eval_info.time_start = time;
			}
			// ó�� �°��� �ƴϸ�
			else {
				run_s->eval_info.time_wait += (time - run_s->eval_info.time_pause); // ���� �� ����...?

			}

			// cpu 1�� ó��
			run_s->eval_info.remain_cpu--;
		}
		// �ƹ�ư �� ó�������� �ð���...


		// waiting queueó���� printf �ؾ� �Ѵ�
		// waiting queue
		if(wait_q->front)
			wait_q->front->data->eval_info.remain_io--;

		// ��� �۾� ����
		if (job_q->count == 0 && term_q->count == count_process) {
			result->time_end = time; // ���� �ð�
			result->util_cpu = (time - idle_time) / time;
			result->throughput = term_q->count / time;
			while (term_q->front) {
				result->awt += term_q->front->data->eval_info.time_wait;
				result->att += term_q->front->data->eval_info.time_turn;
				result->art += term_q->front->data->eval_info.time_res;
				PtrProcess pc = pop_queue(term_q);
				free_process(pc);
			}
			result->awt /= count_process;
			result->att /= count_process;
			result->art /= count_process;
			// ��� ť �Ҵ� ����
			free_state(run_s, job_q, ready_q, wait_q, term_q, result);
			break;
		}

		time++;
	}
	puts("JOB IS DONE!\n");
}// first-come, first-out
void prem_sjf(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result) {
	
} // preemitive shortest job first
void nprem_sjf(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // non-preemitive shortest job first
void prem_priority(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // preemitive priority first
void nprem_priority(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // non-preemitive priority first
void rr(int quantum, PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // round robin
//void hrrn(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // highest response ratio next
//void mlq(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // multi-level queue
