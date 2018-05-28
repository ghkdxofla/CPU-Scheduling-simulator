#include <stdio.h>
#include <stdlib.h>

#include "algorithm.h"

// cpu scheduling algorithm

void total_alg(int solution, int quantum, int io_when, PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result) {

	int count_process = job_q->count; // ���� ���θ� �Ǵ��ϱ� ����
	int time = 0; // ����
	int idle_time = 0; // run state�� ����ִ� �ð�

	int quant_iter = quantum; // quantum�� ����ϴ� Round-robin�� iterator
	
	// ��Ʈ ��Ʈ ��¿�
	
	switch (solution) {
	case 0:
		// FCFS
		puts("||#################################|| ###         FCFS        ###");
		break;
	case 1:
		// Non-preemitive SJF
		puts("||#################################|| ###  Non-preemitive SJF ###");
		break;
	case 2:
		// Preemitive SJF
		puts("||#################################|| ###    preemitive SJF   ###");
		break;
	case 3:
		// Non-preemitive Priority
		puts("||#################################|| # Non-preemitive priority #");
		break;
	case 4:
		// Preemitive Priority
		puts("||#################################|| ##  preemitive priority  ##");
		break;
	case 5:
		// Round-robin
		puts("||#################################|| ###      Round-robin    ###");
		break;
	case 6:
		// HRRN
		puts("||#################################|| ###         HRRN        ###");
		break;
	case 7:
		// Shortest I/O First
		puts("||#################################|| ##   Shortest I/O First  ##");
		break;
	}
	puts("||=================================|| --- GANTT CHART START!! ---");
	while (time >= 0) {
		// job queue�� ���� ��� return
		// job queue���� ready queue�� �Ѿ(arrive)
		if (job_q->count > 0) {
			while (job_q->front && job_q->front->data->arr_time == time) {
				push_queue(ready_q, pop_queue(job_q));
				// ������ process
				if (result->time_start == -1) {
					result->time_start = time;
					idle_time = 0;
				}
			}

			if (result->time_start == -1) {
				time++;
				continue;
			}


		}

		// ready queue���� run state�� ����
		// run state�� ����ų�(NULL), �۾� ���� ��(CPU burst ��)

		// run state�� �����, ready queue�� ���� ���

		//ready queue �����
		if (wait_q->front && wait_q->front->data->eval_info.remain_io == 0) {
			//if (wait_q->front->data->eval_info.remain_cpu > 0) {
				push_queue(ready_q, pop_queue(wait_q));
			//}
			
		}
		
		switch (solution) {
		case 0:
			// FCFS
			break;
		case 1:
			// Non-preemitive SJF
			sort_queue(ready_q, SHORTEST);
			break;
		case 2:
			// Preemitive SJF
			sort_queue(ready_q, SHORTEST);
			break;
		case 3:
			// Non-preemitive Priority
			sort_queue(ready_q, PRIORITY);
			break;
		case 4:
			// Preemitive Priority
			sort_queue(ready_q, PRIORITY);
			break;
		case 5:
			// Round-robin
			break;
		case 6:
			// HRRN
			sort_queue(ready_q, HRRN);
			break;
		case 7:
			// Shortest I/O First
			sort_queue(ready_q, IO);
			break;
		}
		

		// run_s�� �����ΰ� ���� ���
		// ���� process ���� �������ų� I/O �۾� �� waiting queue�� �ѱ��


		if (run_s != NULL) {
			// I/O �߻� �� 
			if (run_s->burst_io > 0 && run_s->eval_info.remain_io > 0) {
				if (run_s->burst_cpu - run_s->eval_info.remain_cpu == io_when || (run_s->burst_cpu < io_when && run_s->eval_info.remain_cpu == 0)) { // ���� �� �� �ڿ� I/O ����Ǵ��� ����
					run_s->eval_info.time_pause = time;
					push_queue(wait_q, run_s);
					run_s = NULL;
					if (solution == 5)
						quant_iter = quantum;
				}
			}
			// �۾��� ���������� Ȯ��
			while (run_s != NULL && run_s->eval_info.remain_cpu == 0 && run_s->eval_info.remain_io == 0) {
				// ���μ��� ó��
				run_s->eval_info.time_end = time; // ���� ó��
				run_s->eval_info.time_turn = run_s->eval_info.time_wait + run_s->burst_cpu; // turnaround ó��

				push_queue(term_q, run_s);
				if (ready_q->front && ready_q->front->data->eval_info.remain_cpu == 0 && ready_q->front->data->eval_info.remain_io == 0) {
					run_s = pop_queue(ready_q);
					continue;
				}
				run_s = NULL;
				if (solution == 5)
					quant_iter = quantum;

			}
			if (run_s != NULL && ready_q->front && (solution == 2 || solution == 4 || solution == 5 || solution == 6 || solution == 7)) {
				// Preemitive �κ�
				if ((solution == 2 && ready_q->front->data->eval_info.remain_cpu < run_s->eval_info.remain_cpu) || (solution == 4 && ready_q->front && ready_q->front->data->priority < run_s->priority)) {
					run_s->eval_info.time_pause = time;
					push_queue(ready_q, run_s);
					run_s = NULL;
				}
				// Round-robin�� ���
				if (solution == 5 && quant_iter == 0) {
					run_s->eval_info.time_pause = time;
					push_queue(ready_q, run_s);

					// �۾��� ���������� Ȯ��
					/*
					while (run_s != NULL && run_s->eval_info.remain_cpu == 0 && run_s->eval_info.remain_io == 0) {
						// ���μ��� ó��
						run_s->eval_info.time_end = time; // ���� ó��
						run_s->eval_info.time_turn = run_s->eval_info.time_wait + run_s->burst_cpu; // turnaround ó��
						push_queue(term_q, run_s);
						if (ready_q->front && ready_q->front->data->eval_info.remain_cpu == 0 && ready_q->front->data->eval_info.remain_io == 0) {
							run_s = pop_queue(ready_q);
							continue;
						}
						run_s = NULL;
						if (solution == 5)
							quant_iter = quantum;

					}
					*/
					run_s = NULL;
					quant_iter = quantum; // �ٽ� quantum �ʱ�ȭ
				}
				// HRRN
				if (solution == 6 && (0.0 + ready_q->front->data->eval_info.time_wait + ready_q->front->data->burst_cpu) / ready_q->front->data->burst_cpu < (0.0 + run_s->eval_info.time_wait + run_s->burst_cpu) / run_s->burst_cpu) {
					run_s->eval_info.time_pause = time;
					push_queue(ready_q, run_s);
					run_s = NULL;
				}
				// Shortest I/O First
				if (solution == 7 && ready_q->front->data->eval_info.remain_io <  run_s->eval_info.remain_io) {
					run_s->eval_info.time_pause = time;
					push_queue(ready_q, run_s);
					run_s = NULL;
				}

			}
		}
		if (run_s == NULL) {
			while (ready_q->front && ready_q->front->data->eval_info.remain_cpu == 0 && ready_q->front->data->eval_info.remain_io == 0) {
				run_s = pop_queue(ready_q);
				run_s->eval_info.time_end = time; // ���� ó��
				run_s->eval_info.time_turn = run_s->eval_info.time_wait + run_s->burst_cpu; // turnaround ó��
				push_queue(term_q, run_s);
				run_s = NULL;
				if (solution == 5)
					quant_iter = quantum;
			}
			if (ready_q->front) {
				run_s = pop_queue(ready_q);
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
			}
			else {
				idle_time++; // cpu�� �ƹ��͵� ���ϴ� �ð�
			}
		}
		// �ƹ�ư �� ó�������� �ð���...

		// Ȯ�ο�(���� ��Ʈ ��Ʈ��...)
		if (run_s != NULL)
			printf("||  pid : %-5d  ||  time : %-5d  || [CPU : %-5d] [I/O : %-5d]\n", run_s->pid, time, run_s->eval_info.remain_cpu, run_s->eval_info.remain_io);
		else {
			if (job_q->count == 0 && term_q->count == count_process){
				printf("||  TERMINATION  ||  time : %-5d  || [TERMINATION] [TERMINATION]\n", time);
				puts("||=================================|| --- GANTT CHART END!!!! ---");
			}
			else
				printf("||  pid : idle   ||  time : %-5d  || [CPU :      ] [I/O :      ]\n", time);
		}
		// cpu 1�� ó��
		if (run_s != NULL) {
			run_s->eval_info.remain_cpu--;
			if (solution == 5)
				quant_iter--;
		}
		// waiting queueó���� printf �ؾ� �Ѵ�

		// waiting queue
		// 0 �� process�� ready queue�� �ѱ��

		if (wait_q->front)
			wait_q->front->data->eval_info.remain_io--;
		// ��� �۾� ����
		if (job_q->count == 0 && term_q->count == count_process) {
			result->util_cpu = (0.0 + time - idle_time) / time;
			result->time_end = time; // ���� �ð�

			result->throughput = (0.0 + term_q->count) / time;
			while (term_q->front) {
				result->awt += term_q->front->data->eval_info.time_wait;
				result->att += term_q->front->data->eval_info.time_turn;
				result->art += term_q->front->data->eval_info.time_res;
				PtrProcess pc = pop_queue(term_q);

				// ���� ���μ����� ���� ���
				puts("=============================================================================");
				puts("pid        start       end        Waiting      Turnaround      Response      ");
				puts("");
				printf("%-11d%-12d%-11d%-13d%-16d%-14d\n", pc->pid, pc->eval_info.time_start, pc->eval_info.time_end, pc->eval_info.time_wait, pc->eval_info.time_turn, pc->eval_info.time_res);
				puts("");
				free_process(pc);
			}
			puts("=============================================================================");
			puts("===============================================       Result       ==========");
			result->awt /= count_process;
			result->att /= count_process;
			result->art /= count_process;


			break;
		}
		//printf("%d\n", time);
		
		time++;
	}
	puts(".");
	puts(".");
	puts(".");
	puts("JOB IS DONE!");
	puts(".");
	puts(".");
	puts(".");
	// ���
	puts("=============================================================================");
	puts("start      end      CPU util      throughput      AWT      ATT      ART      ");
	puts("");
	printf("%-11d%-9d%-14.3f%-16.3f%-9.3f%-9.3f%-9.3f\n", result->time_start, result->time_end, result->util_cpu, result->throughput, result->awt, result->att, result->art);
	puts("");
	puts("=============================================================================");
	puts("===============================================  Total Evaluation  ==========");
	puts("");
	puts("");
	// ��� ť �Ҵ� ����
	free_state(run_s, job_q, ready_q, wait_q, term_q, result);
}

// simulate and evaluate function
void simulate(int solution, int quant, int io_when, PtrQueue init_q) {
	// ���� init_q�� job_q�� ����
	PtrQueue job_q = copy_queue(init_q);
	PtrQueue ready_q = init_queue();
	PtrQueue wait_q = init_queue();
	PtrQueue term_q = init_queue();
	PtrProcess run_s = NULL;
	PtrEvalTotal result = init_evaluation(); // ���� ����� ����
	// ����
	total_alg(solution, quant, io_when, run_s, job_q, ready_q, wait_q, term_q, result);
}

