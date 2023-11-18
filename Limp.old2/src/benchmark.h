#include "time.h"


Uint64_t actual_time(){
	static struct timeval __timeval_te__;
	gettimeofday(&__timeval_te__, 0);
	Uint64_t secs = __timeval_te__.tv_sec;
	Uint64_t usecs = __timeval_te__.tv_usec;
	return secs*1000000+usecs;
}

Uint64_t _bench_tim;

void bench_begin(){
	_bench_tim = actual_time();
}
void bench_end(){
	printf("\n\nProgram has taken: %f seconds.", ((actual_time()-_bench_tim)/1000000.0f));
}
