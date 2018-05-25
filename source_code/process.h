#pragma once

#include <time.h>

// evaluation total structure
typedef struct EvalTotal* PtrEvalTotal;
typedef struct EvalTotal{
	int time_start; // start time
	int time_end; // end time
	double util_cpu; // CPU utilization
	int throughput; // throught
	double awt; // average waiting time
	double att; // average turnaround time
	double art; // average response time
} EvalTotal;

// evaluation process structure
typedef struct EvalProcess{
	int time_res; // response time
	int time_wait; // waiting time
	int time_turn; // turnaround time
	int remain_cpu; // remaining cpu time
	int remain_io; // remaining I/O time
} EvalProcess;

// process structure
typedef struct Process* PtrProcess;
typedef struct Process{
	int pid; // process id
	int burst_cpu; // CPU burst
	int burst_io; // I/O burst
	int arr_time; // arrival time
	int priority; // priority
	EvalProcess eval_info; // evaluation information
} Process;

PtrProcess init_process();
void free_process(PtrProcess pc);
PtrProcess ran_process();
