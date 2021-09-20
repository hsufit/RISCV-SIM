#include "memory.h"

MEMORY::MEMORY(sc_module_name name) : sc_module(name){
	memory_socket.register_b_transport(this, &MEMORY::b_transport);
}

void MEMORY::b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay){
	delay = sc_core::SC_ZERO_TIME;
	tlm::tlm_command cmd = trans.get_command();
	sc_dt::uint64 adr = trans.get_address();
	unsigned char *ptr = trans.get_data_ptr();
	unsigned int len = trans.get_data_length();
		if(adr < dataMemory.size())
	{
		*(char*)ptr = dataMemory[adr];
		std::cout << "time " << sc_core::sc_time_stamp() << ":" << "moon response!!" << dataMemory[adr] << std::endl;
		trans.set_response_status(tlm::TLM_OK_RESPONSE);
	}
	else
	{
		trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
		std::cout << "error an address " << adr << "!!" << std::endl;
	}
}
