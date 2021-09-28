#include "cpu.h"

CPU::CPU(sc_module_name name) : sc_module(name)
{
	SC_HAS_PROCESS(CPU);
	SC_THREAD(hello_thread);
}

void CPU::hello_thread(void)
{
	for(int i = 0; i < 10; i++) {
		step();
		wait(delay);
	}
}

void CPU::step()
{

//       char data = address_space->read(pc, 1);
//       std::cout << "time " << sc_core::sc_time_stamp() << ":" << "hello received!!" << data << std::endl;
//       TODO:fake instructions, move to memory
	auto fakeInstructionMemory = std::array<uint32_t, 10> {
		0b000000000001'00000'000'00001'0010011, //ADDI x1 = x0 + 1
		0b111111111111'00001'000'00010'0010011, //ADDI x2 = x1 + (-1)
		0b000000000000'00000'000'00000'0010011, //NOP
		0b100000000000'00001'010'00000'0010011, //SLTI x1 = x0 < negativeNum
		0b100000000000'00010'011'00010'0010011, //SLTU x2 = x0 < PositiveNum
		0b0000000'11111'00010'001'00011'0010011, //SLLI x3 = x2 << 31
		0b0000000'00001'00011'101'00100'0010011, //SRLI x4 = x2 >> 1
		0b0100000'00001'00011'101'00101'0010011, //SRAI x5 = x2 >> 1
		0b00000000000000000001'00110'0110111, //LUI x6 = 1 << 12
		0b00000000000000000001'00110'0010111, //AUIPC x6 = pc + (1 << 12)
	};

	instruction_decoder->set_instruction(fakeInstructionMemory[register_file->get_pc() / 4]);
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
