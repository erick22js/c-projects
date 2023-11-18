
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"


C786Cpu *C786Cpu_create(C786Bus *bus){
    C786Cpu *l_cpu = (C786Cpu*)malloc(sizeof(C786Cpu));
    l_cpu->device_bus = bus;
    return l_cpu;
}

void C786Cpu_destroy(C786Cpu *l_cpu){
    free((void*)l_cpu);
}
