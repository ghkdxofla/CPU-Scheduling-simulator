#include <stdio.h>
#include <stdlib.h>

#include "process.h"
/*
* file : process.c
* date : 2018-05-14
* author : Taelim Hwang
* purpose : create, delete and random generate process list.
*/

// create evaluation part
PtrEvalTotal init_evaluation() {
	PtrEvalTotal et = (PtrEvalTotal)malloc(sizeof(struct EvalTotal));
	et->time_start = -1;
	et->time_end = 0;
	et->util_cpu = 0.0;
	et->throughput = 0.0;
	et->awt = 0.0;
	et->att = 0.0;
	et->art = 0.0;
	return et;
}
// delete evaluation
void free_evaluation(PtrEvalTotal et) {
	free(et);
}
// create process
PtrProcess init_process() {
	PtrProcess pc = (PtrProcess)malloc(sizeof(struct Process));
	pc->pid = 0;
	pc->burst_cpu = 0;
	pc->burst_io = 0;
	pc->arr_time = 0;
	pc->priority = 0;

	pc->eval_info.remain_cpu = 0;
	pc->eval_info.remain_io = 0;
	pc->eval_info.time_res = -1; // 처음에만 값 변경하기 위함
	pc->eval_info.time_turn = 0;
	pc->eval_info.time_wait = 0;

	pc->eval_info.time_start = 0;
	pc->eval_info.time_pause = 0;
	pc->eval_info.time_end = 0;
	return pc;
}

// delete process
void free_process(PtrProcess pc) {
	free(pc);
}

PtrProcess ran_process(int pid) {
	PtrProcess pc = (PtrProcess)malloc(sizeof(struct Process));
	pc->pid = pid; // 받아온 값을 pid로 생성
	pc->burst_cpu = (rand() % 10) + 1; // 1부터 100까지의 값 생성
	pc->burst_io = rand() % 11; // 0부터 100까지의 값 생성
	pc->arr_time = rand() % 11; // 0부터 1000까지의 값 생성
	pc->priority = (rand() % 100) + 1; // 1부터 1000까지의 값 생성

	pc->eval_info.remain_cpu = pc->burst_cpu;
	pc->eval_info.remain_io = pc->burst_io;
	pc->eval_info.time_res = -1;
	pc->eval_info.time_turn = 0;
	pc->eval_info.time_wait = 0;

	pc->eval_info.time_start = 0;
	pc->eval_info.time_pause = 0;
	pc->eval_info.time_end = 0;
	return pc;
}

/*
int main(){
PtrProcess pc1 = init_process();
PtrProcess pc2 = ran_process();
printf("%d\n", pc2->pid);
free_process(pc1);
free_process(pc2);
printf("%d\n", pc2->pid);
return 0;
}
*/
