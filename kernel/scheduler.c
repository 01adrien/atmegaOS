#include "scheduler.h"
#include "task.h"

Task *tasks = NULL;
uint8_t tasks_count = 0;
Task tasks_pool[MAX_TASKS] = {0};