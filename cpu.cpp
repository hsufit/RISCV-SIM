#include "cpu.h"

CPU::CPU(sc_module_name name) : sc_module(name){ 
	SC_HAS_PROCESS(CPU);
	SC_THREAD(hello_thread);
}

void CPU::hello_thread(void)
{
	for(int i = 0; i < 30; i++)
	{
		step();
		wait(delay);
	}
}

void CPU::step()
{
	char data;
	sc_dt::uint64 addr = pc;
	int size = 1;
	tlm::tlm_generic_payload trans;
	trans.set_command(tlm::TLM_READ_COMMAND);
	trans.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
	trans.set_data_length(size);
	trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
	trans.set_address(addr);
	sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
		memory_socket->b_transport(trans, delay);
	std::cout << "time " << sc_core::sc_time_stamp() << ":" << "hello received!!" << data << std::endl;
		pc++;
}
