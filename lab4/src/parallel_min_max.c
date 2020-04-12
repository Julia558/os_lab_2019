#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>

#include <getopt.h>

#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv) {
  int seed = -1;
  int array_size = -1;
  int pnum = -1;
  bool with_files = false;

  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"seed", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"by_files", no_argument, 0, 'f'},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            seed = atoi(optarg);
            // your code here
            // error handling
            if (seed <= 0) {
                printf("seed is a positive number\n");
                return 1;}
            break;
          case 1:
            array_size = atoi(optarg);
            // your code here
            // error handling
            if (array_size <= 0) {
                printf("array_size is a positive number\n");
                return 1;}
            break;
          case 2:
            pnum = atoi(optarg);
            // your code here
            // error handling
            if (pnum <= 0) {
                printf("pnum is a positive number\n");
                return 1;}
            break;
          case 3:
            with_files = true;
            break;

          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case 'f':
        with_files = true;
        break;
      case '?':
        break;
      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (seed == -1 || array_size == -1 || pnum == -1) {
    printf("Usage: %s --seed \"num\" --array_size \"num\" --pnum \"num\" \n",
           argv[0]);
    return 1;
  }

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);
  int active_child_processes = 0;

    // Время начала
  struct timeval start_time;
  gettimeofday(&start_time, NULL);

// Файл
  FILE *f;
  char name[] = "min_max.txt";
  if ((f = fopen(name, "w")) == NULL) {
    printf("Failed to create file");
    getchar();
    return -1;
  }
  int file = fileno(f);

    // Pipe
  int file_pipe_min[2];
  int file_pipe_max[2];
  if (pipe(file_pipe_min)<0)
    exit(0);
  if (pipe(file_pipe_max)<0)
    exit(0);

  int i;
  for (i = 0; i < pnum; i++) {
      // child_pid - идентификатор процесса
    pid_t child_pid = fork();
    if (child_pid >= 0) {
      // successful fork
      active_child_processes += 1;
      // Процесс-родитель получает идентификатор (PID) потомка
      // Процесс-потомок получает в качестве кода возврата значение 0
      if (child_pid == 0) {
        // child process
        struct MinMax min_max = GetMinMax(array,0,array_size);
        // parallel somehow

        char bufmin[100];
        sprintf(bufmin, "%d\n", min_max.min);
        char bufmax[100];
        sprintf(bufmax, "%d\n", min_max.max);
        
        if (with_files) {
          // use files here
          // Установить эксклюзивную блокировку для записи
          flock(file, LOCK_EX);  
          write(file, (void*)bufmin, strlen(bufmin));
          write(file, (void*)bufmax, strlen(bufmax));
          //Снять блокировку         
          flock(file, LOCK_UN);
          fclose(f);
        } else {
          // use pipe here
          char buf[100];
          sprintf(buf,"%d",min_max.min);
          write(file_pipe_min[1],buf,30);
          sprintf(buf,"%d",min_max.max);
          write(file_pipe_max[1],buf,30);
        }
        return 0;
      }

    } else {
      printf("Fork failed!\n");
      return 1;
    }
  }

  int status;
  while (active_child_processes > 0) {
    // your code here
    wait(&status);
    active_child_processes -= 1;
  }

  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  for (i = 0; i < pnum; i++) {
    int min = INT_MAX;
    int max = INT_MIN;

    if (with_files) {
      // read from files
      FILE *f = fopen("min_max.txt","r");
      char buf[100];
      int a;
      fscanf(f,"%s",buf);
      a=atoi(buf);
      if (min>a) 
        min=a;
      fscanf(f,"%s",buf);
      a=atoi(buf);
      if (max<a) 
        max=a;
    } else {
      // read from pipes
      char buf[100];
      int a;
      read(file_pipe_min[0],buf,30);
      a=atoi(buf);
      if (min>a) 
        min=a;
      read(file_pipe_max[0],buf,30);
      a=atoi(buf);
      if (max<a) 
        max=a;
    }

    if (min < min_max.min) min_max.min = min;
    if (max > min_max.max) min_max.max = max;
  }

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  free(array);

  printf("Min: %d\n", min_max.min);
  printf("Max: %d\n", min_max.max);
  printf("Elapsed time: %fms\n", elapsed_time);
  fflush(NULL);
  return 0;
}
