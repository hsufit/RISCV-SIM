#include "systemc.h"

#include "cpu.h"
#include "memory.h"
#include "register.h"
#include "bus.h"

int sc_main(int argc,char** argv)
{

	MEMORY memory("moon");

	CPU cpu("cpu");
	cpu.set_register_file(std::make_shared<REGISTER>());
	cpu.set_address_space(std::make_shared<BUS>("bus"));
	cpu.memory_socket.bind(memory.memory_socket);
	sc_core::sc_start();
	return 0;
}




