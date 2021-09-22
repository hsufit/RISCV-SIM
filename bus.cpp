#include "bus.h"


BUS::BUS(sc_module_name name): sc_module(name), memory("memory")
{
	this->memory_socket.bind(memory.memory_socket);
}

int32_t BUS::read(uint32_t addr, uint32_t size)
{
	return 0;
}

void BUS::write(uint32_t addr, uint32_t data, uint32_t size) {}




