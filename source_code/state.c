/*
state.c는 queue 처리를 위한 보조 프로그램임
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state.h"

void free_state(PtrProcess run_s, PtrQueue job_q, PtrQueue ready_q, PtrQueue wait_q, PtrQueue term_q, PtrEvalTotal result){
  free_queue(job_q);
  free_queue(ready_q);
  free_queue(wait_q);
  free_queue(term_q);
  free_process(run_s);
  free_evaluation(result);
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