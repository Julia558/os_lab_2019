#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t child_pid;
    //Создаем дочерний процесс
    child_pid = fork();
    //В родительском ждем 30с
    if (child_pid > 0) 
    {
        sleep(60);
        printf("Parent wait 60s \n");
    }
    //В дочернем процессе немедленно завершаем работу
    else 
    {
        exit(0);
        printf("Child exit \n");
    }
 return 0;
}

// gcc zombie.c -o zombie.o
// ./zombie.o&
// Смотрим все процессы (pid родителя в 3 колонке)
// ps ajx | grep -w Z
// Смотрим, что за процесс
// ps auxww | grep [pid]
// Убиваем
// kill -9 [pid]