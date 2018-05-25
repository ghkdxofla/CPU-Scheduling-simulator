#pragma once

#include "queue.h"
//typedef enum State {JOB, READY, RUN, WAIT, TERM} State;


//void init_state(PtrQueue job_q, PtrQueue ready_q, PtrQueue run_q, PtrQueue wait_q, PtrQueue term_q); // queue 할당
void free_state(PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q); // 모든 queue 삭제
void move_state(PtrQueue from_queue, PtrQueue to_queue); // 상태 이동
void save_state(PtrQueue job_q); // 상태 저장
void time_state(PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q); //시간 경과
Queue load_state(char* file_name); //상태 불러오기
