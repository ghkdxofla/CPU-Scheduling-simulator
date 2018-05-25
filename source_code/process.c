#include <stdio.h>
#include <stdlib.h>

#include "process.h"
/*
* file : process.c
* date : 2018-05-14
* author : Taelim Hwang
* purpose : create, delete and random generate process list.
*/

// create process
PtrProcess init_process(){
  PtrProcess pc = (PtrProcess)malloc(sizeof(struct Process));
  pc->pid = 0;
  pc->burst_cpu = 0;
  pc->burst_io = 0;
  pc->arr_time = 0;
  pc->priority = 0;
  pc->eval_info.remain_cpu = 0;
  pc->eval_info.remain_io = 0;
  pc->eval_info.time_res = 0;
  pc->eval_info.time_turn = 0;
  pc->eval_info.time_wait = 0;
  return pc;
}

// delete process
void free_process(PtrProcess pc){
  free(pc);
}

PtrProcess ran_process(){
  PtrProcess pc = (PtrProcess)malloc(sizeof(struct Process));
  // 시드를 통한 난수 생성
  //srand((unsigned)time(NULL));
  pc->pid = rand();
  pc->burst_cpu = rand();
  pc->burst_io = rand();
  pc->arr_time = rand();
  pc->priority = rand();

  pc->eval_info.remain_cpu = pc->burst_cpu;
  pc->eval_info.remain_io = pc->burst_io;
  pc->eval_info.time_res = 0;
  pc->eval_info.time_turn = 0;
  pc->eval_info.time_wait = 0;
  return pc;
}

/*
int main(){
  PtrProcess pc1 = init_process();
  PtrProcess pc2 = ran_process();
  printf("%d\n", pc2->pid);
  free_process(pc1);
  free_process(pc2);
  printf("%d\n", pc2->pid);
  return 0;
}
*/
