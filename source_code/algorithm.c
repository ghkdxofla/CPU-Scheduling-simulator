#include <stdio.h>
#include <stdlib.h>

#include "algorithm.h"

// cpu scheduling algorithm

void fcfs(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result) {
	int count_process = job_q->count; // 종료 여부를 판단하기 위함
	int time = 0; // 시작
	int idle_time = 0; // run state가 비어있는 시간
	while (time >= 0) {
		// job queue가 없는 경우 return
		// job queue에서 ready queue로 넘어감(arrive)
		if (job_q->count > 0) {
			if (job_q->front->data->arr_time == time) {
				push_queue(ready_q, pop_queue(job_q));
				// 최초의 process
				if (result->time_start = -1) {
					result->time_start = time;
					idle_time = 0;
				}
			}
			else 
				continue;
			
		}		

		// ready queue에서 run state로 향함
		// run state가 비었거나(NULL), 작업 종료 시(CPU burst 끝)

		// run state가 비었고, ready queue가 있을 경우

		if (run_s == NULL){
			// ready queue가 비었지만, wait queue에서 오는게 필요한 경우
			if(!ready_q->front && wait_q->front->data->eval_info.remain_io == 0)
				push_queue(ready_q, pop_queue(wait_q));
			if (ready_q->front) 
				run_s = pop_queue(ready_q);
			else {
				run_s = NULL;
				time++;
				idle_time++; // cpu가 아무것도 안하는 시간
				continue;
			}
		}

		// run_s에 무엇인가 있을 경우

		if (run_s != NULL) {
			// 작업이 마쳐졌는지부터 확인
			if (run_s->eval_info.remain_cpu == 0) {
				// 프로세스 처리
				run_s->eval_info.time_end = time; // 종료 처리
				run_s->eval_info.time_turn = run_s->eval_info.time_wait + run_s->burst_cpu; // turnaround 처리
				push_queue(term_q, run_s);
				// ready queue에서 꺼내 넣는다
				if (ready_q->front)
					run_s = pop_queue(ready_q);
				else {
					run_s = NULL;
					time++;
					idle_time++;
					continue;
				}

			}
			// I/O 발생 시
			if (run_s->burst_io > 0 && run_s->burst_cpu - run_s->eval_info.remain_cpu == 1) {
				run_s->eval_info.time_pause = time;
				push_queue(wait_q, run_s);
				// ready queue에서 꺼내 넣는다
				if (ready_q->front)
					run_s = pop_queue(ready_q);
				else {
					run_s = NULL;
					time++;
					idle_time++;
					continue;
				} 
			}
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

			// cpu 1초 처리
			run_s->eval_info.remain_cpu--;
		}
		// 아무튼 다 처리했으니 시간을...


		// waiting queue처리와 printf 해야 한다
		// waiting queue
		if(wait_q->front)
			wait_q->front->data->eval_info.remain_io--;

		// 모든 작업 종료
		if (job_q->count == 0 && term_q->count == count_process) {
			result->time_end = time; // 종료 시간
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
			// 모든 큐 할당 해제
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
