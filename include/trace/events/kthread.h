#undef TRACE_SYSTEM
#define TRACE_SYSTEM kthread

#if !defined(_TRACE_KTHREAD_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_KTHREAD_H

#include <linux/tracepoint.h>

TRACE_EVENT(
	tp1,
	TP_PROTO(pid_t pid, int v),
	TP_ARGS(pid, v),
	TP_STRUCT__entry(
		__field(int, pid)
		__field(int, v)
	),
	TP_fast_assign(
		entry->pid = pid;
		entry->v = v;
	),
	TP_printk("pid=%d, v=%d", __entry->pid, __entry->v)
   );

TRACE_EVENT(
	tp2,
	TP_PROTO(pid_t pid, int v),
	TP_ARGS(pid, v),
	TP_STRUCT__entry(
		__field(int, pid)
		__field(int, v)
	),
	TP_fast_assign(
		entry->pid = pid;
		entry->v = v;
	),
	TP_printk("pid=%d, v=%d", __entry->pid, __entry->v)
   );

#endif /* _TRACE_KTHREAD_H */

/* this part must be outside protection */
#include <trace/define_trace.h>
