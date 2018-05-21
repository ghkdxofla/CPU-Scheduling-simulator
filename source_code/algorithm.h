#pragma once

#include "process.h"
#include "queue.h"

// common algorithm

#define 

void sort_heap();

// cpu scheduling algorithm

void fcfs(); // first-come, first-out
void prem_sjf(); // preemitive shortest job first
void nprem_sjf(); // non-preemitive shortest job first
void prem_priority(); // preemitive priority first
void nprem_priority(); // non-preemitive priority first
void rr(); // round robin
void hrrn(); // highest response ratio next
void mlq(); // multi-level queue
