#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algorithm.h"

// simulate and evaluate function
void simulate(int algorithm, PtrQueue init_q) {
	// 먼저 init_q를 job_q에 복사
	PtrQueue job_q = copy_queue(init_q);
	PtrQueue ready_q = init_queue();
	PtrQueue wait_q = init_queue();
	PtrQueue term_q = init_queue();
	PtrProcess run_s = NULL;
	PtrEvalTotal result = init_evaluation(); // 최종 결과가 담긴다
	
	int quant = 3; // rr의 time quantum
	// 시작
	puts("================================================");
	puts("================================================");
	switch (algorithm) {
	case 0:
		fcfs(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 1:
		//prem_sjf(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 2:
		//nprem_sjf(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 3:
		//prem_priority(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 4:
		//nprem_priority(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 5:
		//rr(quant, run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 6:
		//hrrn(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	case 7:
		//mlq(run_s, job_q, ready_q, wait_q, term_q, result);
		break;
	default:
		puts("해당하는 알고리즘이 없습니다!");
		break;
	}
	// 알고리즘 평가 출력
	gets();
	puts("================================================");
	puts("================================================");
}

// 다 끝나면 init_q를 꼭 할당해제 해야 한다

int main(int argc, char* argv[]) {
	// seed 초기화 - 이건 메인에 한 번 써야된다
	srand((unsigned)time(NULL));
	// init queue 초기화
	PtrQueue init_q = init_queue();
	
	// random process 생성
	for (int i = 0; i < 10; i++) {
		PtrProcess pc = ran_process(i);
		push_queue(init_q, pc);
	}
	
	// 도착 순으로 정렬
	sort_queue(init_q, ARRIVAL);

	// simulate
	simulate(0, init_q);

	// 끝나면 init_q 할당 해제
	free_queue(init_q);
	return 0;
}
