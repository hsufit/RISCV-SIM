#include <iostream>

#include "executor.h"

void EXECUTOR::execute()
{
	if(instruction_decoder->get_opcode() == INSTRUCTION_DECODER_INTERFACE::OP_IMM &&
	   instruction_decoder->get_func3() == 0b000) {
		auto rs1 = instruction_decoder->get_rs1();
		auto rd = instruction_decoder->get_rd();

		auto value = register_file->get_value_integer(rs1) + instruction_decoder->get_imm(31, 20);
		register_file->set_value_integer(rd, value);
		//TODO: just for test, move these to decoder and logger in future
		std::cout << "ADDI" << std::endl;
		std::cout << "rs1: " << rs1 << std::endl;
		std::cout << "rd: " << rd << std::endl;
		std::cout << "value: " << value << std::endl;
	}
}
