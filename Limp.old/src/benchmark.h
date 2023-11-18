#include "time.h"

u_int64_t actual_time(){
	static struct timeval __timeval_te__;
	gettimeofday(&__timeval_te__, 0);
	u_int64_t secs = __timeval_te__.tv_sec;
	u_int64_t usecs = __timeval_te__.tv_usec;
	return secs*1000000+usecs;
}
u_int64_t _bench_tim;
void bench_begin(){
	_bench_tim = actual_time();
}
void bench_end(){
	printf("\n\nProgram has taken: %f seconds.", ((actual_time()-_bench_tim)/1000000.0f));
}