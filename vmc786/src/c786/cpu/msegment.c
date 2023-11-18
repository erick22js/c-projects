
#include "msegment.h"


Uint32 _C786MSeg_adr_logical2Linear(C786Cpu *l_cpu, Uint32 logical_adr, Uint16 selector){
    Uint32 linear_selector = 0;
    
    if(selector&4){
        _C786MSeg_accessSegment(l_cpu, selector&(~7), _C786Cpu_reg_ldtr(l_cpu), linear_selector);
    }
    else{
        _C786MSeg_accessSegment(cpu, selector&(~7), _C786Cpu_reg_gdtr(cpu), linear_selector);
    }
    _C786MSeg_accessSegment(cpu, selector&(~7), _C786Cpu_reg_ldtr(cpu), linear_selector);
    
    Uint32 linear_adr = 0;
    Uint32 segd_l = _C786Cpu_getBus32(cpu, linear_seletor, linear_adr);
    Uint32 segd_h = _C786Cpu_getBus32(cpu, linear_seletor+4, linear_adr);
    
    C786Segd descriptor;
    _C786Seg_decode2segd(segd_l, segd_h, descriptor);
    
    //_C786MSeg_accessSegment(cpu)
    
    return linear_adr;
}

