#include "systemc.h"

#include "cpu.h"
#include "memory.h"

int sc_main(int argc,char** argv){
	
        HELLO hello("hello");
	MOON moon("moon");
	hello.moon_access_socket.bind(moon.moon_access_socket);
	sc_core::sc_start();
        return 0;
}




