#include "cpu_mem.h"


/*
	CPU Internal Functions
*/



/*
	CPU Control Functions
*/

void cpuInit(){
	cpu.reg_acu = 0;
	cpu.reg_dbr = 0;
	cpu.reg_x = 0;
	cpu.reg_y = 0;
	cpu.reg_dp = 0;
	cpu.reg_s = 0;
	cpu.reg_pc = 0;
	cpu.reg_pbr = 0;
	cpu.flag_e = 0;
	cpu.reg_p = 0;

	cpu.proc = null;
	cpu.data = 0;
	cpu.mem_adr = 0;
	cpu.is_mem_dest = false;
}

void cpuStep(){
	cpuFetch();
}
