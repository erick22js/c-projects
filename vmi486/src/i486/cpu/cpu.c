
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"


I486Cpu *I486Cpu_create(I486Bus *bus){
    I486Cpu *l_cpu = (I486Cpu*)malloc(sizeof(I486Cpu));
    l_cpu->device_bus = bus;
    return l_cpu;
}

void I486Cpu_destroy(I486Cpu *l_cpu){
    free((void*)l_cpu);
}
