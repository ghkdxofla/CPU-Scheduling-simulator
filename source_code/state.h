#pragma once

#include "queue.h"
void free_state(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // ��� queue ����
void save_state(PtrQueue job_q); // ���� ����
void load_state(PtrQueue init_q); //���� �ҷ�����
