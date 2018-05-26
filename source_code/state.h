#pragma once

#include "queue.h"
//typedef enum State {JOB, READY, RUN, WAIT, TERM} State;



//void init_state(PtrQueue job_q, PtrQueue ready_q, PtrQueue run_q, PtrQueue wait_q, PtrQueue term_q); // queue 할당
void free_state(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // 모든 queue 삭제
void save_state(PtrQueue job_q); // 상태 저장
Queue load_state(char* file_name); //상태 불러오기
