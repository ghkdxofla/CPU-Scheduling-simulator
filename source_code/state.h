#pragma once

#include "queue.h"
void free_state(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result); // ��� queue ����
int load_state(PtrQueue init_q); // ���� ����
int save_state(PtrQueue init_q, int n, char select); //���� �ҷ�����
 