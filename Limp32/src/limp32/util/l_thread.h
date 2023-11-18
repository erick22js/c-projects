#ifndef LIMP32_THREAD_H_INCLUDED
#define LIMP32_THREAD_H_INCLUDED

#include <pthread.h>

#include "l_type.h"

/**
	INTERFACE FOR THEADING IN APPLICATIONS
*/

struct _L32appthread{
	pthread_t pt_i;
	void (*call_func)(void*);
	void* call_args;
	void* call_ret;
	Bool running;
};
typedef struct _L32appthread L32AppThread;

/**
	LIMP32 APPLICATION THREAD MODULES
*/

/// Function: Initializates a Thread
/// returns True on sucessful

Bool l32app_thread_create(L32AppThread *thread, void(*call_func)(void*), void* call_args){
	thread->pt_i = null;
	thread->running = false;
	thread->call_func = call_func;
	thread->call_args = call_args;
	thread->call_ret = null;
	return true;
}

/// Function: Starts the Thread
/// returns True on sucessful

Bool l32app_thread_start(L32AppThread *thread){
	if(thread->running){
		return false;
	}
	else{
		int status = pthread_create(&thread->pt_i, 0, thread->call_func, thread->call_args);
		if(status){
			return false;
		}
		else{
			thread->running = true;
			return true;
		}
	}
}

/// Function: Ends the Thread
/// returns True on sucessful

Bool l32app_thread_end(L32AppThread *thread){
	if(thread->running){
		pthread_exit(thread->pt_i);
		thread->running = false;
		return true;
	}
	else{
		return false;
	}
}

/// Function: Join to Thread
/// returns True on sucessful

Bool l32app_thread_join(L32AppThread *thread){
	if(thread->running){
		int status = pthread_join(thread->pt_i, &thread->call_ret);
		thread->running = false;
		if(status){
			return false;
		}
		else{
			return true;
		}
	}
	else{
		return false;
	}
}

/// Function: Retrieves the return value from Thread

void* l32app_thread_returned(L32AppThread *thread){
	return thread->call_ret;
}


#endif // LIMP32_THREAD_H_INCLUDED
