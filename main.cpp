#include "systemc.h"

#include "cpu.h"
#include "memory.h"
#include "register.h"

int sc_main(int argc,char** argv)
{

	MEMORY memory("moon");
	
	CPU cpu("cpu");
	auto qqq =  std::make_shared<REGISTER>();
	cpu.set_register_file(qqq);
	cpu.memory_socket.bind(memory.memory_socket);
	sc_core::sc_start();
	return 0;
}




