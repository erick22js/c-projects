
#include "bus.h"


Uint8 _I486Bus_get8_null(I486Bus *l_bus, Uint32 adr){
    return 0;
}
void _I486Bus_set8_null(I486Bus *l_bus, Uint32 adr, Uint8 data){
    
}
Uint16 _I486Bus_get16_null(I486Bus *l_bus, Uint32 adr){
    return 0;
}
void _I486Bus_set16_null(I486Bus *l_bus, Uint32 adr, Uint16 data){
    
}
Uint32 _I486Bus_get32_null(I486Bus *l_bus, Uint32 adr){
    return 0;
}
void _I486Bus_set32_null(I486Bus *l_bus, Uint32 adr, Uint32 data){
    
}

I486Bus *I486Bus_create(){
    I486Bus *l_bus = (I486Bus*)malloc(sizeof(I486Bus));
    l_bus->get8 = &_I486Bus_get8_null;
    l_bus->set8 = &_I486Bus_set8_null;
    l_bus->get16 = &_I486Bus_get16_null;
    l_bus->set16 = &_I486Bus_set16_null;
    l_bus->get32 = &_I486Bus_get32_null;
    l_bus->set32 = &_I486Bus_set32_null;
    return l_bus;
}

void I486Bus_destroy(I486Bus *l_bus){
    free((void*)l_bus);
}
