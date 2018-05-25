#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state.h"

void free_state(PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q){
  free_queue(job_q);
  free_queue(ready_q);
  free_queue(wait_q);
  free_queue(term_q);
}
void move_state(PtrQueue from_queue, PtrQueue to_queue){
  PtrProcess temp;
  if((temp = pop_queue(from_queue)) == NULL){
    printf("From queue is NULL!\n");
    return;
  }
  push_queue(to_queue, temp);
}
void save_state(PtrQueue job_q){
  //FILE *fp;
  //fp = fopen("process_list.dat", "wb");


}
/*
Queue load_state(char* file_name){
  Queue a;
  return a;
}
*/
void time_state(PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q) {
	
} //시간 경과
int main(int argc, char* argv[]){
	//PtrProcess pc = ran_process();
	
	
	//printf("%d\n", pc->pid);
  
	// state 초기화
	PtrProcess run_s = NULL;
	// job queue 초기화
	PtrQueue init_q = init_queue();
	for (int i = 0; i < 10; i++) {
		PtrProcess pc = ran_process();
		push_queue(init_q, pc);
		//printf("%d, ", pc->pid);
		//printf("%d, ", pc->arr_time);
		//printf("%d, ", job_q->front->data->burst_cpu);
		//printf("%d, ", job_q->front->data->priority);
	}
	// job queue 복사
	PtrQueue job_q = copy_queue(init_q);
	
	PtrQueue ready_q = init_queue();
	PtrQueue wait_q = init_queue();
	PtrQueue term_q = init_queue();
	srand((unsigned)time(NULL)); // seed 초기화 - 이건 메인에 한 번 써야된다

	
	sort_queue(init_q, ARRIVAL);
	while (init_q) {
		PtrProcess result = pop_queue(init_q);
		printf("arr_time: %d // ", result->arr_time);
	}
	
	
	//init_state(job_q, ready_q, run_q, wait_q, term_q);
	/*
	
	push_queue(job_q, pc);
	printf("%d\n", job_q->front->data->pid);

	printf("%d\n", pc->pid);
	*/
	return 0;
}
