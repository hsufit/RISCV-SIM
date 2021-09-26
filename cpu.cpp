#include "cpu.h"

CPU::CPU(sc_module_name name) : sc_module(name)
{
	SC_HAS_PROCESS(CPU);
	SC_THREAD(hello_thread);
}

void CPU::hello_thread(void)
{
	for(int i = 0; i < 5; i++) {
		step();
		wait(delay);
	}
}

void CPU::step()
{
//       char data = address_space->read(pc, 1);
//       std::cout << "time " << sc_core::sc_time_stamp() << ":" << "hello received!!" << data << std::endl;
//       TODO:fake instructions, move to memory
	auto fakeInstructionMemory = std::array<uint32_t, 5> {
		0b000000000001'00000'000'00001'0010011,
		0b111111111111'00001'000'00010'0010011,
		0b000000000000'00000'000'00000'0010011,
		0b100000000000'00000'010'00000'0010011,
		0b100000000000'00000'011'00000'0010011,
	};

	instruction_decoder->set_instruction(fakeInstructionMemory[pc]);
	executor->execute();
	pc++;
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

}
