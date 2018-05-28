#include <stdio.h>
#include <stdlib.h>

#include "algorithm.h"

// cpu scheduling algorithm

void total_alg(int solution, int quantum, int io_when, PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result) {

	int count_process = job_q->count; // 종료 여부를 판단하기 위함
	int time = 0; // 시작
	int idle_time = 0; // run state가 비어있는 시간

	int quant_iter = quantum; // quantum을 사용하는 Round-robin의 iterator
	
	// 간트 차트 출력용
	
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
		// job queue가 없는 경우 return
		// job queue에서 ready queue로 넘어감(arrive)
		if (job_q->count > 0) {
			while (job_q->front && job_q->front->data->arr_time == time) {
				push_queue(ready_q, pop_queue(job_q));
				// 최초의 process
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

		// ready queue에서 run state로 향함
		// run state가 비었거나(NULL), 작업 종료 시(CPU burst 끝)

		// run state가 비었고, ready queue가 있을 경우

		//ready queue 만들기
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
		

		// run_s에 무엇인가 있을 경우
		// 끝난 process 먼저 내보내거나 I/O 작업 시 waiting queue로 넘기기


		if (run_s != NULL) {
			// I/O 발생 시 
			if (run_s->burst_io > 0 && run_s->eval_info.remain_io > 0) {
				if (run_s->burst_cpu - run_s->eval_info.remain_cpu == io_when || (run_s->burst_cpu < io_when && run_s->eval_info.remain_cpu == 0)) { // 실행 후 얼마 뒤에 I/O 실행되는지 설정
					run_s->eval_info.time_pause = time;
					push_queue(wait_q, run_s);
					run_s = NULL;
					if (solution == 5)
						quant_iter = quantum;
				}
			}
			// 작업이 마쳐졌는지 확인
			while (run_s != NULL && run_s->eval_info.remain_cpu == 0 && run_s->eval_info.remain_io == 0) {
				// 프로세스 처리
				run_s->eval_info.time_end = time; // 종료 처리
				run_s->eval_info.time_turn = run_s->eval_info.time_wait + run_s->burst_cpu; // turnaround 처리

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
				// Preemitive 부분
				if ((solution == 2 && ready_q->front->data->eval_info.remain_cpu < run_s->eval_info.remain_cpu) || (solution == 4 && ready_q->front && ready_q->front->data->priority < run_s->priority)) {
					run_s->eval_info.time_pause = time;
					push_queue(ready_q, run_s);
					run_s = NULL;
				}
				// Round-robin의 경우
				if (solution == 5 && quant_iter == 0) {
					run_s->eval_info.time_pause = time;
					push_queue(ready_q, run_s);

					// 작업이 마쳐졌는지 확인
					/*
					while (run_s != NULL && run_s->eval_info.remain_cpu == 0 && run_s->eval_info.remain_io == 0) {
						// 프로세스 처리
						run_s->eval_info.time_end = time; // 종료 처리
						run_s->eval_info.time_turn = run_s->eval_info.time_wait + run_s->burst_cpu; // turnaround 처리
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
					quant_iter = quantum; // 다시 quantum 초기화
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
				run_s->eval_info.time_end = time; // 종료 처리
				run_s->eval_info.time_turn = run_s->eval_info.time_wait + run_s->burst_cpu; // turnaround 처리
				push_queue(term_q, run_s);
				run_s = NULL;
				if (solution == 5)
					quant_iter = quantum;
			}
			if (ready_q->front) {
				run_s = pop_queue(ready_q);
				// 처음 들어온 경우
				// response time 설정
				if (run_s->eval_info.time_res == -1) {
					run_s->eval_info.time_res = time - run_s->arr_time; // 경과 시간 - 도착 시간 => 응답 시간
					run_s->eval_info.time_wait = run_s->eval_info.time_res;
					run_s->eval_info.time_start = time;
				}
				// 처음 온것이 아니면
				else {
					run_s->eval_info.time_wait += (time - run_s->eval_info.time_pause); // 에러 날 수도...?
				}
			}
			else {
				idle_time++; // cpu가 아무것도 안하는 시간
			}
		}
		// 아무튼 다 처리했으니 시간을...

		// 확인용(추후 간트 차트로...)
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
		// cpu 1초 처리
		if (run_s != NULL) {
			run_s->eval_info.remain_cpu--;
			if (solution == 5)
				quant_iter--;
		}
		// waiting queue처리와 printf 해야 한다

		// waiting queue
		// 0 된 process는 ready queue로 넘긴다

		if (wait_q->front)
			wait_q->front->data->eval_info.remain_io--;
		// 모든 작업 종료
		if (job_q->count == 0 && term_q->count == count_process) {
			result->util_cpu = (0.0 + time - idle_time) / time;
			result->time_end = time; // 종료 시간

			result->throughput = (0.0 + term_q->count) / time;
			while (term_q->front) {
				result->awt += term_q->front->data->eval_info.time_wait;
				result->att += term_q->front->data->eval_info.time_turn;
				result->art += term_q->front->data->eval_info.time_res;
				PtrProcess pc = pop_queue(term_q);

				// 개별 프로세스의 정보 출력
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
	// 출력
	puts("=============================================================================");
	puts("start      end      CPU util      throughput      AWT      ATT      ART      ");
	puts("");
	printf("%-11d%-9d%-14.3f%-16.3f%-9.3f%-9.3f%-9.3f\n", result->time_start, result->time_end, result->util_cpu, result->throughput, result->awt, result->att, result->art);
	puts("");
	puts("=============================================================================");
	puts("===============================================  Total Evaluation  ==========");
	puts("");
	puts("");
	// 모든 큐 할당 해제
	free_state(run_s, job_q, ready_q, wait_q, term_q, result);
}

// simulate and evaluate function
void simulate(int solution, int quant, int io_when, PtrQueue init_q) {
	// 먼저 init_q를 job_q에 복사
	PtrQueue job_q = copy_queue(init_q);
	PtrQueue ready_q = init_queue();
	PtrQueue wait_q = init_queue();
	PtrQueue term_q = init_queue();
	PtrProcess run_s = NULL;
	PtrEvalTotal result = init_evaluation(); // 최종 결과가 담긴다
	// 시작
	total_alg(solution, quant, io_when, run_s, job_q, ready_q, wait_q, term_q, result);
}

