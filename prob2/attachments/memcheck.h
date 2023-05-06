#ifndef CS100_MEMCHECK_H
#define CS100_MEMCHECK_H 1

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 1000

struct Record {
  void *ptr;              // address of the allocated memory
  size_t size;            // size of the allocated memory
  int line_no;            // line number, at which a call to malloc or calloc happens
  const char *file_name;  // name of the file, in which the call to malloc or calloc happens
};

struct Record records[MAX_RECORDS];
int num = 0; 

void *recorded_malloc(size_t size, int line, const char *file) {
  void *ptr = malloc(size);
  if (ptr != NULL) {
    records[num].ptr = ptr;
    records[num].line_no = line;
    records[num].file_name = file;
    records[num].size = size;
    num++;
  }
  return ptr;
}

void *recorded_calloc(size_t cnt, size_t each_size, int line, const char *file) {
  void *ptr = calloc(cnt, each_size);
  if (ptr != NULL) {
    records[num].ptr = ptr;
    records[num].line_no = line;
    records[num].file_name = file;
    records[num].size = each_size * cnt;
    num++;
  }
  return ptr;
}

void recorded_free(void *ptr, int line, const char *file) {
  if(ptr == NULL)
  	return ;
  int found = 0;
  for(int i = 0; i < num; i++){
  	if(records[i].ptr == ptr){
  		found = 1;
  		records[i].ptr = NULL;
  		break;
		}
	}
	if(!found){
		printf("Invalid free in file %s, line %d\n", file, line);
	}
	return ;
}

void check_leak(void) __attribute__((destructor));

void check_leak(void) {
  printf("Summary:\n");
  int N = 0;
  unsigned long long M = 0;
  for(int i = 0; i < num; i++){
  	if(records[i].ptr != NULL){
  		N++;
  		M += sizeof(records[i].ptr);
  		printf("%llu bytes memory not freed (allocated in file %s, line %d)\n", sizeof(records[i].ptr), records[i].file_name, records[i].line_no);
		}
	}
	if(N == 0){
		printf("All allocations have been freed.\n");
	}
	else {
		printf("%d allocation records not freed (%llu bytes in total).", N, M);
	}
}

#define malloc(SIZE) recorded_malloc(SIZE, __LINE__, __FILE__)
#define calloc(CNT, EACH_SIZE) recorded_calloc(CNT, EACH_SIZE, __LINE__, __FILE__)
#define free(PTR) recorded_free(PTR, __LINE__, __FILE__)

#endif // CS100_MEMCHECK_H
