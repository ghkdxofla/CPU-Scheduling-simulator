#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"
/*
* file : process.c
* date : 2018-05-14
* author : Taelim Hwang
* purpose : create, delete and random generate process list.
*/

// create process
PtrProcess process_create(){
  PtrProcess pc = (PtrProcess)malloc(sizeof(struct Process));
  printf("Insert process id, burst cpu, burst I/O, arrival time and priority\n");
  scanf("%d %d %d %d %d", &pc->pid, &pc->burst_cpu, &pc->burst_io, &pc->arr_time, &pc->priority);
  // printf("%d, %d, %d, %d, %d\n", pc->pid, pc->burst_cpu, pc->burst_io, pc->arr_time, pc->priority);

  return pc;
}

// delete process
void process_delete(PtrProcess pc){
  free(pc);
}

PtrProcess process_random_gen(){
  PtrProcess pc = (PtrProcess)malloc(sizeof(struct Process));
  // 시드를 통한 난수 생성
  srand(time(NULL));
  pc->pid = rand();
  pc->burst_cpu = rand();
  pc->burst_io = rand();
  pc->arr_time = rand();
  pc->priority = rand();

  return pc;
}

int main(){
  PtrProcess pc1 = process_create();
  PtrProcess pc2 = process_random_gen();
  printf("%d\n", pc2->pid);
  process_delete(pc1);
  process_delete(pc2);
  printf("%d\n", pc2->pid);
  return 0;
}
