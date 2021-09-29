#include "cpu.h"

CPU::CPU(sc_module_name name) : sc_module(name)
{
	SC_HAS_PROCESS(CPU);
	SC_THREAD(hello_thread);
}

void CPU::hello_thread(void)
{
	for(int i = 0; i < 12; i++) {
		step();
		wait(delay);
	}
}

void CPU::step()
{
	uint32_t instruction = address_space->read(register_file->get_pc(), 4);

	instruction_decoder->set_instruction(instruction);
	executor->execute();
}

void CPU::set_register_file(const std::shared_ptr<REGISTER_INTERFACE> &instance)
{
	register_file = instance;
	if(executor != nullptr) {
		executor->set_register_file(register_file);
	}
}

void CPU::set_address_space(const std::shared_ptr<ADDRESS_SPACE_INTERFACE> &instance)
{
	address_space = instance;
	if(executor != nullptr) {
		executor->set_address_space(address_space);
	}
}

void CPU::set_instruction_decoder(const std::shared_ptr<INSTRUCTION_DECODER_INTERFACE> &instance)
{
	instruction_decoder = instance;
	if(executor != nullptr) {
		executor->set_instruction_decoder(instruction_decoder);
	}
}

void CPU::set_executor(const std::shared_ptr<EXECUTOR_INTERFACE> &instance)
{
	executor = instance;
	if(instruction_decoder != nullptr) {
		executor->set_instruction_decoder(instruction_decoder);
	}

	if(register_file != nullptr) {
		executor->set_register_file(register_file);
	}

	if(address_space != nullptr) {
		executor->set_address_space(address_space);
	}

}
