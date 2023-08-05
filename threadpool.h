#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUMBER 10
#include <pthread.h>

// 任务结构体
typedef struct Task
{
    void (*function)(void *arg);
    void *arg;
} Task;

// 线程池结构体
typedef struct ThreadPool
{
    // 任务队列
    Task *taskQ;
    int queueCapacity;
    int queueSize; // 当前任务个数
    int queueFront;
    int queueRear;

    pthread_t managerID;  // 管理者线程ID
    pthread_t *threadIDs; // 工作的线程ID

    int minNum;  // 最小线程数
    int maxNum;  // 最大线程数
    int busyNum; // 忙的线程数
    int liveNum; // 存活的线程数
    int exitNum; // 要杀死的线程个数

    pthread_mutex_t mutexPool; // 锁整个线程池
    pthread_mutex_t mutexBusy; // 锁busyNum变量

    pthread_cond_t notFull; // 任务队列是否是满的
    pthread_cond_t notEmpty;

    int shutdown; // 是否销毁线程池
} ThreadPool;

ThreadPool *threadPoolCreate(int min, int max, int queueSize);

int threadPoolDestroy(ThreadPool *pool);

void threadPoolAdd(ThreadPool *pool, void (*func)(void *), void *arg);

int threadPoolBusyNum(ThreadPool *pool);

int threadPoolAliveNum(ThreadPool *pool);

void *manager(void *arg);

void *worker(void *arg);

void threadExit(ThreadPool *pool);
