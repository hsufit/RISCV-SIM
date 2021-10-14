#include "bus.h"

BUS::BUS(sc_module_name name): sc_module(name), memory("memory")
{
	this->memory_socket.bind(memory.memory_socket);
}

int32_t BUS::read(uint32_t addr, uint32_t size)
{
	uint32_t data = 0;
	tlm::tlm_generic_payload trans;
	trans.set_command(tlm::TLM_READ_COMMAND);
	trans.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
	trans.set_data_length(size);
	trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
	trans.set_address(addr);
	sc_core::sc_time delay = sc_core::SC_ZERO_TIME;

	memory_socket->b_transport(trans, delay);
	return data;
}

void BUS::write(uint32_t addr, uint32_t data, uint32_t size)

{
	tlm::tlm_generic_payload trans;
	trans.set_command(tlm::TLM_WRITE_COMMAND);
	trans.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
	trans.set_data_length(size);
	trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
	trans.set_address(addr);
	sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
	switch (addr) {
		case CONSOLE_BASE:
			std::cout << "console: \'" << *reinterpret_cast<unsigned char*>(&data) << "\'" << std::endl;
			break;
		default:
			memory_socket->b_transport(trans, delay);
			break;
	}
}




