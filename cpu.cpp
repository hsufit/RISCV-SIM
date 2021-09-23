#include "cpu.h"

CPU::CPU(sc_module_name name) : sc_module(name)
{
	SC_HAS_PROCESS(CPU);
	SC_THREAD(hello_thread);
}

void CPU::hello_thread(void)
{
	for(int i = 0; i < 30; i++) {
		step();
		wait(delay);
	}
}

void CPU::step()
{
	char data = address_space->read(pc, 1);
	std::cout << "time " << sc_core::sc_time_stamp() << ":" << "hello received!!" << data << std::endl;
	pc++;
}

void CPU::set_register_file(const std::shared_ptr<REGISTER_INTERFACE> &instance)
{
	register_file = instance;
}

void CPU::set_address_space(const std::shared_ptr<ADDRESS_SPACE_INTERFACE> &instance)
{
	address_space = instance;
}

void CPU::set_instruction_decoder(const std::shared_ptr<INSTRUCTION_DECODER_INTERFACE> &instance)
{
	instruction_decoder = instance;
}

