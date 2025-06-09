#if !defined(TASK_H)
#define TASK_H

#include "common.h"

typedef enum
{
    TASK_READY,
    TASK_RUNNING,
    TASK_WAITING
} TaskState;

typedef void (*TaskFunction)(void);

typedef struct
{
    uint8_t id;
    uint8_t priority;
    TaskState state;
    TaskFunction function;
    Task *next;
} Task;

Task *task_create(uint8_t priority, TaskFunction func);

#endif // TASK_H
