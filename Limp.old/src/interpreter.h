#ifndef limp_interpreter_h
#define limp_interpreter_h

#include <stdio.h>
#include <string.h>

#include "limp/limp.h"

LIMPCpu G_cpu;
LIMPCpu *Gm_cpu = &G_cpu;
Lbool _li_running = TRUE;
Lbool _li_feedback = TRUE;
Luint32 _li_t0 = 0;
Luint32 _li_t1 = 0;
Luint32 _li_t2 = 0;
Luint32 _li_t3 = 0;
Luint32 _li_ladr = 0;

Lbool _li_readFile(char* path, char* buffer, int max_length){
	FILE *file = fopen(path, "r");
	
	if(file==NULL){
		return FALSE;
	}
	
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	fread(buffer, 1, length<max_length?length:max_length, file);
	fclose(file);
	return TRUE;
}

Lbool _li_writeFile(char* path, char* buffer, int length){
	FILE *file = fopen(path, "w");
	
	if(file==NULL){
		return FALSE;
	}
	
	fwrite(buffer, 1, length, file);
	fclose(file);
	return TRUE;
}

FILE *_li_createFile(char* path){
	FILE *file = fopen(path, "w");
	
	if(file==NULL){
		return NULL;
	}
	
	fwrite(NULL, 1, 0, file);
	fclose(file);
	
	file = fopen(path, "a");
	return file;
}

FILE *_li_openFile(char* path){
	FILE *file = fopen(path, "r");
	
	if(file==NULL){
		return NULL;
	}
	
	return file;
}

Lbool _li_appendFile(FILE *file, Luint8 data){
	fputc(data, file);
	return TRUE;
}

Lbool _li_se(char* str1, char* str2){
	return strcmp(str1, str2)==0;
}

void _li_nextparam_(char** cmd, char* buffer){
	char* src = *cmd;
	char chr;
	Lbool first = TRUE;
	chr = *src;
	{
		if(chr=='"'){
			src++;
			chr = *src;
			while((chr!='"')&&(chr!=0)){
				buffer = chr;
				buffer++;
				src++;
				chr = *src;
			}
			*buffer = 0;
			*cmd = src;
			return;
		}
	}
	do{
		
		*buffer = ((chr>='A')&&(chr<='Z'))?chr+('a'-'A'):chr;
		buffer++;
		
		src++;
		if(first){
			if((chr==0)||!((chr>='a'&&chr<='z')||(chr>='A'&&chr<='Z')||(chr>='0'&&chr<='9')||(chr=='_'))){
				break;
			}
		}
		chr = *src;
		first = FALSE;
			}while((chr!=0)&&((chr>='a'&&chr<='z')||(chr>='A'&&chr<='Z')||(chr>='0'&&chr<='9')||(chr=='_')));
	
	*buffer = 0;
	if((*src)=='\\'){
		src++;
	}
	*cmd = src;
}

void _li_nextparam(char** cmd, char* buffer){
	do{
		_li_nextparam_(cmd, buffer);
	}while(
		(_li_se(buffer, " ")||
		_li_se(buffer, "(")||
		_li_se(buffer, ")")||
		_li_se(buffer, ","))
	);
}

Lsint32 _li_nextgreg(char** cmd){
	char buffer[256];
	_li_nextparam(cmd, buffer);
	Lsint32 reg = -1;
	
	if(_li_se(buffer, "eax")){
		reg = 0;
	}
	if(_li_se(buffer, "edx")){
		reg = 1;
	}
	if(_li_se(buffer, "ecx")){
		reg = 2;
	}
	if(_li_se(buffer, "ebx")){
		reg = 3;
	}
	if(_li_se(buffer, "efp")){
		reg = 4;
	}
	if(_li_se(buffer, "esp")){
		reg = 5;
	}
	if(_li_se(buffer, "ess")){
		reg = 6;
	}
	if(_li_se(buffer, "esd")){
		reg = 7;
	}
	if(_li_se(buffer, "ax")){
		reg = 8;
	}
	if(_li_se(buffer, "dx")){
		reg = 9;
	}
	if(_li_se(buffer, "cx")){
		reg = 10;
	}
	if(_li_se(buffer, "bx")){
		reg = 11;
	}
	if(_li_se(buffer, "fp")){
		reg = 12;
	}
	if(_li_se(buffer, "sp")){
		reg = 13;
	}
	if(_li_se(buffer, "ss")){
		reg = 14;
	}
	if(_li_se(buffer, "sd")){
		reg = 15;
	}
	if(_li_se(buffer, "al")){
		reg = 16;
	}
	if(_li_se(buffer, "ah")){
		reg = 17;
	}
	if(_li_se(buffer, "dl")){
		reg = 18;
	}
	if(_li_se(buffer, "dh")){
		reg = 19;
	}
	if(_li_se(buffer, "cl")){
		reg = 20;
	}
	if(_li_se(buffer, "ch")){
		reg = 21;
	}
	if(_li_se(buffer, "bl")){
		reg = 22;
	}
	if(_li_se(buffer, "bh")){
		reg = 23;
	}
	
	return reg;
}

Lsint32 _li_nextflag(char** cmd){
	char buffer[256];
	_li_nextparam(cmd, buffer);
	Lsint32 reg = -1;
	
	if(_li_se(buffer, "cf")){
		reg = 0;
	}
	if(_li_se(buffer, "bf")){
		reg = 1;
	}
	if(_li_se(buffer, "vf")){
		reg = 2;
	}
	if(_li_se(buffer, "nf")){
		reg = 3;
	}
	if(_li_se(buffer, "zf")){
		reg = 4;
	}
	if(_li_se(buffer, "of")){
		reg = 5;
	}
	if(_li_se(buffer, "df")){
		reg = 6;
	}
	if(_li_se(buffer, "rn")){
		reg = 16;
	}
	if(_li_se(buffer, "ei")){
		reg = 18;
	}
	if(_li_se(buffer, "pl")){
		reg = 24;
	}
	if(_li_se(buffer, "pg")){
		reg = 26;
	}
	if(_li_se(buffer, "ir")){
		reg = 27;
	}
	
	return reg;
}

Luint32 _li_getReg(Lsint32 reg){
	switch(reg){
		case 0:{
			return LIMP_CPU_getReg_EAX(Gm_cpu);
		}
		case 1:{
			return LIMP_CPU_getReg_EDX(Gm_cpu);
		}
		case 2:{
			return LIMP_CPU_getReg_ECX(Gm_cpu);
		}
		case 3:{
			return LIMP_CPU_getReg_EBX(Gm_cpu);
		}
		case 4:{
			return LIMP_CPU_getReg_EFP(Gm_cpu);
		}
		case 5:{
			return LIMP_CPU_getReg_ESP(Gm_cpu);
		}
		case 6:{
			return LIMP_CPU_getReg_ESS(Gm_cpu);
		}
		case 7:{
			return LIMP_CPU_getReg_ESD(Gm_cpu);
		}
		case 8:{
			return LIMP_CPU_getReg_AX(Gm_cpu);
		}
		case 9:{
			return LIMP_CPU_getReg_DX(Gm_cpu);
		}
		case 10:{
			return LIMP_CPU_getReg_CX(Gm_cpu);
		}
		case 11:{
			return LIMP_CPU_getReg_BX(Gm_cpu);
		}
		case 12:{
			return LIMP_CPU_getReg_FP(Gm_cpu);
		}
		case 13:{
			return LIMP_CPU_getReg_SP(Gm_cpu);
		}
		case 14:{
			return LIMP_CPU_getReg_SS(Gm_cpu);
		}
		case 15:{
			return LIMP_CPU_getReg_SD(Gm_cpu);
		}
		case 16:{
			return LIMP_CPU_getReg_AL(Gm_cpu);
		}
		case 17:{
			return LIMP_CPU_getReg_AH(Gm_cpu);
		}
		case 18:{
			return LIMP_CPU_getReg_DL(Gm_cpu);
		}
		case 19:{
			return LIMP_CPU_getReg_DH(Gm_cpu);
		}
		case 20:{
			return LIMP_CPU_getReg_CL(Gm_cpu);
		}
		case 21:{
			return LIMP_CPU_getReg_CH(Gm_cpu);
		}
		case 22:{
			return LIMP_CPU_getReg_BL(Gm_cpu);
		}
		case 23:{
			return LIMP_CPU_getReg_BH(Gm_cpu);
		}
	}
	return 0;
}

Luint32 _li_getFlag(Lsint32 flag){
	switch(flag){
		case 0:{
			return Gm_cpu->reg_st.cf;
		}
		case 1:{
			return Gm_cpu->reg_st.bf;
		}
		case 2:{
			return Gm_cpu->reg_st.vf;
		}
		case 3:{
			return Gm_cpu->reg_st.nf;
		}
		case 4:{
			return Gm_cpu->reg_st.zf;
		}
		case 5:{
			return Gm_cpu->reg_st.of;
		}
		case 6:{
			return Gm_cpu->reg_st.df;
		}
		case 16:{
			return Gm_cpu->reg_st.rn;
		}
		case 18:{
			return Gm_cpu->reg_st.ei;
		}
		case 24:{
			return Gm_cpu->reg_st.pl;
		}
		case 26:{
			return Gm_cpu->reg_st.pg;
		}
		case 27:{
			return Gm_cpu->reg_st.ir;
		}
	}
	return 0;
}

Luint32 _li_nextvalue(char** cmd){
	char buffer[256];
	_li_nextparam(cmd, buffer);
	Luint32 data = 0;
	
	if(buffer[0]=='0'){
		if(buffer[1]=='x'){
			sscanf(buffer+2, "%x", &data);
		}
		else if(buffer[1]=='f'){
			sscanf(buffer+2, "%f", &data);
		}
		else{
			sscanf(buffer, "%d", &data);
		}
	}
	else if(buffer[0]>='0'&&buffer[0]<='9'){
		sscanf(buffer, "%d", &data);
	}
	else if(_li_se(buffer, "$")){
		Lsint32 reg = _li_nextgreg(cmd);
		data = _li_getReg(reg);
	}
	else if(_li_se(buffer, "!")){
		Lsint32 flag = _li_nextflag(cmd);
		data = _li_getFlag(flag);
	}
	else if(_li_se(buffer, "&32")){
		Luint32 adr = _li_nextvalue(cmd);
		LIMP_CPU_getMem32(Gm_cpu, adr, data);
	}
	else if(_li_se(buffer, "&16")){
		Luint32 adr = _li_nextvalue(cmd);
		LIMP_CPU_getMem16(Gm_cpu, adr, data);
	}
	else if(_li_se(buffer, "&8")){
		Luint32 adr = _li_nextvalue(cmd);
		LIMP_CPU_getMem8(Gm_cpu, adr, data);
	}
	else if(_li_se(buffer, "epc")){
		data = G_cpu.reg_epc;
	}
	else if(_li_se(buffer, "fdt")){
		data = G_cpu.reg_fdt;
	}
	else if(_li_se(buffer, "t0")){
		data = _li_t0;
	}
	else if(_li_se(buffer, "t1")){
		data = _li_t1;
	}
	else if(_li_se(buffer, "t2")){
		data = _li_t2;
	}
	else if(_li_se(buffer, "t3")){
		data = _li_t3;
	}
	else if(_li_se(buffer, "float")){
		Lfloat32 dataf = _li_nextvalue(cmd);
		data = *((Luint32*)&dataf);
	}
	else if(_li_se(buffer, "int")){
		Luint32 datarf = _li_nextvalue(cmd);
		Lfloat32 dataf = *((Lfloat32*)&datarf);
		data = dataf;
	}
	else if(_li_se(buffer, "+")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1+opr2;
	}
	else if(_li_se(buffer, "-")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1-opr2;
	}
	else if(_li_se(buffer, "*")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1*opr2;
	}
	else if(_li_se(buffer, "/")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1/opr2;
	}
	else if(_li_se(buffer, "%")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1%opr2;
	}
	else if(_li_se(buffer, "&")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1&opr2;
	}
	else if(_li_se(buffer, "|")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1|opr2;
	}
	else if(_li_se(buffer, "^")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1^opr2;
	}
	else if(_li_se(buffer, ">")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1>>opr2;
	}
	else if(_li_se(buffer, "<")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1<<opr2;
	}
	else if(_li_se(buffer, "~")){
		Luint32 opr = _li_nextvalue(cmd);
		data = ~opr;
	}
	else if(_li_se(buffer, "equal")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1==opr2;
	}
	else if(_li_se(buffer, "nequal")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1!=opr2;
	}
	else if(_li_se(buffer, "less")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1<opr2;
	}
	else if(_li_se(buffer, "greater")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1>opr2;
	}
	else if(_li_se(buffer, "lequal")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1<=opr2;
	}
	else if(_li_se(buffer, "gequal")){
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = opr1>=opr2;
	}
	else if(_li_se(buffer, "not")){
		Luint32 opr = _li_nextvalue(cmd);
		data = !opr;
	}
	else if(_li_se(buffer, "?")){
		Luint32 test = _li_nextvalue(cmd);
		Luint32 opr1 = _li_nextvalue(cmd);
		Luint32 opr2 = _li_nextvalue(cmd);
		data = test?opr1:opr2;
	}
	else if(_li_se(buffer, "dro")){
		Luint32 opc = _li_nextvalue(cmd);
		Luint32 opr = _li_nextvalue(cmd);
		Luint32 rsd = _li_nextvalue(cmd);
		Luint32 regd = _li_nextvalue(cmd);
		Luint32 extra = _li_nextvalue(cmd);
		data = LI_DRO_create(opc, opr, rsd, regd, extra);
	}
	else if(_li_se(buffer, "uro")){
		Luint32 opc = _li_nextvalue(cmd);
		Luint32 regs = _li_nextvalue(cmd);
		Luint32 regd = _li_nextvalue(cmd);
		Luint32 extra = _li_nextvalue(cmd);
		data = LI_URO_create(opc, regs, regd, extra);
	}
	else if(_li_se(buffer, "ido")){
		Luint32 opc = _li_nextvalue(cmd);
		Luint32 extra = _li_nextvalue(cmd);
		data = LI_IDO_create(opc, extra);
	}
	else if(_li_se(buffer, "ifo")){
		Luint32 opc = _li_nextvalue(cmd);
		Luint32 func = _li_nextvalue(cmd);
		Luint32 extra = _li_nextvalue(cmd);
		data = LI_IFO_create(opc, func, extra);
	}
	else if(_li_se(buffer, "dfr")){
		Luint32 opc = _li_nextvalue(cmd);
		Luint32 tm = _li_nextvalue(cmd);
		Luint32 regs = _li_nextvalue(cmd);
		Luint32 regd = _li_nextvalue(cmd);
		Luint32 extra = _li_nextvalue(cmd);
		data = LI_DFR_create(opc, tm, regs, regd, extra);
	}
	else if(_li_se(buffer, "fro")){
		Luint32 opc = _li_nextvalue(cmd);
		Luint32 func = _li_nextvalue(cmd);
		Luint32 regd = _li_nextvalue(cmd);
		Luint32 regs = _li_nextvalue(cmd);
		Luint32 extra = _li_nextvalue(cmd);
		data = LI_FRO_create(opc, func, regd, regs, extra);
	}
	else if(_li_se(buffer, "fur")){
		Luint32 opc = _li_nextvalue(cmd);
		Luint32 func = _li_nextvalue(cmd);
		Luint32 rego = _li_nextvalue(cmd);
		Luint32 extra = _li_nextvalue(cmd);
		data = LI_FUR_create(opc, func, rego, extra);
	}
	else if(_li_se(buffer, "mio")){
		Luint32 opc = _li_nextvalue(cmd);
		Luint32 adm = _li_nextvalue(cmd);
		Luint32 regb = _li_nextvalue(cmd);
		Luint32 rego = _li_nextvalue(cmd);
		Luint32 regi = _li_nextvalue(cmd);
		Luint32 sc = _li_nextvalue(cmd);
		Luint32 extra = _li_nextvalue(cmd);
		data = LI_MIO_create(opc, adm, regb, rego, regi, sc, extra);
	}
	
	return data;
}

Luint32 _li_setReg(Lsint32 reg, Luint32 data){
	switch(reg){
		case 0:{
			LIMP_CPU_setReg_EAX(Gm_cpu, data);
			return 0;
		}
		case 1:{
			LIMP_CPU_setReg_EDX(Gm_cpu, data);
			return 0;
		}
		case 2:{
			LIMP_CPU_setReg_ECX(Gm_cpu, data);
			return 0;
		}
		case 3:{
			LIMP_CPU_setReg_EBX(Gm_cpu, data);
			return 0;
		}
		case 4:{
			LIMP_CPU_setReg_EFP(Gm_cpu, data);
			return 0;
		}
		case 5:{
			LIMP_CPU_setReg_ESP(Gm_cpu, data);
			return 0;
		}
		case 6:{
			LIMP_CPU_setReg_ESS(Gm_cpu, data);
			return 0;
		}
		case 7:{
			LIMP_CPU_setReg_ESD(Gm_cpu, data);
			return 0;
		}
		case 8:{
			LIMP_CPU_setReg_AX(Gm_cpu, data);
			return 0;
		}
		case 9:{
			LIMP_CPU_setReg_DX(Gm_cpu, data);
			return 0;
		}
		case 10:{
			LIMP_CPU_setReg_CX(Gm_cpu, data);
			return 0;
		}
		case 11:{
			LIMP_CPU_setReg_BX(Gm_cpu, data);
			return 0;
		}
		case 12:{
			LIMP_CPU_setReg_FP(Gm_cpu, data);
			return 0;
		}
		case 13:{
			LIMP_CPU_setReg_SP(Gm_cpu, data);
			return 0;
		}
		case 14:{
			LIMP_CPU_setReg_SS(Gm_cpu, data);
			return 0;
		}
		case 15:{
			LIMP_CPU_setReg_SD(Gm_cpu, data);
			return 0;
		}
		case 16:{
			LIMP_CPU_setReg_AL(Gm_cpu, data);
			return 0;
		}
		case 17:{
			LIMP_CPU_setReg_AH(Gm_cpu, data);
			return 0;
		}
		case 18:{
			LIMP_CPU_setReg_DL(Gm_cpu, data);
			return 0;
		}
		case 19:{
			LIMP_CPU_setReg_DH(Gm_cpu, data);
			return 0;
		}
		case 20:{
			LIMP_CPU_setReg_CL(Gm_cpu, data);
			return 0;
		}
		case 21:{
			LIMP_CPU_setReg_CH(Gm_cpu, data);
			return 0;
		}
		case 22:{
			LIMP_CPU_setReg_BL(Gm_cpu, data);
			return 0;
		}
		case 23:{
			LIMP_CPU_setReg_BH(Gm_cpu, data);
			return 0;
		}
	}
	return -1;
}

Luint32 _li_setFlag(Lsint32 flag, Luint32 data){
	switch(flag){
		case 0:{
			Gm_cpu->reg_st.cf = data;
			return 0;
		}
		case 1:{
			Gm_cpu->reg_st.bf = data;
			return 0;
		}
		case 2:{
			Gm_cpu->reg_st.vf = data;
			return 0;
		}
		case 3:{
			Gm_cpu->reg_st.nf = data;
			return 0;
		}
		case 4:{
			Gm_cpu->reg_st.zf = data;
			return 0;
		}
		case 5:{
			Gm_cpu->reg_st.of = data;
			return 0;
		}
		case 6:{
			Gm_cpu->reg_st.df = data;
			return 0;
		}
		case 16:{
			Gm_cpu->reg_st.rn = data;
			return 0;
		}
		case 18:{
			Gm_cpu->reg_st.ei = data;
			return 0;
		}
		case 24:{
			Gm_cpu->reg_st.pl = data;
			return 0;
		}
		case 26:{
			Gm_cpu->reg_st.pg = data;
			return 0;
		}
		case 27:{
			Gm_cpu->reg_st.ir = data;
			return 0;
		}
	}
	return -1;
}

Luint32 _li_cmd_setReg(char** cmd){
	Lsint32 reg = _li_nextgreg(cmd);
	
	if(reg!=-1){
		Luint32 data = _li_nextvalue(cmd);
		return _li_setReg(reg, data);
	}
	
	return -1;
}

Luint32 _li_cmd_setFlag(char** cmd){
	Lsint32 flag = _li_nextflag(cmd);
	
	if(flag!=-1){
		Luint32 data = _li_nextvalue(cmd);
		
		return _li_setFlag(flag, data);
	}
	
	return -1;
}

Luint32 _li_cmd_setBus(char** cmd, Luint8 mode){
	
	{
		Luint32 adr = _li_nextvalue(cmd);
		Luint32 data = _li_nextvalue(cmd);
		
		_li_ladr = adr;
		
		if(mode==1){
			LIMP_CPU_set_bus16(Gm_cpu, adr, data);
		}
		else if(mode==1){
			LIMP_CPU_set_bus8(Gm_cpu, adr, data);
		}
		else{
			LIMP_CPU_set_bus32(Gm_cpu, adr, data);
		}
		
		return 0;
	}
	
	return -1;
}

Luint32 _li_cmd_setMem(char** cmd, Luint8 mode){
	
	{
		Luint32 adr = _li_nextvalue(cmd);
		Luint32 data = _li_nextvalue(cmd);
		
		_li_ladr = adr;
		
		if(mode==1){
			LIMP_CPU_setMem16(Gm_cpu, adr, data);
		}
		else if(mode==1){
			LIMP_CPU_setMem8(Gm_cpu, adr, data);
		}
		else{
			LIMP_CPU_setMem32(Gm_cpu, adr, data);
		}
		
		return 0;
	}
	
	return -1;
}

Luint32 _li_cmd_set(char** cmd, Luint32 (*set_cmd_func)(char**, Luint8 mode)){
	char buffer[256];
	_li_nextparam(cmd, buffer);
	
	if(_li_se(buffer, "16")){
		return set_cmd_func(cmd, 1);
	}
	else if(_li_se(buffer, "8")){
		return set_cmd_func(cmd, 2);
	}
	else{
		return set_cmd_func(cmd, 0);
	}
	
	return -1;
}

Luint32 li_execute(char* cmd);

Luint32 _li_execute(char* *cmd){
	char buffer[256];
	_li_nextparam(cmd, buffer);
	
	if(buffer[0]==0){
		return 0;
	}
	
	if(_li_se(buffer, "setreg")){
		_li_cmd_setReg(cmd);
		if(_li_feedback){
			LIMP_CPU_log(Gm_cpu);
		}
		return 0;
	}
	else if(_li_se(buffer, "setflag")){
		_li_cmd_setFlag(cmd);
		if(_li_feedback){
			LIMP_CPU_log(Gm_cpu);
		}
		return 0;
	}
	else if(_li_se(buffer, "setbus")){
		_li_cmd_set(cmd, &_li_cmd_setBus);
		if(_li_feedback){
			LIMP_CPU_busLog(Gm_cpu, _li_ladr&(~0xf));
		}
		return 0;
	}
	else if(_li_se(buffer, "setmem")){
		_li_cmd_set(cmd, &_li_cmd_setMem);
		if(_li_feedback){
			LIMP_CPU_memLog(Gm_cpu, _li_ladr&(~0xf));
		}
		return 0;
	}
	else if(_li_se(buffer, "jmpabs")){
		Luint32 data = _li_nextvalue(cmd);
		G_cpu.reg_epc = data;
		if(_li_feedback){
			LIMP_CPU_log(Gm_cpu);
		}
		return 0;
	}
	else if(_li_se(buffer, "jmprel")){
		Luint32 data = _li_nextvalue(cmd);
		G_cpu.reg_epc += data;
		if(_li_feedback){
			LIMP_CPU_log(Gm_cpu);
		}
		return 0;
	}
	else if(_li_se(buffer, "fetch")){
		LIMP_CPU_fetch(Gm_cpu);
		if(_li_feedback){
			LIMP_CPU_log(Gm_cpu);
		}
		return 0;
	}
	else if(_li_se(buffer, "do")){
		LI_ISA(Gm_cpu);
		if(_li_feedback){
			LIMP_CPU_log(Gm_cpu);
		}
		return 0;
	}
	else if(_li_se(buffer, "fdo")){
		LIMP_CPU_fetch(Gm_cpu);
		LI_ISA(Gm_cpu);
		if(_li_feedback){
			LIMP_CPU_log(Gm_cpu);
		}
		return 0;
	}
	else if(_li_se(buffer, "feedback")){
		_li_nextparam(cmd, buffer);
		
		if(_li_se(buffer, "enabled")||_li_se(buffer, "1")){
			_li_feedback = TRUE;
		}
		else if(_li_se(buffer, "disabled")||_li_se(buffer, "0")){
			_li_feedback = FALSE;
		}
		else if(_li_se(buffer, "toggle")||_li_se(buffer, "")){
			_li_feedback = !_li_feedback;
		}
		else{
			return -1;
		}
		
		printf("Status: %s", _li_feedback?"activated":"deactivated");
		
		return 0;
	}
	else if(_li_se(buffer, "show")){
		LIMP_CPU_log(Gm_cpu);
		return 0;
	}
	else if(_li_se(buffer, "showbus")){
		Luint32 offset = _li_nextvalue(cmd);
		LIMP_CPU_busLog(Gm_cpu, offset);
		return 0;
	}
	else if(_li_se(buffer, "showmem")){
		Luint32 offset = _li_nextvalue(cmd);
		LIMP_CPU_memLog(Gm_cpu, offset);
		return 0;
	}
	else if(_li_se(buffer, "exit")){
		_li_running = FALSE;
		return 0;
	}
	else if(_li_se(buffer, "reset")){
		LIMP_CPU_init(Gm_cpu);
		if(_li_feedback){
			LIMP_CPU_log(Gm_cpu);
		}
		return 0;
	}
	else if(_li_se(buffer, "cmd")){
		system(*cmd);
		return 0;
	}
	else if(_li_se(buffer, "t0")){
		_li_t0 = _li_nextvalue(cmd);
		if(_li_feedback){
			printf("%d\n", _li_t0);
		}
		return 0;
	}
	else if(_li_se(buffer, "t1")){
		_li_t1 = _li_nextvalue(cmd);
		if(_li_feedback){
			printf("%d\n", _li_t1);
		}
		return 0;
	}
	else if(_li_se(buffer, "t2")){
		_li_t2 = _li_nextvalue(cmd);
		if(_li_feedback){
			printf("%d\n", _li_t2);
		}
		return 0;
	}
	else if(_li_se(buffer, "t3")){
		_li_t3 = _li_nextvalue(cmd);
		if(_li_feedback){
			printf("%d\n", _li_t3);
		}
		return 0;
	}
	else if(_li_se(buffer, "bin")){
		Luint32 data = _li_nextvalue(cmd);
		printf("%d\n", data);
		return 0;
	}
	else if(_li_se(buffer, "dec")){
		Luint32 data = _li_nextvalue(cmd);
		printf("%d\n", data);
		return 0;
	}
	else if(_li_se(buffer, "hex")){
		Luint32 data = _li_nextvalue(cmd);
		printf("0x%x\n", data);
		return 0;
	}
	else if(_li_se(buffer, "dump")){
		_li_nextparam(cmd, buffer);
		Luint8 mode = 0;
		
		/* Dump mode */
		if(_li_se(buffer, "mem")){
			mode = 0;
		}
		else if(_li_se(buffer, "bus")){
			mode = 1;
		}
		
		/* Offset */
		Luint32 offset = _li_nextvalue(cmd);
		
		/* Size */
		Luint32 size = _li_nextvalue(cmd);
		
		/* Out file */
		char pathname[256];
		_li_nextparam(cmd, pathname);
		
		FILE *outfile;
		
		if((outfile=_li_createFile(pathname))){
			for(int i=0; i<size; i++){
				if(mode==0){
					Luint8 data;
					LIMP_CPU_getMem8(Gm_cpu, offset+i, data);
					_li_appendFile(outfile, data);
				}
				else if(mode==1){
					_li_appendFile(outfile, LIMP_CPU_get_bus8(Gm_cpu, offset+i));
				}
			}
		}
		fclose(outfile);
	}
	else if(_li_se(buffer, "import")){
		_li_nextparam(cmd, buffer);
		char script[1024];
		int script_i = 0;
		int consumed = 0;
		FILE *infile;
		
		if(!(infile=_li_openFile(buffer))){
			printf("File not found!");
			return 0;
		}
		
		fseek(infile, 0, SEEK_END);
		int size = ftell(infile);
		fseek(infile, 0, SEEK_SET);
		
		char chr;
		do{
			chr = fgetc(infile);
			script[script_i] = chr;
			// printf("%d of %d char: '%c'\n", (script_i+consumed), size, chr);
			
			script_i++;
			if((chr=='\n')||(chr==0)||(chr==EOF)||((script_i+consumed)>=size)){
				consumed += script_i;
				script[script_i] = 0;
				// printf("Executing: %s\n", script);
				li_execute(script);
				script_i = 0;
			}
			
		}while((chr!=EOF)&&(chr!=0)&&((script_i+consumed)<size));
		
		return 0;
	}
	else if(_li_se(buffer, "repeat")){
		Luint32 times = _li_nextvalue(cmd);
		for(Luint32 ti=1; ti<times; ti++){
			char* src_exec = *cmd;
			li_execute(src_exec);
		}
		return 0;
	}
	else if(_li_se(buffer, "help")){
		printf("\n COMMANDS HELP:\n\n\
\tsetreg [regname] [value]\n\
\tsetbus [sizedata: 8, 16 or 32] [address] [data]\n\
\tsetmem [sizedata: 8, 16 or 32] [address] [data]\n\
\tjmpabs [value]\n\
\tjmprel [value]\n\
\tfetch\n\
\tdo\n\
\tfdo\n\
\tfeedback [setstate: enabled/1, disabled/0 or toggle]\n\
\tshow\n\
\tshowbus [offset]\n\
\tshowmem [offset]\n\
\texit\n\
\treset\n\
\ttemp[0-3] [value]\n\
\tcmd [systemcmd]\n\
\tbin [value]\n\
\tdec [value]\n\
\thex [value]\n\
\tdump [what: mem or bus] [offset] [length] [outfilepath]\n\
\trepeat [times] [scripts]\n\n");

		return 0;
	}
	
	return -1;
}

Luint32 li_execute(char* cmd){
	if(!_li_running){
		return 0;
	}
	while(*cmd){
		if(_li_execute(&cmd)){
			//printf("Unknown command\n");
		}
	}
}


#endif