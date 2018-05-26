#pragma once

#include <time.h>
// evaluation total structure
typedef struct EvalTotal* PtrEvalTotal;
typedef struct EvalTotal {

	int time_start; // start time
	int time_end; // end time

	double util_cpu; // CPU utilization
	double throughput; // throught
	double awt; // average waiting time
	double att; // average turnaround time
	double art; // average response time
} EvalTotal;

// evaluation process structure
typedef struct EvalProcess{
	int time_start; // start time
	int time_pause; // paused time
	int time_end; // end time
	int time_res; // response time, 음수로 시작(첫 한 번만 하기 위해)
	int time_wait; // waiting time
	int time_turn; // turnaround time
	int remain_cpu; // remaining cpu time
	int remain_io; // remaining I/O time
} EvalProcess;

// process structure
typedef struct Process* PtrProcess;
typedef struct Process{
	int pid; // process id
	int burst_cpu; // CPU burst, 1 이상
	int burst_io; // I/O burst, 0 이상, 기본적으로 1초 뒤에 작업 수행
	int arr_time; // arrival time, 0 이상
	int priority; // priority, 1 이상
	EvalProcess eval_info; // evaluation information
} Process;

PtrEvalTotal init_evaluation();
void free_evaluation(PtrEvalTotal et);

PtrProcess init_process();
void free_process(PtrProcess pc);
PtrProcess ran_process(int pid);
