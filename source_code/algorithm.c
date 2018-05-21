#include <stdio.h>
#include <stdlib.h>

// common algorithm
#define SWAP(a, b) {int t; t = a; a = b; b = t;}
#define PARENT(i) ((i - 1) / 2)
#define LCHILD(i) (2 * i + 1)
#define RCHILD(i) (2 * i + 2)

void sort_heap(int array[], int len){
	for(int i = 1;i < len; i++){
		int j = i;
		while(j > 0){
			int parent = PARENT(j);
			if(array[parent] < array[j]){
				SWAP(array[parent], array[j]);

      }
			else
				break;
			j = parent;

		}
  }

	while(len > 0){
		len--;
		// swap root end end leaf node
		SWAP(array[0], array[len]);
		int i = 0;
		while(1){
			int left = LCHILD(i);
			int right = RCHILD(i);

			// no child node
			if(len <= left)
				break;
			else if(len == right){
				if(array[i] < array[left]){
					SWAP(array[i], array[left]);
        }
				break;
			}
			else{
				int temp = left;
				if(array[left] < array[right])
					temp = right;
				if(array[i] < array[temp]){
					SWAP(array[i], array[temp]);
					i = temp;
				}
				else
					break;
			}
		}
	}

}

// cpu scheduling algorithm

void fcfs(); // first-come, first-out
void prem_sjf(); // preemitive shortest job first
void nprem_sjf(); // non-preemitive shortest job first
void prem_priority(); // preemitive priority first
void nprem_priority(); // non-preemitive priority first
void rr(); // round robin
void hrrn(); // highest response ratio next
void mlq(); // multi-level queue
