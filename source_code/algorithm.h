#pragma once

#include "state.h"

// cpu scheduling algorithm
//void hrrn(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // highest response ratio next
//void mlq(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // multi-level queue
void total_alg(int solution, int quantum, int io_when, PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // total solution
void simulate(int solution, int quant, int io_when, PtrQueue init_q);

