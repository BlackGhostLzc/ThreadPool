#include <stdio.h>

typedef struct
{
    int param1;
    float param2;
    char param3;
} MyParams;

typedef struct Task
{
    void (*function)(void *arg);
    void *arg;
} Task;

void myFunction(void *arg)
{
    MyParams *params = (MyParams *)arg;
    // 使用 params->param1, params->param2, params->param3 进行操作
    printf("argument 1 is %d \n", params->param1);
    printf("argument 2 is %lf \n", params->param2);
    printf("argument 1 is %c \n", params->param3);
}

int main()
{
    MyParams params;
    params.param1 = 10;
    params.param2 = 3.14;
    params.param3 = 'A';

    Task task;
    task.function = myFunction;
    task.arg = &params;

    task.function(task.arg);
    // 在 myFunction 内部，使用强制类型转换将 arg 转换为 MyParams 指针
    // 然后可以访问 params->param1, params->param2, params->param3
    // 进行相应的操作
    return 0;
}