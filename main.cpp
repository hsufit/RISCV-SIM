#include "systemc.h"

#include "cpu.h"
#include "memory.h"

int sc_main(int argc,char** argv){
	
        CPU cpu("cpu");
	MEMORY memory("moon");
	cpu.memory_socket.bind(memory.memory_socket);
	sc_core::sc_start();
        return 0;
}




