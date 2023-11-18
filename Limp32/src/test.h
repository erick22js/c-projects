#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "limp32/limp32.h"

#include "limp32/util/l_jmp.h"

L32Cpu g_cpu;
L32Cpu *cpu = &g_cpu;
L32Bus g_bus;
L32Bus *bus = &g_bus;

Uint8 memory[1024*1024];


/// Functions: interfacing bus object

Uint8 test_l32bus_get8(Uint32 adr){
	while(g_bus.busy);
	g_bus.busy = true;
	Uint8 data = 0;
	if(adr<(sizeof(memory))){
		data = memory[adr];
	}
	g_bus.busy = false;
	return data;
}

void test_l32bus_set8(Uint32 adr, Uint8 data){
	while(g_bus.busy);
	g_bus.busy = true;
	if(adr<(sizeof(memory))){
		memory[adr] = data;
	}
	g_bus.busy = false;
}

Uint16 test_l32bus_get16(Uint32 adr){
	while(g_bus.busy);
	g_bus.busy = true;
	Uint16 data = 0;
	if(adr<(sizeof(memory))){
		data = (memory[adr])|(memory[adr+1]<<8);
	}
	g_bus.busy = false;
	return data;
}

void test_l32bus_set16(Uint32 adr, Uint16 data){
	while(g_bus.busy);
	g_bus.busy = true;
	if(adr<(sizeof(memory))){
		memory[adr] = data;
		memory[adr+1] = data>>8;
	}
	g_bus.busy = false;
}

Uint32 test_l32bus_get32(Uint32 adr){
	while(g_bus.busy);
	g_bus.busy = true;
	Uint32 data = 0;
	if(adr<(sizeof(memory))){
		data = (memory[adr])|(memory[adr+1]<<8)|(memory[adr+2]<<16)|(memory[adr+3]<<24);
	}
	g_bus.busy = false;
	return data;
}

void test_l32bus_set32(Uint32 adr, Uint32 data){
	while(g_bus.busy);
	g_bus.busy = true;
	if(adr<(sizeof(memory))){
		memory[adr] = data;
		memory[adr+1] = data>>8;
		memory[adr+2] = data>>16;
		memory[adr+3] = data>>24;
	}
	g_bus.busy = false;
}


/**
	FUNCTIONS: Variables initializing
*/

void test_initialize(){
	l32cpu(cpu);
	g_bus.set8 = test_l32bus_set8;
	g_bus.get8 = test_l32bus_get8;
	g_bus.set16 = test_l32bus_set16;
	g_bus.get16 = test_l32bus_get16;
	g_bus.set32 = test_l32bus_set32;
	g_bus.get32 = test_l32bus_get32;
	cpu->devc_bus = bus;
}


#endif // TEST_H_INCLUDED
