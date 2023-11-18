
#include "bus.h"


Uint8 _C786Bus_get8_null(C786Bus *l_bus, Uint32 adr){
    return 0;
}
void _C786Bus_set8_null(C786Bus *l_bus, Uint32 adr, Uint8 data){
    
}
Uint16 _C786Bus_get16_null(C786Bus *l_bus, Uint32 adr){
    return 0;
}
void _C786Bus_set16_null(C786Bus *l_bus, Uint32 adr, Uint16 data){
    
}
Uint32 _C786Bus_get32_null(C786Bus *l_bus, Uint32 adr){
    return 0;
}
void _C786Bus_set32_null(C786Bus *l_bus, Uint32 adr, Uint32 data){
    
}

C786Bus *C786Bus_create(){
    C786Bus *l_bus = (C786Bus*)malloc(sizeof(C786Bus));
    l_bus->get8 = &_C786Bus_get8_null;
    l_bus->set8 = &_C786Bus_set8_null;
    l_bus->get16 = &_C786Bus_get16_null;
    l_bus->set16 = &_C786Bus_set16_null;
    l_bus->get32 = &_C786Bus_get32_null;
    l_bus->set32 = &_C786Bus_set32_null;
    return l_bus;
}

void C786Bus_destroy(C786Bus *l_bus){
    free((void*)l_bus);
}
