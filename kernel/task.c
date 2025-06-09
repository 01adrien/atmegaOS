#include "task.h"

extern uint8_t tasks_count;
extern Task tasks_pool[];
extern Task *tasks;

static inline Task *task_alloc()
{
    return tasks_count == MAX_TASKS
               ? NULL
               : tasks_pool + tasks_count;
}

Task *task_create(uint8_t priority, TaskFunction func)
{
    Task *t = task_alloc();
    if (t)
    {
        t->id = tasks_count++;
        t->state = TASK_READY;
        t->priority = priority;
        t->function = func;
        t->next = NULL;
        return t;
    }
    return NULL;
}
