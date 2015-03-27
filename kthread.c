#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>

#define CREATE_TRACE_POINTS
#include <trace/events/kthread.h>

#define NR_THREAD 5
#define STEPS 100000

struct task_struct *task[NR_THREAD];
int thread_data[NR_THREAD];

static
int work(void *data)
{
	int base = *((int *) data);
	int i;
	int cnt = 0;

	while(!kthread_should_stop()){
		for (i = base; i < base + STEPS; i++) {
			cnt++;
		}
		schedule();
	}

	return 0;
}

static
int kernel_init(void)
{
	int i;

	for (i = 0; i < NR_THREAD; i++) {
		thread_data[i] = i * STEPS;
		task[i] = kthread_run(&work, (void *) &thread_data[i],
				"kbench%d", i);
	}
	return 0;
}

static
void kernel_exit(void)
{
	int i;

	for (i = 0; i < NR_THREAD; i++)
		kthread_stop(task[i]);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Julien Desfossez <jdesfossez@efficios.com>");
MODULE_LICENSE("GPL");
