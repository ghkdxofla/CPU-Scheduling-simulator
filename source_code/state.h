#pragma once

#include "queue.h"
void free_state(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // 모든 queue 삭제
void save_state(PtrQueue job_q); // 상태 저장
void load_state(PtrQueue init_q); //상태 불러오기
