#pragma once

#include "queue.h"

// cpu scheduling algorithm

void fcfs(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q); // first-come, first-out
void prem_sjf(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q); // preemitive shortest job first
void nprem_sjf(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q); // non-preemitive shortest job first
void prem_priority(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q); // preemitive priority first
void nprem_priority(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q); // non-preemitive priority first
void rr(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q); // round robin
void hrrn(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q); // highest response ratio next
void mlq(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q); // multi-level queue
