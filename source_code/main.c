#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algorithm.h"

void cli_control(PtrQueue init_q) {

	puts("================================================================");
	puts("================                                ================");
	puts("================ CPU SCHEDULING SIMULATOR  v1.0 ================");
	puts("================                                ================");
	puts("================ - TAELIM HWANG -- 2011140138 - ================");
	puts("================                                ================");
	puts("================================================================");


	while (1) {
		puts("#####     Main menu     #####");
		puts("1. Load process         [ 1 ]");
		puts("2. Generate process     [ 2 ]");
		puts("0. Exit program         [ 0 ]");
		puts("");
		char select;
		int quantum = 0;
		scanf(" %c", &select);
		if (select == '1') {
			puts("####   Load process   ####");
			puts("1. From cache        [ 1 ]");
			puts("2. From file         [ 2 ]");
			puts("0. Back       [ 0 OR ANY ]");
			puts("");
			scanf(" %c", &select);
			//printf("%c\n", &select);
			if (select != '1' && select != '2')
				continue;
			else if (select == '1') {
				if (init_q->count <= 0) {
					puts("");
					puts("NO CACHE!!!");
					puts("");
					continue;
				}
			}
			else if (select == '2') {
				if (!load_state(init_q)) {
					continue;
				}
				
			}
			puts("####   Select algorithm   ####");
			puts("1. FCFS                  [ 1 ]");
			puts("2. Non-premitive SJF     [ 2 ]");
			puts("3. Premitive SJF         [ 3 ]");
			puts("4. Non-premitive Prioirty[ 4 ]");
			puts("5. Premitive Priority    [ 5 ]");
			puts("6. Round-robin           [ 6 ]");
			puts("7. HRRN                  [ 7 ]");
			puts("8. Shortest I/O First    [ 8 ]");
			puts("9. ALL                   [ 9 ]");
			puts("0. Back           [ 0 OR ANY ]");
			puts("");
			scanf(" %c", &select);
			switch (select) {
			case '1':
				// FCFS
				simulate(0, 0, init_q);
				break;
			case '2':
				// Non-preemitive SJF
				simulate(1, 0, init_q);
				break;
			case '3':
				// Preemitive SJF
				simulate(2, 0, init_q);
				break;
			case '4':
				// Non-preemitive Priority
				simulate(3, 0, init_q);
				break;
			case '5':
				// Preemitive Priority
				simulate(4, 0, init_q);
				break;
			case '6':
				puts("");
				puts("** Insert time quantum for Round-robin **");
				puts("");
				
				// Round-robin, time quantum need
				do {
					scanf(" %d", &quantum);
					if (quantum < 0)
						puts("NO NEGATIVE NUMBER!!!");
				} while (quantum < 0);
				simulate(5, quantum, init_q);
				break;
			case '7':
				// HRRN
				simulate(6, 0, init_q);
				break;
			case '8':
				// Shortest I/O First
				simulate(7, 0, init_q);
				break;
			case '9':
				simulate(0, 0, init_q);
				simulate(1, 0, init_q);
				simulate(2, 0, init_q);
				simulate(3, 0, init_q);
				simulate(4, 0, init_q);
				simulate(6, 0, init_q);
				simulate(7, 0, init_q);
				puts("");
				puts("** Insert time quantum for Round-robin **");
				puts("");
				// Round-robin, time quantum need
				do {
					scanf(" %d", &quantum);
					if(quantum < 0)
						puts("NO NEGATIVE NUMBER!!!");
				} while (quantum < 0);
				simulate(5, quantum, init_q);
				break;
			default:
				break;
			}
		}
		else if (select == '2') {
			puts("####   Generate process   ####");
			puts("1. Generate manually     [ 1 ]");
			puts("2. Generate randomly     [ 2 ]");
			puts("0. Back           [ 0 OR ANY ]");
			puts("");
			scanf(" %c", &select);
			//printf("%c\n", &select);
			if (select != '1' && select != '2')
				continue;
			puts("");
			puts("** How many processes? **");
			puts("");
			int n;
			scanf(" %d", &n);
			if (!save_state(init_q, n, select)) {
				continue;
			}
			
		}
		else if (select == '0') {
			puts("");
			puts("...SEE YOU!!!");
			break;
		}
		else {
			puts("");
			puts("WRONG NUMBER!!!");
			puts("");
			continue;
		}
	}
}

int main(int argc, char* argv[]) {
	// seed 초기화 - 이건 메인에 한 번 써야된다
	srand((unsigned)time(NULL));
	// init queue 초기화
	PtrQueue init_q = init_queue();
	// 도착 순 초기화 및 인터페이스 로드
	cli_control(init_q);
	// 끝나면 init_q 할당 해제
	free_queue(init_q);
	return 0;
}
